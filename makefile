CC = gcc
CFLAGS = -Wall -Wextra -g

all: main

main: src/main.o src/leitura_arquivo.o src/grafo.o src/dijkstra.o src/yen.o
	$(CC) $(CFLAGS) -o main src/main.o src/leitura_arquivo.o src/grafo.o src/dijkstra.o src/yen.o

main.o: src/main.c include/leitura_arquivo.h include/grafo.h include/dijkstra.h include/yen.h
	$(CC) $(CFLAGS) -c src/main.c

leitura_arquivo.o: src/leitura_arquivo.c include/leitura_arquivo.h include/grafo.h include/dijkstra.h include/yen.h
	$(CC) $(CFLAGS) -c src/leitura_arquivo.c

grafo.o: src/grafo.c include/grafo.h
	$(CC) $(CFLAGS) -c src/grafo.c

dijkstra.o: src/dijkstra.c include/dijkstra.h
	$(CC) $(CFLAGS) -c src/dijkstra.c

yen.o: src/yen.c include/yen.h include/dijkstra.h include/grafo.h
	$(CC) $(CFLAGS) -c src/yen.c

clean:
	rm -f main *.o
