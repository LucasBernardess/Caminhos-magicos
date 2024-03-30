#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>

typedef struct {
    int vertex; // O vértice do nó no heap
    int dist;   // A chave ou distância do vértice do nó no heap
} HeapNode;

typedef struct {
    int capacity; // Capacidade máxima do heap
    int size;     // Número atual de nós no heap
    HeapNode *nodes; // Array de nós do heap
    int *pos;     // Esta array é necessário para a operação de decreaseKey
} MinHeap;

// Protótipos das funções do heap mínimo
MinHeap *createMinHeap(int capacity);
void freeMinHeap(MinHeap *heap);
void insertMinHeap(MinHeap *heap, int vertex, int dist);
HeapNode extractMin(MinHeap *heap);
void decreaseKey(MinHeap *heap, int vertex, int dist);
bool isMinHeapEmpty(const MinHeap *heap);

#endif // HEAP_H
