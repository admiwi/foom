#include "foom.h"
#ifndef _FOOM_MAP_
#define _FOOM_MAP_

#define HASH_SZ 2111
#define INT_SZ 4

typedef enum {
    map_string = 1,
    map_integer = 2,
    map_float = 4,
    map_object = 8,
    map_keyword = 16,
    map_unary = 32,
    map_binary = 64,
    map_grammer = 128,
    map_immutable = 256,
    map_native = 512
} map_flags;

#define MAP map **

typedef struct _map {
  struct _map * next;
  char key[ARB_LEN];
  void * data;
  map_flags flags;
} map;

union charint {
  char c[INT_SZ];
  int i;
};

MAP map_new();
unsigned int hash(char*);
int map_set(MAP, char*, void*, int);
void map_del(MAP, char*, int);
map * map_get(MAP, char*);
//object * scope_get(scope *, char *);
#endif
