#include "foom.h"
#include "foom_lib.h"
#include "foom_objects.h"

object * hi_hello(object * self, object * args) {
  object * o = new_str(args->scp);
  o->val.Str = malloc(sizeof(str));
  o->val.Str->val = strdup("Hello world");
  o->val.Str->len = strlen("Hello world");
  o->name = strdup("hello");
  return o;
}

object * init_lib(const char* n, scope *cscope){
  object * hi = new_object(cscope);
  
  object * o = new_str(cscope);
  o->val.Str = malloc(sizeof(str));
  o->val.Str->val = strdup("Hello world");
  o->val.Str->len = strlen("Hello world");
  o->null = false;  // new objects are null by default
  o->name = strdup("again");

  hi->null = false;
  hi->name = strdup(n);
  
  add_member(hi, nnative_wrapper(&hi_hello, cscope, "hello", func_binary));
  add_member(hi, o);
  
  scope_set(cscope, hi, map_immutable);
  return hi;
}
