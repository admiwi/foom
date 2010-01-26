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
ast * make_int(char * n, long v, scope *s);
ast * make_dec(char * n, double v, scope *s);
ast * make_str(char * n, str * v, scope *s);
ast * make_bool(char * n, int v, scope *s);
ast * make_map(char * n, map * v, scope *s);
ast * make_list(char * n, list * v, scope *s);
ast * make_func(char * n, func * v, scope *s);
ast * make_obj(char * n, scope * s);
ast * make_closure(char * n, ast_list *);

#endif
