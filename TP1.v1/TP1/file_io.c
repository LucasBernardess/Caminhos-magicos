#include "file_io.h"
#include <stdio.h>
#include <stdlib.h>

void readGraphFromFile(const char *fileName, Graph **graph) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo de entrada.\n");
        exit(EXIT_FAILURE);
    }

    int numVertices, numEdges;
    fscanf(file, "%d %d", &numVertices, &numEdges);

    *graph = createGraph(numVertices);

    int src, dest, cost;
    for (int i = 0; i < numEdges; i++) {
        fscanf(file, "%d %d %d", &src, &dest, &cost);
        addEdge(*graph, src - 1, dest - 1, cost); // Ajustando índice para base 0
    }

    fclose(file);
}

void writeResultsToFile(const char *fileName, int distance) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo de saída.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%d\n", distance);
    fclose(file);
}
