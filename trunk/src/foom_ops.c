#include "foom.h"

FuncP func_tbl[100] = {NULL};

int if_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int switch_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int case_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int else_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int break_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int return_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}

//int try_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int catch_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int finally_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int throw_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int assert_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int import_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int namespace_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int class_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int extend_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int interface_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int mixin_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int virtual_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int is_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int was_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}

int as_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int for_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int while_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int loop_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int do_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int continue_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}

//int obj_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int int_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int dec_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int bool_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int func_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int bin_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int list_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int map_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int str_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}

int and_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int or_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int not_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int xor_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}

//int oparen_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int cparen_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int ocurly_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int ccurly_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int osquare_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int csquare_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int dquote_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int squote_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int id_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int string_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int integer_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int float_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
int lt_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int gt_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int le_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int ge_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int eq_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int neq_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int assign_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int plus_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int minus_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int star_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int carrot_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int bang_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int andper_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int slash_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int dot_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int at_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int dollar_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int colon_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int grave_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int tilda_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int bar_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int comma_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int dand_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int dor_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int dotdot_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int elipse_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}
int newline_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
}

//int semi_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int funccall_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int subscript_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int member_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int group_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
//}
//int unknown_func(object * ret, object * a1, object * a2, object * a3, object * a4, object * a5){
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
//  func_tbl[funccall_sym] = &funccall_func;
//  func_tbl[subscript_sym] = &subscript_func;
//  func_tbl[member_sym] = &member_func;
//  func_tbl[group_sym] = &group_func;
//  func_tbl[unknown_sym] = &unknown_func;
}





