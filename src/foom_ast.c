#include "foom_ast.h"
#include "foom_objects.h"

ast_list * new_astlist() {
  ast_list * al = malloc(sizeof(ast_list));
  memset(al, 0, sizeof(ast_list));
  return al;
}

ast * new_astnode(scope * s) {
  ast * a = malloc(sizeof(ast));
  memset(a, 0, sizeof(ast));
  a->scp = s;
  return a;
}

ast * get_obj(scope * cscope, char * n){
  ast * a;
  object * o = scope_get(cscope, n);
  if(!o) {
    fprintf(stderr, "%s is not defined\n", n);
    return NULL;
  }
  a = new_astnode(cscope);
  a->tag = obj_ast;
  a->op.obj = o;
  return a;
}

ast * make_obj(scope * cscope, char * n) {
  ast * a = new_astnode(cscope);
  a->tag = obj_ast;
  a->op.obj = new_object();
  a->scp = cscope;
  map_set(cscope->symbols, a->op.obj->name, a->op.obj, map_object);
  return a;
}

ast * make_int(scope * cscope, char * n, long v) {
  ast * a = new_astnode(cscope);
  a->tag = obj_ast;
  a->op.obj = new_int();
  a->op.obj->name = n;
  a->op.obj->val.Int = v;
  a->scp = cscope;
  map_set(cscope->symbols, a->op.obj->name, a->op.obj, map_object);
  return a;
}
ast * make_dec(scope * cscope, char * n, double v) {
  ast * a = new_astnode(cscope);
  a->tag = obj_ast;
  a->op.obj = new_dec();
  a->op.obj->name = n;
  a->op.obj->val.Dec = v;
  a->scp = cscope;
  map_set(cscope->symbols, a->op.obj->name, a->op.obj, map_object);
  return a;
}
ast * make_str(scope * cscope, char * n, str * v) {
  ast * a = new_astnode(cscope);
  a->tag = obj_ast;
  a->op.obj = new_str();
  a->op.obj->name = n;
  a->op.obj->val.Str = v;
  a->scp = cscope;
  map_set(cscope->symbols, a->op.obj->name, a->op.obj, map_object);
  return a;
}
ast * make_bool(scope * cscope, char * n, int v) {
  ast * a = new_astnode(cscope);
  a->tag = obj_ast;
  a->op.obj = new_bool();
  a->op.obj->name = n;
  a->op.obj->val.Bool = v;
  a->scp = cscope;
  map_set(cscope->symbols, a->op.obj->name, a->op.obj, map_object);
  return a;
}
ast * make_map(scope * cscope, char * n, map * v) {
  ast * a = new_astnode(cscope);
  a->tag = obj_ast;
  a->op.obj = new_map();
  a->op.obj->name = n;
  a->op.obj->val.Map = v;
  a->scp = cscope;
  map_set(cscope->symbols, a->op.obj->name, a->op.obj, map_object);
  return a;
}
ast * make_list(scope * cscope, char * n, list * v){
  ast * a = new_astnode(cscope);
  a->tag = obj_ast;
  a->op.obj = new_list();
  a->op.obj->name = n;
  a->op.obj->val.List = v;
  a->scp = cscope;
  map_set(cscope->symbols, a->op.obj->name, a->op.obj, map_object);
  return a;
}
ast * make_func(scope * cscope, char * n, func * v){
  ast * a = new_astnode(cscope);
  a->tag = obj_ast;
  a->op.obj = new_func();
  a->op.obj->name = n;
  a->op.obj->val.Func = v;
  a->scp = cscope;
  map_set(cscope->symbols, a->op.obj->name, a->op.obj, map_object);
  return a;
}
ast * make_call_args(scope * cscope, ast_list * al){
  ast * a = new_astnode(cscope);
  a->tag = func_args_ast;
  a->op.call.args = al;
  a->scp = cscope;
  //map_set(cscope->symbols, a->op.obj->name, a->op.obj, map *_OBJECT);
  return a;
}
//TODO  Need to make this different == it's not going to work very well as is.
ast * make_closure(scope * cscope, char * n, ast_list * v){
  ast * a = new_astnode(cscope);
  a->tag = block_ast;
  a->op.block.stmts = v;
  a->scp = cscope;
  //map_set(cscope->symbols, a->op.obj->name, a->op.obj, map *_OBJECT);
  return a;
}

ast * make_binary_op(Symbol s, ast * l, ast * r) {
  ast * a = new_astnode(NULL);
  a->tag = binary_ast;
  a->op.binary.left = l;
  a->op.binary.right = r;
  a->op.binary.oper = s;
  return a;
}
ast * make_unary_op(Symbol s, ast * ar){
  ast * a = new_astnode(NULL);
  a->tag = unary_ast;
  a->op.unary.arg = ar;
  a->op.unary.oper = s;
  return a;
}
