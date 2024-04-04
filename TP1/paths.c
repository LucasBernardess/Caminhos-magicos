#include "paths.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

ShortestPaths* alocarListaCaminhos() {
    ShortestPaths* listaCaminhos = (ShortestPaths*)malloc(sizeof(ShortestPaths));
    if (!listaCaminhos) {
        perror("Erro ao alocar memória para a lista de MenoresCaminhos");
        exit(EXIT_FAILURE);
    }
    listaCaminhos->cabeca = NULL;
    return listaCaminhos;
}


void liberarListaDeCaminhos(ShortestPaths* lista) {
    ShortestPath* atual = lista->cabeca;
    while (atual != NULL) {
        ShortestPath* proximo = atual->prox;
        free(atual->caminho);
        free(atual);
        atual = proximo;
    }
    free(lista);
}

void liberarCaminho(ShortestPath* caminho) {
    if (caminho != NULL) {
        free(caminho->caminho);
        free(caminho);
    }
}

ShortestPath* criarCaminho(int* caminho, int tamanhoCaminho, int custo) {
    if (tamanhoCaminho <= 0) return NULL;

    int* copiaCaminho = (int*)malloc(tamanhoCaminho * sizeof(int));
    ShortestPath* novoCaminho = (ShortestPath*)malloc(sizeof(ShortestPath));

    if (!copiaCaminho || !novoCaminho) {
        free(copiaCaminho); // Previne vazamento de memória caso a alocação de 'novoCaminho' falhe
        free(novoCaminho);
        return NULL;
    }

    memcpy(copiaCaminho, caminho, tamanhoCaminho * sizeof(int));

    novoCaminho->caminho = copiaCaminho;
    novoCaminho->comprimentoCaminho = tamanhoCaminho;
    novoCaminho->custo = custo;
    novoCaminho->prox = NULL;

    return novoCaminho;
}

void inserirMenorCaminho(ShortestPaths* listaCaminhos, ShortestPath* novoCaminho) {
    if (listaCaminhos == NULL || novoCaminho == NULL) {
        printf("Erro: Lista de Menores Caminhos ou novo caminho inválidos.\n");
        return;
    }

    novoCaminho->prox = listaCaminhos->cabeca; 
    listaCaminhos->cabeca = novoCaminho; 
}

bool verificaCaminho(ShortestPaths* caminhos, ShortestPath* caminhoTeste) {
    ShortestPath* atual = caminhos->cabeca;
    while (atual != NULL) {
        // Comparar os comprimentos dos caminhos
        if (atual->comprimentoCaminho == caminhoTeste->comprimentoCaminho) {
            // Verificar se os caminhos são idênticos
            bool iguais = true;
            for (int i = 0; i < atual->comprimentoCaminho; i++) {
                if (atual->caminho[i] != caminhoTeste->caminho[i]) {
                    iguais = false;
                    break;
                }
            }
            // Se os caminhos são idênticos, retornar true
            if (iguais) return true;
        }
        atual = atual->prox;
    }
    // Se nenhum caminho idêntico foi encontrado, retornar false
    return false;
}

bool caminhoJaExiste(ShortestPaths* caminhosPrincipais, ShortestPaths* caminhosAuxiliares, ShortestPath* caminhoEncontrado) {
    // Verifica se o caminho já existe na lista principal
    if (verificaCaminho(caminhosPrincipais, caminhoEncontrado)) {
        return true;
    }
    // Verifica se o caminho já existe na lista auxiliar
    if (verificaCaminho(caminhosAuxiliares, caminhoEncontrado)) {
        return true;
    }

    return false;
}

void inverterListaCaminhos(ShortestPaths* caminhos) {
    ShortestPath* prev = NULL;
    ShortestPath* current = caminhos->cabeca;
    ShortestPath* next = NULL;

    while (current != NULL) {
        next = current->prox;  // Salva o próximo
        current->prox = prev;  // Inverte o ponteiro do atual
        prev = current;        // Move prev para frente
        current = next;        // Move current para frente
    }
    caminhos->cabeca = prev;  // Atualiza a cabeça da lista para o novo primeiro elemento
}

void imprimirCaminhos(ShortestPaths* caminhos) {
    if (caminhos == NULL || caminhos->cabeca == NULL) {
        printf("Lista de caminhos vazia.\n");
        return;
    }

    ShortestPath* atual = caminhos->cabeca;
    int index = 1;

    while (atual != NULL) {
        printf("Caminho %d: Comprimento = %d, Custo = %d\n", index, atual->comprimentoCaminho, atual->custo);
        printf("Caminho:");
        for (int i = 0; i < atual->comprimentoCaminho; i++) {
            printf(" %d", atual->caminho[i]);
        }
        printf("\n");

        atual = atual->prox;
        index++;
    }
}