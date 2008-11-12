#include "foom.h"
#include "foom_class.h"

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

object * str_class() {
  object * o = new_object();
  o->val.Class = new_class(true);
  o->type = class_sym;
  o->null = false;
  o->name = "str";
  map_set(o->members, _symbols_[plus_sym], &str_plus, MAP_BINARY);
  return o;
}
