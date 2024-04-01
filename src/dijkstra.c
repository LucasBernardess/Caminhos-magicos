// dijkstra.c
#include "../include/dijkstra.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

// Função auxiliar para inserir um nó na heap
static void inserirNoHeap(NoHeap* heap, int* tamHeap, int no, int custo) {
    int i = (*tamHeap)++;
    while (i && custo < heap[(i - 1) / 2].custo) {
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap[i].no = no;
    heap[i].custo = custo;
}

// Função auxiliar para corrigir a heap para baixo a partir de um índice
static void heapMinimo(NoHeap* heap, int tamHeap, int i) {
    int menor = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < tamHeap && heap[esquerda].custo < heap[menor].custo) {
        menor = esquerda;
    }
    if (direita < tamHeap && heap[direita].custo < heap[menor].custo) {
        menor = direita;
    }
    if (menor != i) {
        NoHeap temp = heap[i];
        heap[i] = heap[menor];
        heap[menor] = temp;
        heapMinimo(heap, tamHeap, menor);
    }
}

// Função auxiliar para extrair o nó com o menor custo da heap
static NoHeap extrairMin(NoHeap* heap, int* tamHeap) {
    NoHeap min = heap[0];
    heap[0] = heap[--(*tamHeap)];
    heapMinimo(heap, *tamHeap, 0);
    return min;
}

// A função relaxar é usada para atualizar o custo de um caminho para um determinado nó
static void relaxar(NoHeap* heap, int* tamHeap, InfoCaminho* caminhos, int src, int dest, int peso) {
    int novoCusto = caminhos[src].custo + peso;
    if (novoCusto < caminhos[dest].custo) {
        caminhos[dest].custo = novoCusto;
        caminhos[dest].noAnterior = src;
        inserirNoHeap(heap, tamHeap, dest, novoCusto);
    }
}

// Implementação do algoritmo de Dijkstra
void dijkstra(Grafo* grafo, int origem) {
    int numVertices = grafo->numVertices;
    InfoCaminho* caminhos = (InfoCaminho*)malloc(numVertices * sizeof(InfoCaminho));
    NoHeap* heap = (NoHeap*)malloc(numVertices * sizeof(NoHeap));
    bool* visitados = (bool*)calloc(numVertices, sizeof(bool));
    int tamHeap = 0;

    // Inicializa as estruturas de caminhos e heap
    for (int i = 0; i < numVertices; i++) {
        caminhos[i].custo = INT_MAX;
        caminhos[i].noAnterior = -1;
    }
    caminhos[origem].custo = 0;
    inserirNoHeap(heap, &tamHeap, origem, 0);

    // Executa o algoritmo de Dijkstra
    while (tamHeap > 0) {
        NoHeap minNo = extrairMin(heap, &tamHeap);
        int u = minNo.no;

        // Se já foi visitado, pule
        if (visitados[u]) continue;
        visitados[u] = true;

        // Processa os vizinhos do nó u
        for (Aresta* e = grafo->vertices[u].proxima; e != NULL; e = e->proxima) {
            if (!visitados[e->destino]) {
                relaxar(heap, &tamHeap, caminhos, u, e->destino, e->peso);
            }
        }
    }

    // Atualiza o grafo com os resultados de Dijkstra
    for (int i = 0; i < numVertices; i++) {
        grafo->vertices[i].custo = caminhos[i].custo;
        grafo->vertices[i].noAnterior = caminhos[i].noAnterior;
    }

    // Libera a memória alocada
    free(caminhos);
    free(heap);
    free(visitados);
}
