#include "foom.h"
#include "foom_gram.h"
#include "foom_lex.h"
#include "foom_class.h"

#define printE(A,B) _printE(__LINE__, A, B)
#define expect(A) _expect(__LINE__, A)
#define accept(A) _accept(__LINE__, A)

extern char * _symbols_[];

scope * global_scope = NULL;
token *prev_tok = NULL;
token *cur_tok = NULL;
pStatus status;
long serial;
ast * gT();
ast * gE();
ast * gTE();
ast * gS();
ast * tMember();
ast * tId();
ast * tMid();
ast * tM(ast *);
ast * eSubscript();
//ast * eFuncCall();
ast * tList();

int indent;

void _printE(int line, Symbol sym, char * e){
#ifdef DEBUG
  extern char * _keywords[];
  int i = indent;
  if(indent < 0) indent = 0;
  if(!cur_tok) return;
  while(i-- >= 0) { fprintf(stderr,"  "); }
  fprintf(stderr, "%s [%d: '%s' %s ] from line %d\n",
    e,
    cur_tok->line,
    cur_tok->lexem,
    _symbols_[sym],
    line
  );
#endif
}

int _expect(int line, Symbol sym) {
  if(cur_tok && sym == cur_tok->symbol) {
    status = pS_ok;
    return 1;
  }
  if(cur_tok) {
    status = pS_invalid;
    return 0;
  }
  status = pS_empty;
  add_error(ERR_ERROR, 0, -1, "out of tokens", 0);
  return 0;
}

Symbol next() {
  prev_tok = cur_tok;
  cur_tok = cur_tok->next;
  status = pS_ok;
  return prev_tok->symbol;
}

int _accept(int line, Symbol sym) {
  char * msg;
  if(_expect(line, sym)) {
    next();
    return 1;
  }
  msg = malloc(ARB_LEN);
  memset(msg, ARB_LEN, 1);
  sprintf(msg, "syntax error: expected %s but found %s (%s)", _symbols_[sym], _symbols_[cur_tok->symbol], cur_tok->lexem);
  add_error(ERR_ERROR, 0, cur_tok->line, msg, 0);
  status = pS_invalid;
  return 0;
}

char * get_serial(char * t ) {
  char * n = malloc(ARB_LEN);
  memset(n, 0, ARB_LEN);
  sprintf(n, "%s_%ld", t, serial++);
  return n;
}

//data

ast * tF(ast * l) {
  ast *ret = l;
  if(expect(oparen_sym)) {
    accept(oparen_sym);
    ret = make_binary_op(funccall_sym, l, tList(list_ast));
    accept(cparen_sym);
  }
  return tM(ret);
}
ast * tS(ast * l) {
  ast *ret = l;
  if(expect(osquare_sym)) {
    accept(osquare_sym);
    ret = make_binary_op(subscript_sym, l, tList(list_ast));
    accept(csquare_sym);
  }
  return tM(ret);
}

ast * tFS(ast * l) {
  ast *ret = l;
  while(expect(osquare_sym) || expect(oparen_sym)) {
    ret = tS(ret);
    ret = tF(ret);
  }
  return tM(ret);
}

ast * tM(ast * r) {
  ast * l, *a;
  if(expect(dot_sym)) {
    l = new_astnode();
    accept(dot_sym);
    l->tag = mid_ast;
    l->op.Id = strdup(cur_tok->lexem);
    printE(cur_tok->symbol,"member");
    next();
    a = make_binary_op(member_sym, l, r);
    return tM(a);
  }
  return r;
}

ast * tId() {
  ast * l = new_astnode();
  l->tag = id_ast;
  l->op.Id = strdup(cur_tok->lexem);
  printE(cur_tok->symbol,"id");
  next();
  l = tM(l);
  return tFS(l);
}

ast * tString() {
  ast * a;
  str * s = malloc(sizeof(str));
  printE(cur_tok->symbol,"string");
  s->val = strdup(cur_tok->lexem);
  s->len = strlen(s->val);
  accept(string_sym);
  a = make_str(get_serial("Lstring"), s, global_scope);
  return a;
}

ast * tInteger(){
  long li = strtol(cur_tok->lexem, NULL, 10);
  printE(cur_tok->symbol,"number");
  accept(integer_sym);
  return make_int(get_serial("Linteger"), li, global_scope);
}
ast * tDecimal(){
  double fl = strtod(cur_tok->lexem,NULL);
  printE(cur_tok->symbol,"number");
  accept(float_sym);
  return make_dec(get_serial("Ldecimal"), fl, global_scope);
}

ast * tParens() {
  ast * ret;
  printE(cur_tok->symbol,"("); indent++;
  accept(oparen_sym);
  ret = make_unary_op(group_sym, gE());
  accept(cparen_sym);
  indent--; printE(cur_tok->symbol,")");
  return ret;
}
ast * sClosure() {
  ast_list * topal, * cural;
  topal = cural = new_astlist();
  printE(cur_tok->symbol,"-> closure");
  indent++;
  next();
  //if(expect(lt_sym) == pS_ok)

  while(cur_tok->symbol != ccurly_sym && !expect(end_sym)) {
    cural->node = gS();
    cural->next = new_astlist();
    cural = cural->next;
  }
  indent--;
  printE(cur_tok->symbol,"<- closure");
  accept(ccurly_sym);
  return make_closure(get_serial("closure"), topal);
}

ast * sIf() {
  ast * ret, * e, *s;
  printE(cur_tok->symbol,"-> if"); indent++;
  accept(if_sym);
  e = tParens();
  if(status == pS_ok)
    s = gS();
  indent--; printE(cur_tok->symbol,"<- if");
  if(expect(else_sym)) {
    accept(else_sym);
    s = make_binary_op(else_sym, s, gS());
  }
  return make_binary_op(if_sym, e, s);
}

ast * sFor() {
  ast * ret, * e, * s;
  ast_list * for_guts, * cural;
  for_guts = cural = new_astlist();
  printE(cur_tok->symbol,"-> for"); indent++;
  accept(for_sym);
  printE(cur_tok->symbol,"("); indent++;
  accept(oparen_sym);

  cural->node = gS();
  cural->next = new_astlist();
  cural = cural->next;
  //accept(semi_sym);
  cural->node = gE();
  cural->next = new_astlist();
  cural = cural->next;
  accept(semi_sym);
  cural->node = gE();
  cural->next = new_astlist();

  indent--; printE(cur_tok->symbol,")");
  accept(cparen_sym);
  s = gS();
  e = new_astnode();
  e->tag = block_ast;
  e->op.block.stmts = for_guts;
  return make_binary_op(for_sym, e, s);
}
    // [1] [1..-1] [a] [a..b] [a,b,c..d] [..b] [a..]
ast * eSubscript() {
  ast_list * topal, *cural;
  ast * ret, * ua;
  topal = cural = new_astlist();
  if(!expect(osquare_sym)) return NULL;
  printE(cur_tok->symbol,"-> subscript"); indent++;
  next();
  do {
    cural->node = gE();
    cural->next = new_astlist();
    cural = cural->next;
  } while(expect(comma_sym) && accept(comma_sym));
  indent--; printE(cur_tok->symbol,"<- subscript");
  accept(csquare_sym);
  return ast_list_wrapper(topal);
}

ast * tList() {
  ast_list * topal, *cural;
  topal = cural = new_astlist();
  //if(!expect(osquare_sym)) return NULL;
  printE(cur_tok->symbol,"-> term list"); indent++;
  do {
    cural->node = gE();
    cural->next = new_astlist();
    cural = cural->next;
  } while(expect(comma_sym) && accept(comma_sym));
  indent--; printE(cur_tok->symbol,"<- term list");
  //accept(csquare_sym);
  return ast_list_wrapper(topal);
}

//TODO: tVar and eSub may have to move
ast * gT() {
  ast * a;
  switch(cur_tok->symbol) {
    case id_sym:
      a = tId();
    break;

    case string_sym:
      a = tString();
      if(expect(osquare_sym)) {
        accept(osquare_sym);
        tList();
        accept(csquare_sym);
      }
      break;
    case integer_sym:
      a = tInteger();
      break;
    case float_sym:
      a = tDecimal();
      break;
    case oparen_sym:
      a = tParens();
      tList(list_ast);
      break;
    case ocurly_sym:
      a = sClosure();
      //accept(ccurly_sym);
      break;
    case osquare_sym:
      accept(osquare_sym);
      a = tList();
      accept(csquare_sym);
      break;
    default:
      printE(cur_tok->symbol,"error");
      next();
  }
  return a;
}

ast * sDeclare() {
  ast * ret = NULL, *typ = new_astnode(), *var = new_astnode();
  typ->op.obj = scope_get(global_scope, cur_tok->lexem);
  typ->tag = obj_ast;
  next();
  printE(cur_tok->symbol,"-> declare call"); indent++;
  var =  tId();
  if(expect(assign_sym)) {
    accept(assign_sym);
    ret = make_binary_op(assign_sym, make_binary_op(declare_sym, typ, var), gE());
  }

  accept(semi_sym);
  indent--; printE(cur_tok->symbol,"<- declare call");
  return ret?ret:make_binary_op(declare_sym, typ, var);
}

int isBinaryOp() {
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
    //case bang_sym:
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
      return 1;
     default:
      return 0;
  }
}

ast * gE() {
  ast * ret, * l, * r;
  Symbol op;
  printE(cur_tok->symbol,"-> expression"); indent++;
  ret = gT();
  if(isBinaryOp()) {
    l = ret;
    op = next();//op
    r = gE();
    ret = make_binary_op(op, l, r);
  } else if(expect(as_sym) || expect(was_sym) || expect(is_sym)) {
    printE(cur_tok->symbol,"class op");
    op = next();
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
        status = pS_invalid;
    }
  }
  indent--; printE(cur_tok->symbol,"<- expression");
  return ret;
}

ast * gS() {
  ast * a;
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
      a = sDeclare();
      break;
    case if_sym:
       a = sIf();
       break;
    case for_sym:
       a = sFor();
       break;
    case while_sym:
    case switch_sym:
    case ocurly_sym:
      a = sClosure();
      break;
    case id_sym:
    case string_sym:
    case integer_sym:
    case float_sym:
      a = gE();
      accept(semi_sym);
      break;
    case end_sym:  //valid
      status = pS_done;
      return NULL;
    default:
      printE(cur_tok->symbol,"invalid statement");
      next();

  }
  return a;
}

ast * gProgram(token * t, scope * s) {
  ast_list * cural;
  ast * ret = new_astnode();
  global_scope = s;
  ret->tag = block_ast;
  ret->op.block.stmts = cural = new_astlist();
  serial = indent = 0;
  cur_tok = t;
  status = pS_ok;

#ifdef DEBUG
  fprintf(stderr,"-> program\n");
#endif
  while(!expect(end_sym)) {
    cural->node = gS();
    cural->next = new_astlist();
    cural = cural->next;
  }
#ifdef DEBUG
  fprintf(stderr,"<- program\n");
#endif
  return ret;
}


