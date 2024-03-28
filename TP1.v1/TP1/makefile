CC = gcc
CFLAGS = -Wall -g
OBJ = main.o file_io.o graph.o heap.o dijkstra.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

project: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o project
