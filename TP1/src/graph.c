#include <stdlib.h>
#include <string.h>
#include "../include/graph.h"

// Inicializa um novo grafo com um número especificado de vértices
Graph* createGraph(int numVertices) {
    Graph* grafo = (Graph*)malloc(sizeof(Graph));
    if (!grafo) {
        fprintf(stderr, "Falha ao alocar memória para o grafo.\n");
        return NULL;
    }

    grafo->numVertices = numVertices;
    grafo->vertices = (Vertex*)malloc(numVertices * sizeof(Vertex));
    if (!grafo->vertices) {
        fprintf(stderr, "Falha ao alocar memória para os vértices.\n");
        free(grafo);
        return NULL;
    }

    for (int i = 0; i < numVertices; i++) {
        grafo->vertices[i].id = i;
        grafo->vertices[i].proxima = NULL;
    }

    return grafo;
}

// Adiciona uma aresta direcionada e ponderada ao grafo
void addEdge(Graph* grafo, int origem, int destino, unsigned long int peso) {
    if (!grafo) return;

    Edge* novaAresta = (Edge*)malloc(sizeof(Edge));
    if (!novaAresta) {
        fprintf(stderr, "Falha ao alocar memória para a nova aresta.\n");
        return;
    }

    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->proxima = grafo->vertices[origem].proxima;
    grafo->vertices[origem].proxima = novaAresta;
}

// Imprime o estado atual do grafo
void printGraph(Graph* grafo) {
    if (!grafo) return;

    printf("Estado atual do grafo com os pesos de cada aresta:\n");
    for (int v = 0; v < grafo->numVertices; v++) {
        printf("Vértice %d:", v);
        for (Edge* aresta = grafo->vertices[v].proxima; aresta; aresta = aresta->proxima) {
            printf(" -> %d (%lu)", aresta->destino, aresta->peso);
        }
        printf("\n");
    }
}

// Libera a memória alocada para o grafo
void freeGraph(Graph* grafo) {
    if (!grafo) return;

    for (int i = 0; i < grafo->numVertices; i++) {
        Edge* aresta = grafo->vertices[i].proxima;
        while (aresta) {
            Edge* tmp = aresta;
            aresta = aresta->proxima;
            free(tmp);
        }
    }
    free(grafo->vertices);
    free(grafo);
}
