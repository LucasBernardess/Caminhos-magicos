#include "../include/yen.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

// Função auxiliar para remover uma aresta do grafo temporário
void removerAresta(Grafo *grafo, int src, int dest)
{
    Aresta *anterior = NULL;
    Aresta *atual = grafo->vertices[src].proxima;

    while (atual != NULL)
    {
        if (atual->destino == dest)
        {
            if (anterior == NULL)
            {
                grafo->vertices[src].proxima = atual->proxima;
            }
            else
            {
                anterior->proxima = atual->proxima;
            }
            free(atual);
            break;
        }
        anterior = atual;
        atual = atual->proxima;
    }
}

void restaurarGrafo(Grafo *grafo, Grafo *grafoTemporario)
{
    int numVertices = grafo->numVertices;

    for (int i = 0; i < numVertices; i++)
    {
        grafo->vertices[i].custo = grafoTemporario->vertices[i].custo;
        grafo->vertices[i].noAnterior = grafoTemporario->vertices[i].noAnterior;

        // Remove todas as arestas do grafo original
        Aresta *atual = grafo->vertices[i].proxima;
        while (atual != NULL)
        {
            Aresta *temp = atual;
            atual = atual->proxima;
            free(temp);
        }
        grafo->vertices[i].proxima = NULL;

        // Copia as arestas do grafo temporário de volta para o grafo original
        Aresta *atualTemp = grafoTemporario->vertices[i].proxima;
        Aresta *anterior = NULL;
        while (atualTemp != NULL)
        {
            Aresta *novaAresta = (Aresta *)malloc(sizeof(Aresta));
            novaAresta->destino = atualTemp->destino;
            novaAresta->peso = atualTemp->peso;
            novaAresta->proxima = NULL;

            if (anterior == NULL)
            {
                grafo->vertices[i].proxima = novaAresta;
            }
            else
            {
                anterior->proxima = novaAresta;
            }

            anterior = novaAresta;
            atualTemp = atualTemp->proxima;
        }
    }
}

// Função auxiliar para copiar um grafo para outro
void copiarGrafo(Grafo *grafoOrigem, Grafo *grafoDestino)
{
    int numVertices = grafoOrigem->numVertices;
    grafoDestino->numVertices = numVertices;
    grafoDestino->vertices = (Vertice *)malloc(numVertices * sizeof(Vertice));

    for (int i = 0; i < numVertices; i++)
    {
        grafoDestino->vertices[i].id = grafoOrigem->vertices[i].id;
        grafoDestino->vertices[i].custo = grafoOrigem->vertices[i].custo;
        grafoDestino->vertices[i].noAnterior = grafoOrigem->vertices[i].noAnterior;
        grafoDestino->vertices[i].proxima = NULL;

        Aresta *atual = grafoOrigem->vertices[i].proxima;
        Aresta *anterior = NULL;

        while (atual != NULL)
        {
            Aresta *novaAresta = (Aresta *)malloc(sizeof(Aresta));
            novaAresta->destino = atual->destino;
            novaAresta->peso = atual->peso;
            novaAresta->proxima = NULL;

            if (anterior == NULL)
            {
                grafoDestino->vertices[i].proxima = novaAresta;
            }
            else
            {
                anterior->proxima = novaAresta;
            }

            anterior = novaAresta;
            atual = atual->proxima;
        }
    }
}

// Função para liberar a memória alocada para os caminhos
void liberarCaminhos(MenorCaminho *caminhos, int numCaminhos)
{
    for (int i = 0; i < numCaminhos; i++)
    {
        free(caminhos[i].caminho);
    }
    free(caminhos);
}

MenorCaminho encontrarCaminho(Grafo *grafo, int origem, int destino)
{
    MenorCaminho caminho;
    caminho.custo = grafo->vertices[destino].custo;
    caminho.comprimentoCaminho = 0;

    // Estimar o tamanho do caminho (isso pode ser ajustado conforme necessário)
    caminho.caminho = (int *)malloc(grafo->numVertices * sizeof(int));
    int atual = destino;

    // Construir o caminho de trás para frente, do destino para a origem
    while (atual != origem)
    {
        caminho.caminho[caminho.comprimentoCaminho++] = atual;
        atual = grafo->vertices[atual].noAnterior;
    }
    caminho.caminho[caminho.comprimentoCaminho++] = origem;

    // Inverter o caminho para que comece na origem e termine no destino
    for (int i = 0; i < caminho.comprimentoCaminho / 2; i++)
    {
        int temp = caminho.caminho[i];
        caminho.caminho[i] = caminho.caminho[caminho.comprimentoCaminho - 1 - i];
        caminho.caminho[caminho.comprimentoCaminho - 1 - i] = temp;
    }

    return caminho;
}

void modificarGrafo(Grafo *grafo, MenorCaminho caminho)
{
    // Exemplo: Remover a última aresta do caminho encontrado
    if (caminho.comprimentoCaminho > 1)
    {
        int penultimoNo = caminho.caminho[caminho.comprimentoCaminho - 2];
        int ultimoNo = caminho.caminho[caminho.comprimentoCaminho - 1];

        Aresta **ptr = &grafo->vertices[penultimoNo].proxima;
        while (*ptr != NULL)
        {
            Aresta *atual = *ptr;
            if (atual->destino == ultimoNo)
            {
                *ptr = atual->proxima; // Remover a aresta
                free(atual);           // Liberar a memória da aresta removida
                break;
            }
            ptr = &atual->proxima;
        }
    }
}

MenorCaminho *yen(Grafo *grafo, int origem, int destino, int k)
{
    MenorCaminho *caminhos = (MenorCaminho *)malloc(k * sizeof(MenorCaminho));
    Grafo grafoTemp;
    copiarGrafo(grafo, &grafoTemp); // Copia o grafo original para o grafo temporário

    for (int i = 0; i < k; i++)
    {
        dijkstra(&grafoTemp, origem);
        MenorCaminho caminho = encontrarCaminho(&grafoTemp, origem, destino);

        // Verifique se o caminho é válido e se o custo é maior que -1.
        if (caminho.custo == -1)
        {
            // Se o custo é -1, não há caminho. Pule para o próximo caminho.
            liberarCaminho(&caminho);
            continue;
        }

        // Verificar se o caminho já foi encontrado
        if (!caminhoJaEncontrado(caminhos, i, caminho))
        {
            caminhos[i] = caminho; // Salvar o caminho se ele não foi encontrado antes
        }
        else
        {
            liberarCaminho(&caminho); // Liberar o caminho se ele já foi encontrado
            i--;                      // Decrementar o índice para tentar encontrar outro caminho
            continue;
        }

        printf("Custo encontrado para o caminho %d: %d\n", i + 1, caminhos[i].custo);
        printf("Caminho %d encontrado: ", i + 1);
        for (int j = 0; j < caminhos[i].comprimentoCaminho; j++)
        {
            printf("%d", caminhos[i].caminho[j] + 1); // +1 para ajustar a impressão conforme a numeração das cidades
            if (j < caminhos[i].comprimentoCaminho - 1)
            {
                printf(" -> ");
            }
        }
        printf("\n\n");

        restaurarGrafo(grafo, &grafoTemp);   // Restaurar o grafo para o estado original
        modificarGrafo(&grafoTemp, caminho); // Modificar o grafo para a próxima busca
    }

    // Restaurar grafoTemp para o estado original se necessário
    return caminhos;
}

// Função para verificar se o caminho já foi encontrado
int caminhoJaEncontrado(MenorCaminho* caminhos, int numeroCaminhos, MenorCaminho novoCaminho) {
    for (int i = 0; i < numeroCaminhos; i++) {
        if (caminhos[i].custo == novoCaminho.custo && compararCaminhos(&caminhos[i], &novoCaminho)) {
            return 1;
        }
    }
    return 0;
}


// Função para comparar dois caminhos (deve ser implementada corretamente)
int compararCaminhos(MenorCaminho* caminho1, MenorCaminho* caminho2) {
    if (caminho1->comprimentoCaminho != caminho2->comprimentoCaminho) {
        return 0; // Os caminhos têm comprimentos diferentes e, portanto, são diferentes
    }
    
    for (int i = 0; i < caminho1->comprimentoCaminho; i++) {
        if (caminho1->caminho[i] != caminho2->caminho[i]) {
            return 0; // Encontrou um nó diferente nos caminhos
        }
    }
    
    return 1; // Os caminhos são iguais
}

// Função para liberar os recursos do caminho
void liberarCaminho(MenorCaminho *caminho)
{
    free(caminho->caminho); // Assumindo que caminho->caminho é um ponteiro para um array dinâmico
    caminho->caminho = NULL;
    caminho->comprimentoCaminho = 0;
    caminho->custo = 0;
}