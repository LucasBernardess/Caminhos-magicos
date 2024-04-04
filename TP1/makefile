CC = gcc
CFLAGS = -Wall -Wextra -g

all: main

main: main.o file_io.o graph.o dijkstra.o yen.o paths.o
	$(CC) $(CFLAGS) -o main main.o file_io.o graph.o dijkstra.o yen.o paths.o

main.o: main.c file_io.h graph.h dijkstra.h yen.h paths.h
	$(CC) $(CFLAGS) -c main.c

file_io.o: file_io.c file_io.h graph.h dijkstra.h yen.h paths.h
	$(CC) $(CFLAGS) -c file_io.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

dijkstra.o: dijkstra.c dijkstra.h
	$(CC) $(CFLAGS) -c dijkstra.c

yen.o: yen.c yen.h dijkstra.h graph.h
	$(CC) $(CFLAGS) -c yen.c

paths.o: paths.c paths.h
	$(CC) $(CFLAGS) -c paths.c

clean:
	rm -f main *.o