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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "sudoku.h"

void print_help() {
  printf(
    "\n"
    "sudoku - as a learning exercise.\n"
    "   solve <...>: solve and print a full 9*9 puzzle\n"
  );
}

void do_solve(const char *puzzle);

int main (int argc, char *argv[]) {
  if (argc >= 1 && argv[1]) {
    if (strcmp(argv[1], "solve") == 0) {
      if (argc < 2) {
        print_help();
        return EXIT_FAILURE;
      }
      do_solve(argv[2]);
    } else {
      print_help();
    }
  } else {
      print_help();
  }

  return EXIT_SUCCESS;
}

void do_solve(const char *puzzle) {
  char solution[81];
  clock_t start, end;

  puts("Solving...");
  puts(puzzle);
  start = clock();
  sudoku_solve(puzzle, solution, 2);
  end = clock();
  printf("Puzzle solved in: %f\n", (end - start) / (double) CLOCKS_PER_SEC);
  puts(solution);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */