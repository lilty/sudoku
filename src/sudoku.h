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

#ifndef _SUDOKU_H
#define _SUDOKU_H

#ifdef __cplusplus
extern "C" {
#endif

extern int sudoku_solve_select(const char *puzzle, char *solution, int limit, int (*select)(int));
extern int sudoku_solve(const char *puzzle, char *solution, int limit);

typedef unsigned char byte;
typedef int bool;
#ifndef true
#define false 0
#define true 1
#endif

#define HIGH_9_BIT(v) (((v) >> 18) & 0x1FF)
#define MID_9_BIT(v) (((v) >> 9) & 0x1FF)
#define LOW_9_BIT(v) ((v) & 0x1FF)

#define FULL_TO_COLUMN(v) (((v) | ((v) >> 9) | ((v) >> 18)) & 0x1FF)
#define FULL_TO_SHRINK(v) (tbl_shrink_mask[(v)&0x1FF] | tbl_shrink_mask[((v)>>9)&0x1FF]<<3 | tbl_shrink_mask[((v)>>18)&0x1FF]<<6)

#define BIT_SET_27 0x07FFFFFF
#define BIT_SET_30 0x3FFFFFFF

#define NORF(n) sudoku->full_mask[n] &= sudoku->block_mask_sum[n%3] ^ sudoku->block_mask[n];
#define SAVF(n) sudoku->games[sudoku->index].full_mask[n] = sudoku->full_mask[n];
#define RESF(n) sudoku->comp_f[n] = sudoku->full_mask[n] = sudoku->games[sudoku->index].full_mask[n];

#define AN(v, n) v &= n

#ifdef __cplusplus
}
#endif

#endif /* _SUDOKU_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */