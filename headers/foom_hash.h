#include "foom.h"
#ifndef _FOOM_MAP_
#define _FOOM_MAP_

#define HASH_SZ 2111
#define INT_SZ 4

typedef enum {
    map_string = 1<<0,
    map_integer = 1<<1,
    map_float = 1<<2,
    map_object = 1<<3,
    map_keyword = 1<<4,
    map_unary = 1<<5,
    map_binary = 1<<6,
    map_grammer = 1<<7,
    map_immutable = 1<<8,
    map_native = 1<<9
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

#endif
