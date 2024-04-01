#include "../include/grafo.h"

// Função para criar um novo grafo
Grafo* criarGrafo(int numVertices) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numVertices = numVertices;
    grafo->vertices = (Vertice*)malloc(numVertices * sizeof(Vertice));

    for (int i = 0; i < numVertices; i++) {
        grafo->vertices[i].id = i;
        grafo->vertices[i].proxima = NULL;
    }

    return grafo;
}

// Função para adicionar uma aresta ao grafo
void adicionarAresta(Grafo* grafo, int origem, int destino, int peso) {
    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->proxima = grafo->vertices[origem].proxima;
    grafo->vertices[origem].proxima = novaAresta;
}

// Função para gerar o arquivo DOT para o Graphviz
void gerarArquivoDot(Grafo* grafo) {
    FILE* arquivoDot = fopen("grafo.dot", "w");

    if (arquivoDot == NULL) {
        printf("Erro ao criar o arquivo DOT.\n");
        return;
    }

    fprintf(arquivoDot, "digraph G {\n");

    for (int i = 0; i < grafo->numVertices; i++) {
        Aresta* arestaAtual = grafo->vertices[i].proxima;
        while (arestaAtual != NULL) {
            fprintf(arquivoDot, "\t%d -> %d [label=\"%d\"];\n", i + 1, arestaAtual->destino + 1, arestaAtual->peso);
            arestaAtual = arestaAtual->proxima;
        }
    }

    fprintf(arquivoDot, "}\n");
    fclose(arquivoDot);
}

void liberarGrafo(Grafo* grafo) {
    if (grafo == NULL) {
        return;
    }

    for (int i = 0; i < grafo->numVertices; i++) {
        Aresta* arestaAtual = grafo->vertices[i].proxima;
        while (arestaAtual != NULL) {
            Aresta* temp = arestaAtual;
            arestaAtual = arestaAtual->proxima;
            free(temp);
        }
        grafo->vertices[i].proxima = NULL;  // Definir o ponteiro como NULL após liberar a memória das arestas
    }

    free(grafo->vertices);
    grafo->vertices = NULL;  // Definir o ponteiro como NULL após liberar a memória dos vértices
    free(grafo);
}
