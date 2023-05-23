#ifndef LIST_H_
#define LIST_H_

#include "arc.h"

typedef Arc List;

enum ListTag {
  Cons,
  Nil,
};

typedef struct list_node {
  enum ListTag tag;
  Arc item;
  List next;
} ListNode;

List list_build_nil() {
  List list = arc_alloc(sizeof(ListNode));
  ListNode* node = (ListNode*) arc_as_ref(list);
  node->tag = Nil;
  return list;
}

List list_build_cons(Arc* head, List* tail) {
  List list = arc_alloc(sizeof(ListNode));
  ListNode* node = (ListNode*) arc_as_ref(list);
  node->tag = Cons;
  node->item = arc_clone(head);
  node->next = arc_clone(tail);
  return list;
}

void list_drop(List list) {
  arc_drop(list);
}

#endif // LIST_H
