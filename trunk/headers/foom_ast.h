#include "foom_typedefs.h"
#ifndef _FOOM_AST_
#define _FOOM_AST_

typedef struct _ast {
  enum {
    binary_ast, unary_ast,
    obj_ast, func_call_ast,
    block_ast, id_ast
  } tag;
  scope * scp;
  union {
    object * obj;
    struct {
      Symbol oper;
      struct _ast * left;
      struct _ast * right;
    } binary;
    struct {
      Symbol oper;
      struct _ast * arg;
    } unary;
    struct {
      object * obj;
      struct _ast_list * arguments;
    } call;
    struct {
      struct _ast_list * stmts;
    } block;
    char * Id;
  } op;
} ast;

typedef struct _ast_list {
  ast * node;
  struct _ast_list * next;
} ast_list;

ast_list * new_astlist();
ast * new_astnode();
object * new_object();
ast * make_binary_op(Symbol s, ast * l, ast * r);
ast * make_unary_op(Symbol s, ast * a);
ast * make_call(scope *, char * fn, ast_list * al);
//long Int;
//double Dec;
//str Str;
//int Bool;
//MAP Map;
//list List;
//func Func;
ast * make_int(scope *, char * n, long v);
ast * make_dec(scope *, char * n, double v);
ast * make_str(scope *, char * n, str * v);
ast * make_bool(scope *, char * n, int v);
ast * make_map(scope *, char * n, MAP v);
ast * make_list(scope *, char * n, list * v);
ast * make_func(scope *, char * n, func * v);
ast * make_closure(scope *, char * n, ast_list *);
ast * make_obj(scope *, char * n);

object * evaluate(scope *, ast *);

#endif
