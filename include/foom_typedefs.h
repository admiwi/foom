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
  void * lexem;
  int type;
  int attr;
  struct _token * next;
} token;

typedef struct _string {
  char * str;
  int len;
} string;

typedef struct _list {
  struct _object * obj;
  struct _list * next;
  int type;
  int count;
} list;

typedef struct _class {
  int foo;  
} class;

typedef struct _object {
  long serial;
  int ntype;
  void * value;
  map ** members;
} object;

typedef struct _ast {
  object * obj;
  struct _ast * right;
  struct _ast * left;
} ast;

typedef struct _symbol {
  char id[ARB_LEN];
  object * obj;
  struct _symbol * next;
} symbol;

typedef struct _scope {
  struct _scope *parent;
  map** symbols;
} scope;

#endif
