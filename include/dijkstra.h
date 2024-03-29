#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "heap.h"

// Finds the k shortest paths from startVertex to endVertex.
void findKShortestPaths(Graph *graph, int startVertex, int endVertex, int k, const char *outputFile);

#endif
