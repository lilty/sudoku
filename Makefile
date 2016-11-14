CC=clang
CFLAGS=-O4 -g -c -std=c99
LDFLAGS=
SOURCES=src/main.c src/sudoku.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=bin/sudoku

all: $(SOURCES) $(EXECUTABLE)

install:
	install -m 755 $(EXECUTABLE) /usr/local/bin

$(EXECUTABLE): $(OBJECTS)
	$(CC) -I. $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) -I. $(CFLAGS) $< -o $@