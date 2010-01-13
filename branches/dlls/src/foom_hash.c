#include "foom.h"
#include "foom_hash.h"

map * map_new() {
  map * m = malloc(sizeof(map));
  memset(m, 0, sizeof(map));
  m->nodes = malloc(sizeof(map_node)*HASH_SZ);
  memset(m->nodes, 0, sizeof(map_node)*HASH_SZ);
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

int map_set(map * mtab, char* k, void* data, int flags) {
  unsigned int hv = hash(k);

  map_node * m = malloc(sizeof(map_node));
  memset(m, 0, sizeof(map_node));
  map_node * cur;
  map_key * key = malloc(sizeof(map_key));
  memset(key, 0, sizeof(map_key));
  key->node = m;
  void* td;
  if(!mtab)
    mtab = map_new();
  strcpy(key->text, k);
  m->data = data;
  m->flags = flags;
  m->next = 0;
  m->key = key;
  key->next = mtab->keys;
  mtab->keys = key;
  if(!mtab->nodes[hv]) {
    mtab->nodes[hv] = m;
    return 0;
  }
  else {
    cur = mtab->nodes[hv];
    do {
      if(!strcmp(cur->key->text, m->key->text)) {
        if(!flaged(cur->flags, map_immutable)) {
          fprintf(stderr, "map_overwrite %s\n", m->key->text);
          td = cur->data;
          cur->data = m->data;
          cur->flags = m->flags;
          free(td);
        }
        free(m);
        return 0;
      }
      if(!cur->next) {
        cur->next = m;
        break;
       }
       cur = cur->next;
    }while(true);
    cur->next = m;
  }
  return 1;
}

map_node* _map_del(map*, map_node*,char*, bool);

void map_del(map * mtab, char* k, int deldata) {
  unsigned int hv = hash(k);
  if(!mtab->nodes[hv])
    return;
  mtab->nodes[hv] = _map_del(mtab, mtab->nodes[hv], k, deldata);
}

void free_key(map * m, map_key * k) {
  map_key * tk, *ck;
  ck = m->keys;
  do {
    if(ck->next == k) {
      tk = ck->next;
      ck->next = tk->next;
      free(tk);
      return;
    }
  } while(ck = ck->next);
}

map_node* _map_del(map * mp, map_node* m, char * key, bool deldata) {
  map_node* tm;
  if(!strcmp(m->key->text, key)){
    tm = m->next;
    if(deldata)
      free(m->data);
    free_key(mp, m->key);
    free(m);
    return tm;
  }
  if(m->next)
    m->next = _map_del(mp, m->next, key, deldata);
  return m;
}

map_node * map_get(map * mtab, char* k) {
  unsigned int hv = hash(k);
  map_node * cur;
  if(!mtab) {
    fprintf(stderr, "uninitialized map looking for key %s\n", k);
    return NULL;
  }
  if(!mtab->nodes[hv]) {
    //fprintf(stderr, "no nodes for hash %d, %s\n", hv, k);  may be in parent
    return NULL;
  }
  cur = mtab->nodes[hv];
  while(cur) {
    if(!strcmp(cur->key->text, k))
      return cur;
    cur = cur->next;
  };
  return NULL;
}

void print_map(map * m) {
  int i;
  for(i=0;i<HASH_SZ;++i) {
    map_node * n = m->nodes[i];
    printf("box %d:\n", i);
    while(n) {
      printf("  %s -> %s\n", n->key->text, ((object*)(n->data))->name);
      n=n->next;
    }
  }
}

scope * new_scope(scope *par) {
  scope * s = malloc(sizeof(scope));
  s->parent = par;
  s->symbols = map_new();
  return s;
}

object * scope_get(scope * s, char * key) {
  map_node * v = map_get(s->symbols, key);
  if(!v && s->parent)
      return scope_get(s->parent, key);
  if(v) return (object *)v->data;
  return NULL;
}
void scope_set(scope * s, object * o, map_flags f) {
  map_set(s->symbols, o->name, o, map_object|f);
}

