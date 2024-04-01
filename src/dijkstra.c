#include "../include/dijkstra.h"
#include "../include/yen.h"
#include <stdio.h>

void relaxar(NoHeap* heap, int* tamHeap, InfoCaminho* caminhos, int src, int dest, int peso) {
    int novoCustoCaminho = caminhos[src].custo + peso;

    // Verificar se o novo caminho não é negativo
    if (novoCustoCaminho >= 0) {
        // Se o novo caminho for mais curto, atualiza o custo mínimo e o nó anterior
        if (novoCustoCaminho < caminhos[dest].custo || caminhos[dest].custo == -1) {
            caminhos[dest].custo = novoCustoCaminho;
            caminhos[dest].noAnterior = src;

            // Inserir o nó na heap se ainda não estiver lá
            if (!estaNoHeap(heap, *tamHeap, dest)) {
                inserirNoHeap(heap, tamHeap, dest, novoCustoCaminho);
            }
        }
    }
}

int estaNoHeap(NoHeap* heap, int tamHeap, int no) {
    for (int i = 0; i < tamHeap; i++) {
        if (heap[i].no == no) {
            return 1;
        }
    }
    return 0;
}

void inserirNoHeap(NoHeap* heap, int* tamHeap, int no, int custo) {
    heap[*tamHeap].no = no;
    heap[*tamHeap].custo = custo;
    (*tamHeap)++;
}

NoHeap extrairMin(NoHeap* heap, int* tamHeap) {
    NoHeap min = heap[0];
    heap[0] = heap[*tamHeap - 1];
    (*tamHeap)--;
    heapMinimo(heap, 0, *tamHeap);
    return min;
}

void heapMinimo(NoHeap* heap, int i, int tamHeap) {
    int menor = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < tamHeap && heap[esquerda].custo < heap[menor].custo) {
        menor = esquerda;
    }
    if (direita < tamHeap && heap[direita].custo < heap[menor].custo) {
        menor = direita;
    }

    if (menor != i) {
        NoHeap temp = heap[i];
        heap[i] = heap[menor];
        heap[menor] = temp;
        heapMinimo(heap, menor, tamHeap);
    }
}

void dijkstraComHeap(Grafo *grafo, int origem) {
    int tamanho = grafo->numVertices;
    NoHeap heap[tamanho]; // Cria a heap para armazenar os vértices
    int tamanhoHeap = 0; // Tamanho atual da heap

    InfoCaminho caminhos[tamanho]; // Armazena custo e caminho
    for(int i = 0; i < tamanho; ++i) {
        caminhos[i].custo = 10000;
        caminhos[i].noAnterior = -1;
        heap[i].no = i;
        heap[i].custo = 1000;
    }

    // Inicializa o custo da origem como 0 e ajusta a heap
    caminhos[origem].custo = 0;
    heap[origem].custo = 0;
    tamanhoHeap++; // Aumenta o tamanho da heap

    // Constrói a heap
    for (int i = tamanho / 2 - 1; i >= 0; i--) {
        heapify(heap, tamanhoHeap, i);
    }

    // Enquanto a heap não estiver vazia
    while (tamanhoHeap != 0) {
        // Extrai o vértice de menor custo
        NoHeap noHeap = heap[0];
        heap[0] = heap[--tamanhoHeap]; // Remove o menor elemento
        heapify(heap, tamanhoHeap, 0);

        int u = noHeap.no; // Vértice selecionado para processamento

        // Relaxamento
        Aresta* aresta = grafo->vertices[u].proxima;
        while (aresta != NULL) {
            int v = aresta->destino;
            int peso = aresta->peso;

            // Se encontrou um caminho mais curto para v
            if (caminhos[v].custo > caminhos[u].custo + peso) {
                // Atualiza a distância de v
                caminhos[v].custo = caminhos[u].custo + peso;
                caminhos[v].noAnterior = u;

                // Atualiza o custo no heap (aqui, pode-se inserir uma função para atualizar o heap eficientemente)
            }
            aresta = aresta->proxima;
        }
    }
    // Após o loop, `caminhos` contém as distâncias mínimas de `origem` para todos os outros vértices
}

void trocarNos(NoHeap *a, NoHeap *b) {
    NoHeap temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(NoHeap heap[], int tamanho, int i) {
    int menor = i; // Inicializa o menor como raiz
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    // Se o filho da esquerda é menor que a raiz
    if (esquerda < tamanho && heap[esquerda].custo < heap[menor].custo)
        menor = esquerda;

    // Se o filho da direita é menor que o menor até agora
    if (direita < tamanho && heap[direita].custo < heap[menor].custo)
        menor = direita;

    // Se o menor não é a raiz
    if (menor != i) {
        trocarNos(&heap[i], &heap[menor]);

        // Heapify recursivamente o sub-heap afetado
        heapify(heap, tamanho, menor);
    }
}