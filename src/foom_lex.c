#include "foom.h"
#include "foom_lex.h"

void process_file(char *file_name) {
  int line = 0;
	char cbuf[BUFSZ];
	char lbuf[BUFSZ];
  FILE * file;
  int cnt;

  file = fopen(file_name,"r");
  do {
    int i = 0;
    cnt = fread(cbuf, 1, BUFSZ, file);
    memcpy(lbuf, cbuf, BUFSZ);
    do {
      putc(cbuf[i], stdout);
      if(cbuf[i] == '\n') {
        line++;
        printf("%04d ",line);
      }
    } while(i++<cnt);
  } while(cnt == BUFSZ);
}

