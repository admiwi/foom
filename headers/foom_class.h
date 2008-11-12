#include "foom.h"
#include "foom_ast.h"

#ifndef __FOOM_CLASS__
#define __FOOM_CLASS__

void add_member(object * c, object * o);

object * get_member(object * o, char * n);

void add_static_member(object * c, object * o);

object * get_static_member(object * c, char * n);

class * new_class(bool );

//native classes

void init_classes(scope * s);
#endif
