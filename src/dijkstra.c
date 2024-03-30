#include "../include/dijkstra.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

DijkstraResult *dijkstra(const Graph *graph, int src, int k) {
    // Código para a implementação simplificada do algoritmo de Dijkstra
    // Esta implementação não encontra k caminhos, mas pode ser um ponto de partida

    // Inicialização do resultado do Dijkstra
    DijkstraResult *result = (DijkstraResult *)malloc(sizeof(DijkstraResult));
    result->numPaths = graph->numVertices;
    result->paths = (Path *)malloc(graph->numVertices * sizeof(Path));

    // Inicializar todos os custos para infinito e os caminhos para NULL
    for (int i = 0; i < graph->numVertices; i++) {
        result->paths[i].cost = INT_MAX;
        result->paths[i].path = (int *)malloc(graph->numVertices * sizeof(int));
        result->paths[i].length = 0;
    }

    // O custo do caminho da origem para ele mesmo é sempre 0
    result->paths[src].cost = 0;
    result->paths[src].path[0] = src;
    result->paths[src].length = 1;

    // Array para manter o controle dos vértices para os quais o menor custo já foi encontrado
    int *minPathFound = (int *)calloc(graph->numVertices, sizeof(int));

    // Estrutura de heap mínimo para escolher o vértice com o menor custo de caminho
    MinHeap *heap = createMinHeap(graph->numVertices);
    for (int i = 0; i < graph->numVertices; i++) {
        if (i != src) {
            insertMinHeap(heap, i, INT_MAX);
        } else {
            insertMinHeap(heap, i, 0); // A distância da origem para ela mesma é zero
        }
    }

    // Algoritmo de Dijkstra
    while (!isMinHeapEmpty(heap)) {
        // Extrai o vértice com o menor custo de caminho
        HeapNode currentNode = extractMin(heap);
        int u = currentNode.vertex;
        minPathFound[u] = 1;

        // Atualiza o custo para todos os vértices adjacentes a u
        Edge *adjList = graph->vertices[u].head;
        while (adjList != NULL) {
            int v = adjList->dest;
            if (!minPathFound[v] && result->paths[u].cost != INT_MAX &&
                result->paths[u].cost + adjList->weight < result->paths[v].cost) {
                // Encontrou um caminho mais curto para o vértice adjacente
                result->paths[v].cost = result->paths[u].cost + adjList->weight;
                
                // Copiar o caminho de u e adicionar v
                memcpy(result->paths[v].path, result->paths[u].path, result->paths[u].length * sizeof(int));
                result->paths[v].length = result->paths[u].length;
                result->paths[v].path[result->paths[v].length++] = v;

                // Atualiza a distância no heap
                decreaseKey(heap, v, result->paths[v].cost);
            }
            adjList = adjList->next;
        }
    }

    free(minPathFound);
    freeMinHeap(heap);
    return result;
}

void freeDijkstraResult(DijkstraResult *result) {
    if (result) {
        for (int i = 0; i < result->capacity; ++i) {
            free(result->paths[i].path);
        }
        free(result->paths);
        free(result);
    }
}

void printDijkstraResult(const DijkstraResult *result) {
    for (int i = 0; i < result->numPaths; ++i) {
        printf("Path %d, cost: %d, vertices: ", i + 1, result->paths[i].cost);
        for (int j = 0; j < result->paths[i].length; ++j) {
            printf("%d ", result->paths[i].path[j]);
        }
        printf("\n");
    }
}