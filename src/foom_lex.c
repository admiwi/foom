#include "foom.h"
#include "foom_lex.h"



void process_file(char *file_name) {
  //                 file, buf, i, cnt, line
  parse_pkg pp = {   NULL,  "",  0,   0,    1};
  extern char* keywords[];
  char ch;
  scope *root_scope = gen_root_scope();
  symbol *s = root_scope->symbols;

  pp.file = fopen(file_name,"r");

  printf("%04d  ",pp.line);
  while((ch = buf_next(&pp)) != EOF) {
    switch(ch) {
      case ' ':
      case '\t':
      case '\r':
        break;
      case '\n':
        pp.line++;
    }
    putc(ch,stdout);
    if(ch == '\n')
      printf("%04d  ",pp.line);
  }
  while(s) {
    printf("%s\n",s->name);
    s = s->next;
  }
}

char buf_next(parse_pkg *pp) {
  char c;
  if(!pp->cnt) {
    pp->cnt = fread(pp->buf, 1, BUFSZ, pp->file);
    pp->i = 0;
    if(!pp->cnt)
      return EOF;
  }
  pp->cnt--;
  c = pp->buf[pp->i++];
  return c;
}

scope * gen_root_scope() {
  extern char * keywords[];
  scope *s = malloc(sizeof(scope));
  symbol *sym = malloc(sizeof(symbol));
  s->symbols = sym;
  int i;
  for(i=0;keywords[i];++i){
    strcpy(sym->name,keywords[i]);
    if(!keywords[i]) {
      sym->next = NULL;
      break;
    }
    sym->next = malloc(sizeof(symbol));
    sym = sym->next;
  }
  return s;
}



