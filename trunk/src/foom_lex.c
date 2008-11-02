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
  t->next = new_token(pp->line, "<EOF>", eof_sym);

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

int add_char(char c, int pos, char **buf, int len) {
  (*buf)[pos] = c;
  if(pos == len - 1) {
    len += len;
    (*buf) = resize_string(*buf, len);
  }
  return len;
}

token * get_string(parse_pkg * pp) {
  int i = 0;
  int len = 1024;
  char * buf = malloc(1024);
  memset(buf, 0, 1024);
  char endc = pp->c;
  while(buf_getc(pp) != EOF) {
    if(!pp->c) continue;
    if(endc == '"' && pp->c == '\\') {
      switch(buf_getc(pp)) {
        case 'n':
          len = add_char('n', i++, &buf, len);
          break;
        case 't':
          len = add_char('t', i++, &buf, len);
          break;
        case '\\':
          len = add_char('\\', i++, &buf, len);
          break;
        case 'b':
          len = add_char('b', i++, &buf, len);
          break;
        case '"':
          len = add_char('"', i++, &buf, len);
          break;
        case '$':
          len = add_char('$', i++, &buf, len);
          break;
        case '\'':
          len = add_char('\'', i++, &buf, len);
          break;
        default:
          add_error(ERR_WARN, pp->filename, pp->line, "invalid \\ sequence", buf);
          len = add_char(pp->c, i++, &buf, len);
      }
      continue;
    }
    if(endc == '\'' && pp->c == '\\') {
      switch(buf_getc(pp)) {
        case '\'':
          len = add_char('\'', i++, &buf, len);
          break;
        default:
          len = add_char('\\', i++, &buf, len);
      }
    }
    //if(pp->c == '$') interpolation
    if(pp->c == endc) {
      return new_token(pp->line, buf, string_sym);
    }
    len = add_char(pp->c, i++, &buf, len);
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
  add_error(ERR_WARN, pp->filename, pp->line, "error in get_symbol", buf);
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
  add_error(ERR_WARN, pp->filename, pp->line, "error in get_number", buf);
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
    case '.':
      buf[i++] = pp->c;
      sym = dot_sym;
      buf_getc(pp);
      if(pp->c == '.') {
        buf[i++] = pp->c;
        sym = dotdot_sym;
        buf_getc(pp);
        if(pp->c == '.') {
          buf[i++] = pp->c;
          sym = elipse_sym;
        } else
          buf_ungetc(pp);
      } else
        buf_ungetc(pp);
      return new_token(pp->line, buf, sym);
    case '+': sym = plus_sym; break;
    case '-': sym = minus_sym; break;
    case '*': sym = star_sym; break;
    case '^': sym = carrot_sym; break;
    case '!': sym = bang_sym; break;
    case '&': sym = andper_sym; break;
    case '/': sym = slash_sym; break;
    case '@': sym = at_sym; break;
    case '$': sym = dollar_sym; break;
    case ':': sym = colon_sym; break;
    case '`': sym = grave_sym; break;
    case '~': sym = tilda_sym; break;
    case '|': sym = bar_sym; break;
    case '(': sym = oparen_sym; break;
    case ')': sym = cparen_sym; break;
    case '[': sym = osquare_sym; break;
    case ']': sym = csquare_sym; break;
    case '{': sym = ocurly_sym; break;
    case '}': sym = ccurly_sym; break;
    case ';': sym = semi_sym; break;
    case ',': sym = comma_sym; break;
    default:
      add_error(ERR_WARN, pp->filename, pp->line, "error in get_operator", buf);
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
    //if(pp->c == '\n')
    //  return new_token(pp->line, "<newline>", newline_sym);
    if(pp->c == ';')
      return new_token(pp->line, ";", semi_sym);
    add_error(ERR_WARN, pp->filename, pp->line, "error in get_token unprocessed character", "");
  }

  return NULL;
}

scope * new_scope(scope *par) {
  scope * s = malloc(sizeof(scope));
  s->parent = par;
  s->symbols = new_map();
  return s;
}


