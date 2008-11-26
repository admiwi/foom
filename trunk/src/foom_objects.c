#include "foom.h"

extern MAP native_classes;
SYMBOLS;


object * new_object() {
  object * o = malloc(sizeof(object));
  //map * v = map_get(native_classes, "obj");
  memset(o, 0, sizeof(object));
  o->type = obj_sym;
  o->null = true;
  o->ref = true;
  o->members = map_new();
  o->class = NULL;
  return o;
}

object * new_int() {
  object * o = new_object();
  o->type = int_sym;
  o->class = map_get(native_classes, "int")->data;
  o->null = false;
  o->ref = false;
  o->val.Int = 0;
  return o;
}

object * new_str() {
  object * o = new_object();
  o->type = str_sym;
  o->class = map_get(native_classes, "str")->data;
  return o;
}

object * new_dec() {
  object * o = new_object();
  o->type = dec_sym;
  o->ref = false;
  o->class = map_get(native_classes, "dec")->data;
  return o;
}

object * new_map() {
  object * o = new_object();
  o->type = map_sym;
  o->class = map_get(native_classes, "map")->data;
  return o;
}

object * new_list() {
  object * o = new_object();
  o->type = list_sym;
  o->class = map_get(native_classes, "list")->data;
  return o;
}

object * new_bool() {
  object * o = new_object();
  o->type = bool_sym;
  o->class = map_get(native_classes, "bool")->data;
  o->null = false;
  o->ref = false;
  o->val.Bool = false;
  return o;
}

object * new_func() {
  object * o = new_object();
  o->type = func_sym;
  o->val.Func = malloc(sizeof(func));
  memset(o->val.Func, 0, sizeof(func));
  o->class = map_get(native_classes, "func")->data;
  return o;
}

object * find_obj(Symbol s) {
  switch(s) {
    case obj_sym: return new_object();
    case int_sym: return new_int();
    case dec_sym: return new_dec();
    case bool_sym: return new_bool();
    case func_sym: return new_func();
    //case bin_sym: return new_bin();
    case list_sym: return new_list();
    case map_sym: return new_map();
    case str_sym: return new_str();
    default:
      fprintf(stderr, "invalid object type %s\n", _symbols_[s]);
      return new_object();
  }
}
