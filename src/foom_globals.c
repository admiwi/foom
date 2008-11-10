#include "foom.h"

char * _keywords[] = {
  "\xff",
  "if", "switch", "case", "else", "break",
  "return",
  "try", "catch", "finally", "throw", "assert",
  "import", "namespace",
  "class", "extend", "interface", "mixin", "virtual",
  "is", "was", "as",
  "for", "while", "loop", "do", "continue",
  "obj", "int", "dec", "bool", "func", "bin", "list", "map", "str",
  "and", "or", "not", "xor",
  "(",")",
  "{","}",
  "[","]",
  "\"","'"
};
char * _symbols_[] = {
  "{end}",
  "{if}",
  "{switch}",
  "{case}",
  "{else}",
  "{break}",
  "{return}",
  "{try}",
  "{catch}",
  "{finally}",
  "{throw}",
  "{assert}",
  "{import}",
  "{namespace}",
  "{class}",
  "{extend}",
  "{interface}",
  "{mixin}",
  "{virtual}",
  "{is}",
  "{was}",
  "{as}",
  "{for}",
  "{while}",
  "{loop}",
  "{do}",
  "{continue}",
  "{obj}",
  "{int}",
  "{dec}",
  "{bool}",
  "{func}",
  "{bin}",
  "{list}",
  "{map}",
  "{str}",
  "{and}",
  "{or}",
  "{not}",
  "{xor}",
  "{oparen}",
  "{cparen}",
  "{ocurly}",
  "{ccurly}",
  "{osquare}",
  "{csquare}",
  "{dquote}",
  "{squote}",
  "{id}",
  "{string}",
  "{integer}",
  "{float}",
  "{lt}",
  "{gt}",
  "{le}",
  "{ge}",
  "{eq}",
  "{neq}",
  "{assign}",
  "{plus}",
  "{minus}",
  "{star}",
  "{carrot}",
  "{bang}",
  "{andper}",
  "{slash}",
  "{dot}",
  "{at}",
  "{dollar}",
  "{colon}",
  "{grave}",
  "{tilda}",
  "{bar}",
  "{comma}",
  "{dand}",
  "{dor}",
  "{dotdot}",
  "{elipse}",
  "{newline}",
  "{semi}",
  "{funccall}",
  "{subscript}",
  "{member}",
  "{group}",
  "{unknown}" };
MAP keywords = NULL;
MAP init_keywords() {
  extern char * _keywords[];
  MAP _kws;
  int i=0;
  if(!keywords) {
    keywords = new_map();
    do {
      int * j = malloc(sizeof(int));
      *j = i;
      map_set(keywords, _keywords[i], j, MAP_STRING);
    } while(++i < 46);//_keywords[++i][0]);
  }
  return keywords;
}

_error_ *errors = 0;

void add_error(int type, char* fn, int line, char* what, char* where) {
  _error_ * curerr;
  _error_ * err = malloc(sizeof(_error_));
  err->type = type;
  err->line = line;
  strcpy(err->file, fn?fn:"<file>");
  err->what = malloc(ARB_LEN);
  err->where = malloc(ARB_LEN);
  strncpy(err->what, what?what:"unknown error", ARB_LEN);
  strcat(err->where, "...");
  strncat(err->where, where?where:"somewhere", ARB_LEN-7);
  strcat(err->where, "...");
  err->next = NULL;
  if(errors) {
    curerr = errors;
    while(curerr->next)
      curerr = curerr->next;
    curerr->next = err;
  } else errors = err;
}

void print_errors() {
  _error_ *err = errors;
  while(err) {
    printf("%s:%d: %s: %s\n",
      err->file, err->line,
      err->type?"error":"warning",  err->what);
    err = err->next;
  }
}

