#ifndef FILE_IO_H
#define FILE_IO_H

#include "graph.h"
#include "dijkstra.h" // Garanta que DijkstraResult está definido

// Protótipos de funções para operações de entrada e saída de arquivos
Graph *readGraphFromFile(const char *filename, int *k);
void writeKShortestPathsToFile(const char *filename, const DijkstraResult *result, int k);

#endif // FILE_IO_H
