#include "foom.h"
#include "foom_hash.h"

map** new_map() {
  map** m = malloc(sizeof(map)*HASH_SZ);
  memset(m, 0, sizeof(map)*HASH_SZ);
  return m;
}

unsigned int hash(char* key) {
  unsigned int i, hv=0;
  union charint ic;
  ic.i = 0;

  for(i=0;i<strlen(key);i+=INT_SZ) {
    strncpy(ic.c, key + i, INT_SZ);
    hv += ic.i;
  }
  return hv % HASH_SZ;
}

void map_set(map** mtab, char* key, void* data) {
  unsigned int hv = hash(key);
  map * m = malloc(sizeof(map));
  map * cur;
  void* td;
  strcpy(m->key, key);
  m->data = data;
  m->next = 0;
  if(!mtab[hv])
    mtab[hv] = m;
  else {
    cur = mtab[hv];
    do {
      if(!strcmp(cur->key, m->key)) {
        td = cur->data;
        cur->data = m->data;
        free(m);
        free(td);
        return;
      }
      cur = cur->next;
    }while(cur->next);
    cur->next = m;
  }
}

map* _map_del(map*,char*);

void map_del(map** mtab, char* key) {
  unsigned int hv = hash(key);
  if(!mtab[hv])
    return;
  mtab[hv] = _map_del(mtab[hv], key);
}

map* _map_del(map* m, char * key) {
  map* t;
  if(!strcmp(m->key, key)){
    t = m->next;
    free(m->data);
    free(m);
    return t;
  }
  if(m->next)
    m->next = _map_del(m->next, key);  
  return m;
}

void* map_get(map** mtab, char* key) {
  unsigned int hv = hash(key);
  map * cur;
  if(!mtab[hv])
    return NULL;
  cur = mtab[hv];
  do {
    if(!strcmp(cur->key, key))
      return cur->data;
    cur = cur->next;
  } while(cur->next);
  return NULL;
}

