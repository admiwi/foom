#include "foom.h"
#ifndef _FOOM_MAP_
#define _FOOM_MAP_

#define HASH_SZ 2111
#define INT_SZ 4

#define MAP_IMMUTABLE (1<<0)
#define MAP_STRING    (1<<1)
#define MAP_INTEGER   (1<<2)
#define MAP_FLOAT     (1<<3)
#define MAP_OBJECT    (1<<4)
#define MAP_KEYWORD   (1<<5)

#define MAP_GRAMMER   (1<<6)

#define MAP map **

typedef struct _map {
  struct _map * next;
  char key[ARB_LEN];
  void * data;
  int flags;
} map;

union charint {
  char c[INT_SZ];
  int i;
};

map** new_map();
unsigned int hash(char*);
int map_set(MAP, char*, void*, int);
void map_del(MAP, char*, int);
void* map_get(MAP, char*);
#endif
