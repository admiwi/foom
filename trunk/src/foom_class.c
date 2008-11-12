#include "foom_class.h"

void add_member(class * c, object * o) {
  map_set(c->members, o->name, o, MAP_OBJECT);
}

object * get_member(object * o, char * n) {
  //class c;
  //c = o->klass;
  fprintf(stderr,"member %s not found\n", n);
  return NULL;//(object *)map_get(c->members, n);
}

void add_static_member(class * c, object * o) {
  map_set(c->static_members, o->name, o, MAP_OBJECT);
}

object * get_static_member(class * c, char * n) {
  return (object *)map_get(c->static_members, n);
}

class * new_class(char * name) {
  class * c = malloc(sizeof(class));
  memset(c, 0, sizeof(class));
  return c;
}

//native classes

void initialize_classes(scope * s) {

}

object * int_class() {
  class * c = new_class('int');
  object * o = new_object();
  o->type = class_sym;
  o->name = "int";

}

