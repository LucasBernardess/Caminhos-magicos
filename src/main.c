#include <stdio.h>
#include <stdlib.h>
#include "../include/leitura_arquivo.h"

int main(int argc, char *argv[]) {
    // Processar os argumentos da linha de comando
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <arquivo de entrada> <arquivo de saída>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *arquivoEntrada = argv[1];
    char *arquivoSaida = argv[2];

    lerGrafoEGravarSaida(arquivoEntrada, arquivoSaida);

    return 0;
}
