#include "foom.h"
#include "foom_lib.h"

object * hi_hello(object * self, object * args) {
  object * o = new_str(self->scp);
  o->val.Str->val = strdup("Hello world");
  o->val.Str->len = strlen("Hello world");
  return o;
}

void init_lib(scope *cscope){
  object * hi = new_object();
  hi->null = false;
  hi->name = strdup("hi");
  map_set(hi->members, "hello", native_wrapper(&hi_hello, cscope, func_binary), map_object);
  scope_set(cscope, hi, map_immutable);
}
