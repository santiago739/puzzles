CC = g++
CFLAGS = -g -Wall -Wextra -std=gnu++98 -O2 $(INCDIRS) 
#CFLAGS = -g -Wall -Wextra -std=gnu++98 -O2 $(INCDIRS) -pg
#CFLAGS = -g -Wall -Wextra -std=gnu++98 -O2 $(INCDIRS) -DDEBUG
#CFLAGS = -g -Wall -Wextra -std=gnu++98 -O2 $(INCDIRS) -pg -ftest-coverage -fprofile-arcs
INCDIRS = 
LIBDIRS = 
LIBS = 
LDFLAGS = $(LIBDIRS) $(LIBS)
SOURCES = gattaca.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = gattaca

all: $(EXECUTABLE)

gattaca: gattaca.o
	$(CC) $(CFLAGS) $(LDFLAGS) gattaca.o -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

tar:
	tar czf gattaca.tar.gz Makefile *.cpp
	
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@
