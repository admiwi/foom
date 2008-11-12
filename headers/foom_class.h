#include "foom.h"
#include "foom_ast.h"

#ifndef __FOOM_CLASS__
#define __FOOM_CLASS__

void add_member(class * c, object * o);

object * get_member(object * o, char * n);

void add_static_member(class * c, object * o);

object * get_static_member(class * c, char * n);

class * new_class(char * name);

//native classes

void initialize_classes(scope * s);
object * int_class();

#endif
