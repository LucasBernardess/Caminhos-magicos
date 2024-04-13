#include "../include/file_io.h"
#include "../include/graph.h"
#include "../include/eppstein.h"
#include <stdio.h>
#include <stdlib.h>

// Limites definidos para validação
#define MIN_CIDADES 2
#define MAX_CIDADES 100000
#define MIN_VOOS 1
#define MAX_VOOS 200000
#define MIN_K 1
#define MAX_K 10
#define MAX_PRECO 1000000000UL

int processInputOutput(const char *inputFileName, const char *outputFileName) {
    // Abre o arquivo de entrada para leitura
    FILE *inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        perror("Erro ao abrir o arquivo de entrada");
        return 0;
    }

    // Lê os parâmetros iniciais do arquivo
    int numCidades, numVoos, k;
    if (fscanf(inputFile, "%d %d %d", &numCidades, &numVoos, &k) != 3) {
        fprintf(stderr, "Formato de arquivo de entrada inválido.\n");
        fclose(inputFile);
        return 0;
    }

    // Valida os parâmetros lidos contra os limites definidos
    if (numCidades < MIN_CIDADES || numCidades > MAX_CIDADES ||
        numVoos < MIN_VOOS || numVoos > MAX_VOOS ||
        k < MIN_K || k > MAX_K) {
        fprintf(stderr, "Os valores de n, m ou k estão fora dos limites permitidos.\n");
        fclose(inputFile);
        return 0;
    }

    // Cria o grafo com o número de cidades especificado
    Graph* grafo = createGraph(numCidades);
    if (!grafo) {
        fclose(inputFile);
        return 0;
    }

    // Lê as arestas do arquivo e adiciona ao grafo
    for (int i = 0; i < numVoos; i++) {
        int cidadeA, cidadeB;
        unsigned long int preco;
        if (fscanf(inputFile, "%d %d %lu", &cidadeA, &cidadeB, &preco) != 3) {
            fprintf(stderr, "Erro ao ler os dados da aresta.\n");
            fclose(inputFile);
            freeGraph(grafo);
            return 0;
        }

        // Valida os dados da aresta
        if (cidadeA < 1 || cidadeA > numCidades || cidadeB < 1 || cidadeB > numCidades || preco > MAX_PRECO) {
            fprintf(stderr, "Os valores de a, b ou c estão fora dos limites permitidos.\n");
            fclose(inputFile);
            freeGraph(grafo);
            return 0;
        }
        addEdge(grafo, cidadeA - 1, cidadeB - 1, preco);
    }
    fclose(inputFile);

    // printGraph(grafo); // Para fins de testes

    // Processa o grafo usando o algoritmo de Eppstein
    unsigned long int* resultados = eppstein(grafo, 0, numCidades-1, k, numCidades);
    if (!resultados) {
        freeGraph(grafo);
        return 0;
    }

    // Abre o arquivo de saída para escrita
    FILE *outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        perror("Erro ao abrir o arquivo de saída");
        freeGraph(grafo);
        free(resultados);
        return 0;
    }
    
    // Escreve os resultados no arquivo de saída
    for (int i = 0; i < k; i++) {
        fprintf(outputFile, "%lu ", resultados[i]);
    }
    fprintf(outputFile, "\n");
    fclose(outputFile);

    // Libera os recursos alocados
    freeGraph(grafo);
    free(resultados);

    return 1; // Indica sucesso
}