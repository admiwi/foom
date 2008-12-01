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
    map_native = 1<<9,
    map_member = 1<<10
} map_flags;

#define MAP map_node **

typedef struct _map_key {
  char text[ARB_LEN];
  struct _map_key * next;
} map_key;

typedef struct _map_node {
  struct _map * next;
  map_key * key;
  void * data;
  map_flags flags;
} map_node;

typedef struct _map {
  MAP nodes;
  map_key * keys;
} map;


union charint {
  char c[INT_SZ];
  int i;
};

map * map_new();
unsigned int hash(char*);
int map_set(map *, char*, void*, int);
void map_del(map *, char*, int);
map_node * map_get(map *, char*);

#endif
