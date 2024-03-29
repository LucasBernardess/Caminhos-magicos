#include "../include/dijkstra].h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Uma função auxiliar para inicializar as distâncias e o heap
MinHeap* dijkstraInitialize(Graph *graph, int src, int *distances) {
    MinHeap* minHeap = createMinHeap(graph->numVertices);

    for (int v = 0; v < graph->numVertices; ++v) {
        distances[v] = INT_MAX;
        minHeap->array[v] = (HeapNode*)malloc(sizeof(HeapNode));
        minHeap->array[v]->vertex = v;
        minHeap->array[v]->cost = distances[v];
        minHeap->pos[v] = v;
    }

    // A distância do vértice de origem para ele mesmo é sempre 0
    distances[src] = 0;
    decreaseKey(minHeap, src, distances[src]);

    minHeap->size = graph->numVertices;

    return minHeap;
}

void findKShortestPaths(Graph *graph, int startVertex, int endVertex, int k, const char *outputFile) {
    int *distances = (int*) malloc(graph->numVertices * sizeof(int));
    MinHeap* minHeap = dijkstraInitialize(graph, startVertex, distances);

    while (!isEmpty(minHeap)) {
        HeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->vertex;

        // Itera através de todos os vértices adjacentes de u
        Edge* pCrawl = graph->adjLists[u];
        while (pCrawl != NULL) {
            int v = pCrawl->dest;

            // Atualiza as distâncias se necessário
            if (isInMinHeap(minHeap, v) && distances[u] != INT_MAX &&
                pCrawl->cost + distances[u] < distances[v]) {
                distances[v] = distances[u] + pCrawl->cost;
                decreaseKey(minHeap, v, distances[v]);
            }
            pCrawl = pCrawl->next;
        }
        // Não chame free(minHeapNode) aqui, pois minHeapNode aponta para um item dentro do array do heap
    }

    // Escreve os resultados no arquivo de saída
    FILE *file = fopen(outputFile, "w");
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo de saída.\n");
        free(distances);
        freeMinHeap(minHeap);
        return;
    }
    fprintf(file, "%d\n", distances[endVertex]);
    fclose(file);

    freeMinHeap(minHeap);
    free(distances);
}

