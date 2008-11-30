#include "foom_typedefs.h"
#ifndef _FOOM_AST_
#define _FOOM_AST_

ast_list * new_astlist();
ast * new_astnode();
object * new_object();
ast * make_binary_op(Symbol s, ast * l, ast * r);
ast * make_unary_op(Symbol s, ast * a);
ast * make_call_args(scope *, ast_list * al);
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
ast * make_map(scope *, char * n, map * v);
ast * make_list(scope *, char * n, list * v);
ast * make_func(scope *, char * n, func * v);
ast * make_closure(scope *, char * n, ast_list *);
ast * make_obj(scope *, char * n);

object * evaluate(scope *, ast *);

#endif
