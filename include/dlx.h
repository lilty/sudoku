/*
 * Copyright (c) 2016, Abel Lucas <ylilt71@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef SUDOKU_DLX_H
#define SUDOKU_DLX_H

#include <stddef.h>

struct headnode_s;

struct node_s {
  struct node_s *left;
  struct node_s *right;
  struct node_s *up;
  struct node_s *down;
  struct headnode_s *chead;
};

struct headnode_s {
  struct node_s base_node;
  size_t s;
  const void *id;
};

typedef struct node_s node;
typedef struct headnode_s hnode;

typedef struct {
  node *row;
  const void *id;
  size_t s;
} dlx_hint;

size_t dlx_exact_cover(node *solution[], hnode *root, size_t k);
size_t dlx_has_covers(hnode *root, size_t k);
size_t dlx_exact_cover_hints(dlx_hint solution[], hnode *root, size_t k);
int dlx_force_row(node *r);
int dlx_unselect_row(node *r);
hnode *dlx_make_headers(hnode *root, hnode *headers, size_t n);
void dlx_make_row(node *nodes, hnode *headers, int cols[], size_t n);

#endif /* SUDOKU_DLX_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */