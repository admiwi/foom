#include "foom.h"
#include "foom_gram.h"
#include "foom_lex.h"

#if 0
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
  {id_sym, END},
  {"(", EXPR, ")", END},
  {CLOSURE, END}
};

char _declare_var[GLEN][GLEN][ARB_LEN] = {
  {TYPE, id_sym, END}
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

char _program[GLEN][GLEN][ARB_LEN] = {
  {STMTS, END}
};


MAP grammer = NULL;

void init_grammer() {
  grammer = new_map();
  map_set(grammer, "if", (void*)&_if_stmt, MAP_GRAMMER);
  map_set(grammer, "for", (void*)&_for_stmt, MAP_GRAMMER);
  map_set(grammer, "while", (void*)&_while_stmt, MAP_GRAMMER);
  map_set(grammer, "{", (void*)&_closure, MAP_GRAMMER);
  map_set(grammer, STMT, (void*)&_stmt, MAP_GRAMMER);
  map_set(grammer, CLOSURE, (void*)&_closure, MAP_GRAMMER);
  map_set(grammer, TERM, (void*)&_term, MAP_GRAMMER);
  map_set(grammer, EXPR, (void*)&_expr, MAP_GRAMMER);
}

#endif
token *cur_tok = NULL;
scope *global = NULL;
void gT();
void gE();
void gS();
void gProgram(token * t);

void printE(Symbol sym, char * e){
  extern char * _keywords[];
  printf("%s [Lex '%s' : line %d : Sym %d (kw '%s')]\n",
    e, 
    cur_tok->lexem, 
    cur_tok->line,
    sym,
    _keywords[sym]?_keywords[sym]:"none"
    );
}

int expect(Symbol sym) {
  if(sym == cur_tok->symbol)
    return 1;
  //add_error(ERR_ERROR, 0, cur_tok->line, 0sprintE(sym,"expecting token %d",sym), cur_tok->lexem);
  printE(sym,"tok err on ");
  return 0;
}

int next() { return !!(cur_tok = cur_tok->next); }

int accept(Symbol sym) {
  if(expect(sym)) {
    next();
    return 1; 
  }
  return 0;
}

void sIf() {
  if(accept(oparen_sym)) {
    gE();
    accept(cparen_sym);
    gS();
  } else {
    printE(cur_tok->symbol,"bad if");    
    next();
  }
}

void gT() {
  switch(cur_tok->symbol) {
    case id_sym: next();
      printE(cur_tok->symbol,"symbol");
      break;
    case integer_sym:
    case float_sym: next();
      printE(cur_tok->symbol,"number");
      break;
    case oparen_sym: next();
      printE(cur_tok->symbol,"(");
      gE();
      if(expect(cparen_sym))
        printE(cur_tok->symbol,")");
      break;
    default:
      printE(cur_tok->symbol,"error");
      next();
      break;
  }
}

int isOp() {
  switch(cur_tok->symbol) {
   case le_sym:
   case ge_sym:
   case lt_sym:
   case gt_sym:
   case neq_sym:
   case eq_sym:
   case assign_sym:
   case and_sym:
   case or_sym:
   case not_sym:
   case bang_sym:
   case plus_sym:
   case minus_sym:
   case star_sym:
   case carrot_sym:
   case andper_sym:
   case slash_sym:
   case tilda_sym:
   case bar_sym: next(); 
     printE(cur_tok->symbol,"operator");
     return 1;
     //next();
   default:
     return 0;
     //printE(sym,"error gOp");
  }
}


void gE() {
  gT();
  while(isOp()) {
    gT();
  }
}

void gS() {
  switch(cur_tok->symbol) {
    case obj_sym:
    case int_sym:
    case dec_sym:
    case bool_sym:
    case func_sym:
    case bin_sym:
    case list_sym:
    case map_sym: next();
      expect(id_sym);
      break;
    case if_sym: next();
      sIf();
      break;
    case while_sym:
    case switch_sym:
    case ocurly_sym: next();
      printE(cur_tok->symbol,"closure");
      while(cur_tok->symbol != ccurly_sym)
        gS();
      accept(ccurly_sym);
      break;
    case id_sym:
    case string_sym:
    case integer_sym:
    case float_sym:
      gE();
      break;
    default:
      printE(cur_tok->symbol,"invalid statement");
      next();
  }
}

void gProgram(token * t) {
  cur_tok = t;
  global = new_scope(NULL);
  while(cur_tok)
    gS();
}


