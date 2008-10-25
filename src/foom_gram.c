#include "foom.h"
#include "foom_gram.h"
#include "foom_lex.h"

token *cur_tok = NULL;
scope *global = NULL;
void gT();
void gE();
void gS();
void gProgram(token * t);

void printE(Symbol sym, char * e){
  extern char * _keywords[];
  if(cur_tok)
  printf("%s [Lex '%s' : line %d : Sym %d (kw '%s')]\n",
    e, 
    cur_tok->lexem, 
    cur_tok->line,
    sym,
    _keywords[sym]?_keywords[sym]:"none"
    );
  fflush(stdout);
}

int expect(Symbol sym) {
  if(cur_tok && sym == cur_tok->symbol)
    return 1;
  if(cur_tok)
    add_error(ERR_ERROR, 0, cur_tok->line, "expecting token", cur_tok->lexem);
  else
    add_error(ERR_ERROR, 0, -1, "out of tokens", 0);
  return 0;
}

int next() { return !!(cur_tok = cur_tok->next); }

int accept(Symbol sym) {
  if(expect(sym)) {
    printE(sym,"accept");
    return next(); 
  }
  return 0;
}

void sIf() {
  printE(cur_tok->symbol,"if");
  if(accept(oparen_sym)) {
    gE();
    accept(cparen_sym);
    gS();
  } else {
    if(cur_tok) {
      printE(cur_tok->symbol,"bad if");    
      if(!next()) return;
    }
  }
}

void gT() {
  switch(cur_tok->symbol) {
    case id_sym: 
      printE(cur_tok->symbol,"symbol");
      if(!next()) return;
      break;
    case integer_sym:
    case float_sym: 
      printE(cur_tok->symbol,"number");
      if(!next()) return;
      break;
    case oparen_sym: 
      printE(cur_tok->symbol,"(");
      if(!next()) return;
      gE();
      if(expect(cparen_sym))
        printE(cur_tok->symbol,")");
      break;
    default:
      printE(cur_tok->symbol,"error");
      if(!next()) return;
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
    case bar_sym: 
      printE(cur_tok->symbol,"operator");
      if(!next()) return 0;
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
    case ocurly_sym: 
      printE(cur_tok->symbol,"closure");
      if(!next()) return 0;
      while(cur_tok && cur_tok->symbol != ccurly_sym)
        gS();
      if(!accept(ccurly_sym)) return;
      break;
    case id_sym:
    case string_sym:
    case integer_sym:
    case float_sym:
      gE();
      break;
    default:
      printE(cur_tok->symbol,"invalid statement");
      if(!next()) return 0;
  }
}

void gProgram(token * t) {
  cur_tok = t;
  global = new_scope(NULL);
  while(cur_tok)
    gS();
}


