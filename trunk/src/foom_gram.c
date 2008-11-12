#include "foom.h"
#include "foom_gram.h"
#include "foom_lex.h"
#include "foom_class.h"

#define printE(A,B) _printE(__LINE__, A, B)
#define expect(A) _expect(__LINE__, A)
#define accept(A) _accept(__LINE__, A)

extern char * _symbols_[];

token *prev_tok = NULL;
token *cur_tok = NULL;
pStatus status;
long serial;
ast * gT(scope *);
ast * gE(scope *);
ast * gTE(scope *);
ast * gS(scope *);
ast * tMember(ast *, scope *);
ast * tId(scope *);
ast * eSubscript(scope *);
ast * eFuncCall(scope *);

int indent;

void _printE(int line, Symbol sym, char * e){
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

ast * tMFS(ast * l, scope * cscope) {
  ast *ret = l;
  if(expect(osquare_sym))
    ret = make_binary_op(subscript_sym, l, eSubscript(cscope));
  else if(expect(oparen_sym))
    ret = make_binary_op(funccall_sym, l, eFuncCall(cscope));
  else if(expect(dot_sym)) {
    accept(dot_sym);
    ret = make_binary_op(member_sym, l, tMember(l, cscope));
  }
  return ret;
}

ast * tMember(ast * a, scope * cscope) {
  ast *ret = NULL, * l = get_member(a->op.obj, cur_tok->lexem);
  ret = l;
  printE(cur_tok->symbol,"member");
  next();
  return tMFS(l, cscope);
}

ast * tId(scope * cscope) {
  ast *ret = NULL, * l = get_obj(cscope, cur_tok->lexem);
  ret = l;
  printE(cur_tok->symbol,"id");
  next();
  if(l) return tMFS(l, cscope);
  return l;
}

ast * tString(scope * cscope) {
  ast * a;
  str * s = malloc(sizeof(str));
  printE(cur_tok->symbol,"string");
  s->val = cur_tok->lexem;
  s->len = strlen(s->val);
  accept(string_sym);
  a = make_str(cscope, get_serial("Lstring"), s);
  return a;
}

ast * tInteger(scope * cscope){
  long li = strtol(cur_tok->lexem, NULL, 10);
  printE(cur_tok->symbol,"number");
  accept(integer_sym);
  return make_int(cscope, get_serial("Linteger"), li);
}
ast * tDecimal(scope * cscope){
  double fl = strtod(cur_tok->lexem,NULL);
  printE(cur_tok->symbol,"number");
  accept(float_sym);
  return make_dec(cscope, get_serial("Ldecimal"), fl);
}

ast * tParens(scope * cscope) {
  ast * ret;
  printE(cur_tok->symbol,"("); indent++;
  accept(oparen_sym);
  ret = make_unary_op(group_sym, gE(cscope));
  accept(cparen_sym);
  indent--; printE(cur_tok->symbol,")");
  return ret;
}
ast * sClosure(scope * cscope) {
  ast_list * topal, * cural;
  topal = cural = new_astlist();
  printE(cur_tok->symbol,"-> closure");
  indent++;
  next();
  //if(expect(lt_sym) == pS_ok)

  while(cur_tok->symbol != ccurly_sym && !expect(end_sym)) {
    cural->node = gS(cscope);
    cural->next = new_astlist();
    cural = cural->next;
  }
  indent--;
  printE(cur_tok->symbol,"<- closure");
  accept(ccurly_sym);
  return make_closure(cscope, get_serial("closure"), topal);
}

ast * sIf(scope * cscope) {
  ast * ret, * e, *s;
  printE(cur_tok->symbol,"-> if"); indent++;
  accept(if_sym);
  e = tParens(cscope);
  if(status == pS_ok)
    s = gS(cscope);
  indent--; printE(cur_tok->symbol,"<- if");
  return make_binary_op(if_sym, e, s);
}

    // [1] [1..-1] [a] [a..b] [a,b,c..d] [..b] [a..]
ast * eSubscript(scope * cscope) {
  ast * ret, * ua;
  if(!expect( osquare_sym)) return NULL;
  printE(cur_tok->symbol,"-> subscript"); indent++;
  next();
  ua = gE(cscope);
  indent--; printE(cur_tok->symbol,"<- subscript");
  accept(csquare_sym);
  return make_unary_op(subscript_sym, ua);
}

ast * eFuncCall(scope * cscope) {
  ast_list * topal, * cural;
  topal = cural = new_astlist();
  if(!expect(oparen_sym)) return NULL;
  char * fn = prev_tok->lexem;
  printE(cur_tok->symbol,"-> func call"); indent++;
  next();
  do {
    cural->node = gE(cscope);
    cural->next = new_astlist();
    cural = cural->next;
  } while(expect(comma_sym) && accept(comma_sym));
  indent--; printE(cur_tok->symbol,"<- func call");
  accept(cparen_sym);
  return make_call(cscope, fn,topal);
}

//TODO: tVar and eSub may have to move
ast * gT(scope * cscope) {
  ast * a;
  switch(cur_tok->symbol) {
    case id_sym:
      a = tId(cscope);
    break;

    case string_sym:
      a = tString(cscope);
      eSubscript(cscope);
      break;
    case integer_sym:
      a = tInteger(cscope);
      break;
    case float_sym:
      a = tDecimal(cscope);
      break;
    case oparen_sym:
      a = tParens(cscope);
      eSubscript(cscope);
      return NULL;
    default:
      printE(cur_tok->symbol,"error");
      next();
  }
  return a;
}

ast * sDeclare(scope * cscope) {
  ast * ret = NULL, *ao = new_astobj();
  ao->tag = obj_ast;
  ao->op.obj->type = cur_tok->symbol;
  next();
  printE(cur_tok->symbol,"-> declare call"); indent++;
  if(expect(id_sym))
    ao->op.obj->name = strdup(cur_tok->lexem);
  accept(id_sym);
  map_set(cscope->symbols, ao->op.obj->name, ao->op.obj, MAP_OBJECT);

  if(expect(assign_sym)) {
    accept(assign_sym);
    ret = make_binary_op(assign_sym, ao, gE(cscope));
  }

  accept(semi_sym);
  indent--; printE(cur_tok->symbol,"<- declare call");
  return ret?ret:ao;
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

ast * gE(scope * cscope) {
  ast * ret, * l, * r;
  Symbol op;
  printE(cur_tok->symbol,"-> expression"); indent++;
  ret = gT(cscope);
  if(isBinaryOp()) {
    l = ret;
    op = next();//op
    r = gE(cscope);
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

ast * gS(scope * cscope) {
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
      a = sDeclare(cscope);
      break;
    case if_sym:
       a = sIf(cscope);
       break;
    case while_sym:
    case switch_sym:
    case ocurly_sym:
      a = sClosure(new_scope(cscope));
      break;
    case id_sym:
    case string_sym:
    case integer_sym:
    case float_sym:
      a = gE(cscope);
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

ast * gProgram(token * t) {
  scope * global = new_scope(NULL);
  ast_list * cural;
  ast * ret = new_astnode();
  ret->tag = block_ast;
  ret->op.block.stmts = cural = new_astlist();
  serial = indent = 0;
  cur_tok = t;
  status = pS_ok;

  fprintf(stderr,"-> program\n");
  while(!expect(end_sym)) {
    cural->node = gS(global);
    cural->next = new_astlist();
    cural = cural->next;
  }
  fprintf(stderr,"<- program\n");
  return ret;
}


