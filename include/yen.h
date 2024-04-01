#ifndef YEN_H
#define YEN_H

#include "dijkstra.h"

typedef struct {
    int* caminho;
    int custo;
    int comprimentoCaminho;  // Adicionando o membro comprimentoCaminho para armazenar o comprimento do caminho
} MenorCaminho;

MenorCaminho* yen(Grafo* grafo, int origem, int destino, int k);
void removerAresta(Grafo* grafo, int src, int dest);
void adicionarAresta(Grafo* grafo, int src, int dest, int peso);
void copiarGrafo(Grafo* grafoOrigem, Grafo* grafoDestino);
MenorCaminho encontrarCaminho(Grafo* grafo, int origem, int destino);
void modificarGrafo(Grafo* grafo, MenorCaminho caminho);
void liberarCaminhos(MenorCaminho* caminhos, int numCaminhos);

#endif
