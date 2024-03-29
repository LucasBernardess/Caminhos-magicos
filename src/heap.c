#include "../include/heap.h"
#include <stdlib.h>
#include <limits.h>

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*) malloc(sizeof(MinHeap));
    minHeap->pos = (int*) malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (HeapNode**) malloc(capacity * sizeof(HeapNode*));
    return minHeap;
}

void swapMinHeapNode(HeapNode** a, HeapNode** b) {
    HeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = left = right = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->cost < minHeap->array[smallest]->cost) {
        smallest = left;
    }

    if (right < minHeap->size && minHeap->array[right]->cost < minHeap->array[smallest]->cost) {
        smallest = right;
    }

    if (smallest != idx) {
        HeapNode* smallestNode = minHeap->array[smallest];
        HeapNode* idxNode = minHeap->array[idx];

        // Troca as posições
        minHeap->pos[smallestNode->vertex] = idx;
        minHeap->pos[idxNode->vertex] = smallest;

        // Troca os nós
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

HeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap)) {
        return NULL;
    }

    // Armazena o nó raiz
    HeapNode* root = minHeap->array[0];

    // Substitui a raiz pelo último nó
    HeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Atualiza a posição do último nó
    minHeap->pos[root->vertex] = minHeap->size-1;
    minHeap->pos[lastNode->vertex] = 0;

    // Reduz o tamanho do heap e heapify a nova raiz
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(MinHeap* minHeap, int vertex, int cost) {
    // Obtém o índice do vértice no heap array
    int i = minHeap->pos[vertex];

    // Obtém o nó e atualiza seu valor de custo
    minHeap->array[i]->cost = cost;

    // Percorre o caminho para a raiz, atualizando a posição se necessário
    while (i && minHeap->array[i]->cost < minHeap->array[(i - 1) / 2]->cost) {
        // Troca este nó com seu pai
        minHeap->pos[minHeap->array[i]->vertex] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->vertex] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        // move para o nó pai
        i = (i - 1) / 2;
    }
}

bool isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

bool isInMinHeap(MinHeap *minHeap, int vertex) {
    if (vertex < minHeap->size) {
        return minHeap->pos[vertex] < minHeap->size;
    }
    return false;
}

void freeMinHeap(MinHeap* minHeap) {
    free(minHeap->pos);
    for (int i = 0; i < minHeap->size; i++) {
        free(minHeap->array[i]);
    }
    free(minHeap->array);
    free(minHeap);
}
