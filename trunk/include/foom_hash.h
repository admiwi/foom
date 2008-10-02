#ifndef _FOOM_MAP_
#define _FOOM_MAP_

#define HASH_SZ 2111
#define INT_SZ 4

typedef struct _map {
  struct _map * next;
  char key[ARB_LEN];
  void * data;
} map;

union charint {
  char c[INT_SZ];
  int i;
};

map** new_map();
unsigned int hash(char*);
void map_set(map**, char*, void*);
void map_del(map**, char*);
void* map_get(map**, char*);
#endif
