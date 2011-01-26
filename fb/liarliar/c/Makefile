CC = gcc
CFLAGS = -g -Wall -Wextra -std=gnu99 -O2 $(INCDIRS)
INCDIRS = 
LIBDIRS = 
LIBS = 
LDFLAGS = $(LIBDIRS) $(LIBS)
SOURCES = liarliar.c
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = liarliar

all: $(EXECUTABLE)

liarliar: queue.o graph.o bfs.o liarliar.o
	$(CC) $(CFLAGS) $(LDFLAGS) queue.o graph.o bfs.o liarliar.o -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

tar:
	tar czf liarliar.tar.gz Makefile *.c *.h
	
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
