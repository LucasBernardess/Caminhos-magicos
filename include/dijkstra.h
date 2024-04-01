// dijkstra.h
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "grafo.h"

typedef struct {
    int no;
    int custo;
} NoHeap;

typedef struct {
    int custo;
    int noAnterior;
} InfoCaminho;

void dijkstra(Grafo* grafo, int origem);

#endif // DIJKSTRA_H
