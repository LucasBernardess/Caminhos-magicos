#ifndef FILE_IO_H
#define FILE_IO_H

#include "graph.h"

// Função para ler o grafo do arquivo de entrada
void readGraphFromFile(const char *fileName, Graph **graph);

// Função para escrever os resultados no arquivo de saída
void writeResultsToFile(const char *fileName, int distance);

#endif
