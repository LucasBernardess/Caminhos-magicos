#include "file_io.h"
#include "yen.h"
#include "paths.h"
#include <stdio.h>
#include <stdlib.h>

int processInputOutput(const char *inputFileName, const char *outputFileName) {
    // Abertura do arquivo de entrada para leitura
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return 0; // Indica falha na abertura do arquivo
    }

    // Variáveis para armazenar o número de cidades, voos e o valor de K
    unsigned long int numCidades, numVoos, k, cidadeOrigem = 1;
    if (fscanf(inputFile, "%lu %lu %lu", &numCidades, &numVoos, &k) != 3) {
        fprintf(stderr, "Formato de arquivo de entrada inválido.\n");
        fclose(inputFile);
        return 0; // Formato inválido do arquivo de entrada
    }

    // Verificações dos limites dos valores lidos
    if (numCidades < 2 || numCidades > 100000 || numVoos < 1 || numVoos > 200000 || k < 1 || k > 10) {
        fprintf(stderr, "Os valores de n, m ou k estão fora dos limites permitidos.\n");
        fclose(inputFile);
        return 0;
    }

    // Criação do grafo com o número de cidades lido
    Graph* grafo = criarGrafo(numCidades);
    for (unsigned long int i = 0; i < numVoos; i++) {
        unsigned long int cidadeA, cidadeB, preco;
        if (fscanf(inputFile, "%lu %lu %lu", &cidadeA, &cidadeB, &preco) != 3) {
            fprintf(stderr, "Erro ao ler os dados da aresta.\n");
            fclose(inputFile);
            liberarGrafo(grafo);
            return 0;
        }

        // Verificações dos limites para as cidades e o preço da aresta
        if (cidadeA < 1 || cidadeA > numCidades || cidadeB < 1 || cidadeB > numCidades || preco < 1 || preco > 1000000000) {
            fprintf(stderr, "Os valores de a, b ou c estão fora dos limites permitidos.\n");
            fclose(inputFile);
            liberarGrafo(grafo);
            return 0;
        }

        // Adiciona a aresta ao grafo
        adicionarAresta(grafo, cidadeA - 1, cidadeB - 1, preco);
    }

    fclose(inputFile); // Fecha o arquivo de entrada após a leitura

    imprimirGrafo(grafo); // Função de depuração para imprimir a estrutura do grafo

    // Executa o algoritmo de Yen para encontrar os K menores caminhos
    ShortestPaths* caminhos = yen(grafo, cidadeOrigem - 1, k);
    if (!caminhos || !caminhos->cabeca) {
        fprintf(stderr, "Erro ao executar o algoritmo de Yen.\n");
        liberarGrafo(grafo);
        return 0;
    }

    // Abre o arquivo de saída para escrita
    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        liberarGrafo(grafo);
        liberarListaDeCaminhos(caminhos);
        return 0;
    }

    // Inverte a lista de caminhos para a ordem correta
    inverterListaCaminhos(caminhos);

    // Escreve os custos dos caminhos encontrados no arquivo de saída
    ShortestPath* atual = caminhos->cabeca;
    while (atual != NULL) {
        fprintf(outputFile, "%u ", atual->custo);  // Atualizado para usar %lu para unsigned long int
        atual = atual->prox;
    }

    fclose(outputFile); // Fecha o arquivo de saída

    // Libera os recursos alocados
    liberarGrafo(grafo);
    liberarListaDeCaminhos(caminhos);

    return 1; // Sucesso
}
