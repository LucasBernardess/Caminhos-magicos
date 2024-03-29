#include "../include/graph.h"
#include "../include/dijkstra].h"
#include "../include/file_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For getopt
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <arquivo de entrada> <arquivo de saída> <k>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *inputFile = argv[1];
    const char *outputFile = argv[2];
    int k = atoi(argv[3]); // Número de c
   

    // Initialize timing structures
    struct rusage usageStart, usageEnd;
    struct timeval userStart, userEnd, sysStart, sysEnd;

    // Time input reading and graph construction
    getrusage(RUSAGE_SELF, &usageStart);
    Graph *graph = readGraphFromFile(inputFile);
    getrusage(RUSAGE_SELF, &usageEnd);

    userStart = usageStart.ru_utime;
    userEnd = usageEnd.ru_utime;
    sysStart = usageStart.ru_stime;
    sysEnd = usageEnd.ru_stime;

    long readUserTime = (userEnd.tv_sec - userStart.tv_sec) * 1000000 + userEnd.tv_usec - userStart.tv_usec;
    long readSysTime = (sysEnd.tv_sec - sysStart.tv_sec) * 1000000 + sysEnd.tv_usec - sysStart.tv_usec;

    if (!graph) {
        fprintf(stderr, "Failed to construct graph from file\n");
        return EXIT_FAILURE;
    }

    // Time the algorithm execution
    getrusage(RUSAGE_SELF, &usageStart);
    findKShortestPaths(graph, 0, graph->numVertices - 1, k, outputFile);
    getrusage(RUSAGE_SELF, &usageEnd);

    userStart = usageStart.ru_utime;
    userEnd = usageEnd.ru_utime;
    sysStart = usageStart.ru_stime;
    sysEnd = usageEnd.ru_stime;

    long algoUserTime = (userEnd.tv_sec - userStart.tv_sec) * 1000000 + userEnd.tv_usec - userStart.tv_usec;
    long algoSysTime = (sysEnd.tv_sec - sysStart.tv_sec) * 1000000 + sysEnd.tv_usec - sysStart.tv_usec;

    freeGraph(graph);

    printf("Timing Information (Microseconds)\n");
    printf("Reading Input: User Time: %ld, System Time: %ld\n", readUserTime, readSysTime);
    printf("Algorithm Execution: User Time: %ld, System Time: %ld\n", algoUserTime, algoSysTime);

    return 0;
}
