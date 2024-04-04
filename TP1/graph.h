#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Estrutura de uma aresta do grafo
typedef struct Edge {
    unsigned long int destino; 
    unsigned long int peso; 
    struct Edge* proxima;
} Edge;

// Estrutura de um vértice do grafo
typedef struct Vertex {
    unsigned long int id;
    Edge* proxima;
    unsigned long int custo;
    unsigned long int noAnterior;
} Vertex;

// Estrutura do grafo
typedef struct Graph {
    unsigned long int numVertices; // Usa unsigned long int para o número de vértices
    Vertex* vertices; // Array de vértices
} Graph;

// Declarações de funções
Graph* criarGrafo(unsigned long int numVertices);
void adicionarAresta(Graph* grafo, unsigned long int origem, unsigned long int destino, unsigned long int peso);
void liberarGrafo(Graph* grafo);
void removerAresta(Graph *grafo, unsigned long int origem, unsigned long int destino);
void copiarGrafo(Graph* grafoOrigem, Graph* grafoDestino);
void imprimirGrafo(Graph* grafo);

#endif
