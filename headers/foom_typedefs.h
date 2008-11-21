#ifndef _FOOM_TYPEDEFS_
#define _FOOM_TYPEDEFS_

#include "foom_hash.h"
typedef enum { false, true } bool;
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
  char * sig;
  bool native;
  list * args;
  struct _class * ret_type;
} func;

typedef struct _str {
  int len;
  char * val;
} str;

typedef struct _class {
  bool native;
  MAP static_members;
} class;

typedef struct _object {
  char * name;
  Symbol type;
  struct _object * class;
  bool ref;
  bool null;
  union {
    class * Class;
    long Int;
    double Dec;
    str * Str;
    bool Bool;
    MAP Map;
    list * List;
    func * Func;
    //struct _object Obj;
  } val;
  MAP members;
} object;

typedef struct _symbol {
  char id[ARB_LEN];
  object * obj;
  struct _symbol * next;
} symbol;

typedef struct _scope {
  struct _scope *parent;
  map** symbols;
} scope;
typedef struct _ast {
  enum {
    binary_ast, unary_ast,
    obj_ast, func_args_ast,
    block_ast, id_ast
  } tag;
  scope * scp;
  union {
    object * obj;
    struct {
      Symbol oper;
      struct _ast * left;
      struct _ast * right;
    } binary;
    struct {
      Symbol oper;
      struct _ast * arg;
    } unary;
    struct {
      struct _ast_list * args;
    } call;
    struct {
      struct _ast_list * stmts;
    } block;
    char * Id;
  } op;
} ast;

typedef struct _ast_list {
  ast * node;
  struct _ast_list * next;
} ast_list;

typedef object *(*FuncP)(ast * op);
#endif
