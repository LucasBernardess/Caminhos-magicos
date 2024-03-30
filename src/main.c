#include "../include/file_io.h"
#include "../include/graph.h"
#include "../include/dijkstra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *inputFile = NULL;
    char *outputFile = NULL;
    int k;

    // Processar os argumentos da linha de comando
    if (argc != 5) {
        fprintf(stderr, "Usage: %s -i inputfile -o outputfile\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "-i") == 0) {
            inputFile = argv[i + 1];
        } else if (strcmp(argv[i], "-o") == 0) {
            outputFile = argv[i + 1];
        } else {
            fprintf(stderr, "Invalid option %s\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    // Verificar se os nomes dos arquivos foram fornecidos
    if (inputFile == NULL || outputFile == NULL) {
        fprintf(stderr, "Input file and output file must be specified\n");
        return EXIT_FAILURE;
    }

    // Ler o grafo do arquivo de entrada
    Graph *graph = readGraphFromFile(inputFile, &k);
    if (graph == NULL) {
        fprintf(stderr, "Erro ao ler o grafo do arquivo.\n");
        return EXIT_FAILURE;
    }

    // Executar o algoritmo de Dijkstra
    DijkstraResult *result = dijkstra(graph, 0, k); // 0 é o vértice de origem
    if (result == NULL) {
        fprintf(stderr, "Erro ao executar o algoritmo de Dijkstra.\n");
        freeGraph(graph);
        return EXIT_FAILURE;
    }

    // Escrever os resultados no arquivo de saída
    writeKShortestPathsToFile(outputFile, result, k);

    // Limpeza e saída
    freeDijkstraResult(result);
    freeGraph(graph);

    return EXIT_SUCCESS;
}
