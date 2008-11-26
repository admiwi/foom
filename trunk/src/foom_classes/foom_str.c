#include "foom.h"
#include "foom_class.h"
#include "foom_objects.h"

SYMBOLS;

object * str_plus(object * self, object * arg) {
  object * o;
  str * s = malloc(sizeof(str));
  char * tmp;
  s->len = self->val.Str->len + arg->val.Str->len;
  s->val = malloc(s->len);
  strcat(s->val, self->val.Str->val);
  strcat(s->val, arg->val.Str->val);
  o = new_object();
  o->type = str_sym;
  o->val.Str = s;
  return o;
}

object * str_get_length(object * self) {
  object * l = new_int();
  if(!self->null)
    l->val.Int = self->val.Str->len;
  return l;
}
object * str_get_self(object * self) {
  return self;
}
object * str_set_self(object * self, object * arg) {
  self->val.Str = arg->val.Str;
  self->null = false;
}

object * str_class() {
  object * o = new_object();
  o->val.Class = new_class(true);
  o->val.Class->native_type = str_sym;
  o->type = class_sym;
  o->null = false;
  o->name = "str";
  map_set(o->members, _symbols_[plus_sym], &str_plus, map_binary|map_native);
  map_set(o->members, "get_length", native_wrapper(&str_get_length, func_unary), map_object);
  map_set(o->members, "get_self", native_wrapper(&str_get_self, func_unary), map_object);
  map_set(o->members, "set_self", native_wrapper(&str_set_self, func_binary), map_object);
  return o;
}
