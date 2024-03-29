CC=gcc
CFLAGS=-Iinclude
DEPS = include/dijkstra.h include/file_io.h include/graph.h include/heap.h
OBJ = src/dijkstra.o src/file_io.o src/graph.o src/heap.o src/main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

project: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f src/*.o project
