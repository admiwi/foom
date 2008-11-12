#include "foom_ast.h"


object * new_object() {
  object * o = malloc(sizeof(object));
  memset(o, 0, sizeof(object));
  return o;
}

ast_list * new_astlist() {
  ast_list * al = malloc(sizeof(ast_list));
  memset(al, 0, sizeof(ast_list));
  return al;
}

ast * new_astnode() {
  ast * a = malloc(sizeof(ast));
  memset(a, 0, sizeof(ast));
  return a;
}

ast * new_astobj() {
  ast * a = new_astnode();
  a->tag = obj_ast;
  a->op.obj = new_object();
  return a;
}



ast * get_obj(scope * cscope, char * n){
  ast * a;
  object * o = scope_get(cscope, n);
  if(!o) {
    fprintf(stderr, "%s is not defined\n", n);
    return NULL;
  }
  a = new_astobj();
  a->tag = id_ast;
  a->op.obj = o;
  return a;
}

ast * make_obj(scope * cscope, char * n) {
  ast * a = new_astobj();
  a->op.obj->name = n;
  a->op.obj->type = obj_sym;
  map_set(cscope->symbols, a->op.obj->name, a->op.obj, MAP_OBJECT);
  return a;
}

ast * make_int(scope * cscope, char * n, long v) {
  ast * a = new_astobj();
  a->op.obj->name = n;
  a->op.obj->type = int_sym;
  a->op.obj->val.Int = v;
  map_set(cscope->symbols, a->op.obj->name, a->op.obj, MAP_OBJECT);
  return a;
}
ast * make_dec(scope * cscope, char * n, double v) {
  ast * a = new_astobj();
  a->op.obj->name = n;
  a->op.obj->type = dec_sym;
  a->op.obj->val.Dec = v;
  map_set(cscope->symbols, a->op.obj->name, a->op.obj, MAP_OBJECT);
  return a;
}
ast * make_str(scope * cscope, char * n, str * v) {
  ast * a = new_astobj();
  a->op.obj->name = n;
  a->op.obj->type = str_sym;
  a->op.obj->val.Str = v;
  map_set(cscope->symbols, a->op.obj->name, a->op.obj, MAP_OBJECT);
  return a;
}
ast * make_bool(scope * cscope, char * n, int v) {
  ast * a = new_astobj();
  a->op.obj->name = n;
  a->op.obj->type = bool_sym;
  a->op.obj->val.Bool = v;
  map_set(cscope->symbols, a->op.obj->name, a->op.obj, MAP_OBJECT);
  return a;
}
ast * make_map(scope * cscope, char * n, MAP v) {
  ast * a = new_astobj();
  a->op.obj->name = n;
  a->op.obj->type = map_sym;
  a->op.obj->val.Map = v;
  map_set(cscope->symbols, a->op.obj->name, a->op.obj, MAP_OBJECT);
  return a;
}
ast * make_list(scope * cscope, char * n, list * v){
  ast * a = new_astobj();
  a->op.obj->name = n;
  a->op.obj->type = list_sym;
  a->op.obj->val.List = v;
  map_set(cscope->symbols, a->op.obj->name, a->op.obj, MAP_OBJECT);
  return a;
}
ast * make_func(scope * cscope, char * n, func * v){
  ast * a = new_astobj();
  a->op.obj->name = n;
  a->op.obj->type = map_sym;
  a->op.obj->val.Func = v;
  map_set(cscope->symbols, a->op.obj->name, a->op.obj, MAP_OBJECT);
  return a;
}
ast * make_call(scope * cscope, char * fn, ast_list * al){
  ast * a = new_astnode();
  a->tag = func_call_ast;
  a->op.call.obj = new_object();
  a->op.call.obj->name = fn;
  a->op.call.arguments = al;
  //map_set(cscope->symbols, a->op.obj->name, a->op.obj, MAP_OBJECT);
  return a;
}
//TODO  Need to make this different == it's not going to work very well as is.
ast * make_closure(scope * cscope, char * n, ast_list * v){
  ast * a = new_astnode();
  a->tag = block_ast;
  a->op.block.stmts = v;
  //map_set(cscope->symbols, a->op.obj->name, a->op.obj, MAP_OBJECT);
  return a;
}

ast * make_binary_op(Symbol s, ast * l, ast * r) {
  ast * a = new_astnode();
  a->tag = binary_ast;
  a->op.binary.left = l;
  a->op.binary.right = r;
  a->op.binary.oper = s;
  return a;
}
ast * make_unary_op(Symbol s, ast * ar){
  ast * a = new_astnode();
  a->tag = unary_ast;
  a->op.unary.arg = ar;
  a->op.unary.oper = s;
  return a;
}
//ast * make_call(char * fn, ast_list * al);

object * eval(scope * cs, ast * a) {
  object * o = new_object();
  switch(a->tag) {
    case binary_ast:
    case unary_ast:
    case obj_ast:

    case func_call_ast:
    default:
      return;
  }
}



