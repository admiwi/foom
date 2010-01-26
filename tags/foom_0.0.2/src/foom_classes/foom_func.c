#include "foom.h"
#include "foom_class.h"

SYMBOLS;

object * func_set_self(object * self, object * arg) {
  self->val.Func = arg->val.Func;
  self->null = false;
  return self;
}

void init_func_class(scope * s) {
  object * o = new_object(s);
  o->val.Class = new_class(true);
  o->val.Class->native_type = func_sym;
  o->type = class_sym;
  o->null = false;
  o->name = "func";
  scope_set(s, o, map_class|map_immutable);
  add_member_name(o, native_wrapper(&func_set_self, s, func_binary), "set_self");
}

object * func_call(object * fo, object * self, object * args) {
  func * f = fo->val.Func;
  ast_list * al;
  object * o;
  scope * cscope;
  if(!fo) {
    fprintf(stderr, "func_call on null object\n");
    return NULL;
  }
  if(fo->type != func_sym) {
    fprintf(stderr, "trying to execute a non-function\n");
    return NULL;
  }
  if(f->flags == func_binary) {
    bFuncP bfp = f->f.bfunc;
    return bfp(self, args);
  }
  if(f->flags == func_unary) {
    uFuncP ufp = f->f.ufunc;
    return ufp(self);
  }
  cscope = new_scope(f->scp);
  if(args) {
    args->name = strdup("args");
    scope_set(cscope, args, map_class);
  }
  if(f->f.acode->op.block.stmts)
    for(al = f->f.acode->op.block.stmts;al->node;al = al->next) {
      o = feval(al->node, cscope);
    }
  else
    printf("**BLOCK ERROR**\n");

  return o;
}
