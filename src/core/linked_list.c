#include "core/linked_list.h"
#include "base.h"
#include <stdio.h>
#include <stdlib.h>

static linked_list_node *linked_list_create_node() {
  linked_list_node *nn = malloc(sizeof(linked_list_node));
  return nn;
}

linked_list linked_list_create(i32 first_value) {
  linked_list_node *fn = linked_list_create_node();
  fn->value = first_value;
  fn->next = fn;
  fn->prev = fn;
  linked_list llc = {.size = 1, .entry_node = fn};
  return llc;
}

void linked_list_pushb(linked_list *llc, i32 newVal) {
  linked_list_node *en = llc->entry_node;
  if (en == NULL) {
    linked_list_node *fn = linked_list_create_node();
    fn->value = newVal;
    fn->next = fn;
    fn->prev = fn;
    llc->entry_node = fn;
    llc->size = 1;
    return;
  }

  linked_list_node *nn = malloc(sizeof(linked_list_node));
  nn->value = newVal;
  linked_list_node *ln = en->prev;
  ln->next = nn;
  en->prev = nn;
  nn->next = en;
  nn->prev = ln;
  llc->size = llc->size + 1;
  return;
}

void linked_list_pushf(linked_list *llc, i32 newVal) {
  linked_list_node *cen = llc->entry_node;
  if (cen == NULL) {
    linked_list_node *fn = linked_list_create_node();
    fn->value = newVal;
    fn->next = fn;
    fn->prev = fn;
    llc->entry_node = fn;
    llc->size = 1;
    return;
  }

  linked_list_node *nn = linked_list_create_node();
  nn->value = newVal;

  linked_list_node *ln = cen->prev;
  llc->entry_node = nn;
  ln->next = nn;
  cen->prev = nn;
  nn->next = cen;
  nn->prev = ln;

  llc->size = llc->size + 1;
  return;
}

linked_list_node *linked_list_get_node(linked_list *llc, isize at) {
  linked_list_node *cn = llc->entry_node;
  if (cn == NULL) {
    return NULL;
  }

  if (at >= 0) {
    usize steps = (usize)at;

    if (steps > llc->size) {
      steps = llc->size;
    }

    for (usize i = 0; i < steps; i++) {
      cn = cn->next;
    }
  }

  else {
    usize steps = (usize) - (at);

    if (steps > llc->size) {
      steps = llc->size;
    }
    for (usize i = steps; i > 0; i--) {
      cn = cn->prev;
    }
  }

  return cn;
}

void linked_list_insert(linked_list *llc, isize at, i32 val) {

  linked_list_node *cn = linked_list_get_node(llc, at);
  linked_list_node *n = linked_list_create_node();
  n->value = val;

  linked_list_node *ln = cn->prev;
  cn->prev = n;
  n->next = cn;
  n->prev = ln;
  ln->next = n;
  llc->size = llc->size + 1;
  if (cn == llc->entry_node) {
    llc->entry_node = n;
  }
}

i32 linked_list_remove(linked_list *llc, isize at) {

  linked_list_node *cn = linked_list_get_node(llc, at);
  if (cn == NULL) {
    return -1;
  }
  i32 val = cn->value;

  if (llc->size == 1) {
    i32 val2 = llc->entry_node->value;
    llc->size = llc->size - 1;
    free(llc->entry_node);
    llc->entry_node = NULL;
    return val2;

  } else {
    linked_list_node *nn = cn->next;
    linked_list_node *ln = cn->prev;
    nn->prev = ln;
    ln->next = nn;

    if (cn == llc->entry_node) {
      llc->entry_node = nn;
    }
  }

  llc->size = llc->size - 1;
  free(cn);
  return val;
}

i32 linked_list_popb(linked_list *llc) {
  if (llc == NULL || llc->size == 0)
    return 0;
  linked_list_node *en = llc->entry_node;
  linked_list_node *ln = en->prev;
  linked_list_node *lln = ln->prev;
  i32 val = ln->value;
  if (llc->size == 1) {
    i32 val2 = llc->entry_node->value;
    llc->size = llc->size - 1;
    free(llc->entry_node);
    llc->entry_node = NULL;
    return val2;
  } else {
    lln->next = en;
    en->prev = lln;
  }

  free(ln);
  llc->size = llc->size - 1;
  return val;
}

i32 linked_list_popf(linked_list *llc) {
  if (llc == NULL || llc->size == 0)
    return 0;
  linked_list_node *en = llc->entry_node;
  linked_list_node *nn = en->next;
  linked_list_node *ln = en->prev;
  i32 val = en->value;
  if (llc->size == 1) {
    i32 val2 = llc->entry_node->value;
    llc->size = llc->size - 1;
    free(llc->entry_node);
    llc->entry_node = NULL;
    return val2;
  }
  ln->next = nn;
  nn->prev = ln;
  free(en);
  llc->entry_node = nn;
  llc->size = llc->size - 1;
  return val;
}

void linked_list_foreach(linked_list *llc, linked_list_callback cb,
                         void *user_data) {
  if (llc == NULL || cb == NULL || llc->entry_node == NULL)
    return;
  linked_list_node *cn = llc->entry_node;
  for (usize i = 0; i < llc->size; i++) {
    cb(cn->value, user_data);
    cn = cn->next;
  }
}

void linked_list_print(linked_list *llc) {

  linked_list_node *cn = NULL;
  for (usize i = 0; i < llc->size; i++) {

    if (cn == NULL) {
      cn = (llc->entry_node);
    }
    if (i != llc->size - 1) {
      printf("#:%d v:%d -> ", (i32)i, cn->value);
    } else {
      printf("#:%d v:%d ", (i32)i, cn->value);
    }
    cn = cn->next;
  }
  printf("\n");
}
