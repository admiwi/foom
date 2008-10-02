#ifndef _FOOM_LEX_
#define _FOOM_LEX_

typedef struct _parse_pkg {
  FILE * file;
  char buf[BUFSZ];
  int i;
  int cnt;
  int line;
} parse_pkg;

void process_file(char*);
char buf_next(parse_pkg*);

#endif

