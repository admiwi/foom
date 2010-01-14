#include "foom.h"
#include "foom_lib.h"
#include "foom_objects.h"

object * foom_import(object * self, object * args) {
  object *l, *n;
  char buf[255];
  if(args->type == list_sym) {
    l = args->val.List->obj;
    n = args->val.List->next->obj;
    if(!n) n = l;
  } else
    n = l = args;
  sprintf(buf, "dlls\\foom_%s.dll", l->val.Str->val);
  return init_native_lib(buf, n->val.Str->val, args->scp);
}

object * init_lib(const char * n, scope *cscope){
  object * foom = new_object(cscope);
  foom->null = false;
  foom->name = strdup("foom");
  add_member(foom, nnative_wrapper(&foom_import, cscope, "import", func_binary));
  scope_set(cscope, foom, map_immutable);
  return foom;
}
