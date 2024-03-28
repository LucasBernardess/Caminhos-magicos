#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

// Função para criar um grafo com um determinado número de vértices
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Edge**) malloc(vertices * sizeof(Edge*));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// Função para adicionar uma aresta ao grafo
void addEdge(Graph *graph, int src, int dest, int cost) {
    // Adicionando aresta do src ao dest
    Edge* newEdge = (Edge*) malloc(sizeof(Edge));
    newEdge->dest = dest;
    newEdge->cost = cost;
    newEdge->next = graph->adjLists[src];
    graph->adjLists[src] = newEdge;
}

// Função para liberar a memória alocada para o grafo
void freeGraph(Graph *graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Edge* edge = graph->adjLists[i];
        while (edge != NULL) {
            Edge* temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
    free(graph->adjLists);
    free(graph);
}
