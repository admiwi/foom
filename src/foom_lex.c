#include "foom.h"
#include "foom_lex.h"
#include "foom_hash.h"
#include <ctype.h>

token * gen_token_chain(parse_pkg *pp) {
  token * tok, * t;
  t = tok = get_token(pp);
  while(t->next = get_token(pp)) {
    t->next->prev = t;
    t = t->next;
  }
  return tok; 
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
  if(pp->c=='\n') pp->line++;
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
      return new_token(pp->line, buf, string_sym);
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
  extern MAP keywords;
  extern char * _keywords[];
  memset(buf, 0, ARB_LEN);
  int *s;
  Symbol sym = id_sym;
  do {
    if(is_char(pp->c))
      buf[i++] = pp->c;
    else {
      if(s = map_get(keywords, buf)) {
        sym = *s;
      }
      buf_ungetc(pp);
      return new_token(pp->line, buf, sym);
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
      return new_token(pp->line, buf, integer_sym);
    }
  } while(buf_getc(pp) != EOF);
  return NULL;
}

token * get_operator(parse_pkg * pp) {
  int i = 0;
  char *buf = malloc(ARB_LEN);
  memset(buf, 0, ARB_LEN);
  Symbol sym = unknown_sym;
  switch(pp->c) {
    case '=':
      buf[i++] = pp->c;
      switch(buf_getc(pp)) {
        case '=':
          buf[i++] = pp->c;
          return new_token(pp->line, buf, eq_sym);
        default:
          buf_ungetc(pp);
      }
      return new_token(pp->line, buf, assign_sym);
    case '>':
      buf[i++] = pp->c;
      switch(buf_getc(pp)) {
        case '=':
          buf[i++] = pp->c;
          return new_token(pp->line, buf, ge_sym);
        default:
          buf_ungetc(pp);
      }
      return new_token(pp->line, buf, gt_sym);
    case '<':
      buf[i++] = pp->c;
      switch(buf_getc(pp)) {
        case '=':
          buf[i++] = pp->c;
          return new_token(pp->line, buf, le_sym);
        case '>':
          buf[i++] = pp->c;
          return new_token(pp->line, buf, neq_sym);
        default:
          buf_ungetc(pp);
      }
      return new_token(pp->line, buf, lt_sym);
    case '+': sym = plus_sym; break;
    case '-': sym = minus_sym; break;
    case '*': sym = star_sym; break;
    case '^': sym = carrot_sym; break;
    case '!': sym = bang_sym; break;
    case '&': sym = andper_sym; break;
    case '/': sym = slash_sym; break;
    case '.': sym = dot_sym; break;
    case '@': sym = at_sym; break;
    case '$': sym = dollar_sym; break;
    case ':': sym = colon_sym; break;
    case '`': sym = grave_sym; break;
    case '~': sym = tilda_sym; break;
    case '|': sym = bar_sym; break;
    case '(': sym = oparen_sym; break;
    case ')': sym = cparen_sym; break;
    case '{': sym = ocurly_sym; break;
    case '}': sym = ccurly_sym; break;
    default:
      return 0;
      
  }
  buf[i++] = pp->c;
  return new_token(pp->line, buf, sym);
}
token * new_token(int line, char* lexem, Symbol sym) {
  token * tok = malloc(sizeof(token));
  memset(tok, 0, sizeof(token));
  tok->lexem = lexem;
  tok->symbol = sym;
  tok->prev = NULL;
  tok->next = NULL;
  tok->line = line;
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


