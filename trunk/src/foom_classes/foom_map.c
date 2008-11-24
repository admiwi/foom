#include "foom.h"
#include "foom_class.h"

SYMBOLS;

object * map_class() {
  object * o = new_object();
  o->val.Class = new_class(true);
  o->val.Class->native_type = map_sym;
  o->type = class_sym;
  o->null = false;
  o->name = "map";
  return o;
}
