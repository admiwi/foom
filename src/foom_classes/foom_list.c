#include "foom.h"
#include "foom_class.h"

SYMBOLS;

object * list_class() {
  object * o = new_object();
  o->val.Class = new_class(true);
  o->val.Class->native_type = list_sym;
  o->type = class_sym;
  o->null = false;
  o->name = "list";
  return o;
}
