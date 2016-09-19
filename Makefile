CC=gcc
CFLAGS=-c -Wall -std=c99
LDFLAGS=
SOURCES=src/main.c src/sudoku.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=sudoku

all: $(SOURCES) $(EXECUTABLE)

install:
	install -m 755 $(EXECUTABLE) /usr/local/bin

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@