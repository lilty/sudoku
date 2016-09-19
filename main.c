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
#include "sudoku.h"

void print_help() {
    printf(
        "\n"
        "sudoku - as a learning exercise.\n"
        "   g generate: generate and print a full 9*9 grid\n"
    );
}

int main (int argc, char *argv[]) {
    sudoku_t *sudoku;

    sudoku = sudoku_ctor();
    if (argc >= 1 && argv[1]) {
        if (strcmp(argv[1], "g") == 0 || strcmp(argv[1], "generate") == 0) {
            sudoku_generate(sudoku);
            sudoku_print(sudoku);
        } else {
            print_help();
        }
    } else {
        print_help();
    }
    sudoku_dtor(sudoku);

    return EXIT_SUCCESS;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */