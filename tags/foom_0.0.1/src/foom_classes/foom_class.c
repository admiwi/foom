#include "foom.h"
#include "foom_class.h"

SYMBOLS;


object * class_class() {
  object * o = new_object();
  o->val.Class = new_class(true);
  o->val.Class->native_type = class_sym;
  o->type = class_sym;
  o->null = false;
  o->name = "class";
  return o;
}
