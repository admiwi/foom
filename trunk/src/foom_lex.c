#include "foom.h"
#include "foom_lex.h"
#include "foom_hash.h"
#include <ctype.h>

void process_file(char *file_name) {
  //               file,    buf, backbuf,  i, count, left, line
  parse_pkg pp = { NULL,   "\0",    "\0",  0,   0,       0,   1};
  token * tok;
  //char ch;
  //scope *root_scope = gen_root_scope();
  pp.file = fopen(file_name,"r");
  printf("file %s open\n", file_name);
  printf("getting token\n");
  tok = get_token(&pp);
  printf("got token at %x\n", tok);

  printf("Heres the name:  %s\n", tok->name);
}

char buf_getc(parse_pkg *pp) {
  char c;
  if(!pp->left) {
    printf("loading buf\n");
    if(pp->buf && pp->count > ARB_LEN) 
      strncpy(pp->backbuf, &(pp->buf[pp->count - ARB_LEN]), ARB_LEN);
    printf("backbuf...\n");
    pp->count = fread(pp->buf, 1, BUFSZ, pp->file);
    printf("loaded %d\n", pp->count);
    pp->left = pp->count;
    pp->i = 0;
    if(!pp->count)
      return EOF;
  }
  pp->left--;
  if(pp->i<0 && pp->backbuf)
    c = pp->backbuf[ARB_LEN+pp->i];
  else
    c = pp->buf[pp->i];
  if(c=='\n') pp->line--;
  pp->i++;
  return c;
}

char buf_ungetc(parse_pkg *pp) {
  char c;
  pp->left++;
  pp->i--;
  if(pp->i < 0 && pp->backbuf)
    c = pp->backbuf[ARB_LEN+pp->i];
  else
    c = pp->buf[pp->i];
  if(c=='\n') pp->line--;
  return c;
}

scope * gen_root_scope() {
  extern char * keywords[];
  scope *s = malloc(sizeof(scope));
  s->symbols = new_map();
  int i=0;
  do {
    map_set(s->symbols, keywords[i], strdup(keywords[i]), MAP_STRING);
  } while(keywords[++i]);
  return s;
}

token * get_token(parse_pkg * pp) {
  char * buf = malloc(1024);
  int i=0;
  char c;
  token * tok = malloc(sizeof(token));
  memset(buf, 0, 1204);
  printf("%d %d \n", pp->i, pp->left);
  while((c = buf_getc(pp)) != EOF) {
    printf("checking char %c(%i)\n",c,(int)c);
    if(!c) continue;
    printf("  not blank");
    if(c == ' ' || c == '\t' || c == '\n')
      break;
    printf("  not whitespace");
    if(c == '"') {
      buf_ungetc(pp);
      get_string(pp, tok);
      free(buf);
      return tok;
    }
    printf("  not a string");
    if(isalpha(c))
      buf[i++] == c;
    printf("  not alpha... dunno what it is\n");
  }
  printf("do we get here?\n");
  strncpy(tok->name, buf, ARB_LEN-1);
  return tok;
}

int get_string(parse_pkg * pp, token* tok) {
  char * buf = malloc(1024);
  int i = 0;
  char c;
  while((c = buf_getc(pp)) != EOF) {
    if(!c) continue;
    if(c == '\\') { }
    if(c == '"')
      break;
    buf[i++] == c;
  }
  strncpy(tok->name, buf, ARB_LEN-1);
  return 0;

}


