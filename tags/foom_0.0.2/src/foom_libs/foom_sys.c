#include "foom.h"
#include "foom_lib.h"
#include "foom_objects.h"
#include <time.h>

object * sys_print(object * self, object * args) {
  object * o;
  if(args->type == list_sym)
    o = args->val.List->obj;
  else
    o = args;
  if(!o) return NULL;
  object * tostr = get_member(o, "to_string");
  object * os = func_call(tostr, o, NULL);
  printf("%s", os->val.Str->val);
  return os;
}

object * sys_println(object * self, object * args) {
  object * o = sys_print(self, args);
  if(o)
  printf("\n");
  return o;
}

object * sys_rand(object * self, object * args) {
  object * o, * i;
  if(args->type == list_sym)
    o = args->val.List->obj;
  else
    o = args;
  
  i = new_int(args->scp);
  i->val.Int = ((o && o->type == int_sym) ? rand() % o->val.Int : rand());
  return i;
}

object * init_lib(const char * n, scope *cscope){
  object * sys = new_object(cscope);
  srand(time(NULL));
  sys->null = false;
  sys->name = strdup(n);
  add_member(sys, nnative_wrapper(&sys_println, cscope, "println", func_binary));
  add_member(sys, nnative_wrapper(&sys_print, cscope, "print", func_binary));
  add_member(sys, nnative_wrapper(&sys_rand, cscope, "rand", func_binary));
  scope_set(cscope, sys, map_immutable);
  return sys;
}
