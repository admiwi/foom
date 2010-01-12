#include "foom.h"
#include "foom_class.h"

SYMBOLS;

void init_obj_class(scope * s) {
  object * o = new_object(s);
  o->val.Class = new_class(true);
  o->val.Class->native_type = obj_sym;
  o->type = class_sym;
  o->null = false;
  o->name = "obj";
 scope_set(s, o, map_class|map_immutable);
}
