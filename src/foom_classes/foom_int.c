#include "foom.h"
#include "foom_class.h"
#include "foom_objects.h"

SYMBOLS;

object * int_mult(object * self, object * arg) {
  object * o;
  o = new_int(self->scp);
  o->val.Int = self->val.Int * arg->val.Int;
  return o;
}

object * int_div(object * self, object * arg) {
  object * o;
  o = new_int(self->scp);
  o->val.Int = self->val.Int / arg->val.Int;
  return o;
}

object * int_plus(object * self, object * arg) {
  object * o;
  o = new_int(self->scp);
  o->val.Int = self->val.Int + arg->val.Int;
  return o;
}

object * int_minus(object * self, object * arg) {
  object * o;
  o = new_int(self->scp);
  o->val.Int = self->val.Int - arg->val.Int;
  return o;
}

object * int_compare(object * self, object * arg) {
  object * o = new_int(self->scp);
  if(self->val.Int < arg->val.Int) o->val.Int = -1;
  else if(self->val.Int > arg->val.Int) o->val.Int = 1;
  else o->val.Int = 0;
  return o;
}

object * int_to_string(object * self){
  object * s = new_str(self->scp);
  s->null = false;
  s->val.Str = malloc(sizeof(str));
  s->val.Str->val = malloc(33*sizeof(char));
  sprintf(s->val.Str->val, "%li",self->val.Int);
  s->val.Str->len = strlen(s->val.Str->val);
  return s;
}

object * int_set_self(object * self, object * arg) {
  self->val.Int = arg->val.Int;
  return self;
}

void init_int_class(scope * s) {
  object * o = new_object(s);
  o->val.Class = new_class(true);
  o->val.Class->native_type = int_sym;
  o->type = class_sym;
  o->null = false;
  o->name = "int";
  scope_set(s, o, map_class|map_immutable);
  add_member_name(o, native_wrapper(&int_mult, s, func_binary), _symbols_[star_sym]);
  add_member_name(o, native_wrapper(&int_div, s, func_binary), _symbols_[slash_sym]);
  add_member_name(o, native_wrapper(&int_minus, s, func_binary), _symbols_[minus_sym]);
  add_member_name(o, native_wrapper(&int_plus, s, func_binary), _symbols_[plus_sym]);
  add_member_name(o, native_wrapper(&int_to_string, s, func_unary), "to_string");
  add_member_name(o, native_wrapper(&int_set_self, s, func_binary), "set_self");
  add_member_name(o, native_wrapper(&int_compare, s, func_binary), "compare");
}
