#ifndef _FOOM_GRAMMER_
#define _FOOM_GRAMMER_


#define GLEN 15

#define LASTG 0x20

typedef enum {
  pS_ok, pS_empty, pS_invalid, pS_error
  
} pStatus;

pStatus gProgram(token *);
#endif
