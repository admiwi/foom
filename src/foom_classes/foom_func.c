#include "foom.h"
#include "foom_class.h"

SYMBOLS;



object * func_class() {
  object * o = new_object();
  o->val.Class = new_class(true);
  o->val.Class->native_type = func_sym;
  o->type = class_sym;
  o->null = false;
  o->name = "func";
  return o;
}

object * func_call(object * fo, object * self, object * args) {
  func * f = fo->val.Func;
  if(flaged(f->flags,func_binary)) {
    bFuncP bfp = f->f.bfunc;
    return bfp(self, args);
  }
  if(flaged(f->flags,func_unary)) {
    uFuncP ufp = f->f.ufunc;
    return ufp(self);
  }
  printf("Not implemented yet %d\n",__LINE__);
  return new_object(false);
}
