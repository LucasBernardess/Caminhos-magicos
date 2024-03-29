#ifndef FILE_IO_H
#define FILE_IO_H

#include "graph.h"

// Function to read the graph from the input file
Graph* readGraphFromFile(const char *fileName);

// Function to write the results to the output file
void writeResultsToFile(const char *fileName, int *distances, int k);

#endif
