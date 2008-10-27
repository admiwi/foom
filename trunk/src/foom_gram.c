#include "foom.h"
#include "foom_gram.h"
#include "foom_lex.h"

#define EChk(A) if((A) == pS_empty) return pS_empty

token *prev_tok = NULL;
token *cur_tok = NULL;
scope *global = NULL;
pStatus gT();
pStatus gE();
pStatus gTE();
pStatus gS();

int indent;

void printE(int line, Symbol sym, char * e){
  extern char * _keywords[];
  int i = indent;
  if(indent < 0) indent = 0;
  if(!cur_tok) return;
  while(i-- >= 0) { printf("  "); }
  printf("%s [%d: '%s' %d ] from line %d\n",
    e, 
    cur_tok->line,
    cur_tok->lexem, 
    sym,
    line
  );
}

pStatus expect(int line, Symbol sym) {
  if(cur_tok && sym == cur_tok->symbol) return pS_ok;
  if(cur_tok) {
    printE(line, sym, "!");
    return pS_invalid;
  }
  add_error(ERR_ERROR, 0, -1, "out of tokens", 0);
  return pS_empty;
}

pStatus next() { 
  prev_tok = cur_tok;
  cur_tok = cur_tok->next;
  return (cur_tok ? pS_ok : pS_empty);
}

pStatus accept(int line, Symbol sym) {
  pStatus s = expect(line, sym);
  switch(s) {
    case pS_ok:
      return next();
    default:
      return s;
  }
}

pStatus sClosure() {
  while(cur_tok->symbol != ccurly_sym) {
    EChk(gS());
  }
  return accept(__LINE__, ccurly_sym);
}

pStatus sIf() {
  switch(accept(__LINE__, oparen_sym)) {
    case pS_ok:
      EChk(gE());
      EChk(accept(__LINE__, cparen_sym));
      EChk(gS());
      return next();
    case pS_invalid:
      return next();
    case pS_empty:
      return pS_empty;
    case pS_error:
      return pS_error;
  }
  return pS_error;
}

    // [1] [1..-1] [a] [a..b] [a,b,c..d] [..b] [a..] 
pStatus eSubscript() {
  pStatus s = expect(__LINE__, osquare_sym);
  if(s != pS_ok) return s;
  printE(__LINE__,cur_tok->symbol,"-> subscript");
  EChk(next());
  indent++;
  EChk(gTE());
  indent--;
  printE(__LINE__,cur_tok->symbol,"-> subscript");
  switch(expect(__LINE__, csquare_sym)) {
    case pS_ok: 
      printE(__LINE__,cur_tok->symbol,"subs ]");
      EChk(next());
      return pS_error;
    case pS_invalid: return pS_invalid;
    default: 
      printf("should never get here %d\n",__LINE__);
      return pS_error;
  }

}

pStatus gT() {
  pStatus s;
  switch(cur_tok->symbol) {
    case id_sym: 
      printE(__LINE__,cur_tok->symbol,"symbol");
      EChk((s=next()));
      EChk(eSubscript());
      return s;
    case string_sym: 
      printE(__LINE__,cur_tok->symbol,"string");
      EChk((s=next()));
      EChk(eSubscript());
      return s;
    case integer_sym:
    case float_sym: 
      printE(__LINE__,cur_tok->symbol,"number");
      return next();
    case oparen_sym: 
      printE(__LINE__,cur_tok->symbol,"(");
      indent++;
      EChk(next());
      EChk(gTE());
      EChk(expect(__LINE__, cparen_sym));
      indent--;
      printE(__LINE__,cur_tok->symbol,")");
      EChk(eSubscript());
      return next();
    default:
      printE(__LINE__,cur_tok->symbol,"error");
      return next();
  }
}

pStatus isOp() {
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
    case dot_sym: 
    case dotdot_sym: 
    case elipse_sym: 
      printE(__LINE__,cur_tok->symbol,"operator");
      return next();
     default:
      return pS_invalid; //valid reply
  }
}

pStatus gE() {
  pStatus s;
  printE(__LINE__,cur_tok->symbol,"-> expression");
    indent++;

  EChk(gT());
  while((s = isOp()) == pS_ok) {
    EChk(gT());
  }
    indent--;
  printE(__LINE__,cur_tok->symbol,"<- expression");
  return pS_ok;
}

pStatus gTE() {
  pStatus s;
  EChk(gE());
  s = accept(__LINE__, semi_sym);
  printf("%d\n",s);
  return pS_ok;
}

pStatus gS() {
  switch(cur_tok->symbol) {
    case obj_sym:
    case int_sym:
    case dec_sym:
    case bool_sym:
    case func_sym:
    case bin_sym:
    case list_sym:
    case map_sym: 
      printE(__LINE__,cur_tok->symbol,"type");
      EChk(next());
      EChk(expect(__LINE__, id_sym));
      return pS_ok;
    case if_sym: 
      printE(__LINE__,cur_tok->symbol,"-> if");
      indent++;
      EChk(next());
      EChk(sIf());
      indent--;
      printE(__LINE__,cur_tok->symbol,"<- if");
      return pS_ok;
    case while_sym:
    case switch_sym:
    case ocurly_sym: 
      printE(__LINE__,cur_tok->symbol,"-> closure");
      indent++;
      EChk(next());
      EChk(sClosure());
      indent--;
      printE(__LINE__,cur_tok->symbol,"<- closure");
      return pS_ok;
    case id_sym:
    case string_sym:
    case integer_sym:
    case float_sym:
      EChk(gTE());
      return accept(__LINE__, semi_sym);
    default:
      printE(__LINE__,cur_tok->symbol,"invalid statement");
      EChk(next());
  }
}

pStatus gProgram(token * t) {
  cur_tok = t;
  global = new_scope(NULL);
  indent = 0;
  while(1) {
    EChk(gS());
  }
}


