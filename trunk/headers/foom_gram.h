#include "foom_ast.h"
#ifndef _FOOM_GRAMMER_
#define _FOOM_GRAMMER_


#define GLEN 15

#define LASTG 0x20

typedef enum {
  pS_ok, pS_empty, pS_invalid, pS_error, pS_done

} pStatus;

ast * gProgram(token *, scope *);

#endif
