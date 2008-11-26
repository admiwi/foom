#include "foom.h"
#include "foom_class.h"

SYMBOLS;

list * list_node() {
  list * l = malloc(sizeof(list));
  memset(l, 0, sizeof(list));
  return l;
}

list * push_list(list * l, object * o) {
  list * nl = list_node();
  while(l->next) l = l->next;
  l->next = nl;
  nl->obj = o;
  return nl;
}

object * list_class() {
  object * o = new_object();
  o->val.Class = new_class(true);
  o->val.Class->native_type = list_sym;
  o->type = class_sym;
  o->null = false;
  o->name = "list";
  return o;
}
