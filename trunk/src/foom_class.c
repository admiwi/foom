#include "foom_class.h"
#include "foom_ast.h"

MAP native_classes;
extern char* _symbols_[];

void add_member(object * c, object * o) {
  map_set(c->members, o->name, o, map_object);
}

object * native_wrapper(void * nf, int flags) {
  object * f = new_func();
  f->null = false;
  f->val.Func->flags = flags;
  if(flaged(flags, func_binary))
    f->val.Func->f.bfunc = (bFuncP*)nf;
  if(flaged(flags, func_unary))
    f->val.Func->f.ufunc = (uFuncP*)nf;
  return f;
}

object * resolve_member_map(object * o, map * v, object * arg) {
  if(flaged(v->flags, map_native|map_unary)) {
    uFuncP ufp = v->data;
    return ufp(o);
  } else if(flaged(v->flags, map_native|map_binary) && arg) {
    bFuncP bfp = v->data;
    return bfp(o, arg);
  }
    return new_object();
}

object * get_member_object(object * o, char * n) {
  map * v = map_get(o->members, n);
  if(!v && o->class)
    v = map_get(o->class->members, n);
  if(!v) {
    fprintf(stderr,"member %s not found, returning null\n", n);
    return new_object();
  }
  return v->data;
}
object * get_member_getter(object * o, char * n) {
  object * ro;
  char gn[ARB_LEN] = "get_";
  strcat(gn, n);
  ro = get_member_object(o, gn);
  if(!ro->null) {
    return func_call(ro, o, NULL);
  }
  return ro;
}

object * get_member_setter(object * o, char * n, object * arg) {
  object * ro;
  char gn[ARB_LEN] = "set_";
  strcat(gn, n);
  ro = get_member_object(o, gn);
  if(!ro->null) {
    return func_call(ro, o, arg);
  }
  return ro;
}


object * get_member(object * o, char * n) {
  object * ro;
  ro = get_member_getter(o, n);
  if(!ro->null) return ro;
  free(ro);
  return get_member_object(o,n);
}

object * set_member(object *o, char * n, object * arg) {
  object * ro;
  ro = get_member_setter(o, n, arg);
  return ro;
}

void add_static_member(object * c, object * o) {
  if(c->type == class_sym && c->val.Class) {
    map_set(c->val.Class->static_members, o->name, o, map_object);
  }
}

object * get_static_member(object * c, char * n) {
  if(c->type == class_sym && c->val.Class) {
    map * v = map_get(c->val.Class->static_members, n);
    if(v)
      return (object *)v->data;
    else
      return new_object(true);
  }
}

class * new_class(bool native) {
  class * c = malloc(sizeof(class));
  memset(c, 0, sizeof(class));
  c->native = native;
  return c;
}

object * cast(object * a, object * b) {

}

//native classes

void init_classes(scope * s) {
  native_classes = map_new();
  object * cls;
  //obj
  cls = obj_class();
  map_set(native_classes, cls->name, cls, map_object|map_immutable);
  map_set(s->symbols, cls->name, cls, map_object|map_immutable);
  //func
  cls = func_class();
  map_set(native_classes, cls->name, cls, map_object|map_immutable);
  map_set(s->symbols, cls->name, cls, map_object|map_immutable);
  //int
  cls = int_class();
  map_set(native_classes, cls->name, cls, map_object|map_immutable);
  map_set(s->symbols, cls->name, cls, map_object|map_immutable);
  //str
  cls = str_class();
  map_set(native_classes, cls->name, cls, map_object|map_immutable);
  map_set(s->symbols, cls->name, cls, map_object|map_immutable);
  //dec
  cls = dec_class();
  map_set(native_classes, cls->name, cls, map_object|map_immutable);
  map_set(s->symbols, cls->name, cls, map_object|map_immutable);
  //bool
  cls = bool_class();
  map_set(native_classes, cls->name, cls, map_object|map_immutable);
  map_set(s->symbols, cls->name, cls, map_object|map_immutable);
  //list
  cls = list_class();
  map_set(native_classes, cls->name, cls, map_object|map_immutable);
  map_set(s->symbols, cls->name, cls, map_object|map_immutable);
  //map
  cls = map_class();
  map_set(native_classes, cls->name, cls, map_object|map_immutable);
  map_set(s->symbols, cls->name, cls, map_object|map_immutable);
  //class
  /*
  cls = class_class();
  map_set(native_classes, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);
  map_set(s->symbols, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);
  */

}
