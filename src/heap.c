#include "../include/heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

MinHeap *createMinHeap(int capacity) {
    MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->nodes = (HeapNode *)malloc(capacity * sizeof(HeapNode));
    return minHeap;
}

void swapHeapNode(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->nodes[left].dist < minHeap->nodes[smallest].dist) {
        smallest = left;
    }

    if (right < minHeap->size && minHeap->nodes[right].dist < minHeap->nodes[smallest].dist) {
        smallest = right;
    }

    if (smallest != idx) {
        // Troca os nós e atualiza suas posições
        minHeap->pos[minHeap->nodes[smallest].vertex] = idx;
        minHeap->pos[minHeap->nodes[idx].vertex] = smallest;
        swapHeapNode(&minHeap->nodes[smallest], &minHeap->nodes[idx]);

        minHeapify(minHeap, smallest);
    }
}

void insertMinHeap(MinHeap *minHeap, int vertex, int dist) {
    if (minHeap->size == minHeap->capacity) {
        printf("Max capacity reached. Cannot insert key.\n");
        return;
    }

    // Insere o novo nó no final do heap
    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->nodes[i].vertex = vertex;
    minHeap->nodes[i].dist = dist;
    minHeap->pos[vertex] = i;

    // Corrige as propriedades do min heap, se violadas
    while (i != 0 && minHeap->nodes[(i - 1) / 2].dist > minHeap->nodes[i].dist) {
        minHeap->pos[minHeap->nodes[i].vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->nodes[(i - 1) / 2].vertex] = i;
        swapHeapNode(&minHeap->nodes[i], &minHeap->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HeapNode extractMin(MinHeap *minHeap) {
    if (isMinHeapEmpty(minHeap)) {
        return (HeapNode){-1, INT_MAX};
    }

    // Armazena o nó raiz
    HeapNode root = minHeap->nodes[0];

    // Substitui a raiz pelo último nó
    HeapNode lastNode = minHeap->nodes[minHeap->size - 1];
    minHeap->nodes[0] = lastNode;

    // Atualiza a posição do último nó
    minHeap->pos[root.vertex] = minHeap->size - 1;
    minHeap->pos[lastNode.vertex] = 0;

    // Reduz o tamanho do heap e heapify na raiz
    minHeap->size--;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(MinHeap *minHeap, int vertex, int dist) {
    // Obtém o índice do vértice no heap
    int i = minHeap->pos[vertex];

    // Atualiza a distância e corrige as propriedades do min heap, se violadas
    minHeap->nodes[i].dist = dist;
    while (i != 0 && minHeap->nodes[(i - 1) / 2].dist > minHeap->nodes[i].dist) {
        minHeap->pos[minHeap->nodes[i].vertex] = (i - 1) / 2;
        minHeap->pos[minHeap->nodes[(i - 1) / 2].vertex] = i;
        swapHeapNode(&minHeap->nodes[i], &minHeap->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

bool isMinHeapEmpty(const MinHeap *minHeap) {
    return minHeap->size == 0;
}

void freeMinHeap(MinHeap *minHeap) {
    if (minHeap != NULL) {
        free(minHeap->pos);
        free(minHeap->nodes);
        free(minHeap);
    }
}
