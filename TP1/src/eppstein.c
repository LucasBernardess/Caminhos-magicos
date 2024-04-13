#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/graph.h"
#include "../include/heap.h"
#include "../include/eppstein.h"

// Função que implementa o algoritmo de Eppstein para encontrar os k caminhos mais curtos
unsigned long int* eppstein(Graph* grafo, int origem, int destino, int k, int numeroVertices){
    MinHeap* q = createMinHeap(numeroVertices); // Cria um heap mínimo para os nós do grafo
    if (!q) {
        fprintf(stderr, "Falha ao criar MinHeap.\n");
        return NULL;
    }

    // Inicializa o contador de caminhos encontrados para cada vértice
    int count[numeroVertices];
    memset(count, 0, sizeof(count));

    // Insere a origem no heap com distância 0
    insertMinHeap(q, 0, origem); 

    // Aloca memória para armazenar os pesos dos k caminhos mais curtos
    unsigned long int* caminhos = malloc(k * sizeof(unsigned long int));
    if (!caminhos) {
        fprintf(stderr, "Falha ao alocar memória para caminhos.\n");
        freeMinHeap(q);
        return NULL;
    }
    for (int i = 0; i < k; i++) {
        caminhos[i] = LONG_MAX; // Define todos os caminhos inicialmente como "infinitos"
    }

    int caminhosEncontrados = 0;

    // Enquanto não encontrar todos os k caminhos desejados
    while(caminhosEncontrados < k){
        // Se a heap está vazia, não há mais caminhos possíveis
        if(heapEmpty(q)) break; 

        // Extrai o nó com a menor distância
        HeapNode aux = extractMin(q); 
        
        // Se já encontramos k caminhos para este vértice, ignora
        if (count[aux.vertice] >= k) continue;

        count[aux.vertice]++;
        
        // Se o vértice extraído é o destino, armazena o peso do caminho encontrado
        if (aux.vertice == destino) {
            caminhos[caminhosEncontrados++] = aux.distancia;
        }
        
        // Relaxa as arestas adjacentes
        for (Edge* aresta = grafo->vertices[aux.vertice].proxima; aresta != NULL; aresta = aresta->proxima) {
            int v = aresta->destino;
            unsigned long int w = aresta->peso;

            // Se menos de k caminhos foram encontrados para o vértice adjacente, insere no heap
            if (count[v] < k) {
                insertMinHeap(q, aux.distancia + w, v);
            }
        }
    }

    printf("# Caminhos encontrados:\n");
    for (int i = 0; i < k; i++) {
        if (caminhos[i] != LONG_MAX) {
            printf("-> Caminho %d: Peso %lu\n", i+1, caminhos[i]);
        } else {
            printf("-> Caminho %d: Não encontrado\n", i+1);
        }
    }

    // Libera os recursos alocados para o heap
    freeMinHeap(q);

    return caminhos; // Retorna os pesos dos k caminhos mais curtos encontrados
}