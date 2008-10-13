#ifndef _FOOM_LEX_
#define _FOOM_LEX_

typedef struct _parse_pkg {
  char filename[ARB_LEN];
  FILE * file;
  char buf[BUFSZ];
  char backbuf[ARB_LEN];
  int i;
  char c;
  int count;
  int left;
  int line;
} parse_pkg;

void process_file(char*);
char buf_getc(parse_pkg*);
char buf_ungetc(parse_pkg*);
scope * gen_root_scope();
//int get_string(parse_pkg*, token*);
token * get_token(parse_pkg *);
map ** get_keywords();
scope * new_scope(scope*);
//token * new_token(char* name, int type, int attr, funcp * func, char* args) 
token * new_token(void*, int, int); 

#endif

