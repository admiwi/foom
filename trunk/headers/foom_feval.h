#include "foom.h"
#include "foom_ast.h"

void start_feval(ast * a, scope *);
void init_fevals();
object * feval(ast*, scope *);
