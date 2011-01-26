CC = gcc
CFLAGS = -g -Wall -Wextra -std=gnu99 -O2 $(INCDIRS)
#CFLAGS = -g -Wall -Wextra -std=gnu99 -O2 $(INCDIRS) -DDEBUG
#CFLAGS = -g -Wall -Wextra -std=gnu99 -O2 $(INCDIRS) -pg
INCDIRS = 
LIBDIRS = 
LIBS = 
PUZZLENAME = gattaca
LDFLAGS = $(LIBDIRS) $(LIBS)
SOURCES = $(PUZZLENAME).c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = $(PUZZLENAME)

all: $(EXECUTABLE)

$(PUZZLENAME): $(PUZZLENAME).o
	$(CC) $(CFLAGS) $(LDFLAGS) $(PUZZLENAME).o -o $@

clean:
	rm -rf *.o *.out $(EXECUTABLE)

tar:
	tar czf $(PUZZLENAME).tar.gz Makefile *.c
	
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
