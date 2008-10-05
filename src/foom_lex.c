#include "foom.h"
#include "foom_lex.h"
#include "foom_hash.h"
#include <ctype.h>

void process_file(char *file_name) {
  //        filename, file,  buf, backbuf,  i,    c, count, left, line
  parse_pkg pp = { "\0", NULL, "\0",    "\0",  0, '\0',     0,    0,   1};
  token * tok;
  scope *s = new_scope(NULL);
  strcpy(pp.filename, file_name);
  pp.file = fopen(file_name,"r");
 
  while(tok = get_token(&pp)){
    printf("Token: '%s' type %d\n", (char*)tok->data, tok->type);
    if(tok) free(tok);
  }
  print_errors();
}

char buf_getc(parse_pkg *pp) {
  if(!pp->left) {
    if(pp->buf && pp->count > ARB_LEN) 
      strncpy(pp->backbuf, &(pp->buf[pp->count - ARB_LEN]), ARB_LEN);
    pp->count = fread(pp->buf, 1, BUFSZ, pp->file);
    pp->left = pp->count;
    pp->i = 0;
    if(!pp->count) return pp->c = EOF;
  }
  pp->left--;
  if(pp->i<0 && pp->backbuf)
    pp->c = pp->backbuf[ARB_LEN+pp->i];
  else
    pp->c = pp->buf[pp->i];
  if(pp->c=='\n') pp->line--;
  pp->i++;
  return pp->c;
}

char buf_ungetc(parse_pkg *pp) {
  pp->left++;
  pp->i--;
  if(pp->i < 0 && pp->backbuf)
    pp->c = pp->backbuf[ARB_LEN+pp->i];
  else
    pp->c = pp->buf[pp->i];
  if(pp->c=='\n') pp->line--;
  return pp->c;
}


token * get_string(parse_pkg * pp) {
  int i = 0;
  int len = 1024;
  char * buf = malloc(1024);
  memset(buf, 0, 1024);
  char endc = pp->c;
  while(buf_getc(pp) != EOF) {
    if(!pp->c) continue;
    if(pp->c == '\\') { 
      switch(buf_getc(pp)) {
        case 'n': buf[i++] = '\n'; break;
        case 't': buf[i++] = '\t'; break;
        case '\\': buf[i++] = '\\'; break;
        case 'b': buf[i++] = '\b'; break;
        case '"': buf[i++] = '"'; break;
        case '$': buf[i++] = '$'; break;
        case '\'': buf[i++] = '\''; break;
        default: 
          add_error(ERR_WARN, pp->filename, pp->line, "invalid \\ sequence", buf);
          buf[i++] = pp->c;
      }
      continue;
    }
    //if(pp->c == '$') interpolation
    if(pp->c == endc)
      return new_token( buf, TOK_STR, ATTR_NONE, NULL, 0);
    buf[i++] = pp->c;
    if(i == len -1) {
      len += len;
      buf = resize_string(buf, len);
    }
  }
  return NULL;
}

token * get_symbol(parse_pkg * pp) {
  int i = 0;
  char *buf = malloc(ARB_LEN);
  extern map ** keywords;
  memset(buf, 0, ARB_LEN);
  do {
    if(is_char(pp->c))
      buf[i++] = pp->c;
    else {
      buf_ungetc(pp);
      return new_token( buf, 
        map_get(keywords, buf)?TOK_SYM:TOK_SYM|TOK_KW, 
        ATTR_NONE, NULL, 0);
    }
  } while(buf_getc(pp) != EOF);
  return NULL;
}

token * get_number(parse_pkg * pp) {
  int i = 0;
  char *buf = malloc(ARB_LEN);
  memset(buf, 0, ARB_LEN);
  do {
    if(is_num(pp->c))
      buf[i++] = pp->c;
    else {
      buf_ungetc(pp);
      return new_token( buf, TOK_NUM, ATTR_NONE, NULL, 0);
    }
  } while(buf_getc(pp) != EOF);
  return NULL;
}

token * get_operator(parse_pkg * pp) {
  int i = 0;
  char *buf = malloc(ARB_LEN);
  memset(buf, 0, ARB_LEN);
  switch(pp->c) {
    case '=':
      buf[i++] = pp->c;
      switch(buf_getc(pp)) {
        case '=':
          buf[i++] = pp->c;
          return new_token( buf, TOK_OP, ATTR_EQ, NULL, 0);
        default:
          buf_ungetc(pp);
      }
      return new_token( buf, TOK_OP, ATTR_ASSIGN, NULL, 0);
    case '>':
      switch(buf_getc(pp)) {
        case '=':
          return new_token( buf, TOK_OP, ATTR_GE, NULL, 0);
        default:
          buf_ungetc(pp);
      }
      return new_token( buf, TOK_OP, ATTR_GT, NULL, 0);
    case '<':
      switch(buf_getc(pp)) {
        case '=':
          buf[i++] = pp->c;
          return new_token( buf, TOK_OP, ATTR_LE, NULL, 0);
        case '>':
          buf[i++] = pp->c;
          return new_token( buf, TOK_OP, ATTR_NE, NULL, 0);
        default:
          buf_ungetc(pp);
      }
      return new_token( buf, TOK_OP, ATTR_LT, NULL, 0);
    default:
      buf[i++] = pp->c;
      return new_token( buf, TOK_OP, ATTR_NONE, NULL, 0);
      
  }
  return 0;
}
token * new_token(void* data, int type, int attr, funcp * func, char* args) {
  token * tok = malloc(sizeof(token));
  memset(tok, 0, sizeof(token));
  tok->data = data;
  tok->type = type;
  tok->attr = attr;
  tok->func = func;
  if(args)
    strcpy(tok->args, args);
  else
    tok->args[0] = 0;

  return tok;
}

token * get_token(parse_pkg * pp) {
  while(buf_getc(pp)) {
    if(pp->c == EOF) return NULL;
    //if(is_irrel(pp->c)) continue;
    if(is_ws(pp->c))
      continue;

    if(pp->c == '"' || pp->c=='\'') 
      return get_string(pp);

    if(is_num(pp->c))
      return get_number(pp);

    if(is_op(pp->c))
      return get_operator(pp);
 
    if(is_char(pp->c))
      return get_symbol(pp);
    printf("unprocessed char ( '%c' : 0x%02x )\n",pp->c,(int)pp->c);
  }
  return NULL;
}

scope * new_scope(scope *par) {
  scope * s = malloc(sizeof(scope));
  s->parent = par;
  s->symbols = new_map();
  return s;
}


