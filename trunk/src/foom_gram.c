#include "foom.h"
#include "foom_gram.h"
#include "foom_lex.h"

#define printE(A,B) _printE(__LINE__, A, B)
#define expect(A) _expect(__LINE__, A)
#define accept(A) _accept(__LINE__, A)

token *prev_tok = NULL;
token *cur_tok = NULL;
scope *global = NULL;
pStatus gT();
pStatus gE();
pStatus gTE();
pStatus gS();

int indent;

void _printE(int line, Symbol sym, char * e){
  extern char * _keywords[];
  int i = indent;
  if(indent < 0) indent = 0;
  if(!cur_tok) return;
  while(i-- >= 0) { fprintf(stderr,"  "); }
  fprintf(stderr, "%s [%d: '%s' %d ] from line %d\n",
    e,
    cur_tok->line,
    cur_tok->lexem,
    sym,
    line
  );
}

pStatus _expect(int line, Symbol sym) {
  if(cur_tok && sym == cur_tok->symbol) return pS_ok;
  if(cur_tok) return pS_invalid;
  add_error(ERR_ERROR, 0, -1, "out of tokens", 0);
  return pS_empty;
}

pStatus next() {
  prev_tok = cur_tok;
  cur_tok = cur_tok->next;
  return (cur_tok ? pS_ok : pS_empty);
}

pStatus _accept(int line, Symbol sym) {
  pStatus s = _expect(line, sym);
  char * msg;
  switch(s) {
    case pS_ok:
      return next();
    default:
      msg = malloc(ARB_LEN);
      memset(msg, ARB_LEN, 1);
      sprintf(msg, "syntax error: expected %d but found %d (%s)", sym, cur_tok->symbol, cur_tok->lexem);
      add_error(ERR_ERROR, 0, cur_tok->line, msg, 0);
      return s;
  }
}

pStatus sClosure() {
  printE(cur_tok->symbol,"-> closure");
  indent++;
  next();
  //if(expect(lt_sym) == pS_ok)

  while(cur_tok->symbol != ccurly_sym && expect(eof_sym) != pS_ok) {
    gS();
  }
  indent--;
  printE(cur_tok->symbol,"<- closure");
  return accept( ccurly_sym);
}

pStatus sIf() {
  pStatus s;
  printE(cur_tok->symbol,"-> if");
  indent++;
  next();

  switch(s = accept(oparen_sym)) {
    case pS_ok:
      gE();
      accept(cparen_sym);
      gS();
      break;
    default:
      break;
  }
  indent--;
  printE(cur_tok->symbol,"<- if");
  return s;
}

    // [1] [1..-1] [a] [a..b] [a,b,c..d] [..b] [a..]
pStatus eSubscript() {
  pStatus s = expect( osquare_sym);
  if(s != pS_ok) return s;
  printE(cur_tok->symbol,"-> subscript");
  next();
  indent++;
  gE();
  indent--;
  printE(cur_tok->symbol,"<- subscript");
  switch(expect( csquare_sym)) {
    case pS_ok:
      next();
      return pS_error;
    case pS_invalid: return pS_invalid;
    default:
      printf("should never get here %d\n",__LINE__);
      return pS_error;
  }

}

pStatus eFuncCall() {
  pStatus s = expect( oparen_sym);
  if(s != pS_ok) return s;
  printE(cur_tok->symbol,"-> func call"); indent++;
  next();
  do {
    gE();
  } while(expect(comma_sym) == pS_ok && accept(comma_sym) == pS_ok);
  indent--; printE(cur_tok->symbol,"<- func call");
  return accept(cparen_sym);
}
pStatus tVar() {
  while(expect(dot_sym) == pS_ok && accept(dot_sym) == pS_ok) {
    printE(cur_tok->symbol,"-> member"); indent++;
    gT();
    indent--; printE(cur_tok->symbol,"<- member");
  }
  return pS_ok;
}

pStatus gT() {
  pStatus s;
  switch(cur_tok->symbol) {
    case id_sym:
      printE(cur_tok->symbol,"symbol");
      s=next();
      tVar();
      eSubscript();
      eFuncCall();
      return s;
    case string_sym:
      printE(cur_tok->symbol,"string");
      s=next();
      tVar();
      eSubscript();
      return s;
    case integer_sym:
    case float_sym:
      printE(cur_tok->symbol,"number");
      (s = next());
      tVar();
      return s;
    case oparen_sym:
      printE(cur_tok->symbol,"(");
      indent++;
      next();
      gTE();
      expect(cparen_sym);
      indent--;
      printE(cur_tok->symbol,")");
      tVar();
      eSubscript();
      return next();
    default:
      printE(cur_tok->symbol,"error");
      return next();
  }
}

void add_id_scope() {

}


pStatus sDeclare() {
  printE(cur_tok->symbol,"-> declare call"); indent++;
  next();
  do {
    if(accept(id_sym)==pS_ok)

    tVar();
    if(expect(assign_sym)==pS_ok) {
      next();
      gE();
    }
  } while(expect(comma_sym) == pS_ok && accept(comma_sym) == pS_ok);
  indent--; printE(cur_tok->symbol,"<- declare call");
  return accept(semi_sym);
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
      printE(cur_tok->symbol,"operator");
      return next();
     default:
      return pS_invalid; //valid reply
  }
}

pStatus gE() {
  pStatus s = pS_ok;
  printE(cur_tok->symbol,"-> expression");
  indent++;

  gT();
  while(expect(eof_sym) != pS_ok) {
    if(isOp() == pS_ok) {
      gT();
    } else if(expect(as_sym) == pS_ok || expect(was_sym) == pS_ok || expect(is_sym) == pS_ok) {
      printE(cur_tok->symbol,"class op");
      next();
      switch(cur_tok->symbol){
        case obj_sym:
        case int_sym:
        case dec_sym:
        case bool_sym:
        case func_sym:
        case bin_sym:
        case list_sym:
        case map_sym:
        case str_sym:
        case id_sym:
          printE(cur_tok->symbol,"class");
          next();
        default:
          s = pS_invalid;
      }
    } else
      break;
  }
  indent--;
  printE(cur_tok->symbol,"<- expression");
  return s;
}

pStatus gTE() {
  gE();
  return accept(semi_sym);
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
    case str_sym:
      printE(cur_tok->symbol,"type");
      return sDeclare();
    case if_sym:
      return sIf();
    case while_sym:
    case switch_sym:
    case ocurly_sym:
      return sClosure();
    case id_sym:
    case string_sym:
    case integer_sym:
    case float_sym:
      return gTE();
    case eof_sym:  //valid
      return pS_done;
    default:
      printE(cur_tok->symbol,"invalid statement");
      return next();
  }
}

pStatus gProgram(token * t) {
  cur_tok = t;
  global = new_scope(NULL);
  indent = 0;
  pStatus s;
  fprintf(stderr,"-> program\n");
  while(expect(eof_sym)!=pS_ok) {
    s = gS();
    if(s == pS_ok) continue;
    if(s == pS_done) break;

  }
  fprintf(stderr,"<- program\n");
  return s;
}


