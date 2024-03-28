#include "graph.h"
#include "dijkstra.h"
#include "file_io.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <arquivo de entrada> <arquivo de saída> <k>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *inputFileName = argv[1];
    const char *outputFileName = argv[2];
    int k = atoi(argv[3]); // Número de caminhos mais curtos a encontrar

    Graph *graph = NULL;
    readGraphFromFile(inputFileName, &graph);

    // Supondo que startVertex seja sempre 0 (Mysthollow) e endVertex seja numVertices-1 (Luminae)
    // A implementação de findKShortestPaths precisa ser ajustada para encontrar e escrever os k caminhos mais curtos
    findKShortestPaths(graph, 0, graph->numVertices - 1, k, outputFileName);

    freeGraph(graph);
    return EXIT_SUCCESS;
}
