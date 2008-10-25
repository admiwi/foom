#include "foom.h"

char * _keywords[] = { 
  "\x255",
  "if", "switch", "case", "else", "break",
  "return",
  "try", "catch", "finally", "throw", "assert",
  "import", "namespace",
  "class", "extend", "interface", "mixin", "virtual",
  "is", "was", "as",
  "for", "while", "loop", "do", "continue",
  "obj", "int", "dec", "bool", "func", "bin", "list", "map",
  "and", "or", "not", "xor",
  "(",")",
  "{","}",
  "[","]",
  "\"","'",
  0
};

MAP keywords = NULL;
MAP init_keywords() {
  extern char * _keywords[];
  MAP _kws;
  if(!keywords) {
    keywords = new_map();
    int i=0;
    do {
      int * j = malloc(sizeof(int));
      *j = i;
      map_set(keywords, _keywords[i], j, MAP_STRING);
    } while(_keywords[++i]);
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
    printf("have errors\n");
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
