#include "foom.h"
#include "foom_lib.h"

object * sys_print(object * self, object * args) {
  object * o;
  if(args->type == list_sym)
    o = args->val.List->obj;
  else
    o = args;
  object * tostr = get_member(o, "to_string");
  object * os = func_call(tostr, o, NULL);
  printf("%s", os->val.Str->val);
  return os;
}

object * sys_println(object * self, object * args) {
  object * o = sys_print(self, args);
  printf("\n");
  return o;
}

void init_lib(scope *cscope){
  object * sys = new_object();
  sys->null = false;
  sys->name = strdup("sys");
  map_set(sys->members, "println", native_wrapper(&sys_println, cscope, func_binary), map_object);
  map_set(sys->members, "print", native_wrapper(&sys_print, cscope, func_binary), map_object);
  scope_set(cscope, sys, map_immutable);
}
