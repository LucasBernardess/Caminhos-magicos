#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "heap.h"

// Structure to store an individual path and its total cost
typedef struct {
    int cost;       // The total cost of the path
    int *path;      // The array of vertices that form the path
    int length;     // The number of vertices in the path
    int capacity;   // The capacity of the path array
} Path;

// Structure to store the results of a path search
typedef struct {
    Path *paths;    // An array of paths
    int numPaths;   // The number of paths found
    int capacity;   // The capacity of the paths array
} DijkstraResult;

// Function to execute the Dijkstra algorithm
DijkstraResult *dijkstra(const Graph *graph, int src, int k);

// Function to free the memory allocated for the Dijkstra result
void freeDijkstraResult(DijkstraResult *result);

// Function to print the Dijkstra result
void printDijkstraResult(const DijkstraResult *result);

#endif // DIJKSTRA_H
