#include "foom.h"
#include "foom_lex.h"
#include "foom_hash.h"
#include <ctype.h>

void process_file(char *file_name) {
  //               file,  buf, backbuf,  i, count, left, line
  parse_pkg pp = { NULL, "\0",    "\0",  0,   0,       0,   1};
  token * tok;
  scope *s = new_scope(NULL);

  pp.file = fopen(file_name,"r");
 
  while(tok = get_token(&pp)){
    printf("Token: '%s' type %d\n", tok->name, tok->type);
    if(tok) free(tok);
  }
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

int get_operator(parse_pkg * pp, char *buf) {
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
token * new_token(char* name, int type, int attr, funcp * func, char* args) {
  token * tok = malloc(sizeof(token));
  memset(tok, 0, sizeof(token));
  strcpy(tok->name, name);
  tok->type = type;
  tok->attr = attr;
  tok->func = func;
  strcpy(tok->args, args);

  return tok;
}

token * get_token(parse_pkg * pp) {
  char * buf = malloc(1024);
  int type = TOK_UNKNOWN;
  int i=0;
  char c;
  map ** kws = get_keywords();
  memset(buf, 0, 1024);
  token * tok = NULL;

  while((c = buf_getc(pp)) != EOF) {
    if(is_irrel(c)) continue;
    if(is_ws(c)) {
      if(buf[0]==0)
        continue;
      else
        break;
    }

    if(c == '"') {
      if(buf[0]==0) {
        get_string(pp, buf);
        type = TOK_LIT_STR;
      } else buf_ungetc(pp);
      break;
    }

    if(is_num(c)) {
      buf_ungetc(pp);
      if(buf[0]==0) {
        get_number(pp, buf);
        type = TOK_LIT_NUM;
        break;
      } else {
        break;
      }
    }

    if(is_op(c)) {
      if(buf[0]) 
        buf_ungetc(pp);
      else{
        type = TOK_OPERATOR;
        buf[0] = c;
      }
      break;
    }

    if(is_char(c)) {
      buf[i++] = c;
      type = TOK_SYMBOL;
      continue;
    }
    printf("unprocessed char ( '%c' : 0x%02x )\n",c,(int)c);
  }
  if(c == EOF) return NULL;
  if(buf) {
    if(type == TOK_SYMBOL && map_get(kws, buf))
      type = TOK_KEYWORD;
    tok = new_token(buf, type, 0, NULL, "");
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


