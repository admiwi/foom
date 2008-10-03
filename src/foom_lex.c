#include "foom.h"
#include "foom_lex.h"
#include "foom_hash.h"
#include <ctype.h>

void process_file(char *file_name) {
  //               file,  buf, backbuf,  i, count, left, line
  parse_pkg pp = { NULL, "\0",    "\0",  0,   0,       0,   1};
  token * tok;
  scope *s = new_scope(NULL);
  map ** kws = get_keywords();

  pp.file = fopen(file_name,"r");
 
  do {
    tok = get_token(&pp);
    printf("Heres the name:  %s\n", tok->name);
    if(tok) free(tok);
  } while(tok);
  
  tok = get_token(&pp);
  printf("Heres the name:  %s\n", tok->name);
  free(tok);
}

char buf_getc(parse_pkg *pp) {
  char c;
  if(!pp->left) {
    if(pp->buf && pp->count > ARB_LEN) 
      strncpy(pp->backbuf, &(pp->buf[pp->count - ARB_LEN]), ARB_LEN);
    pp->count = fread(pp->buf, 1, BUFSZ, pp->file);
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

map ** get_keywords() {
  extern char * keywords[];
  map ** kws = new_map();
  int i=0;
  do {
    map_set(kws, keywords[i], strdup(keywords[i]), MAP_STRING);
  } while(keywords[++i]);
  return kws;
}

int get_string(parse_pkg * pp, char *buf) {
  int i = 0;
  char c;
  while((c = buf_getc(pp)) != EOF) {
    if(!c) continue;
    if(c == '\\') { }
    if(c == '"')
      break;
    buf[i++] = c;
  }
  return 0;
}

int get_number(parse_pkg * pp, char *buf) {
  int i = 0;
  char c;
  while((c = buf_getc(pp)) != EOF) {
    if(is_num(c))
      buf[i++] = c;
    else {
      buf_ungetc(pp);
      break;
    }
  }
  return 0;
}

token * new_token() {
  token * tok = malloc(sizeof(token));
  memset(tok, 0, sizeof(token));
  return tok;
}

token * get_token(parse_pkg * pp) {
  char * buf = malloc(1024);
  int i=0;
  char c;
  memset(buf, 0, 1024);
  token * tok = NULL;

  while((c = buf_getc(pp)) != EOF) {
    if(is_ws(c)) {
      if(buf[0]==0)
        continue;
      else
        break;
    }

    if(c == '"') {
      if(buf[0]==0) {
        get_string(pp, buf);
      } else {
        buf_ungetc(pp);
        break;
      }
    }

    if(is_num(c)) {
      buf_ungetc(pp);
      if(buf[0]==0) {
        get_number(pp, buf);
        break;
      } else {
        break;
      }
    }

    if(is_op(c)) {
      if(buf[0]) 
        buf_ungetc(pp);
      else
        buf[0] = c;
      break;
    }

    if(is_char(c)) {
      buf[i++] = c;
      continue;
    }
    printf("unprocessed char ( '%c' : 0x%02x )\n",c,(int)c);
  }
  if(c == EOF) return NULL;
  if(buf) {
     tok = new_token();
    strncpy(tok->name, buf, ARB_LEN-1);
    free(buf);
  }
  return tok;

}

scope * new_scope(scope *par) {
  scope * s = malloc(sizeof(scope));
  s->parent = par;
  s->symbols = new_map();
  return s;
}


