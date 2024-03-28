#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

// Estrutura para representar uma aresta no grafo
typedef struct Edge {
    int dest;    // Destino da aresta
    int cost;    // Custo da aresta
    struct Edge *next; // Próximo nó na lista
} Edge;

// Estrutura para representar a lista de adjacências de cada vértice
typedef struct {
    int numVertices; // Número total de vértices no grafo
    Edge **adjLists; // Array de ponteiros para os nós de aresta
} Graph;

// Funções para manipulação do grafo
Graph* createGraph(int vertices);
void addEdge(Graph *graph, int src, int dest, int cost);
void freeGraph(Graph *graph);

#endif
