#include "foom.h"
#include "foom_test.h"
SYMBOLS;
FuncP func_tbl[100] = {NULL};

object * if_func(ast * op){
  ast * cond, * exec;
  cond = op->op.binary.left;
  exec = op->op.binary.right;
  printf("\nif");
  decend_ast(cond);
  printf("\n");
  if(exec->tag == binary_ast && exec->op.binary.oper == else_sym) {
    decend_ast(exec->op.binary.left);
    printf("\nelse\n");
    decend_ast(exec->op.binary.right);
  } else
  decend_ast(exec);
  printf("\n");
}
object * switch_func(ast * op){
}
object * case_func(ast * op){
}
/* not needed, handled in if
object * else_func(ast * op){
}
*/
object * break_func(ast * op){
}
object * return_func(ast * op){
}

//object * try_func(ast * op){
//}
//object * catch_func(ast * op){
//}
//object * finally_func(ast * op){
//}
//object * throw_func(ast * op){
//}
//object * assert_func(ast * op){
//}
//object * import_func(ast * op){
//}
//object * namespace_func(ast * op){
//}
//object * class_func(ast * op){
//}
//object * extend_func(ast * op){
//}
//object * interface_func(ast * op){
//}
//object * mixin_func(ast * op){
//}
//object * virtual_func(ast * op){
//}
//object * is_func(ast * op){
//}
//object * was_func(ast * op){
//}

object * as_func(ast * op){
}
object * for_func(ast * op){
  ast * init = op->op.binary.left;
  ast_list * c = init->op.block.stmts;
  ast * e = op->op.binary.right;
  printf("for(");
  decend_ast(c->node);
  c = c->next;
  printf("; ");
  decend_ast(c->node);
  c = c->next;
  printf("; ");
  decend_ast(c->node);
  printf(")\n");
  decend_ast(e);
}
object * while_func(ast * op){
}
object * loop_func(ast * op){
}
object * do_func(ast * op){
}
object * continue_func(ast * op){
}

//object * obj_func(ast * op){
//}
//object * int_func(ast * op){
//}
//object * dec_func(ast * op){
//}
//object * bool_func(ast * op){
//}
//object * func_func(ast * op){
//}
//object * bin_func(ast * op){
//}
//object * list_func(ast * op){
//}
//object * map_func(ast * op){
//}
//object * str_func(ast * op){
//}

object * and_func(ast * op){
}
object * or_func(ast * op){
}
object * not_func(ast * op){
}
object * xor_func(ast * op){
}

//object * oparen_func(ast * op){
//}
//object * cparen_func(ast * op){
//}
//object * ocurly_func(ast * op){
//}
//object * ccurly_func(ast * op){
//}
//object * osquare_func(ast * op){
//}
//object * csquare_func(ast * op){
//}
//object * dquote_func(ast * op){
//}
//object * squote_func(ast * op){
//}
//object * id_func(ast * op){
//}
//object * string_func(ast * op){
//}
//object * integer_func(ast * op){
//}
//object * float_func(ast * op){
//}
object * lt_func(ast * op){
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  decend_ast(l);
  printf(" < ");
  decend_ast(r);
}
object * gt_func(ast * op){
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  decend_ast(l);
  printf(" > ");
  decend_ast(r);
}
object * le_func(ast * op){
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  decend_ast(l);
  printf(" <= ");
  decend_ast(r);
}
object * ge_func(ast * op){
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  decend_ast(l);
  printf(" >= ");
  decend_ast(r);
}
object * eq_func(ast * op){
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  decend_ast(l);
  printf(" == ");
  decend_ast(r);
}
object * neq_func(ast * op){
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  decend_ast(l);
  printf(" <> ");
  decend_ast(r);
}
object * assign_func(ast * op){
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  decend_ast(l);
  printf(" = ");
  decend_ast(r);
}
object * plus_func(ast * op){
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  decend_ast(l);
  printf(" + ");
  decend_ast(r);
}
object * minus_func(ast * op){
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  decend_ast(l);
  printf(" - ");
  decend_ast(r);
}
object * star_func(ast * op){
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  decend_ast(l);
  printf(" * ");
  decend_ast(r);
}
object * carrot_func(ast * op){
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  decend_ast(l);
  printf(" ^ ");
  decend_ast(r);
}
object * bang_func(ast * op){
}
object * andper_func(ast * op){
}
object * slash_func(ast * op){
}
object * dot_func(ast * op){
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  decend_ast(l);
  printf(".");
  decend_ast(r);
}
object * at_func(ast * op){
}
object * dollar_func(ast * op){
}
object * colon_func(ast * op){
}
object * grave_func(ast * op){
}
object * tilda_func(ast * op){
}
object * bar_func(ast * op){
}
object * comma_func(ast * op){
}
object * dand_func(ast * op){
}
object * dor_func(ast * op){
}
object * dotdot_func(ast * op){
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  decend_ast(l);
  printf("..");
  decend_ast(r);
}
object * elipse_func(ast * op){
}
object * newline_func(ast * op){
}

//object * semi_func(ast * op){
//}

object * funccall_func(ast * op){
  ast * func = op->op.binary.left;
  ast * args = op->op.binary.right;
  printf("%s(",func->op.Id);
  decend_ast(args);
  printf(")");
}
object * subscript_func(ast * op){
  ast * var = op->op.binary.left;
  ast * sub = op->op.binary.right;
  decend_ast(var);
  printf("[");
  decend_ast(sub);
  printf("]");
}
object * member_func(ast * op){
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  decend_ast(l);
  printf(".");
  decend_ast(r);
}
object * group_func(ast * op){
  printf("(");
  decend_ast(op->op.unary.arg);
  printf(")");
}
object * declare_func(ast * op){
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  object * o = find_obj(l->op.obj->val.Class->native_type);
  o->name = strdup(r->op.Id);
  map_set(l->scp->symbols, o->name, o, MAP_OBJECT);
  printf("%s %s", l->op.obj->name, r->op.Id);
  return o;
}
object * generic_func(ast * op) {
  switch(op->tag) {
    case binary_ast:
      printf("(");
      printf("%s:", _symbols_[op->op.binary.oper]);
      decend_ast(op->op.binary.left);
      printf(",");
      decend_ast(op->op.binary.right);
      printf(")");
      break;
    case unary_ast:
      printf("(%s:", _symbols_[op->op.unary.oper]);
      decend_ast(op->op.unary.arg);
      break;
    default:
      printf("\n***error generic function***\n");
  }
}
//object * unknown_func(ast * op){
//}



void init_funcs() {
  int i;
  for(i = 0;i<100;i++)
    func_tbl[i] = &generic_func;
  func_tbl[if_sym] = &if_func;

 // func_tbl[switch_sym] = &switch_func;
 // func_tbl[case_sym] = &case_func;

  //func_tbl[else_sym] = &else_func; not needed, handled in 'if'

/*
  func_tbl[break_sym] = &break_func;
  func_tbl[return_sym] = &return_func;
  func_tbl[as_sym] = &as_func;
 */
  func_tbl[for_sym] = &for_func;
 /*
  func_tbl[while_sym] = &while_func;
  func_tbl[loop_sym] = &loop_func;
  func_tbl[do_sym] = &do_func;
  func_tbl[continue_sym] = &continue_func;
  func_tbl[and_sym] = &and_func;
  func_tbl[or_sym] = &or_func;
  func_tbl[not_sym] = &not_func;
  func_tbl[xor_sym] = &xor_func;
 */
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
  /*
  func_tbl[bang_sym] = &bang_func;
  func_tbl[andper_sym] = &andper_func;
  func_tbl[slash_sym] = &slash_func;
  */
  func_tbl[dot_sym] = &dot_func;
  func_tbl[dotdot_sym] = &dotdot_func;
  /*
  func_tbl[at_sym] = &at_func;
  func_tbl[dollar_sym] = &dollar_func;
  func_tbl[colon_sym] = &colon_func;
  func_tbl[grave_sym] = &grave_func;
  func_tbl[tilda_sym] = &tilda_func;
  func_tbl[bar_sym] = &bar_func;
  func_tbl[comma_sym] = &comma_func;
  func_tbl[dand_sym] = &dand_func;
  func_tbl[dor_sym] = &dor_func;

  func_tbl[elipse_sym] = &elipse_func;
  */
  func_tbl[funccall_sym] = &funccall_func;
  func_tbl[subscript_sym] = &subscript_func;
  func_tbl[member_sym] = &member_func;
  func_tbl[group_sym] = &group_func;
  func_tbl[declare_sym] = &declare_func;



//  func_tbl[obj_sym] = &obj_func;
//  func_tbl[int_sym] = &int_func;
//  func_tbl[dec_sym] = &dec_func;
//  func_tbl[bool_sym] = &bool_func;
//  func_tbl[func_sym] = &func_func;
//  func_tbl[bin_sym] = &bin_func;
//  func_tbl[list_sym] = &list_func;
//  func_tbl[map_sym] = &map_func;
//  func_tbl[str_sym] = &str_func;
//  func_tbl[try_sym] = &try_func;
//  func_tbl[catch_sym] = &catch_func;
//  func_tbl[finally_sym] = &finally_func;
//  func_tbl[throw_sym] = &throw_func;
//  func_tbl[assert_sym] = &assert_func;
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
//  func_tbl[import_sym] = &import_func;
//  func_tbl[namespace_sym] = &namespace_func;
//  func_tbl[class_sym] = &class_func;
//  func_tbl[extend_sym] = &extend_func;
//  func_tbl[interface_sym] = &interface_func;
//  func_tbl[mixin_sym] = &mixin_func;
//  func_tbl[virtual_sym] = &virtual_func;
//  func_tbl[is_sym] = &is_func;
//  func_tbl[was_sym] = &was_func;
//  func_tbl[newline_sym] = &newline_func;
//  func_tbl[semi_sym] = &semi_func;

}
