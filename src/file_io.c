#include "../include/file_io.h"
#include <stdio.h>
#include <stdlib.h>

Graph *readGraphFromFile(const char *filename, int *k) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    int numVertices, numEdges;
    fscanf(file, "%d %d %d", &numVertices, &numEdges, k);

    Graph *graph = createGraph(numVertices);
    for (int i = 0; i < numEdges; i++) {
        int src, dest, weight;
        fscanf(file, "%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    printGraph(graph);

    fclose(file);
    return graph;
}

void writeKShortestPathsToFile(const char *filename, const DijkstraResult *result, int k) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erro ao abrir o arquivo de saída");
        return;
    }

    // Escreva os k caminhos mais curtos no arquivo
    // O código exato dependerá de como seus caminhos estão armazenados em DijkstraResult
    for (int i = 0; i < k; ++i) {
        // Código fictício, depende da implementação de DijkstraResult
        fprintf(file, "Caminho %d, custo: %d\n", i + 1, result->paths[i].cost);
        fprintf(file, "Path: ");
        for (int j = 0; j < result->paths[i].length; j++) {
            fprintf(file, "%d ", result->paths[i].path[j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}