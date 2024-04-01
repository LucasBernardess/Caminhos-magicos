#include "../include/leitura_arquivo.h"
#include "../include/yen.h"
#include "../include/dijkstra.h"

void lerGrafoEGravarSaida(char *arquivoEntrada, char *arquivoSaida) {
    FILE *arquivoEntradaPtr, *arquivoSaidaPtr;
    int numCidades, numVoos, k;
    int cidadeOrigem = 1;  // Mysthollow é a cidade 1
    int cidadeDestino;     // Luminae é a cidade n, que é o número de cidades

    // Abre o arquivo de entrada para leitura
    arquivoEntradaPtr = fopen(arquivoEntrada, "r");
    if (arquivoEntradaPtr == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return;
    }

    // Lê os valores de numCidades, numVoos e k do arquivo
    fscanf(arquivoEntradaPtr, "%d %d %d", &numCidades, &numVoos, &k);
    cidadeDestino = numCidades;

    // Após a leitura dos valores do arquivo de entrada
    printf("numCidades: %d\n", numCidades);
    printf("numVoos: %d\n", numVoos);
    printf("k: %d\n\n", k);

    // Cria o grafo com o número de vértices (cidades)
    Grafo *grafo = criarGrafo(numCidades);

    // Adiciona as arestas ao grafo lendo do arquivo
    for (int i = 0; i < numVoos; i++) {
        int cidadeA, cidadeB, preco;
        fscanf(arquivoEntradaPtr, "%d %d %d", &cidadeA, &cidadeB, &preco);
        adicionarAresta(grafo, cidadeA - 1, cidadeB - 1, preco);  // Ajusta os índices para começar de 0
        // Dentro do loop de adição de arestas
        printf("Aresta adicionada: %d -> %d (Peso: %d)\n", cidadeA, cidadeB, preco);
    }

    // Fecha o arquivo de entrada após a leitura
    fclose(arquivoEntradaPtr);

    // Antes da chamada da função yen
    printf("\nCidade Origem: %d, Cidade Destino: %d, k: %d\n\n", cidadeOrigem, cidadeDestino, k);
    // Chama o algoritmo de Yen para encontrar os k caminhos mais curtos
    MenorCaminho* caminhos = (MenorCaminho*)malloc(k * sizeof(MenorCaminho));
    caminhos = yen(grafo, cidadeOrigem - 1, cidadeDestino - 1, k);

    // Abre o arquivo de saída para escrita
    arquivoSaidaPtr = fopen(arquivoSaida, "w");
    if (arquivoSaidaPtr == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return;
    }

    // Escreve a saída no arquivo de saída
    for (int i = 0; i < k; i++) {
        fprintf(arquivoSaidaPtr, "%d ", caminhos[i].custo);
    }
    // Fecha o arquivo de saída após a escrita
    fclose(arquivoSaidaPtr);
    // Libera a memória alocada para os caminhos mais curtos
    liberarCaminhos(caminhos, k);
    // Libera a memória alocada para o grafo
    liberarGrafo(grafo);
}
