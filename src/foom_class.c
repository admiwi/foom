#include "foom_class.h"
#include "foom_ast.h"

MAP native_classes;
extern char* _symbols_[];

void add_member(object * c, object * o) {
  map_set(c->members, o->name, o, MAP_OBJECT);
}

object * get_member(object * o, char * n) {
  object * mo = map_get(o->members, n);
  if(!mo && o->class) {
    mo = map_get(o->class->members, n);
    if(!mo) {
      fprintf(stderr,"member %s not found, created\n", n);
      mo = new_object();
    }
  }
  return mo;//(object *)map_get(c->members, n);
}

void add_static_member(object * c, object * o) {
  if(c->type == class_sym && c->val.Class) {
    map_set(c->val.Class->static_members, o->name, o, MAP_OBJECT);
  }
}

object * get_static_member(object * c, char * n) {
  if(c->type == class_sym && c->val.Class) {
    return (object *)map_get(c->val.Class->static_members, n);
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

  //int
  cls = int_class();
  map_set(native_classes, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);
  map_set(s->symbols, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);
  //str
  cls = str_class();
  map_set(native_classes, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);
  map_set(s->symbols, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);
  //dec
  cls = dec_class();
  map_set(native_classes, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);
  map_set(s->symbols, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);
  //bool
  cls = bool_class();
  map_set(native_classes, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);
  map_set(s->symbols, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);
  //func
  cls = func_class();
  map_set(native_classes, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);
  map_set(s->symbols, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);
  //list
  cls = list_class();
  map_set(native_classes, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);
  map_set(s->symbols, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);
  //map
  cls = map_class();
  map_set(native_classes, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);
  map_set(s->symbols, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);
  //obj
  cls = obj_class();
  map_set(native_classes, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);
  map_set(s->symbols, cls->name, cls, MAP_OBJECT|MAP_IMMUTABLE);

}
