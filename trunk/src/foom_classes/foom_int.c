#include "foom.h"
#include "foom_class.h"
#include "foom_objects.h"
SYMBOLS;

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
  o = new_object();
  o->type = int_sym;
  o->val.Int = self->val.Int - arg->val.Int;
  return o;
}
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
  o = new_object();
  o->type = int_sym;
  o->val.Int = self->val.Int + arg->val.Int;
  return o;
}

object * int_to_string(object * self){
  object * s = new_str();
  s->null = false;
  s->val.Str = malloc(sizeof(str));
  s->val.Str->val = malloc(33*sizeof(char));
  ltoa(self->val.Int, s->val.Str->val, 10);
  s->val.Str->len = strlen(s->val.Str->val);
  return s;
}

object * int_class() {
  object * o = new_object();
  o->val.Class = new_class(true);
  o->val.Class->native_type = int_sym;
  o->type = class_sym;
  o->null = false;
  o->name = "int";
  map_set(o->members, _symbols_[minus_sym], &int_minus, map_binary);
  map_set(o->members, _symbols_[plus_sym], &int_plus, map_binary);
  map_set(o->members, "to_string", native_wrapper(&int_to_string, func_unary), map_object);
  return o;
}
