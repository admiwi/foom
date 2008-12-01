#include "foom_typedefs.h"
#ifndef _FOOM_AST_
#define _FOOM_AST_

ast_list * new_astlist();
ast * new_astnode();
object * new_object();
ast * make_binary_op(Symbol s, ast * l, ast * r);
ast * make_unary_op(Symbol s, ast * a);
ast * ast_list_wrapper(ast_list * al);
//long Int;
//double Dec;
//str Str;
//int Bool;
//MAP Map;
//list List;
//func Func;
ast * make_int(char * n, long v);
ast * make_dec(char * n, double v);
ast * make_str(char * n, str * v);
ast * make_bool(char * n, int v);
ast * make_map(char * n, map * v);
ast * make_list(char * n, list * v);
ast * make_func(char * n, func * v);
ast * make_closure(char * n, ast_list *);
ast * make_obj(char * n);

#endif
