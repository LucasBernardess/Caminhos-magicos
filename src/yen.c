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

// // Função principal do algoritmo Yen
MenorCaminho* yen(Grafo* grafo, int origem, int destino, int k) {
    MenorCaminho* caminhos = (MenorCaminho*)malloc(k * sizeof(MenorCaminho));
    Grafo grafoTemporario;
    copiarGrafo(grafo, &grafoTemporario);  // Copia o grafo original para o grafo temporário

    for (int i = 0; i < k; i++) {
        // Encontra o caminho mais curto do source para o target no grafo temporário
        dijkstra(&grafoTemporario, origem, destino);

        // Armazena o custo e o caminho no array de caminhos
        caminhos[i].custo = grafoTemporario.vertices[destino].custo;
        caminhos[i].caminho = (int*)malloc(grafoTemporario.numVertices * sizeof(int));
        caminhos[i].comprimentoCaminho = 0;
        int noAtual = destino;
        int indiceCaminho = 0;
        while (noAtual != origem) {
            caminhos[i].caminho[indiceCaminho++] = noAtual;
            noAtual = grafoTemporario.vertices[noAtual].noAnterior;  // Move para o predecessor
        }
        caminhos[i].caminho[indiceCaminho++] = origem;  // Adiciona o nó de origem ao caminho
        caminhos[i].comprimentoCaminho = indiceCaminho;  // Salva o comprimento do caminho

        printf("Custo encontrado para o caminho %d: %d\n", i + 1, caminhos[i].custo);
        printf("Caminho %d encontrado: ", i + 1);
        for (int j = caminhos[i].comprimentoCaminho - 1; j >= 0; j--) {
            printf("%d", caminhos[i].caminho[j]);
            if (j > 0) {
                printf(" -> ");
            }
        }
        printf("\n\n");

        // Remove a última aresta do caminho encontrado para encontrar o próximo caminho
        noAtual = origem;  // Manter esta declaração e inicialização
        for (int j = 0; j < caminhos[i].comprimentoCaminho - 1; j++) {
            int proximoNo = caminhos[i].caminho[j];
            removerAresta(&grafoTemporario, noAtual, proximoNo);
            noAtual = proximoNo;
        }
    }

    return caminhos;
}

MenorCaminho encontrarCaminho(Grafo *grafo, int origem, int destino)
{
    MenorCaminho caminho;
    caminho.custo = grafo->vertices[destino].custo;
    caminho.comprimentoCaminho = 0;

    // Estimar o tamanho do caminho (isso pode ser ajustado conforme necessário)
    caminho.caminho = (int *)malloc(grafo->numVertices * sizeof(int));

    int atual = destino;
    while (atual != origem)
    {
        caminho.caminho[caminho.comprimentoCaminho++] = atual;
        atual = grafo->vertices[atual].noAnterior;
    }
    caminho.caminho[caminho.comprimentoCaminho++] = origem;

    // Opcional: Inverter o caminho se necessário para que comece na origem e termine no destino
    for (int i = 0; i < caminho.comprimentoCaminho / 2; i++)
    {
        int temp = caminho.caminho[i];
        caminho.caminho[i] = caminho.caminho[caminho.comprimentoCaminho - 1 - i];
        caminho.caminho[caminho.comprimentoCaminho - 1 - i] = temp;
    }

    return caminho;
}

void modificarGrafo(Grafo *grafo, MenorCaminho caminho) {
    // Aqui você pode aumentar o peso das arestas que foram usadas no caminho
    for (int i = 0; i < caminho.comprimentoCaminho - 1; ++i) {
        // Encontre a aresta entre caminho.caminho[i] e caminho.caminho[i + 1] e aumente o peso
        Aresta* aresta = grafo->vertices[caminho.caminho[i]].proxima;
        while (aresta != NULL) {
            if (aresta->destino == caminho.caminho[i + 1]) {
                aresta->peso = INT_MAX; // Aumente o peso para um valor muito alto
                break;
            }
            aresta = aresta->proxima;
        }
    }
}


// Função principal do algoritmo Yen
MenorCaminho* yen(Grafo* grafo, int origem, int destino, int k) {
    MenorCaminho* caminhos = (MenorCaminho*)malloc(k * sizeof(MenorCaminho));
    // Inicialização dos caminhos
    for (int i = 0; i < k; ++i) {
        caminhos[i].caminho = NULL;
        caminhos[i].comprimentoCaminho = 0;
        caminhos[i].custo = INT_MAX;
    }

    // Crie um grafo temporário para usar no algoritmo
    Grafo grafoTemp;
    copiarGrafo(grafo, &grafoTemp);

    // Vamos encontrar os k menores caminhos
    for (int i = 0; i < k; ++i) {
        dijkstra(&grafoTemp, origem);
        caminhos[i] = encontrarCaminho(&grafoTemp, origem, destino);

        // Verificar se o caminho é válido
        if (caminhos[i].custo == INT_MAX) {
            liberarCaminho(&caminhos[i]); // Não foi encontrado um caminho válido
            continue;
        }

        // Agora, vamos modificar o grafo para a próxima iteração
        // Isso pode envolver remover arestas ou aumentar o peso das arestas para não encontrar o mesmo caminho
        modificarGrafo(&grafoTemp, caminhos[i]);

        // Restaurar o grafo para o estado original
        restaurarGrafo(grafo, &grafoTemp);
    }

    // Liberar recursos do grafo temporário aqui, se necessário

    return caminhos;
}


// Função para verificar se o caminho já foi encontrado
int caminhoJaEncontrado(MenorCaminho *caminhos, int numeroCaminhos, MenorCaminho caminho)
{
    for (int i = 0; i < numeroCaminhos; i++)
    {
        if (compararCaminhos(&caminhos[i], &caminho))
        {
            return 1;
        }
    }
    return 0;
}

// Função para comparar dois caminhos (deve ser implementada corretamente)
int compararCaminhos(MenorCaminho* caminho1, MenorCaminho* caminho2) {
    // Se os caminhos tiverem comprimentos diferentes, eles não são iguais
    if (caminho1->comprimentoCaminho != caminho2->comprimentoCaminho) {
        return 0;
    }
    
    // Compare cada nó nos caminhos
    for (int i = 0; i < caminho1->comprimentoCaminho; i++) {
        if (caminho1->caminho[i] != caminho2->caminho[i]) {
            return 0; // Os caminhos são diferentes
        }
    }
    
    // Se todos os nós são iguais, os caminhos são iguais
    return 1;
}

// Função para liberar os recursos do caminho
void liberarCaminho(MenorCaminho *caminho)
{
    free(caminho->caminho); // Assumindo que caminho->caminho é um ponteiro para um array dinâmico
    caminho->caminho = NULL;
    caminho->comprimentoCaminho = 0;
    caminho->custo = 0;
}