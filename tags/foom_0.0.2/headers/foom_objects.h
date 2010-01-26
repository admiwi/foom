#include "foom.h"
#ifndef __FOOM_OBJECTS__
#define __FOOM_OBJECTS__

object * new_object(scope*);
object * new_int(scope*);
object * new_str(scope*);
object * new_dec(scope*);
object * new_map(scope*);
object * new_list(scope*);
object * new_bool(scope*);
object * new_func(scope*);
object * find_obj(Symbol s,scope *);
#endif
