#include "foom.h"
#ifndef __FOOM_OBJECTS__
#define __FOOM_OBJECTS__

object * new_object();
object * new_int();
object * new_str();
object * new_dec();
object * new_map();
object * new_list();
object * new_bool();
object * new_func();
object * find_obj(Symbol s);
#endif
