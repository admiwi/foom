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
  char * lexem;
  Symbol symbol;
  int line;
  int pos;
  struct _token * prev;
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

typedef struct _ast_node {
  object * obj;
  struct _ast * right;
  struct _ast * left;
} ast_node;

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
