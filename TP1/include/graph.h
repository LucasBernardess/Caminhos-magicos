#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Estrutura de uma aresta do grafo
typedef struct Edge {
    int destino;
    unsigned long int peso;
    struct Edge* proxima;
} Edge;

// Estrutura de um vértice do grafo
typedef struct Vertex {
    int id;
    Edge* proxima;
    unsigned long int custo;
    int noAnterior;
} Vertex;

// Estrutura do grafo
typedef struct Graph {
    int numVertices;
    Vertex* vertices;
} Graph;

Graph* createGraph(int numVertices);
void addEdge(Graph* grafo, int origem, int destino, unsigned long int peso);
void printGraph(Graph* grafo);
void freeGraph(Graph* grafo);

#endif
