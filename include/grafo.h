#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Estrutura de uma aresta do grafo
typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta* proxima;
} Aresta;

// Estrutura de um vértice do grafo
typedef struct Vertice {
    int id;
    Aresta* proxima;
    int custo;
    int noAnterior;
} Vertice;

// Estrutura do grafo
typedef struct Grafo {
    int numVertices;
    Vertice* vertices;
} Grafo;

Grafo* criarGrafo(int numVertices);
void adicionarAresta(Grafo* grafo, int origem, int destino, int peso);
void gerarArquivoDot(Grafo* grafo);
void liberarGrafo(Grafo* grafo);

#endif
