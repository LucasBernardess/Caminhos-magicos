#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>

typedef struct {
    unsigned long int distancia;
    int vertice;
} HeapNode;

typedef struct {
    HeapNode* elementos;
    int tamanho;
    int capacidade;
} MinHeap;

MinHeap* createMinHeap(int capacidade);
void insertMinHeap(MinHeap* heap, unsigned long int distancia, int vertice);
HeapNode extractMin(MinHeap* heap);
void heapify(MinHeap* heap, int indice);
bool heapEmpty(MinHeap* heap);
void freeMinHeap(MinHeap* heap);

#endif
