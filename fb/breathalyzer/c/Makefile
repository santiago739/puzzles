CC = gcc
CFLAGS = -g -Wall -Wextra -std=gnu99 -O2 $(INCDIRS) #-DDEBUG
INCDIRS = 
LIBDIRS = 
LIBS = 
LDFLAGS = $(LIBDIRS) $(LIBS)
SOURCES = breathalyzer.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = breathalyzer

all: $(EXECUTABLE)

liarliar: breathalyzer.o
	$(CC) $(CFLAGS) $(LDFLAGS) breathalyzer.o -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

tar:
	tar czf breathalyzer.tar.gz Makefile *.c *.h
	
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
