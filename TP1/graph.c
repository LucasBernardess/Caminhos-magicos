#include "graph.h"

// Função para criar um novo grafo
Graph* criarGrafo(unsigned long int numVertices) {
    Graph* grafo = (Graph*)malloc(sizeof(Graph));
    grafo->numVertices = numVertices;
    grafo->vertices = (Vertex*)malloc(numVertices * sizeof(Vertex));

    for (unsigned long int i = 0; i < numVertices; i++) {
        grafo->vertices[i].id = i;
        grafo->vertices[i].proxima = NULL;
    }

    return grafo;
}

// Função para adicionar uma aresta ao grafo
void adicionarAresta(Graph* grafo, unsigned long int origem, unsigned long int destino, unsigned long int peso) {
    Edge* novaAresta = (Edge*)malloc(sizeof(Edge));
    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->proxima = grafo->vertices[origem].proxima;
    grafo->vertices[origem].proxima = novaAresta;
}

// Função para liberar toda a memória alocada para o grafo
void liberarGrafo(Graph* grafo) {
    if (grafo == NULL) return;

    for (unsigned long int i = 0; i < grafo->numVertices; i++) {
        Edge* arestaAtual = grafo->vertices[i].proxima;
        while (arestaAtual != NULL) {
            Edge* tmp = arestaAtual;
            arestaAtual = arestaAtual->proxima;
            free(tmp);
        }
    }
    free(grafo->vertices);
    free(grafo);
}

// Função para remover uma aresta do grafo
void removerAresta(Graph* grafo, unsigned long int origem, unsigned long int destino) {
    Edge **ptr = &(grafo->vertices[origem].proxima), *temp;
    while (*ptr != NULL) {
        if ((*ptr)->destino == destino) {
            temp = *ptr;
            *ptr = (*ptr)->proxima;
            free(temp);
            break;
        }
        ptr = &((*ptr)->proxima);
    }
}

void copiarGrafo(Graph* origem, Graph* destino) {
    // Certifica-se de que a memória atualmente alocada para destino->vertices seja liberada, se existir
    if (destino->vertices != NULL) {
        for (unsigned long int i = 0; i < destino->numVertices; i++) {
            Edge* atual = destino->vertices[i].proxima;
            while (atual != NULL) {
                Edge* paraRemover = atual;
                atual = atual->proxima;
                free(paraRemover); // Libera a aresta atual
            }
        }
        free(destino->vertices); // Libera os vértices
    }
    
    // Continua com a operação de cópia
    destino->numVertices = origem->numVertices;
    destino->vertices = (Vertex*)calloc(origem->numVertices, sizeof(Vertex)); // Usando calloc para inicializar tudo com NULL
    if (destino->vertices == NULL) {
        fprintf(stderr, "Falha ao alocar memória para os vértices do grafo de destino.\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned long int i = 0; i < origem->numVertices; i++) {
        destino->vertices[i].proxima = NULL;
        Edge* atual = origem->vertices[i].proxima;
        Edge** ptrDestino = &(destino->vertices[i].proxima);

        while (atual != NULL) {
            *ptrDestino = (Edge*)malloc(sizeof(Edge));
            if (*ptrDestino == NULL) {
                // Falha ao alocar memória para uma aresta do grafo de destino
                fprintf(stderr, "Falha ao alocar memória para uma aresta do grafo de destino.\n");
                exit(EXIT_FAILURE);
            }
            (*ptrDestino)->destino = atual->destino;
            (*ptrDestino)->peso = atual->peso;
            (*ptrDestino)->proxima = NULL;
            ptrDestino = &((*ptrDestino)->proxima);
            atual = atual->proxima;
        }
    }
}

// Função para imprimir o grafo (para depuração)
void imprimirGrafo(Graph* grafo) {
    printf("Estado atual do grafo:\n");
    for (unsigned long int i = 0; i < grafo->numVertices; i++) {
        printf("Vértice %lu:", i);
        for (Edge* e = grafo->vertices[i].proxima; e != NULL; e = e->proxima) {
            printf(" -> %lu (%lu)", e->destino, e->peso);
        }
        printf("\n");
    }
}