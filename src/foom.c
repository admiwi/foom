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

void process_file(char *file_name) {
  //        filename, file,  buf, backbuf,  i,    c, count, left, line
  parse_pkg pp = { "\0", NULL, "\0",    "\0",  0, '\0',     0,    0,   1};
  scope *s = new_scope(NULL);
  token * tok, t;
  strcpy(pp.filename, file_name);
  pp.file = fopen(file_name,"r");
 
  tok = gen_token_chain(&pp);

  while(tok) {
    printf("cur: '%s' %d %d prev:'%s'\n", tok->lexem, tok->type, tok->attr, tok->prev?tok->prev->lexem: "none");
    tok = tok->next;
  }
}

int main(int argc, char** argv) {
  struct stat sb;
  int i = 0, j = 0;
  extern MAP grammer;
  char *stmts[] = {"if","while","for", 0};
  void * g;
  char gram[GLEN][GLEN][ARB_LEN];

  init_grammer();
  if(argc < 2) {
    printf("Usage: %s <source file>\n", argv[0]);
    exit(EXIT_SUCCESS);
  }

  if (stat(argv[1], &sb) == -1) {
    perror("error");
    exit(EXIT_SUCCESS);
  }
  /* 
  memcpy(&gram, map_get(grammer, "while"), sizeof(gram)) ;
  for(i=0; gram[i][0][0];i++) {
    printf("g%d ",i);
    for(j=0; gram[i][j][0];j++) {
      if(gram[i][j][0] > LASTG)
        printf("%s", gram[i][j]);
      else
       printf("%d", (int)gram[i][j][0]);
      printf(" ");
    }
    printf("\n");
  }
  */

  init_keywords();
  
  process_file(argv[1]);
  putc('\n', stdout);
	return EXIT_SUCCESS;
}
/*
void test_stuff(char *file_name) {
  //               file,    buf, backbuf,  i, cnt, line
  parse_pkg pp = { NULL,   "\0",    "\0",  0,   0,   1};
  extern char* keywords[];
  char ch;
  int i=0;
  char * tmp;
  char not_found[] = "not found";
  scope *root_scope = gen_root_scope();
  pp.file = fopen(file_name,"r");

  printf("%04d  ",pp.line);
  while((ch = buf_getc(&pp)) != EOF) {
    switch(ch) {
      case ' ':
      case '\t':
      case '\r':
      case '\n':
        break;
        
    }
    putc(ch,stdout);
    if(ch == '\n')
      printf("%04d  ",pp.line);
  }
  putc('\n',stdout);
  map_del(root_scope->symbols, "loop", 1); 
  map_del(root_scope->symbols, "func", 1); 
  map_del(root_scope->symbols, "xor", 1); 
  do {
    tmp = (char*)map_get(root_scope->symbols, (void*)keywords[i]);
    if(!tmp)
      tmp = not_found;
    printf("k:%s v:%s\n",keywords[i], tmp);
  } while(keywords[++i]);
}
*/
