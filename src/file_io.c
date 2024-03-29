#include "../include/file_io.h"
#include "../include/graph.h"
#include <stdio.h>
#include <stdlib.h>

Graph* readGraphFromFile(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return NULL;
    }

    int numVertices, numEdges;
    fscanf(file, "%d %d", &numVertices, &numEdges);
    Graph* graph = createGraph(numVertices);

    int src, dest, cost;
    for (int i = 0; i < numEdges; i++) {
        fscanf(file, "%d %d %d", &src, &dest, &cost);
        addEdge(graph, src, dest, cost);
    }

    fclose(file);
    return graph;
}

void writeResultsToFile(const char *fileName, int *distances, int k) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < k; i++) {
        fprintf(file, "%d\n", distances[i]);
    }

    fclose(file);
}
