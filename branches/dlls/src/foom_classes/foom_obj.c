#include "foom.h"
#include "foom_class.h"

SYMBOLS;
map * native_classes;

object * obj_class() {
  object * o = new_object();
  o->val.Class = new_class(true);
  o->val.Class->native_type = obj_sym;
  o->type = class_sym;
  o->null = false;
  o->name = "obj";
  map_set(native_classes, o->name, o, map_object|map_immutable);
  return o;
}
