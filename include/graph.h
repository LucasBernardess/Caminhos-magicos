#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

// Estrutura para uma aresta
typedef struct Edge {
    int dest;           // Destino da aresta
    int weight;         // Peso da aresta
    struct Edge *next;  // Próximo nó na lista de adjacências
} Edge;

// Estrutura para um vértice no grafo
typedef struct Vertex {
    Edge *head;         // Cabeça da lista de adjacências
} Vertex;

// Estrutura do grafo
typedef struct Graph {
    int numVertices;    // Número de vértices no grafo
    Vertex *vertices;   // Array de listas de adjacências
} Graph;

// Protótipos de funções para manipulação de grafos
Graph *createGraph(int numVertices);
void addEdge(Graph *graph, int src, int dest, int weight);
void printGraph(const Graph *graph);
void freeGraph(Graph *graph);
char *graphToString(const Graph *graph);  // Representação em string do grafo para depuração

#endif // GRAPH_H
