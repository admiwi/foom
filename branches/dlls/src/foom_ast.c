#include "foom_ast.h"
#include "foom_objects.h"

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

ast * make_obj(char * n, scope * s) {
  ast * a = new_astnode();
  a->tag = obj_ast;
  a->op.obj = new_object(s);

  return a;
}

ast * make_int(char * n, long v, scope * s) {
  ast * a = new_astnode();
  a->tag = obj_ast;
  a->op.obj = new_int(s);
  a->op.obj->name = n;
  a->op.obj->val.Int = v;

  return a;
}
ast * make_dec(char * n, double v, scope * s) {
  ast * a = new_astnode();
  a->tag = obj_ast;
  a->op.obj = new_dec(s);
  a->op.obj->name = n;
  a->op.obj->val.Dec = v;

  return a;
}
ast * make_str(char * n, str * v, scope * s) {
  ast * a = new_astnode();
  a->tag = obj_ast;
  a->op.obj = new_str(s);
  a->op.obj->name = n;
  a->op.obj->val.Str = v;

  return a;
}
ast * make_bool(char * n, int v, scope * s) {
  ast * a = new_astnode();
  a->tag = obj_ast;
  a->op.obj = new_bool(s);
  a->op.obj->name = n;
  a->op.obj->val.Bool = v;

  return a;
}
ast * make_map(char * n, map * v, scope * s) {
  ast * a = new_astnode();
  a->tag = obj_ast;
  a->op.obj = new_map(s);
  a->op.obj->name = n;
  a->op.obj->val.Map = v;

  return a;
}
ast * make_list(char * n, list * v, scope * s){
  ast * a = new_astnode();
  a->tag = obj_ast;
  a->op.obj = new_list(s);
  a->op.obj->name = n;
  a->op.obj->val.List = v;

  return a;
}

ast * ast_list_wrapper(ast_list * al){
  ast * a = new_astnode();
  a->tag = list_ast;
  a->op.call.args = al;

  return a;
}
//TODO  Need to make this different == it's not going to work very well as is.
ast * make_closure(char * n, ast_list * v){
  ast * a = new_astnode();
  a->tag = block_ast;
  a->op.block.stmts = v;

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
