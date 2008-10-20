#ifndef _FOOM_
#define _FOOM_

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFSZ 4096
#define ARB_LEN 64

#define TOK_UNK (0)
#define TOK_KW  (1<<0)
#define TOK_NUM (1<<1)
#define TOK_STR (1<<2)
#define TOK_OP  (1<<3)
#define TOK_SYM (1<<4)
// 0x01-0x1f  ctrl chars

#define STMT "\x1"
#define STMTS "\x2"
#define EXPR "\x3"
#define CLOSURE "\x4"
#define WS "\x5" 
#define TYPE "\x6"
#define ID "\x7"
#define TERM "\x8"
#define OP "\x9"
#define LITERAL "\xA"
#define KEYWORD "\xB"


#define ATTR_NONE 0
#define ATTR_EQ 1
#define ATTR_LT 2
#define ATTR_GT 3
#define ATTR_LE 4
#define ATTR_GE 5
#define ATTR_NE 6

#define ATTR_ASSIGN 7
//literals
#define ATTR_INTEGER 8
#define ATTR_FLOAT 9
#define ATTR_STRING 10
//ids
#define ATTR_KEYWORD 11
#define ATTR_SYMBOL 12
//statments
#define ATTR_IF 13
#define ATTR_WHILE 14
#define ATTR_CASE 15
#define ATTR_DECLARE 16


#define ERR_WARN  0
#define ERR_ERROR 1

void add_error(int, char*, int, char*, char*);
void print_errors();

typedef enum { 
  end_sym, //0
  if_sym, switch_sym, case_sym, else_sym, break_sym, //5
  return_sym, // 6
  try_sym, catch_sym, finally_sym, throw_sym, assert_sym, //11
  import_sym, namespace_sym, //13
  //classes
  class_sym, extend_sym, interface_sym, mixin_sym, virtual_sym, //18
  //type inspection and cast
  is_sym, was_sym, as_sym, //21
  //statments
  for_sym, while_sym, loop_sym, do_sym, continue_sym, //26
  //types
  obj_sym, int_sym, dec_sym, bool_sym, func_sym, bin_sym, list_sym, map_sym,// 34
  //logicals
  and_sym, or_sym, not_sym, xor_sym, //38
  //containers
  oparen_sym, cparen_sym,  //40
  ocurly_sym, ccurly_sym, //42
  osquare_sym, csquare_sym, //44
  dquote_sym, squote_sym, //46
  //others
  id_sym, string_sym, integer_sym, float_sym, //50
  //  <      >        <=     >=       ==      <>          =
  lt_sym, gt_sym, le_sym, ge_sym, eq_sym, neq_sym, assign_sym, //57
  //    +         -        *          ^        !          &         /
  plus_sym, minus_sym, star_sym, carrot_sym, bang_sym, andper_sym, slash_sym, //64
  //   .      @          $         :         `         ~              |
  dot_sym, at_sym, dollar_sym, colon_sym, grave_sym, tilda_sym, bar_sym, //71
  //    &&       ||
  dand_sym, dor_sym, // 73
  unknown_sym // 74
} Symbol;

#include "foom_typedefs.h"
#include "foom_util.h"

#endif

