#include "foom.h"
#include "foom_class.h"
SYMBOLS;

object * dec_minus(object * self, object * arg) {
  object * tmp, * o;
  if(self->type != arg->type) {
    fprintf(stderr, "should deal with invalid types\n");
  }
  o = new_object(self->scp);
  o->type = dec_sym;
  o->val.Dec = self->val.Dec - arg->val.Dec;
  return o;
}
object * dec_plus(object * self, object * arg) {
  object * tmp, * o;
  if(self->type != arg->type) {
    fprintf(stderr, "should deal with invalid types\n");

  }
  o = new_object(self->scp);
  o->type = dec_sym;
  o->val.Dec = self->val.Dec + arg->val.Dec;
  return o;
}

void init_dec_class(scope * s) {
  object * o = new_object(s);
  o->val.Class = new_class(true);
  o->val.Class->native_type = dec_sym;
  o->type = class_sym;
  o->null = false;
  o->name = "dec";
  map_set(o->members, _symbols_[minus_sym], &dec_minus, map_binary);
  map_set(o->members, _symbols_[plus_sym], &dec_plus, map_binary);
 scope_set(s, o, map_class|map_immutable);
}
