CC = g++
CFLAGS = -g -Wall -Wextra -std=gnu++98 -O2 $(INCDIRS) 
#CFLAGS = -g -Wall -Wextra -std=gnu++98 $(INCDIRS) -DDEBUG
INCDIRS = 
LIBDIRS = 
LIBS = 
#LIBS = -pg 
PUZZLENAME = dancebattle
LDFLAGS = $(LIBDIRS) $(LIBS)
SOURCES = main.cpp DanceBattle.cpp Matrix.cpp Position.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = $(PUZZLENAME)

all: $(SOURCES) $(EXECUTABLE)

$(PUZZLENAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

tar:
	tar czf $(PUZZLENAME).tar.gz Makefile *.cpp *.h
	
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@
