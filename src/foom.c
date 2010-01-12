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
#include "foom_feval.h"
#include "foom_lib.h"
#include "foom_hash.h"

SYMBOLS;

void print_toks(token * tok) {
  while(tok) {
    printf("cur: '%s' %d prev:'%s'\n", tok->lexem, tok->symbol, tok->prev?tok->prev->lexem: "none");
    tok = tok->next;
  }
}

void print_map(map *m) {
  int i = 0;
  map_node * n;
  for(i=0;i< HASH_SZ;++i) {
    printf("map box %d:\n", i);
    n = m->nodes[i];
    while(n){
      printf("  key %s\n", n->key->text);
      n = n->next;
    }

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
  init_classes(s);
  init_libs(s);
  tok = gen_token_chain(&pp);
  pgm = gProgram(tok, s);
  print_errors();
  start_feval(pgm, s);
}

int main(int argc, char** argv) {
  struct stat sb;
  extern map * keywords;
  map_node * m;

  if(argc < 2) {
    printf("Usage: %s <source file>\n", argv[0]);
    exit(EXIT_SUCCESS);
  }

  if (stat(argv[1], &sb) == -1) {
    perror("error");
    exit(EXIT_SUCCESS);
  }
  init_keywords();
  //print_map(keywords);
  //m = map_get(keywords, "str");
  //if(m)
  //printf("%s\n", m->key->text);
  init_fevals();
  process_file(argv[1]);
  putc('\n', stdout);
	return EXIT_SUCCESS;
}
