CC = g++
CFLAGS = -g -Wall -Wextra -std=gnu++98 -O2 $(INCDIRS) 
#CFLAGS = -g -Wall -Wextra -std=gnu++98 -O2 $(INCDIRS) -pg -ftest-coverage -fprofile-arcs
INCDIRS = 
LIBDIRS = 
LIBS = 
LDFLAGS = $(LIBDIRS) $(LIBS)
SOURCES = liarliar.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = liarliar

all: $(EXECUTABLE)

liarliar: liarliar.o
	$(CC) $(CFLAGS) $(LDFLAGS) liarliar.o -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

tar:
	tar czf liarliar.tar.gz Makefile *.cpp *.h
	
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@
