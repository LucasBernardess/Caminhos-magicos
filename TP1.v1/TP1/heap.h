#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>

// Estrutura para representar um nó na fila de prioridade
typedef struct HeapNode {
    int vertex; // O vértice do nó
    int cost; // Custo para alcançar este vértice
} HeapNode;

// Estrutura para representar a fila de prioridade (min heap)
typedef struct MinHeap {
    int size;     // Número atual de elementos no heap
    int capacity; // Capacidade do heap
    int *pos;     // Este array é usado para rastrear a posição dos elementos do heap
    HeapNode **array;
} MinHeap;

// Funções para manipulação da fila de prioridade
MinHeap* createMinHeap(int capacity);
void insertMinHeap(MinHeap* minHeap, int vertex, int cost);
HeapNode* extractMin(MinHeap* minHeap);
void decreaseKey(MinHeap* minHeap, int vertex, int cost);
bool isEmpty(MinHeap* minHeap);
bool isInMinHeap(MinHeap *minHeap, int vertex);
void freeMinHeap(MinHeap* minHeap);

#endif
