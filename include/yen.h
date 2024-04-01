#ifndef YEN_H
#define YEN_H

#include "dijkstra.h"

typedef struct {
    int* caminho;
    int custo;
    int comprimentoCaminho;  // Adicionando o membro comprimentoCaminho para armazenar o comprimento do caminho
} MenorCaminho;

typedef struct {
    MenorCaminho* caminhos;
    int numeroDeCaminhos;
} ListaCaminhos;

MenorCaminho* yen(Grafo* grafo, int origem, int destino, int k);
void removerAresta(Grafo* grafo, int src, int dest);
void adicionarAresta(Grafo* grafo, int src, int dest, int peso);
void copiarGrafo(Grafo* grafoOrigem, Grafo* grafoDestino);
MenorCaminho encontrarCaminho(Grafo* grafo, int origem, int destino);
void modificarGrafo(Grafo* grafo, MenorCaminho caminho);
int caminhoJaEncontrado(ListaCaminhos* encontrados, MenorCaminho caminhoAtual);
void adicionarCaminhoEncontrado(ListaCaminhos* encontrados, MenorCaminho caminhoAtual);
void liberarCaminho(MenorCaminho* caminho);
Aresta* encontrarArestasRemover(Grafo* copiaGrafo, MenorCaminho caminhoAtual);
void liberarArestas(Aresta* arestasRemover);
void liberarCaminhos(MenorCaminho* caminhos, int numCaminhos);

#endif
