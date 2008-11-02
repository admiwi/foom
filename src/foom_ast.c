#include "foom_ast.h"


object * obj_alloc() {
  object * o = malloc(sizeof(object));
  memset(o, 0, sizeof(object));
  return o;
}

ast * ast_alloc() {
  ast * a = malloc(sizeof(ast));
  memset(a, 0, sizeof(ast));
  return a;
}

ast * astobj_alloc() {
  ast * a = ast_alloc();
  a->tag = obj_ast;
  a->op.obj = obj_alloc();
  return a;
}

ast * make_int(char * n, long v) {
  ast * a = astobj_alloc();
  a->op.obj->name = n;
  a->op.obj->type = int_sym;
  a->op.obj->val.Int = v;
  return a;
}
ast * make_dec(char * n, double v) {
  ast * a = astobj_alloc();
  a->op.obj->name = n;
  a->op.obj->type = dec_sym;
  a->op.obj->val.Dec = v;
  return a;
}
ast * make_str(char * n, str * v) {
  ast * a = astobj_alloc();
  a->op.obj->name = n;
  a->op.obj->type = str_sym;
  a->op.obj->val.Str = v;
  return a;
}
ast * make_bool(char * n, int v) {
  ast * a = astobj_alloc();
  a->op.obj->name = n;
  a->op.obj->type = bool_sym;
  a->op.obj->val.Bool = v;
  return a;
}
ast * make_map(char * n, MAP v) {
  ast * a = astobj_alloc();
  a->op.obj->name = n;
  a->op.obj->type = map_sym;
  a->op.obj->val.Map = v;
  return a;
}
ast * make_list(char * n, list * v){
  ast * a = astobj_alloc();
  a->op.obj->name = n;
  a->op.obj->type = list_sym;
  a->op.obj->val.List = v;
  return a;
}
ast * make_func(char * n, func * v){
  ast * a = astobj_alloc();
  a->op.obj->name = n;
  a->op.obj->type = map_sym;
  a->op.obj->val.Func = v;
  return a;
}
//ast * make_obj(char * n, class * c);
