#include "foom.h"
#include "foom_class.h"
#include "foom_objects.h"

SYMBOLS;
map * native_classes;

object * int_plus(object * self, object * arg) {
  object * tmp, * o;
  if(self->type != arg->type) {
    fprintf(stderr, "should deal with invalid types\n");
    //mebbe an exception object?
    /*
    tmp = get_member(arg->members, "_to_int_");
    if(tmp && tmp->type == func_sym) {
      //list * args = new_list();

    }else {

    }*/
  }
  o = new_int();
  //o->type = int_sym;
  o->val.Int = self->val.Int + arg->val.Int;
  return o;
}

object * int_minus(object * self, object * arg) {
  object * tmp, * o;
  if(self->type != arg->type) {
    fprintf(stderr, "should deal with invalid types\n");
    //mebbe an exception object?
    /*
    tmp = get_member(arg->members, "_to_int_");
    if(tmp && tmp->type == func_sym) {
      //list * args = new_list();

    }else {

    }*/
  }
  o = new_int();
  //o->type = int_sym;
  o->val.Int = self->val.Int - arg->val.Int;
  return o;
}
object * int_compare(object * self, object * arg) {
  object * o = new_int();
  if(self->val.Int < arg->val.Int) o->val.Int = -1;
  else if(self->val.Int > arg->val.Int) o->val.Int = 1;
  else o->val.Int = 0;
  return o;
}

object * int_to_string(object * self){
  object * s = new_str();
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

object * int_class() {
  object * o = new_object();
  o->val.Class = new_class(true);
  o->val.Class->native_type = int_sym;
  o->type = class_sym;
  o->null = false;
  o->name = "int";
  map_set(native_classes, o->name, o, map_object|map_immutable);
  add_member_name(o, native_wrapper(&int_minus, func_binary), _symbols_[minus_sym]);
  add_member_name(o, native_wrapper(&int_plus, func_binary), _symbols_[plus_sym]);
  add_member_name(o, native_wrapper(&int_to_string, func_unary), "to_string");
  add_member_name(o, native_wrapper(&int_set_self, func_binary), "set_self");
  add_member_name(o, native_wrapper(&int_compare, func_binary), "compare");
  return o;
}
