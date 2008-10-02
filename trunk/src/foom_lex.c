#include "foom.h"
#include "foom_lex.h"



void process_file(char *file_name) {
  //              file, buf, i, cnt, line
  parse_pkg pp = {   0,  "",  0,   0,    1};
  extern char* keywords[];
  char ch;

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


