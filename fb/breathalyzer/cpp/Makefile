CC = g++
CFLAGS = -g -Wall -Wextra -std=gnu++98 -O2 $(INCDIRS) 
#CFLAGS = -g -Wall -Wextra -std=gnu++98 -O2 $(INCDIRS) -pg -ftest-coverage -fprofile-arcs
INCDIRS = 
LIBDIRS = 
LIBS = 
LDFLAGS = $(LIBDIRS) $(LIBS)
SOURCES = breathalyzer.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = breathalyzer

all: $(EXECUTABLE)

breathalyzer: breathalyzer.o
	$(CC) $(CFLAGS) $(LDFLAGS) breathalyzer.o -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

tar:
	tar czf breathalyzer.tar.gz Makefile *.cpp
	
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@
