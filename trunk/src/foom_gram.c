#include "foom.h"
#include "foom_gram.h"

#if 0
production * gen_if() {
  production * p = malloc(sizeof(production));
  int i = 0;
  char *** stff = malloc(sizeof(char*)*2);
  char *if1[] = {"if", "(", EXPR, ")", CLOSURE, END};
  char *end[] = {END};
  stff[i++] = if1;
  stff[i++] = end;
 // ["if", "(", EXPR, ")", CLOSURE, END];
  return p;
}
#endif
char _if_stmt[GLEN][GLEN][ARB_LEN] = {
  {"if", "(", EXPR, ")", CLOSURE, END},
  {"if", "(", EXPR, ")", STMT, END},
  {"if", "(", EXPR, ")", CLOSURE, "else", STMT, END},
  {"if", "(", EXPR, ")", STMT, "else", CLOSURE, END},
  {"if", "(", EXPR, ")", STMT, "else", STMT, END}
};
char _while_stmt[GLEN][GLEN][ARB_LEN] = {
  {"while", "(", EXPR, ")", STMT, END},
  {"while", "(", EXPR, ")", CLOSURE, END}
};

char _for_stmt[GLEN][GLEN][ARB_LEN] = {
  {"for", "(", EXPR, ",", EXPR, ",", EXPR, ")", STMT, END},
  {"for", "(", EXPR, ",", EXPR, ",", EXPR, ")", CLOSURE, END}
};

char _expr[GLEN][GLEN][ARB_LEN] = {
  {TERM},
  {TERM, OP, EXPR, END},
  {END}
};

char _term[GLEN][GLEN][ARB_LEN] = {
  {ID, END},
  {"(", EXPR, ")", END}
};

char _declare_var[GLEN][GLEN][ARB_LEN] = {
  {TYPE, ID, END}
};

char _closure[GLEN][GLEN][ARB_LEN] = {
  {"{", STMTS, "}", END}
};

char _stmt[GLEN][GLEN][ARB_LEN] = {
  {IF_STMT, END},
  {FOR_STMT, END},
  {WHILE_STMT, END},
  {CASE_STMT, END}
};

MAP grammer = NULL;

void init_grammer() {
  grammer = new_map();
  map_set(grammer, "if", (void*)&_if_stmt, MAP_GRAMMER);
  map_set(grammer, "for", (void*)&_for_stmt, MAP_GRAMMER);
  map_set(grammer, "while", (void*)&_while_stmt, MAP_GRAMMER);
  map_set(grammer, "{", (void*)&_closure, MAP_GRAMMER);
}

void statement(token * tok) {
  
}




