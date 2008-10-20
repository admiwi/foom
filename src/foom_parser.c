#include "foom.h"
#include "foom_lex.h"


// _if_statement_ = if <exp> <closure> [else _if_statement`_]
#if 0
ast * parse(token * tokchain) {
  ast * abtree = malloc(sizeof(ast));
  scope * s = new_scope(NULL);
  token * curtok = tokchain;
  
}

int match(char * s, token * t) {
  return !strcmp(t->lexem, s);
}

int expr(ast *st , scope * s, token * t){
  
}

int stmt(ast *st , scope * s, token * t){

}


int if_stmt(ast * st, scope * s, token * t) {
  if(match("if",t)) {
  }
  return 0;
}
void sym_integer(ast * st, scope * s, token * t) {
}
void sym_string(ast * st, scope * s, token * t) {
}

void expression(ast * st, scope * s, token * t) {
    
}
#endif
