#include "../include/heap.h"
#include <stdlib.h>
#include <stdio.h>

// Cria uma estrutura de min-heap com a capacidade fornecida
MinHeap* createMinHeap(int capacidade) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) {
        fprintf(stderr, "Erro ao alocar memória para o MinHeap.\n");
        return NULL;
    }

    heap->elementos = (HeapNode*)malloc(capacidade * sizeof(HeapNode));
    if (!heap->elementos) {
        fprintf(stderr, "Erro ao alocar memória para os elementos do MinHeap.\n");
        free(heap);
        return NULL;
    }

    heap->tamanho = 0;
    heap->capacidade = capacidade;
    return heap;
}

// Insere um novo nó ao min-heap
void insertMinHeap(MinHeap* heap, unsigned long int distancia, int vertice) {
    if (heap->tamanho == heap->capacidade) {
        return;
    }

    // Primeiro insere no final do heap
    int atual = heap->tamanho++;
    heap->elementos[atual] = (HeapNode){.distancia = distancia, .vertice = vertice};

    // Corrige a propriedade de min heap se o nó for menor que seu pai
    while (atual != 0 && heap->elementos[(atual - 1) / 2].distancia > heap->elementos[atual].distancia) {
        // Troca o nó com o pai
        HeapNode temp = heap->elementos[(atual - 1) / 2];
        heap->elementos[(atual - 1) / 2] = heap->elementos[atual];
        heap->elementos[atual] = temp;

        // Move para o índice do pai
        atual = (atual - 1) / 2;
    }
}

// Remove e retorna o elemento com a menor distância (raiz do heap)
HeapNode extractMin(MinHeap* heap) {
    if (heap->tamanho <= 0) {
        fprintf(stderr, "MinHeap vazio, não é possível extrair elemento.\n");
        return (HeapNode){.distancia = -1, .vertice = -1};
    }

    // Raiz do heap é o elemento a ser extraído
    HeapNode raiz = heap->elementos[0];
    // Move o último elemento para a raiz e reduz o tamanho
    heap->elementos[0] = heap->elementos[--heap->tamanho];
    // Heapify na raiz
    heapify(heap, 0);

    return raiz;
}

// Função auxiliar para manter a propriedade de min-heap
void heapify(MinHeap* heap, int indice) {
    int menor = indice; // Inicializa menor como raiz
    int esquerda = 2 * indice + 1; // índice da esquerda = 2*i + 1
    int direita = 2 * indice + 2; // índice da direita = 2*i + 2

    // Se o filho da esquerda é menor que a raiz
    if (esquerda < heap->tamanho && heap->elementos[esquerda].distancia < heap->elementos[menor].distancia) {
        menor = esquerda;
    }

    // Se o filho da direita é menor que o menor até agora
    if (direita < heap->tamanho && heap->elementos[direita].distancia < heap->elementos[menor].distancia) {
        menor = direita;
    }

    // Se o menor não é raiz
    if (menor != indice) {
        // Troca
        HeapNode temp = heap->elementos[indice];
        heap->elementos[indice] = heap->elementos[menor];
        heap->elementos[menor] = temp;

        // Heapify recursivamente o sub-heap afetado
        heapify(heap, menor);
    }
}

// Verifica se o min-heap está vazio
bool heapEmpty(MinHeap* heap) {
    return heap->tamanho == 0;
}

// Libera a memória alocada para o min-heap
void freeMinHeap(MinHeap* heap) {
    if (!heap) return;
    
    free(heap->elementos);
    free(heap);
}
