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
  o = new_object(self->scp);
  o->type = str_sym;
  o->val.Str = s;
  return o;
}

object * str_get_length(object * self) {
  object * l = new_int(self->scp);
  if(!self->null)
    l->val.Int = self->val.Str->len;
  return l;
}
object * str_get_self(object * self) {
  return self;
}
object * str_set_self(object * self, object * arg) {
  self->val.Str = malloc(sizeof(str));
  self->val.Str->val = strdup(arg->val.Str->val);
  self->val.Str->len = arg->val.Str->len;
  self->null = false;
  return self;
}

object * str_to_string(object * self) {
  return self;
}

void init_str_class(scope * s) {
  object * o = new_object(s);
  o->val.Class = new_class(true);
  o->val.Class->native_type = str_sym;
  o->type = class_sym;
  o->null = false;
  o->name = "str";
  add_member_name(o, native_wrapper(&str_get_length, s, func_unary), "get_length");
  add_member_name(o, native_wrapper(&str_get_self, s, func_unary), "get_self");
  add_member_name(o, native_wrapper(&str_set_self, s, func_binary), "set_self");
  add_member_name(o, native_wrapper(&str_to_string, s, func_unary), "to_string");
 scope_set(s, o, map_class|map_immutable);
}

