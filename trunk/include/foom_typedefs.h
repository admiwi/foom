#ifndef _FOOM_TYPEDEFS_
#define _FOOM_TYPEDEFS_
typedef int funcp(char*,...);

typedef struct _attrib {
  char name[ARB_LEN];
  int type;
  struct _attrib * next;
} attrib;

typedef struct _token {
  char name[ARB_LEN];
  attrib *attr;
  funcp *func;
  char arg_map[ARB_LEN];
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
  symbol *symbols;
} scope;

#endif
