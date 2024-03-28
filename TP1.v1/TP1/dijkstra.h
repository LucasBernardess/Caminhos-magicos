#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "heap.h"

// Declaração da função para encontrar os k caminhos mais curtos usando o algoritmo de Dijkstra
void findKShortestPaths(Graph *graph, int startVertex, int endVertex, int k, const char *outputFile);

#endif
