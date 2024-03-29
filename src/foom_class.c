#include "foom_class.h"
#include "foom_objects.h"
#include "foom_ast.h"
#include "foom_classes.h"

extern char* _symbols_[];

void add_member(object * s, object * o) {
  add_member_name(s, o, o->name);
}

void add_member_name(object * s, object * o, char * n) {
  map_set(s->members, n, o, map_member);
}

object * native_wrapper(void * nf, scope * s, int flags) {
  char n[ARB_LEN];
  sprintf(n, "native_func%x", (int)nf);
  return nnative_wrapper(nf, s, n, flags);
}

object * nnative_wrapper(void * nf, scope * s, const char * n, int flags) {
  object * f = new_func(s);
  f->name = strdup(n);
  f->null = false;
  f->val.Func->flags = flags;
  if(flaged(flags, func_binary))
    f->val.Func->f.bfunc = (bFuncP*)nf;
  if(flaged(flags, func_unary))
    f->val.Func->f.ufunc = (uFuncP*)nf;
  return f;
}

object * get_member_object(object * o, char * n) {
  map_node * v = map_get(o->members, n);
  if(!v && o->class)
    v = map_get(o->class->members, n);
  return v ? v->data : NULL;
}
object * get_member_getter(object * o, char * n) {
  object * ro;
  char gn[ARB_LEN] = "get_";
  strcat(gn, n);
  ro = get_member_object(o, gn);
  if(ro) {
    return func_call(ro, o, NULL);
  }
  return NULL;
}

object * get_member_setter(object * o, char * n, object * arg) {
  object * sf, *ro;
  char gn[ARB_LEN] = "set_";
  strcat(gn, n);
  sf = get_member_object(o, gn);
  if(sf) {
    ro = func_call(sf, o, arg);
    return ro;
  }
  return new_object(o->scp);
}

object * get_member(object * o, char * n) {
  object * ro;
  ro = get_member_getter(o, n);
  if(ro) return ro;
  ro = get_member_object(o, n);
  if(ro) return ro;
  fprintf(stderr,"error: '%s' is not a member of %s\n", n, o->name);
  return NULL;
}

object * set_member(object *o, char * n, object * arg) {
  object * ro;
  ro = get_member_setter(o, n, arg);
  if(ro) return ro;
  return new_object(o->scp);
}

void add_static_member(object * c, object * o) {
  if(c->type == class_sym && c->val.Class) {
    map_set(c->val.Class->static_members, o->name, o, map_object);
  }
}

object * get_static_member(object * c, char * n) {
  if(c->type == class_sym && c->val.Class) {
    map_node * v = map_get(c->val.Class->static_members, n);
    if(v)
      return (object *)v->data;
  }
  return new_object(c->scp);
}

class * new_class(bool native) {
  class * c = malloc(sizeof(class));
  memset(c, 0, sizeof(class));
  c->native = native;
  return c;
}

object * cast(object * a, object * b) {
  return NULL;
}

//native classes

void init_classes(scope * s) {
  init_obj_class(s);
  init_func_class(s);
  init_int_class(s);
  init_str_class(s);
  init_dec_class(s);
  init_bool_class(s);
  init_list_class(s);
  init_map_class(s);
  //init_class_class();
}
