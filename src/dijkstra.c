#include "../include/dijkstra.h"
#include "../include/yen.h"
#include <stdio.h>

void relaxar(NoHeap* heap, int* tamHeap, InfoCaminho* caminhos, int src, int dest, int peso) {
    int novoCustoCaminho = caminhos[src].custo + peso;

    // Verificar se o novo caminho não é negativo
    if (novoCustoCaminho >= 0) {
        // Se o novo caminho for mais curto, atualiza o custo mínimo e o nó anterior
        if (novoCustoCaminho < caminhos[dest].custo || caminhos[dest].custo == -1) {
            caminhos[dest].custo = novoCustoCaminho;
            caminhos[dest].noAnterior = src;

            // Inserir o nó na heap se ainda não estiver lá
            if (!estaNoHeap(heap, *tamHeap, dest)) {
                inserirNoHeap(heap, tamHeap, dest, novoCustoCaminho);
            }
        }
    }
}

int estaNoHeap(NoHeap* heap, int tamHeap, int no) {
    for (int i = 0; i < tamHeap; i++) {
        if (heap[i].no == no) {
            return 1;
        }
    }
    return 0;
}

void inserirNoHeap(NoHeap* heap, int* tamHeap, int no, int custo) {
    heap[*tamHeap].no = no;
    heap[*tamHeap].custo = custo;
    (*tamHeap)++;
}

NoHeap extrairMin(NoHeap* heap, int* tamHeap) {
    NoHeap min = heap[0];
    heap[0] = heap[*tamHeap - 1];
    (*tamHeap)--;
    heapMinimo(heap, 0, *tamHeap);
    return min;
}

void heapMinimo(NoHeap* heap, int i, int tamHeap) {
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
        heapMinimo(heap, menor, tamHeap);
    }
}

void dijkstra(Grafo* grafo, int origem) {
    int numVertices = grafo->numVertices;
    InfoCaminho* caminhos = (InfoCaminho*)malloc(numVertices * sizeof(InfoCaminho));
    NoHeap* heap = (NoHeap*)malloc(numVertices * sizeof(NoHeap));
    int tamHeap = 0;

    for (int i = 0; i < numVertices; i++) {
        caminhos[i].custo = -1;
        caminhos[i].noAnterior = -1;
    }

    caminhos[origem].custo = 0;
    inserirNoHeap(heap, &tamHeap, origem, 0);

    while (tamHeap > 0) {
        NoHeap minNo = extrairMin(heap, &tamHeap);
        int noAtual = minNo.no;

        Aresta* arestaAtual = grafo->vertices[noAtual].proxima;
        while (arestaAtual != NULL) {
            relaxar(heap, &tamHeap, caminhos, noAtual, arestaAtual->destino, arestaAtual->peso);
            arestaAtual = arestaAtual->proxima;
        }
    }

    // Atualização do grafo com os resultados de Dijkstra
    for (int i = 0; i < numVertices; i++) {
        grafo->vertices[i].custo = caminhos[i].custo;
        grafo->vertices[i].noAnterior = caminhos[i].noAnterior;
    }

    // Adicione instruções de impressão para depurar o resultado do Dijkstra
    for (int i = 0; i < numVertices; i++) {
        printf("Custo mínimo de %d para %d: %d\n", origem, i, caminhos[i].custo);
    }

    free(caminhos);
    free(heap);
}
