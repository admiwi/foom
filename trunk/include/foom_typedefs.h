#ifndef _FOOM_TYPEDEFS_
#define _FOOM_TYPEDEFS_

#include "foom_hash.h"

typedef int funcp(char*,...);

typedef struct _error {
  int type;
  char file[ARB_LEN];
  int line;
  char what[ARB_LEN];
  char where[ARB_LEN];
  struct _error * next;
} _error_;


typedef struct _attrib {
  char name[ARB_LEN];
  int type;
  struct _attrib * next;
} attrib;

typedef struct _token {
  void * data;
  int type;
  int attr;
  funcp *func;
  char args[ARB_LEN];
  struct _token * next;
} token;

typedef struct _object {
  char id[ARB_LEN];
} object;

typedef struct _symbol {
  char name[ARB_LEN];
  object * obj;
  struct _symbol * next;
} symbol;

typedef struct _scope {
  struct _scope *parent;
  map** symbols;
} scope;

#endif
