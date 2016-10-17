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

#ifndef SUDOKU_SUDOKU_H
#define SUDOKU_SUDOKU_H

#include <stdlib.h>

#define SUDOKU_GRID_N 9
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define SHUFFLE(buffer, length) \
  srand((unsigned int)time(NULL)); \
  for (int i = length - 1; i > 0; i--) { \
      int *b = &buffer[rand() % (i + 1)]; \
      int t = buffer[i]; buffer[i] = *b; *b = t; \
  }
#define FILL(buffer, length, start) \
  for (int i = 0; i < length; i++) { buffer[i] = start + i; }
#define GET_AT(buffer, x, y) \
  *(buffer + ((y) * SUDOKU_GRID_N + (x)))
#define EMPTY_INDEX(buffer, length, at) ({ int __ret = -1, i; \
  for (i = at; i < length; i++) { \
    if (*(buffer + i) == 0) { \
      __ret = i; \
      break; \
    } \
  } \
  if (__ret == -1) \
    for (i = at-1; i >= 0; i--) { \
      if (*(buffer + i) == 0) { \
        __ret = i; \
        break; \
      } \
    } \
  ;__ret; })
#define IF_POSSIBLE_BEGIN(buffer, index, val) \
  int n = SUDOKU_GRID_N / 3; \
  int x = index % SUDOKU_GRID_N; \
  int y = index / SUDOKU_GRID_N; \
  int bx = x - (x % n); \
  int by = y - (y % n); \
  int value; \
  for (int i = 1; i <= SUDOKU_GRID_N; i++) { \
      value = val; \
      for (int j = 0; j < SUDOKU_GRID_N; j++) { \
          if (GET_AT(buffer, j, y) == value || \
              GET_AT(buffer, x, j) == value || \
              GET_AT(buffer, bx + (j % n), by + (j / n)) == value) { \
              goto next; \
          } \
      }
#define IF_POSSIBLE_END \
next: \
      continue; \
  }

typedef struct _sudoku_t {
  size_t length;
  int *puzzle;
  int *solution;
} sudoku_t;

void sudoku_init(sudoku_t *sudoku);
int sudoku_dtor(sudoku_t *sudoku);
int sudoku_generate(sudoku_t *sudoku);
int sudoku_puzzle(sudoku_t *sudoku, int empty);
int sudoku_solve(sudoku_t *sudoku);
void sudoku_print_solution(sudoku_t *sudoku);
void sudoku_print_puzzle(sudoku_t *sudoku);


#endif /* SUDOKU_SUDOKU_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */