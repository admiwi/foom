#include "foom.h"
#include "foom_lex.h"
#include "foom_hash.h"



void process_file(char *file_name) {
  //                 file, buf, i, cnt, line
  parse_pkg pp = {   NULL,  "",  0,   0,    1};
  extern char* keywords[];
  char ch;
  int i=0;
  char * tmp;
  char not_found[] = "not found";
  scope *root_scope = gen_root_scope();
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
  map_del(root_scope->symbols, "loop"); 
  map_del(root_scope->symbols, "func"); 
  map_del(root_scope->symbols, "xor"); 
  do {
    tmp = (char*)map_get(root_scope->symbols, (void*)keywords[i]);
    if(!tmp)
      tmp = not_found;
    printf("k:%s v:%s\n",keywords[i], tmp);
  } while(keywords[++i]);
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
  s->symbols = new_map();
  int i=0;
  do {
    map_set(s->symbols, keywords[i], strdup(keywords[i]));
  } while(keywords[++i]);
  return s;
}



