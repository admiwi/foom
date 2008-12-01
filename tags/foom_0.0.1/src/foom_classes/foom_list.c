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

object * list_subscript(object * self, object * subs) {
  list * cur = self->val.List;
  list * csub = subs->val.List;
  object * rl = new_list(), *ro;
  list * rn = list_node();
  int ci = 0, cr = 0;
  long i = csub->obj->val.Int;
  rl->val.List = rn;
  while(cur->next && csub->next) {
    if(ci < csub->obj->val.Int) {
      ci++;
      cur = cur->next;
      continue;
    }
    rn->obj = cur->obj;
    rn->next = list_node();
    rn = rn->next;
    csub = csub->next;
    ci++;
    cr++;
  }
  if(cr == 1) {
    ro = rl->val.List->obj;
    free(rl->val.List->next);
    free(rl);
    return ro;
  } else
    return rl;
}

object * list_to_string(object * self) {
  object * s = new_str();
  list * tl, * l = self->val.List;
  s->val.Str = malloc(sizeof(str));
  s->val.Str->val = strdup(l->obj->name);
  s->val.Str->len = strlen(s->val.Str->val);
  return s;
}

object * list_set_self(object * self, object * args) {
  self->val.List = args->val.List;
  self->null = false;
  return self;
}

object * list_get_length(object * self) {
  object * l = new_int();
  list * tl = self->val.List;
  l->val.Int = 0;
  while(tl->obj) {
    l->val.Int++;
    tl = tl->next;
  }
  return l;
}

object * list_class() {
  object * o = new_object();
  o->val.Class = new_class(true);
  o->val.Class->native_type = list_sym;
  o->type = class_sym;
  o->null = false;
  o->name = "list";
  add_member_name(o, native_wrapper(&list_to_string, func_unary), "to_string");
  add_member_name(o, native_wrapper(&list_set_self, func_binary), "set_self");
  add_member_name(o, native_wrapper(&list_get_length, func_binary), "get_length");
  add_member_name(o, native_wrapper(&list_subscript, func_binary), _symbols_[subscript_sym]);
  return o;
}
