#ifndef _FOOM_TYPEDEFS_
#define _FOOM_TYPEDEFS_

#include "foom_hash.h"

typedef struct _parse_pkg {
  char filename[ARB_LEN];
  FILE * file;
  char buf[BUFSZ];
  char backbuf[ARB_LEN];
  int i;
  char c;
  int count;
  int left;
  int line;
} parse_pkg;

typedef struct _error {
  int type;
  char file[ARB_LEN];
  int line;
  char * what;
  char * where;
  struct _error * next;
} _error_;


typedef struct _attrib {
  char name[ARB_LEN];
  int type;
  struct _attrib * next;
} attrib;

typedef struct _token {
  char * lexem;
  Symbol symbol;
  int line;
  int pos;
  struct _token * prev;
  struct _token * next;
} token;

typedef struct _list {
  struct _object * obj;
  struct _list * next;
  int count;
} list;

typedef struct _func {
  list * args;
  struct _object * ret_type;
} func;

typedef struct _str {
  int len;
  char * val;
} str;

typedef struct _class {
  char * name;
  MAP members;
  MAP static_members;
} class;

typedef struct _object {
  char * name;
  Symbol type;
  class * klass;
  int refval;  // pass by ref or val
  union {
    class * Class;
    long Int;
    double Dec;
    str * Str;
    int Bool;
    MAP Map;
    list * List;
    func * Func;
    //struct _object Obj;
  } val;
  MAP members;
} object;

typedef int(*FuncP)(object * ret , object * a1, object * a2, object * a3, object * a4, object * a5);

typedef struct _symbol {
  char id[ARB_LEN];
  object * obj;
  struct _symbol * next;
} symbol;

typedef struct _scope {
  struct _scope *parent;
  map** symbols;
} scope;

typedef struct _prod_path {
  char ** prod;
} prod_path;

typedef struct _prod {
  char ** path;
  prod_path * paths[ARB_LEN];
} production;


#endif
