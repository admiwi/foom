/*
 ============================================================================
 Name        : foom.c
 Author      : Adam Wilson
 Version     :
 Copyright   : MIT
 Description : Foom, the programming language
 ============================================================================
 */

#include "foom.h"
#include "foom_lex.h"
#include "foom_gram.h"
#include "foom_test.h"

void print_toks(token * tok) {
  while(tok) {
    printf("cur: '%s' %d prev:'%s'\n", tok->lexem, tok->symbol, tok->prev?tok->prev->lexem: "none");
    tok = tok->next;
  }
}

void process_file(char *file_name) {
  //        filename, file,  buf, backbuf,  i,    c, count, left, line
  parse_pkg pp = { "\0", NULL, "\0",    "\0",  0, '\0',     0,    0,   1};
  scope *s = new_scope(NULL);
  token * tok, t;
  ast * pgm;
  strcpy(pp.filename, file_name);
  pp.file = fopen(file_name,"r");

  tok = gen_token_chain(&pp);
  pgm = gProgram(tok);
  print_errors();

  //decend_ast(pgm);


}

int main(int argc, char** argv) {
  struct stat sb;
  int i = 0, j = 0;
  extern MAP grammer;
  char *stmts[] = {"if","while","for", 0};
  void * g;

  if(argc < 2) {
    printf("Usage: %s <source file>\n", argv[0]);
    exit(EXIT_SUCCESS);
  }

  if (stat(argv[1], &sb) == -1) {
    perror("error");
    exit(EXIT_SUCCESS);
  }
  init_keywords();
  process_file(argv[1]);
  putc('\n', stdout);
	return EXIT_SUCCESS;
}
