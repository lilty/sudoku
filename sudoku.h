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

typedef struct _sudoku_t {
    int grid[9*9];
} sudoku_t;

sudoku_t *sudoku_ctor();
int sudoku_dtor(sudoku_t *sudoku);
int sudoku_fill(sudoku_t *sudoku);


#endif /* SUDOKU_SUDOKU_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */