CC = g++
#CFLAGS = -g -Wall -Wextra -std=gnu++98 -O2 $(INCDIRS) 
CFLAGS = -g -Wall -Wextra -std=gnu++98 $(INCDIRS) -DDEBUG
INCDIRS = 
LIBDIRS = 
LIBS = -lm
#LIBS = -pg 
PUZZLENAME = peaktraffic
LDFLAGS = $(LIBDIRS) $(LIBS)
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = $(PUZZLENAME)

all: $(SOURCES) $(EXECUTABLE)

$(PUZZLENAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

tar:
	tar czf $(PUZZLENAME).tar.gz Makefile *.cpp 
	
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@
