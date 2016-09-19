CC=gcc
CFLAGS=-c -Wall -std=c99
LDFLAGS=
SOURCES=main.c sudoku.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=sudoku

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@