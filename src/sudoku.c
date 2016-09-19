/*
  +----------------------------------------------------------------------+
  | sudoku                                                               |
  +----------------------------------------------------------------------+
  | Copyright (c) IUT Team 2016                                          |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Valentin Nahim                                               |
  | Author: Valentin Lajeunesse                                          |
  | Author: Abel Lucas                                                   |
  +----------------------------------------------------------------------+
 */

#include <time.h>
#include <stdio.h>
#include <string.h>
#include "../sudoku.h"

static void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

static void shuffle(int *buffer, int length) {
    int r;
    srand((unsigned int)time(NULL));

    for (int i = length - 1; i > 0; i--) {
        r = rand() % (i + 1);
        swap(&buffer[i], &buffer[r]);
    }
}

static void fill(int *buffer, int length, int start) {
    for (int i = 0; i < length; i++) {
        buffer[i] = start + i;
    }
}

static int get_at(int *buffer, int x, int y) {
    int index = y * SUDOKU_GRID_N + x;
    return *(buffer + index);
}

void print_buffer(int *buffer) {
    int at;

    for (int y = 0; y < SUDOKU_GRID_N; y++) {
        for (int x = 0; x < SUDOKU_GRID_N; x++) {
            at = get_at(buffer, x, y);
            if (at) {
                printf(" %d ", get_at(buffer, x, y));
            } else {
                printf("   ");
            }
        }
        printf("\n");
    }
}

static int empty_index(int *buffer, int length) {
    for (int i = 0; i < length; i++) {
        if (*(buffer + i) == 0) { return i; }
    }

    return -1;
}

static int is_possible(int *buffer, int index, int value) {
    int n = SUDOKU_GRID_N / 3;
    int x = index % SUDOKU_GRID_N;
    int y = index / SUDOKU_GRID_N;
    int bx = x - (x % n);
    int by = y - (y % n);

    for (int i = 0; i < SUDOKU_GRID_N; i++) {
        if (get_at(buffer, i, y) == value ||
            get_at(buffer, x, i) == value ||
            get_at(buffer, bx + (int)(i % n), by + (int)(i / n)) == value) {
            return 0;
        }
    }

    return 1;
}

sudoku_t *sudoku_ctor() {
    sudoku_t *sudoku = malloc(sizeof(sudoku_t));
    sudoku->length = SUDOKU_GRID_N * SUDOKU_GRID_N;
    sudoku->grid = calloc(sudoku->length, sizeof(int));
    sudoku->puzzle = calloc(sudoku->length, sizeof(int));
    return sudoku;
}

int sudoku_dtor(sudoku_t *sudoku) {
    if (sudoku) {
        free(sudoku->grid);
        free(sudoku->puzzle);
        free(sudoku);
        return 1;
    }

    return 0;
}

void sudoku_clear(sudoku_t *sudoku) {
    int *ptr = sudoku->grid;
    while (ptr) {
        *ptr = 0;
        ptr++;
    }
    ptr = sudoku->puzzle;
    while (ptr) {
        *ptr = 0;
        ptr++;
    }
}

int sudoku_generate(sudoku_t *sudoku) {
    int index = empty_index(sudoku->grid, (int) sudoku->length);
    int values[SUDOKU_GRID_N], i, value;

    if (index == -1) {
        return 1;
    }
    fill(values, SUDOKU_GRID_N, 1);
    shuffle(values, SUDOKU_GRID_N);
    for (i = 0; i < SUDOKU_GRID_N; i++) {
        value = *(values + i);
        if (is_possible(sudoku->grid, index, value)) {
            sudoku->grid[index] = value;
            if (sudoku_generate(sudoku)) {
                return 1;
            }
            sudoku->grid[index] = 0;
        }
    }

    return 0;
}

int sudoku_puzzle(sudoku_t *sudoku, int empty) {
    int *r = calloc(sudoku->length, sizeof(int));
    empty = empty ?: 54;

    sudoku_generate(sudoku);
    memcpy(sudoku->puzzle, sudoku->grid, sudoku->length * sizeof(int));
    fill(r, (int) sudoku->length, 0);
    shuffle(r, (int) sudoku->length);
    for (int i = 0; i < empty; i++) {
        sudoku->puzzle[*(r + i)] = 0;
    }
    free(r);

    return 1;
}

int sudoku_solve_backtracking(sudoku_t *sudoku) {
    int index = empty_index(sudoku->puzzle, (int) sudoku->length);

    if (index == -1) {
        return 1;
    }
    for (int i = 1; i <= SUDOKU_GRID_N; i++) {
        if (is_possible(sudoku->puzzle, index, i)) {
            sudoku->puzzle[index] = i;
            if (sudoku_solve_backtracking(sudoku)) {
                return 1;
            }
            sudoku->puzzle[index] = 0;
        }
    }

    return 0;
}

void sudoku_print_grid(sudoku_t *sudoku) {
    print_buffer(sudoku->grid);
}

void sudoku_print_puzzle(sudoku_t *sudoku) {
    print_buffer(sudoku->puzzle);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */