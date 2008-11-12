#include "foom.h"

FuncP func_tbl[100] = {NULL};

int if_func(void * ret, list * args){
  return 1;
}
int switch_func(void * ret, list * args){
  return 1;
}
int case_func(void * ret, list * args){
  return 1;
}
int else_func(void * ret, list * args){
  return 1;
}
int break_func(void * ret, list * args){
  return 1;
}
int return_func(void * ret, list * args){
  return 1;
}

//int try_func(void * ret, list * args){
//}
//int catch_func(void * ret, list * args){
//}
//int finally_func(void * ret, list * args){
//}
//int throw_func(void * ret, list * args){
//}
//int assert_func(void * ret, list * args){
//}
//int import_func(void * ret, list * args){
//}
//int namespace_func(void * ret, list * args){
//}
//int class_func(void * ret, list * args){
//}
//int extend_func(void * ret, list * args){
//}
//int interface_func(void * ret, list * args){
//}
//int mixin_func(void * ret, list * args){
//}
//int virtual_func(void * ret, list * args){
//}
//int is_func(void * ret, list * args){
//}
//int was_func(void * ret, list * args){
//}

int as_func(void * ret, list * args){
  return 1;
}
int for_func(void * ret, list * args){
  return 1;
}
int while_func(void * ret, list * args){
  return 1;
}
int loop_func(void * ret, list * args){
  return 1;
}
int do_func(void * ret, list * args){
  return 1;
}
int continue_func(void * ret, list * args){
  return 1;
}

//int obj_func(void * ret, list * args){
//}
//int int_func(void * ret, list * args){
//}
//int dec_func(void * ret, list * args){
//}
//int bool_func(void * ret, list * args){
//}
//int func_func(void * ret, list * args){
//}
//int bin_func(void * ret, list * args){
//}
//int list_func(void * ret, list * args){
//}
//int map_func(void * ret, list * args){
//}
//int str_func(void * ret, list * args){
//}

int and_func(void * ret, list * args){
  return 1;
}
int or_func(void * ret, list * args){
  return 1;
}
int not_func(void * ret, list * args){
  return 1;
}
int xor_func(void * ret, list * args){
  return 1;
}

//int oparen_func(void * ret, list * args){
//}
//int cparen_func(void * ret, list * args){
//}
//int ocurly_func(void * ret, list * args){
//}
//int ccurly_func(void * ret, list * args){
//}
//int osquare_func(void * ret, list * args){
//}
//int csquare_func(void * ret, list * args){
//}
//int dquote_func(void * ret, list * args){
//}
//int squote_func(void * ret, list * args){
//}
//int id_func(void * ret, list * args){
//}
//int string_func(void * ret, list * args){
//}
//int integer_func(void * ret, list * args){
//}
//int float_func(void * ret, list * args){
//}
int lt_func(void * ret, list * args){
  return 1;
}
int gt_func(void * ret, list * args){
  return 1;
}
int le_func(void * ret, list * args){
  return 1;
}
int ge_func(void * ret, list * args){
  return 1;
}
int eq_func(void * ret, list * args){
  return 1;
}
int neq_func(void * ret, list * args){
  return 1;
}
int assign_func(void * ret, list * args){
  return 1;
}
int plus_func(void * ret, list * args){
  return 1;
}
int minus_func(void * ret, list * args){
  return 1;
}
int star_func(void * ret, list * args){
  return 1;
}
int carrot_func(void * ret, list * args){
  return 1;
}
int bang_func(void * ret, list * args){
  return 1;
}
int andper_func(void * ret, list * args){
  return 1;
}
int slash_func(void * ret, list * args){
  return 1;
}
int dot_func(void * ret, list * args){
  return 1;
}
int at_func(void * ret, list * args){
  return 1;
}
int dollar_func(void * ret, list * args){
  return 1;
}
int colon_func(void * ret, list * args){
  return 1;
}
int grave_func(void * ret, list * args){
  return 1;
}
int tilda_func(void * ret, list * args){
  return 1;
}
int bar_func(void * ret, list * args){
  return 1;
}
int comma_func(void * ret, list * args){
  return 1;
}
int dand_func(void * ret, list * args){
  return 1;
}
int dor_func(void * ret, list * args){
  return 1;
}
int dotdot_func(void * ret, list * args){
  return 1;
}
int elipse_func(void * ret, list * args){
  return 1;
}
int newline_func(void * ret, list * args){
  return 1;
}

//int semi_func(void * ret, list * args){
//}

int funccall_func(void * ret, list * args){
  return 1;
}
int subscript_func(void * ret, list * args){
  return 1;
}
int member_func(void * ret, list * args){
  return 1;
}
int group_func(void * ret, list * args){
  return 1;
}
//int unknown_func(void * ret, list * args){
//}

void init_funcs() {
  func_tbl[if_sym] = &if_func;
  func_tbl[switch_sym] = &switch_func;
  func_tbl[case_sym] = &case_func;
  func_tbl[else_sym] = &else_func;
  func_tbl[break_sym] = &break_func;
  func_tbl[return_sym] = &return_func;

//  func_tbl[try_sym] = &try_func;
//  func_tbl[catch_sym] = &catch_func;
//  func_tbl[finally_sym] = &finally_func;
//  func_tbl[throw_sym] = &throw_func;
//  func_tbl[assert_sym] = &assert_func;

//  func_tbl[import_sym] = &import_func;
//  func_tbl[namespace_sym] = &namespace_func;
//  func_tbl[class_sym] = &class_func;
//  func_tbl[extend_sym] = &extend_func;
//  func_tbl[interface_sym] = &interface_func;
//  func_tbl[mixin_sym] = &mixin_func;
//  func_tbl[virtual_sym] = &virtual_func;
//  func_tbl[is_sym] = &is_func;
//  func_tbl[was_sym] = &was_func;

  func_tbl[as_sym] = &as_func;

  func_tbl[for_sym] = &for_func;
  func_tbl[while_sym] = &while_func;
  func_tbl[loop_sym] = &loop_func;
  func_tbl[do_sym] = &do_func;
  func_tbl[continue_sym] = &continue_func;

//  func_tbl[obj_sym] = &obj_func;
//  func_tbl[int_sym] = &int_func;
//  func_tbl[dec_sym] = &dec_func;
//  func_tbl[bool_sym] = &bool_func;
//  func_tbl[func_sym] = &func_func;
//  func_tbl[bin_sym] = &bin_func;
//  func_tbl[list_sym] = &list_func;
//  func_tbl[map_sym] = &map_func;
//  func_tbl[str_sym] = &str_func;

  func_tbl[and_sym] = &and_func;
  func_tbl[or_sym] = &or_func;
  func_tbl[not_sym] = &not_func;
  func_tbl[xor_sym] = &xor_func;

//  func_tbl[oparen_sym] = &oparen_func;
//  func_tbl[cparen_sym] = &cparen_func;
//  func_tbl[ocurly_sym] = &ocurly_func;
//  func_tbl[ccurly_sym] = &ccurly_func;
//  func_tbl[osquare_sym] = &osquare_func;
//  func_tbl[csquare_sym] = &csquare_func;
//  func_tbl[dquote_sym] = &dquote_func;
//  func_tbl[squote_sym] = &squote_func;
//  func_tbl[id_sym] = &id_func;
//  func_tbl[string_sym] = &string_func;
//  func_tbl[integer_sym] = &integer_func;
//  func_tbl[float_sym] = &float_func;

  func_tbl[lt_sym] = &lt_func;
  func_tbl[gt_sym] = &gt_func;
  func_tbl[le_sym] = &le_func;
  func_tbl[ge_sym] = &ge_func;
  func_tbl[eq_sym] = &eq_func;
  func_tbl[neq_sym] = &neq_func;
  func_tbl[assign_sym] = &assign_func;
  func_tbl[plus_sym] = &plus_func;
  func_tbl[minus_sym] = &minus_func;
  func_tbl[star_sym] = &star_func;
  func_tbl[carrot_sym] = &carrot_func;
  func_tbl[bang_sym] = &bang_func;
  func_tbl[andper_sym] = &andper_func;
  func_tbl[slash_sym] = &slash_func;
  func_tbl[dot_sym] = &dot_func;
  func_tbl[at_sym] = &at_func;
  func_tbl[dollar_sym] = &dollar_func;
  func_tbl[colon_sym] = &colon_func;
  func_tbl[grave_sym] = &grave_func;
  func_tbl[tilda_sym] = &tilda_func;
  func_tbl[bar_sym] = &bar_func;
  func_tbl[comma_sym] = &comma_func;

  func_tbl[dand_sym] = &dand_func;
  func_tbl[dor_sym] = &dor_func;
  func_tbl[dotdot_sym] = &dotdot_func;

  func_tbl[elipse_sym] = &elipse_func;

//  func_tbl[newline_sym] = &newline_func;
//  func_tbl[semi_sym] = &semi_func;

  func_tbl[funccall_sym] = &funccall_func;
  func_tbl[subscript_sym] = &subscript_func;
  func_tbl[member_sym] = &member_func;
  func_tbl[group_sym] = &group_func;

}





