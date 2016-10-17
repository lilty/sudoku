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

#include "dlx.h"

static void remove_lr(node *n) {
  n->left->right = n->right;
  n->right->left = n->left;
}

static void remove_ud(node *n) {
  n->up->down = n->down;
  n->down->up = n->up;
}

static void insert_lr(node *n) {
  n->left->right = n->right->left = n;
}

static void insert_ud(node *n) {
  n->up->down = n->down->up = n;
}

static int is_removed_ud(node *n) {
  return n->up->down != n;
}

static void column_append_node(hnode *c, node *n) {
  node *cn = (node *) c;

  n->chead = c;
  n->up = cn->up;
  n->down = cn;
  insert_ud(n);
}

static void cover(hnode *chead) {
  node *i, *j;
  node *c = (node *) chead;

  remove_lr(c);

  i = c;
  while ((i = i->down) != c) {
    j = i;
    while ((j = j->right) != i) {
      remove_ud(j);
      (j->chead->s)--;
    }
  }
}

static void uncover(hnode *chead) {
  node *i, *j;
  node *c = (node *) chead;

  i = c;
  while ((i = i->up) != c) {
    j = i;
    while ((j = j->left) != i) {
      (j->chead->s)++;
      insert_ud(j);
    }
  }

  insert_lr(c);
}

static hnode *min_hnode_s(hnode *root) {
  size_t n;
  size_t min = (size_t) -1u;
  node *h = (node *) root;
  node *i = h;
  node *c = NULL;

  while ((i = i->right) != h) {
    n = ((hnode *) i)->s;
    if (n < min) {
      min = n;
      c = i;
    }
  }
  return (hnode *) c;
}

size_t dlx_exact_cover(node *solution[], hnode *root, size_t k) {
  size_t n;
  node *i, *j, *cn;
  hnode *c;
  node *h = (node *) root;

  if (h->right == h) {
    return k;
  }

  c = min_hnode_s(root);

  cover(c);

  cn = (node *) c;
  n = 0;

  i = cn;
  while ((i = i->down) != cn) {
    solution[k] = i;

    j = i;
    while ((j = j->right) != i)
      cover(j->chead);

    n = dlx_exact_cover(solution, root, k + 1);
    j = i;
    while ((j = j->left) != i)
      uncover(j->chead);
    if (n > 0)
      break;
  }

  uncover(c);
  return n;
}

size_t dlx_exact_cover_hints(dlx_hint solution[], hnode *root, size_t k) {
  size_t n;
  node *i, *j, *cn;
  hnode *c;
  node *h = (node *) root;

  if (h->right == h)
    return k;

  c = min_hnode_s(root);

  cover(c);

  solution[k].id = c->id;
  solution[k].s = c->s;

  cn = (node *) c;
  n = 0;

  i = cn;
  while ((i = i->down) != cn) {
    solution[k].row = i;
    j = i;
    while ((j = j->right) != i)
      cover(j->chead);

    n = dlx_exact_cover_hints(solution, root, k + 1);

    j = i;
    while ((j = j->left) != i)
      uncover(j->chead);

    if (n > 0)
      break;
  }

  uncover(c);
  return n;
}

size_t dlx_has_covers(hnode *root, size_t k) {
  node *i, *j, *cn;
  hnode *c;
  node *h = (node *) root;

  if (h->right == h) {
    return k - 1;
  }

  c = min_hnode_s(root);

  cover(c);

  cn = (node *) c;

  i = cn;
  while ((i = i->down) != cn) {
    j = i;
    while ((j = j->right) != i)
      cover(j->chead);

    k = dlx_has_covers(root, k);

    j = i;
    while ((j = j->left) != i)
      uncover(j->chead);

    if (k == 0)
      break;
  }

  uncover(c);

  return k;
}

int dlx_force_row(node *r) {
  node *i = r;
  if (is_removed_ud(r))
    return -1;

  do {
    cover(i->chead);
  } while ((i = i->right) != r);
  return 0;
}

int dlx_unselect_row(node *r) {
  node *i = r;
  if (!is_removed_ud(r))
    return -1;

  do {
    uncover((i = i->left)->chead);
  } while (i != r);
  return 0;
}

hnode *dlx_make_headers(hnode *root, hnode *headers, size_t n) {
  node *h = (node *) root;
  node *ni;
  size_t i;

  h->left = (node *) (headers + n - 1);
  h->right = (node *) headers;
  h->up = NULL;
  h->down = NULL;
  h->chead = NULL;
  root->s = 0;

  ni = (node *) headers;
  ni->left = h;
  ni->right = (node *) (headers + 1);
  ni->up = ni;
  ni->down = ni;
  ni->chead = (hnode *) ni;
  headers->s = 0;

  for (i = 1; i < n - 1; i++) {
    ni = (node *) (headers + i);
    ni->left = (node *) (headers + i - 1);
    ni->right = (node *) (headers + i + 1);
    ni->up = ni;
    ni->down = ni;
    ni->chead = (hnode *) ni;
    ((hnode *) ni)->s = 0;
  }

  ni = (node *) (headers + n - 1);
  ni->left = (node *) (headers + n - 2);
  ni->right = h;
  ni->up = ni;
  ni->down = ni;
  ni->chead = (hnode *) ni;
  ((hnode *) ni)->s = 0;

  return root;
}

void dlx_make_row(node *nodes, hnode *headers, int cols[], size_t n) {
  size_t i;
  node *ni;

  ni = nodes;

  ni->left = ni + n - 1;
  ni->right = ni + 1;
  column_append_node(headers + cols[0], ni);
  (ni->chead->s)++;

  ni++;

  for (i = 1; i < n - 1; i++, ni++) {
    ni->left = ni - 1;
    ni->right = ni + 1;
    column_append_node(headers + cols[i], ni);
    (ni->chead->s)++;
  }

  ni->left = ni - 1;
  ni->right = nodes;
  column_append_node(headers + cols[n - 1], ni);
  (ni->chead->s)++;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */