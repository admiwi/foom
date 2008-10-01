#include "foom.h"
#include "foom_lex.h"



void process_file(char *file_name) {
  parse_pkg pp = {0, "", 0, 0, 0, 1};
  extern char* keywords[];
  char ch;

  pp.file = fopen(file_name,"r");

  while((ch = next_char(&pp)) != EOF)
    putc(ch,stdout);


  

}

char next_char(parse_pkg *pp) {
  char c;
  if(!pp->cnt)
    pp->cnt = fread(pp->buf, 1, BUFSZ, pp->file);
  c = pp->buf[pp->ci++];
  if(pp->ci == pp->cnt)
    pp->ci = pp->li = pp->cnt = 0;

  return c;
}

