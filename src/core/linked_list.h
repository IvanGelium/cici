#pragma once
#include "base.h"

typedef struct linked_list_node {
  struct linked_list_node *next;
  struct linked_list_node *prev;
  i32 value;
} linked_list_node;

typedef struct linked_list {
  linked_list_node *entry_node;
  usize size;
} linked_list;

typedef void (*linked_list_callback)(i32 value, void *user_data);

linked_list linked_list_create(i32);
linked_list_node *linked_list_get_node(linked_list *llc, isize at);
void linked_list_pushf(linked_list *, i32);
void linked_list_pushb(linked_list *, i32);
i32 linked_list_popf(linked_list *);
i32 linked_list_popb(linked_list *);
void linked_list_insert(linked_list *, isize, i32);
i32 linked_list_remove(linked_list *, isize);
void linked_list_foreach(linked_list *, linked_list_callback, void *);
void linked_list_print(linked_list *);