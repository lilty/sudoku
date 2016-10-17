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
#include <stdlib.h>
#include <string.h>
#include "sudoku.h"

static void print_buffer(int *buffer) {
  int at;

  for (int x = 0; x < SUDOKU_GRID_N; x++) {
    printf("+---");
  }
  printf("+\n");
  for (int y = 0; y < SUDOKU_GRID_N; y++) {
    for (int x = 0; x < SUDOKU_GRID_N; x++) {
      printf("|");
      if ((at = GET_AT(buffer, x, y))) {
        printf(" %d ", at);
      } else {
        printf("   ");
      }
    }
    printf("|\n");
    for (int x = 0; x < SUDOKU_GRID_N; x++) {
      if ((y + 1) % 3 == 0) {
        printf("+---");
      } else {
        printf("+ - ");
      }
    }
    printf("+\n");
  }
}

static int is_possible(int *buffer, int index, int value) {
  int n = SUDOKU_GRID_N / 3;
  int x = index % SUDOKU_GRID_N;
  int y = index / SUDOKU_GRID_N;
  int bx = x - (x % n);
  int by = y - (y % n);

  for (int i = 0; i < SUDOKU_GRID_N; i++) {
    if (GET_AT(buffer, i, y) == value ||
        GET_AT(buffer, x, i) == value ||
        GET_AT(buffer, bx + i % n, by + i / n) == value) {
      return 0;
    }
  }

  return 1;
}

static int candidates(int *grid, int index) {
  int boxN = SUDOKU_GRID_N / 3;
  int x = index % SUDOKU_GRID_N;
  int y = index / SUDOKU_GRID_N;
  int boxX = x - (x % boxN);
  int boxY = y - (y % boxN);
  int i;
  int counts[SUDOKU_GRID_N + 1] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int candidate = 0;

  for (i = 0; i < SUDOKU_GRID_N; i++) {
    counts[GET_AT(grid, i, y)]++;
    counts[GET_AT(grid, x, i)]++;
    counts[GET_AT(grid, boxX + i % boxN, boxY + i / boxN)]++;
  }

  for (i = 1; i <= SUDOKU_GRID_N; i++) {
    if (*(counts + i) == 0) {
      if (candidate > 0) {
        return 0;
      }
      candidate = i;
    }
  }

  grid[index] = candidate;
  return candidate > 0;
}

void sudoku_init(sudoku_t *sudoku) {
  sudoku->length = SUDOKU_GRID_N * SUDOKU_GRID_N;
  sudoku->solution = calloc(sudoku->length, sizeof(int));
  sudoku->puzzle = calloc(sudoku->length, sizeof(int));
}

int sudoku_dtor(sudoku_t *sudoku) {
  if (sudoku) {
    free(sudoku->solution);
    free(sudoku->puzzle);
    return 1;
  }

  return 0;
}

int sudoku_generate(sudoku_t *sudoku) {
  int index = EMPTY_INDEX(sudoku->puzzle, (int) sudoku->length, 0);
  int values[SUDOKU_GRID_N];

  if (index == -1) {
    return 1;
  }
  FILL(values, SUDOKU_GRID_N, 1);
  SHUFFLE(values, SUDOKU_GRID_N);
  for (int i = 0; i < SUDOKU_GRID_N; i++) {
    int value = *(values + i);
    if (is_possible(sudoku->puzzle, index, value)) {
      sudoku->puzzle[index] = value;
      if (sudoku_generate(sudoku)) {
        return 1;
      }
      sudoku->puzzle[index] = 0;
    }
  }

  return 0;
}

int sudoku_puzzle(sudoku_t *sudoku, int empty) {
  int *r = calloc(sudoku->length, sizeof(int));
  empty = empty ?: 54;

  sudoku_generate(sudoku);
  FILL(r, (int) sudoku->length, 0);
  SHUFFLE(r, (int) sudoku->length);
  for (int i = 0; i < empty; i++) {
    sudoku->puzzle[*(r + i)] = 0;
  }
  free(r);

  return 1;
}

int sudoku_solve_conditions_(sudoku_t *sudoku) {
  int empty = 0;
  int change = 0;

  for (int i = 1; i <= SUDOKU_GRID_N; i++) {
    if (*(sudoku->solution + i) == 0) {
      if (candidates(sudoku->solution, i)) {
        change = 1;
      } else {
        empty = 1;
      }
    }
  }
  if (empty) {
    if (change) {
      return sudoku_solve_conditions_(sudoku);
    } else {
      return 0;
    }
  }

  return 1;
}

int sudoku_solve_backtracking_(sudoku_t *sudoku, int index) {
  if ((index = EMPTY_INDEX(sudoku->solution, (int) sudoku->length, index)) == -1) {
    return 1;
  }
  IF_POSSIBLE_BEGIN(sudoku->solution, index, i)
    sudoku->solution[index] = value;
    if (sudoku_solve_backtracking_(sudoku, index + 1)) {
      return 1;
    }
    sudoku->solution[index] = 0;
  IF_POSSIBLE_END;

  return 0;
}

int sudoku_solve(sudoku_t *sudoku) {
  memcpy(sudoku->solution, sudoku->puzzle, sudoku->length * sizeof(int));

  return sudoku_solve_conditions_(sudoku) || sudoku_solve_backtracking_(sudoku, 41);
}

void sudoku_print_solution(sudoku_t *sudoku) {
  int at;

  for (int x = 0; x < SUDOKU_GRID_N; x++) {
    printf("+---");
  }
  printf("+\n");
  for (int y = 0; y < SUDOKU_GRID_N; y++) {
    for (int x = 0; x < SUDOKU_GRID_N; x++) {
      printf("|");
      if ((at = GET_AT(sudoku->solution, x, y))) {
        if (GET_AT(sudoku->puzzle, x, y) == 0) {
          printf(ANSI_COLOR_MAGENTA" %d "ANSI_COLOR_RESET, at);
        } else {
          printf(" %d ", at);
        }
      } else {
        printf("   ");
      }
    }
    printf("|\n");
    for (int x = 0; x < SUDOKU_GRID_N; x++) {
      if ((y + 1) % 3 == 0) {
        printf("+---");
      } else {
        printf("+ - ");
      }
    }
    printf("+\n");
  }
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