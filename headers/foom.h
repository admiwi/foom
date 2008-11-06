#ifndef _FOOM_
#define _FOOM_

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFSZ 4096
#define ARB_LEN 64
#define ARB_SLEN 16

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
  //statements
  for_sym, while_sym, loop_sym, do_sym, continue_sym, //26
  //types
  obj_sym, int_sym, dec_sym, bool_sym, func_sym, bin_sym, list_sym, map_sym, str_sym, // 35
  //logicals
  and_sym, or_sym, not_sym, xor_sym, //39
  //containers
  oparen_sym, cparen_sym,  //41
  ocurly_sym, ccurly_sym, //43
  osquare_sym, csquare_sym, //45
  dquote_sym, squote_sym, //47
  //others
  id_sym, string_sym, integer_sym, float_sym, //51
  //  <      >        <=     >=       ==      <>          =
  lt_sym, gt_sym, le_sym, ge_sym, eq_sym, neq_sym, assign_sym, //58
  //    +         -        *          ^        !          &         /
  plus_sym, minus_sym, star_sym, carrot_sym, bang_sym, andper_sym, slash_sym, //65
  //   .      @          $         :         `         ~              |
  dot_sym, at_sym, dollar_sym, colon_sym, grave_sym, tilda_sym, bar_sym, comma_sym, //71
  //    &&       ||
  dand_sym, dor_sym, // 75
  // ..          ...
  dotdot_sym, elipse_sym, //77
  // \n           ;
  newline_sym, semi_sym, //79
  funccall_sym, subscript_sym, member_sym, group_sym,  //82
  unknown_sym // 83
} Symbol;

#include "foom_typedefs.h"
#include "foom_util.h"

#endif

