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
#include "sudoku.h"

static void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

static void shuffle(int *array, int length) {
    int r;
    srand((unsigned int)time(NULL));

    for (int i = length - 1; i > 0; i--) {
        r = rand() % (i + 1);
        swap(&array[i], &array[r]);
    }
}

static void fill(int *array, int length, int start) {
    for (int i = 0; i < length; i++) {
        array[i] = start + i;
    }
}

static int sudoku_get_at(sudoku_t *sudoku, int x, int y) {
    int index = y * SUDOKU_GRID_N + x;
    return *(sudoku->grid + index);
}

static int sudoku_empty_index(sudoku_t *sudoku) {
    for (int i = 0; i < sudoku->length; i++) {
        if (*(sudoku->grid + i) == 0) { return i; }
    }

    return -1;
}

static int sudoku_is_possible(sudoku_t *sudoku, int index, int value) {
    int n = SUDOKU_GRID_N / 3;
    int x = index % SUDOKU_GRID_N;
    int y = index / SUDOKU_GRID_N;
    int bx = x - (x % n);
    int by = y - (y % n);

    for (int i = 0; i < SUDOKU_GRID_N; i++) {
        if (sudoku_get_at(sudoku, i, y) == value ||
            sudoku_get_at(sudoku, x, i) == value ||
            sudoku_get_at(sudoku, bx + (int)(i % n), by + (int)(i / n)) == value) {
            return 0;
        }
    }

    return 1;
}

sudoku_t *sudoku_ctor() {
    sudoku_t *sudoku = malloc(sizeof(sudoku_t));
    sudoku->length = SUDOKU_GRID_N * SUDOKU_GRID_N;
    sudoku->grid = calloc(sudoku->length, sizeof(int));
    return sudoku;
}

int sudoku_dtor(sudoku_t *sudoku) {
    if (sudoku) {
        free(sudoku->grid);
        free(sudoku);
        return 1;
    }

    return 0;
}

int sudoku_generate(sudoku_t *sudoku) {
    int index = sudoku_empty_index(sudoku);
    int values[SUDOKU_GRID_N], i, value;

    if (index == -1) {
        return 1;
    }
    fill(values, SUDOKU_GRID_N, 1);
    shuffle(values, SUDOKU_GRID_N);
    for (i = 0; i < SUDOKU_GRID_N; i++) {
        value = *(values + i);
        if (sudoku_is_possible(sudoku, index, value)) {
            sudoku->grid[index] = value;
            if (sudoku_generate(sudoku)) {
                return 1;
            }
            sudoku->grid[index] = 0;
        }
    }

    return 0;
}

void sudoku_print(sudoku_t *sudoku) {
    for (int y = 0; y < SUDOKU_GRID_N; y++) {
        for (int x = 0; x < SUDOKU_GRID_N; x++) {
            printf(" %d ", sudoku_get_at(sudoku, x, y));
        }
        printf("\n");
    }
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */