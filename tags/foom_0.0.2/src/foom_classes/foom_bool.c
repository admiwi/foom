#include "foom.h"
#include "foom_class.h"
SYMBOLS;

bool bool_test(object * o) {
  if(o->type == bool_sym)
    return o->val.Bool;
  else if(o->type == int_sym)
    return o->val.Int?true:false;
  else
    return o->null?false:true;
}

void init_bool_class(scope *s) {
  object * o = new_object(s);
  o->val.Class = new_class(true);
  o->val.Class->native_type = bool_sym;
  o->type = class_sym;
  o->null = false;
  o->name = "bool";
 scope_set(s, o, map_class|map_immutable);
}
