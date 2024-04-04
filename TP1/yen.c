#include "yen.h"
#include "graph.h"
#include "paths.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void removerArestasYen(Graph* grafoCopia, ShortestPaths* caminhos, ShortestPath* rootPath, int spurNode) {
    removerAresta(grafoCopia, caminhos->cabeca->caminho[spurNode-1], caminhos->cabeca->caminho[spurNode]);
    ShortestPath* aux = caminhos->cabeca->prox;
    while (aux != NULL) {
        int igual = 1;
        for (int i = 0; i < rootPath->comprimentoCaminho; i++) {
            if (i >= aux->comprimentoCaminho || aux->caminho[i] != rootPath->caminho[i]) {
                igual = 0;
                break;
            }
        }
        if (igual == 1 && spurNode < aux->comprimentoCaminho) {
            removerAresta(grafoCopia, aux->caminho[spurNode-1], aux->caminho[spurNode]);
        }
        aux = aux->prox;
    }
}

void definirRootPath(Graph* grafo, ShortestPath* root) {
    if (grafo == NULL || root == NULL || root->comprimentoCaminho <= 0) return;
    
    for (int i = 0; i < root->comprimentoCaminho - 1; i++) {
        Edge **ptr = &(grafo->vertices[root->caminho[i]].proxima);
        while (*ptr != NULL) {
            if ((*ptr)->destino != root->caminho[i + 1]) {
                Edge* arestaRemovida = *ptr;
                *ptr = (*ptr)->proxima;
                free(arestaRemovida);
            } else {
                ptr = &(*ptr)->proxima;
            }
        }
    }
}

ShortestPaths* yen(Graph* grafo, int origem, int k) {
    ShortestPaths* caminhos = (ShortestPaths*)malloc(sizeof(ShortestPaths));
    caminhos->cabeca = NULL;
    inserirMenorCaminho(caminhos, dijkstra(grafo, origem));

    ShortestPaths *caminhosAuxiliares = alocarListaCaminhos();

    for (int i = 0; i < k - 1; i++) {
        for (int j = 1; j < caminhos->cabeca->comprimentoCaminho; j++) {
            int* vetor = (int*)malloc(j * sizeof(int));
            for (int r = 0; r < j; r++) {
                vetor[r] = caminhos->cabeca->caminho[r];
            }

            Graph* grafoTemporario = criarGrafo(grafo->numVertices);
            copiarGrafo(grafo, grafoTemporario);
            ShortestPath* rootPath = criarCaminho(vetor, j, 0);
            definirRootPath(grafoTemporario, rootPath);
            removerArestasYen(grafoTemporario, caminhos, rootPath, j);
            
            ShortestPath* caminho = dijkstra(grafoTemporario, origem);
            
            if (caminho != NULL && !caminhoJaExiste(caminhos, caminhosAuxiliares, caminho)) {
                inserirMenorCaminho(caminhosAuxiliares, caminho);
            } else {
                if (caminho != NULL) {
                    liberarCaminho(caminho);
                }
            }
            free(vetor);
            liberarCaminho(rootPath);
            liberarGrafo(grafoTemporario);
        }

        ShortestPath* minimo = NULL;
        int menorCusto = INT_MAX;
        ShortestPath* atual = caminhosAuxiliares->cabeca;
        while (atual != NULL) {
            if (atual->custo < menorCusto && !verificaCaminho(caminhos, atual)) {
                minimo = atual;
                menorCusto = atual->custo;
            }
            atual = atual->prox;
        }

        if (minimo != NULL) {
            ShortestPath* copiaMinimo = criarCaminho(minimo->caminho, minimo->comprimentoCaminho, minimo->custo);
            inserirMenorCaminho(caminhos, copiaMinimo);
        }
    }
    imprimirCaminhos(caminhos);

    liberarListaDeCaminhos(caminhosAuxiliares);
    return caminhos;
}

