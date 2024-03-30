#include "../include/graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Graph *createGraph(int numVertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->vertices = (Vertex *)malloc(numVertices * sizeof(Vertex));

    for (int i = 0; i < numVertices; ++i) {
        graph->vertices[i].head = NULL;
    }

    return graph;
}

void addEdge(Graph *graph, int src, int dest, int weight) {
    Edge *newEdge = (Edge *)malloc(sizeof(Edge));
    newEdge->dest = dest;
    newEdge->weight = weight;
    newEdge->next = graph->vertices[src].head;
    graph->vertices[src].head = newEdge;
}

void freeGraph(Graph *graph) {
    if (graph == NULL) {
        return;
    }

    for (int i = 0; i < graph->numVertices; ++i) {
        Edge *edge = graph->vertices[i].head;
        while (edge) {
            Edge *tmp = edge;
            edge = edge->next;
            free(tmp);
        }
    }

    free(graph->vertices);
    free(graph);
}

void printGraph(const Graph *graph) {
    for (int i = 0; i < graph->numVertices; ++i) {
        Edge *edge = graph->vertices[i].head;
        printf("Vertex %d:\n", i);
        while (edge) {
            printf(" -> %d (weight %d)\n", edge->dest, edge->weight);
            edge = edge->next;
        }
        printf("\n");
    }
}

char *graphToString(const Graph *graph) {
    char *str = malloc(1024 * sizeof(char)); // Assume um tamanho suficiente grande
    char buffer[256];
    strcpy(str, "");

    for (int i = 0; i < graph->numVertices; ++i) {
        Edge *edge = graph->vertices[i].head;
        sprintf(buffer, "Vertex %d: ", i);
        strcat(str, buffer);

        while (edge) {
            sprintf(buffer, " -> %d (weight %d)", edge->dest, edge->weight);
            strcat(str, buffer);
            edge = edge->next;
        }
        strcat(str, "\n");
    }

    return str; // Lembre-se de liberar essa string depois de usá-la!
}
