#include "foom.h"

SYMBOLS;

void clone_members(object * to, object * from) {
  map_key * ck = from->members->keys;
  map_node * v;
  object * o;
  while(ck) {
    v = map_get(from->members, ck->text);
    o = (object*)v->data;
    o->parent = to;
    map_set(to->members, ck->text, o, v->flags);
    ck = ck->next;
  }
}

object * new_object(scope *s) {
  object * o = malloc(sizeof(object));
  memset(o, 0, sizeof(object));
  o->type = obj_sym;
  o->null = true;
  o->ref = true;
  o->members = map_new();
  o->class = NULL;
  o->scp = s;
  return o;
}

object * new_int(scope *s) {
  object * o = new_object(s);
  o->type = int_sym;
  o->class = scope_get(s, "int");
  o->null = false;
  o->ref = false;
  o->val.Int = 0;
  clone_members(o, o->class);
  return o;
}

object * new_str(scope *s) {
  object * o = new_object(s);
  o->type = str_sym;
  o->class = scope_get(s, "str");
  clone_members(o, o->class);
  return o;
}

object * new_dec(scope *s) {
  object * o = new_object(s);
  o->type = dec_sym;
  o->ref = false;
  o->class = scope_get(s, "dec");
  clone_members(o, o->class);
  return o;
}

object * new_map(scope *s) {
  object * o = new_object(s);
  o->type = map_sym;
  o->class = scope_get(s, "map");
  clone_members(o, o->class);
  return o;
}

object * new_list(scope *s) {
  object * o = new_object(s);
  o->type = list_sym;
  o->class = scope_get(s, "list");
  clone_members(o, o->class);
  return o;
}

object * new_bool(scope *s) {
  object * o = new_object(s);
  o->type = bool_sym;
  o->class = scope_get(s, "bool");
  o->null = false;
  o->ref = false;
  o->val.Bool = false;
  clone_members(o, o->class);
  return o;
}

object * new_func(scope *s) {
  object * o = new_object(s);
  o->type = func_sym;
  o->val.Func = malloc(sizeof(func));
  memset(o->val.Func, 0, sizeof(func));
  o->val.Func->scp = new_scope(NULL);
  o->class = scope_get(s, "func");
  clone_members(o, o->class);
  return o;
}

object * find_obj(Symbol s, scope * sc) {
  switch(s) {
    case obj_sym: return new_object(sc);
    case int_sym: return new_int(sc);
    case dec_sym: return new_dec(sc);
    case bool_sym: return new_bool(sc);
    case func_sym: return new_func(sc);
    //case bin_sym: return new_bin();
    case list_sym: return new_list(sc);
    case map_sym: return new_map(sc);
    case str_sym: return new_str(sc);
    default:
      fprintf(stderr, "invalid object type %s\n", _symbols_[s]);
      return new_object(sc);
  }
}
