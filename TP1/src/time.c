#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "../include/time.h"

// Função para calcular e exibir o tempo de execução do programa
void calculateExecutionTime(struct timeval start, struct timeval end, 
                           struct rusage usageStart, struct rusage usageEnd) {
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    double userTime = (usageEnd.ru_utime.tv_sec - usageStart.ru_utime.tv_sec) + 
                      (usageEnd.ru_utime.tv_usec - usageStart.ru_utime.tv_usec) / 1e6;
    double sysTime = (usageEnd.ru_stime.tv_sec - usageStart.ru_stime.tv_sec) + 
                     (usageEnd.ru_stime.tv_usec - usageStart.ru_stime.tv_usec) / 1e6;

    printf("\n# Tempo de execução:\n");
    printf("-> Tempo total de execução: %.3f segundos.\n", elapsed);
    printf("-> Tempo de usuário: %.3f segundos.\n", userTime);
    printf("-> Tempo de sistema: %.3f segundos.\n", sysTime);
}