CC = g++
CFLAGS = -g -Wall $(INCDIRS)
INCDIRS = 
LIBDIRS = 
LIBS = 
LDFLAGS = $(LIBDIRS) $(LIBS)
SOURCES = hoppity.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = hoppity

all: $(EXECUTABLE)

hoppity: hoppity.o
	$(CC) $(CFLAGS) $(LDFLAGS) hoppity.o -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

tar:
	tar czf hoppity.tar.gz Makefile *.cpp
	
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@
