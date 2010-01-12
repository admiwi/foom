#include "foom.h"
#include "foom_ast.h"

#ifndef __FOOM_CLASS__
#define __FOOM_CLASS__

void add_member(object * c, object * o);
void add_member_name(object * c, object * o, char *);

object * get_member(object * o, char * n);
object * set_member(object * o, char * n, object * arg);
object * native_wrapper(void * f, scope *, int);


void add_static_member(object * c, object * o);

object * get_static_member(object * c, char * n);

class * new_class(bool );

//native classes

void init_classes(scope * s);

//class functions
object * func_call(object *, object *, object *);
list * list_node();
bool bool_test(object * o);
#endif
