#include "foom.h"
#include "foom_feval.h"
SYMBOLS;

FuncP feval_tbl[100] = {NULL};


//_symbols_
object * id_feval(ast * op){
  object * o = scope_get(op->scp, op->op.Id);
  return o;
}

object * member_feval(ast * op){
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  if(r->tag == binary_ast) {
    object * ro = member_feval(r);
    if(ro->null)
      return ro;
    else
      return get_member(ro, l->op.Id);
  }
  if(r->tag == id_ast) {
    return get_member(id_feval(r), l->op.Id);
  }
  return new_object(false);
}

object * object_feval(ast * op){
  return op->op.obj;
}

object * call_args_feval(ast *a) {
  ast_list * al;
  object * ret = new_list();
  list * l;
  l = ret->val.List = list_node();
  if(a->op.block.stmts)
    for(al = a->op.block.stmts;al->node;al = al->next) {
      l->obj = feval(al->node);
      l->next = list_node();
      l = l->next;
    }
  else
    printf("**BLOCK ERROR**\n");
  return ret;
}
object * block_feval(ast * a) {
  ast_list * al;
  object * o;
  o = new_func();
  //o->val.Func = malloc(sizeof(func));
  o->val.Func->flags = func_foom;
  o->val.Func->f.acode = a;
  return o;
  /*
  if(a->op.block.stmts)
    for(al = a->op.block.stmts;al->node;al = al->next) {
      ret = feval(al->node);
    }
  else
    printf("**BLOCK ERROR**\n");
  return ret;
  */
}

object * feval(ast * a) {
  object *o;
  switch(a->tag) {
    case binary_ast:
      return feval_tbl[a->op.binary.oper](a);
    case unary_ast:
      return feval_tbl[a->op.unary.oper](a);
    case id_ast:
      return id_feval(a);
    case obj_ast:
      return object_feval(a);
    case func_args_ast:
      return call_args_feval(a);
    case block_ast:
      return block_feval(a);
    default:
      printf("ERROR in feval\n");
  }
}

void start_feval(ast * a){
  ast_list * al;
  object * o;
  if(a->op.block.stmts)
    for(al = a->op.block.stmts;al->node;al = al->next) {
      o = feval(al->node);
    }
  else
    printf("**BLOCK ERROR**\n");
}



object * if_feval(ast * op){
  ast * cond, * eval;
  cond = op->op.binary.left;
  eval = op->op.binary.right;
  bool bc;
  object * oc = feval(cond), *ro;
  bc = bool_test(oc);

  if(eval->tag == binary_ast && eval->op.binary.oper == else_sym) {
    if(bc) {
      ro = feval(eval->op.binary.left);
    } else {
      ro = feval(eval->op.binary.right);
    }
    if(ro->type == func_sym)
      ro = func_call(ro, NULL, NULL);
    return ro;
  }
  if(bc) {
    ro = feval(eval);
    if(ro->type == func_sym)
      ro = func_call(ro, NULL, NULL);
    return ro;
  }
  return NULL;
}
object * switch_feval(ast * op){
}
object * case_feval(ast * op){
}
/* not needed, handled in if
object * else_feval(ast * op){
}
*/
object * break_feval(ast * op){
}
object * return_feval(ast * op){
}

//object * try_feval(ast * op){
//}
//object * catch_feval(ast * op){
//}
//object * finally_feval(ast * op){
//}
//object * throw_feval(ast * op){
//}
//object * assert_feval(ast * op){
//}
//object * import_feval(ast * op){
//}
//object * namespace_feval(ast * op){
//}
//object * class_feval(ast * op){
//}
//object * extend_feval(ast * op){
//}
//object * interface_feval(ast * op){
//}
//object * mixin_feval(ast * op){
//}
//object * virtual_feval(ast * op){
//}
//object * is_feval(ast * op){
//}
//object * was_feval(ast * op){
//}

object * as_feval(ast * op){
}
object * for_feval(ast * op){
  ast * top = op->op.binary.left;
  ast_list * c = top->op.block.stmts;
  ast * e = op->op.binary.right;
  ast * comp, * inc;
  object * co, * io, * eo;

  feval(c->node);
  c = c->next;
  comp = c->node;
  c = c->next;
  inc = c->node;
  co = feval(comp);
  while(bool_test(co)) {
    eo = feval(e);
    if(eo->type == func_sym)
      func_call(eo, NULL, NULL);
    io = feval(inc);
    co = feval(comp);
  }

}
object * while_feval(ast * op){
}
object * loop_feval(ast * op){
}
object * do_feval(ast * op){
}
object * continue_feval(ast * op){
}

//object * obj_feval(ast * op){
//}
//object * int_feval(ast * op){
//}
//object * dec_feval(ast * op){
//}
//object * bool_feval(ast * op){
//}
//object * func_feval(ast * op){
//}
//object * bin_feval(ast * op){
//}
//object * list_feval(ast * op){
//}
//object * map_feval(ast * op){
//}
//object * str_feval(ast * op){
//}

object * and_feval(ast * op){
}
object * or_feval(ast * op){
}
object * not_feval(ast * op){
}
object * xor_feval(ast * op){
}

//object * oparen_feval(ast * op){
//}
//object * cparen_feval(ast * op){
//}
//object * ocurly_feval(ast * op){
//}
//object * ccurly_feval(ast * op){
//}
//object * osquare_feval(ast * op){
//}
//object * csquare_feval(ast * op){
//}
//object * dquote_feval(ast * op){
//}
//object * squote_feval(ast * op){
//}

//object * string_feval(ast * op){
//}
//object * integer_feval(ast * op){
//}
//object * float_feval(ast * op){
//}

object * compare_feval(ast * op) {
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  object * lo = feval(l);
  object * ro = feval(r);
  object * sf = get_member(lo, "compare");
  return func_call(sf, lo, ro);
}

object * lt_feval(ast * op){
  object * ro = compare_feval(op);
  object * br = new_bool();
  br->val.Bool =  (ro->val.Int == -1 ? true : false);
  return br;
}
object * gt_feval(ast * op){
  object * ro = compare_feval(op);
  object * br = new_bool();
  br->val.Bool =  (ro->val.Int == 1 ? true : false);
  return br;
}
object * le_feval(ast * op){
  object * ro = compare_feval(op);
  object * br = new_bool();
  br->val.Bool =  (ro->val.Int < 1 ? true : false);
  return br;
}
object * ge_feval(ast * op){
  object * ro = compare_feval(op);
  object * br = new_bool();
  br->val.Bool =  (ro->val.Int > -1 ? true : false);
  return br;
}
object * eq_feval(ast * op){
  object * ro = compare_feval(op);
  object * br = new_bool();
  br->val.Bool =  (ro->val.Int == 0 ? true : false);
  return br;
}
object * neq_feval(ast * op){
  object * ro = compare_feval(op);
  object * br = new_bool();
  br->val.Bool =  (ro->val.Int != 0 ? true : false);
  return br;
}
object * assign_feval(ast * op){
  object * o;
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  object * lo = feval(l);
  object * ro = feval(r);
  o = set_member(lo, "self", ro);
  return o;
}

object * bop_feval(ast * op, Symbol s) {
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  object * lo = feval(l);
  object * ro = feval(r);
  object * sf = get_member(lo, _symbols_[s]);
  return func_call(sf, lo, ro);
}

object * plus_feval(ast * op){
  return bop_feval(op, plus_sym);
}
object * minus_feval(ast * op){
  return bop_feval(op, minus_sym);
}
object * star_feval(ast * op){
  return bop_feval(op, star_sym);
}
object * carrot_feval(ast * op){
  return bop_feval(op, carrot_sym);
}
object * bang_feval(ast * op){
}
object * andper_feval(ast * op){
}
object * slash_feval(ast * op){
}
object * dot_feval(ast * op){
  return bop_feval(op, dot_sym);
}
object * at_feval(ast * op){
}
object * dollar_feval(ast * op){
}
object * colon_feval(ast * op){
}
object * grave_feval(ast * op){
}
object * tilda_feval(ast * op){
}
object * bar_feval(ast * op){
}
object * comma_feval(ast * op){
}
object * dand_feval(ast * op){
}
object * dor_feval(ast * op){
}
object * dotdot_feval(ast * op){
  return bop_feval(op, dotdot_sym);
}
object * elipse_feval(ast * op){
  return bop_feval(op, elipse_sym);
}
object * newline_feval(ast * op){
}

//object * semi_feval(ast * op){
//}

object * funccall_feval(ast * op){
  ast * f = op->op.binary.left;
  ast * a = op->op.binary.right;
  object * of = feval(f);
  object * oa = feval(a);
  return func_call(of, of->parent, oa);
}
object * subscript_feval(ast * op){
  ast * var = op->op.binary.left;
  ast * sub = op->op.binary.right;
  object * v = feval(var);
  if(!v) {
    fprintf(stderr, "symbol not found (%s)\n", var->tag == id_ast? var->op.Id : var->op.obj->name);
    return new_object();
  }
  object * s = feval(sub);
  object * sf = get_member(v, _symbols_[subscript_sym]);
  return func_call(sf, v, s);
}

object * group_feval(ast * op){
  return feval(op->op.unary.arg);
}
object * declare_feval(ast * op){
  ast * l = op->op.binary.left;
  ast * r = op->op.binary.right;
  object * o = find_obj(l->op.obj->val.Class->native_type);
  o->name = strdup(r->op.Id);
  scope_set(l->scp, o, map_object);
  return o;
}
object * generic_feval(ast * op) {
  switch(op->tag) {
    case binary_ast:
      printf("(");
      printf("%s:", _symbols_[op->op.binary.oper]);
      feval(op->op.binary.left);
      printf(",");
      feval(op->op.binary.right);
      printf(")");
      break;
    case unary_ast:
      printf("(%s:", _symbols_[op->op.unary.oper]);
      feval(op->op.unary.arg);
      break;
    default:
      printf("\n***error generic function***\n");
  }
}
//object * unknown_feval(ast * op){
//}



void init_fevals() {
  int i;
  for(i = 0;i<100;i++)
    feval_tbl[i] = &generic_feval;
  feval_tbl[if_sym] = &if_feval;

 // feval_tbl[switch_sym] = &switch_feval;
 // feval_tbl[case_sym] = &case_feval;

  //feval_tbl[else_sym] = &else_feval; not needed, handled in 'if'

/*
  feval_tbl[break_sym] = &break_feval;
  feval_tbl[return_sym] = &return_feval;
  feval_tbl[as_sym] = &as_feval;
 */
  feval_tbl[for_sym] = &for_feval;
 /*
  feval_tbl[while_sym] = &while_feval;
  feval_tbl[loop_sym] = &loop_feval;
  feval_tbl[do_sym] = &do_feval;
  feval_tbl[continue_sym] = &continue_feval;
  feval_tbl[and_sym] = &and_feval;
  feval_tbl[or_sym] = &or_feval;
  feval_tbl[not_sym] = &not_feval;
  feval_tbl[xor_sym] = &xor_feval;
 */
  feval_tbl[lt_sym] = &lt_feval;
  feval_tbl[gt_sym] = &gt_feval;
  feval_tbl[le_sym] = &le_feval;
  feval_tbl[ge_sym] = &ge_feval;
  feval_tbl[eq_sym] = &eq_feval;
  feval_tbl[neq_sym] = &neq_feval;
  feval_tbl[assign_sym] = &assign_feval;
  feval_tbl[plus_sym] = &plus_feval;
  feval_tbl[minus_sym] = &minus_feval;
  feval_tbl[star_sym] = &star_feval;
  feval_tbl[carrot_sym] = &carrot_feval;
  /*
  feval_tbl[bang_sym] = &bang_feval;
  feval_tbl[andper_sym] = &andper_feval;
  feval_tbl[slash_sym] = &slash_feval;
  */
  feval_tbl[dot_sym] = &dot_feval;
  feval_tbl[dotdot_sym] = &dotdot_feval;
  /*
  feval_tbl[at_sym] = &at_feval;
  feval_tbl[dollar_sym] = &dollar_feval;
  feval_tbl[colon_sym] = &colon_feval;
  feval_tbl[grave_sym] = &grave_feval;
  feval_tbl[tilda_sym] = &tilda_feval;
  feval_tbl[bar_sym] = &bar_feval;
  feval_tbl[comma_sym] = &comma_feval;
  feval_tbl[dand_sym] = &dand_feval;
  feval_tbl[dor_sym] = &dor_feval;

  feval_tbl[elipse_sym] = &elipse_feval;
  */
  feval_tbl[funccall_sym] = &funccall_feval;
  feval_tbl[subscript_sym] = &subscript_feval;
  feval_tbl[member_sym] = &member_feval;
  feval_tbl[group_sym] = &group_feval;
  feval_tbl[declare_sym] = &declare_feval;



//  feval_tbl[obj_sym] = &obj_feval;
//  feval_tbl[int_sym] = &int_feval;
//  feval_tbl[dec_sym] = &dec_feval;
//  feval_tbl[bool_sym] = &bool_feval;
//  feval_tbl[func_sym] = &func_feval;
//  feval_tbl[bin_sym] = &bin_feval;
//  feval_tbl[list_sym] = &list_feval;
//  feval_tbl[map_sym] = &map_feval;
//  feval_tbl[str_sym] = &str_feval;
//  feval_tbl[try_sym] = &try_feval;
//  feval_tbl[catch_sym] = &catch_feval;
//  feval_tbl[finally_sym] = &finally_feval;
//  feval_tbl[throw_sym] = &throw_feval;
//  feval_tbl[assert_sym] = &assert_feval;
//  feval_tbl[oparen_sym] = &oparen_feval;
//  feval_tbl[cparen_sym] = &cparen_feval;
//  feval_tbl[ocurly_sym] = &ocurly_feval;
//  feval_tbl[ccurly_sym] = &ccurly_feval;
//  feval_tbl[osquare_sym] = &osquare_feval;
//  feval_tbl[csquare_sym] = &csquare_feval;
//  feval_tbl[dquote_sym] = &dquote_feval;
//  feval_tbl[squote_sym] = &squote_feval;
  feval_tbl[id_sym] = &id_feval;
//  feval_tbl[string_sym] = &string_feval;
//  feval_tbl[integer_sym] = &integer_feval;
//  feval_tbl[float_sym] = &float_feval;
//  feval_tbl[import_sym] = &import_feval;
//  feval_tbl[namespace_sym] = &namespace_feval;
//  feval_tbl[class_sym] = &class_feval;
//  feval_tbl[extend_sym] = &extend_feval;
//  feval_tbl[interface_sym] = &interface_feval;
//  feval_tbl[mixin_sym] = &mixin_feval;
//  feval_tbl[virtual_sym] = &virtual_feval;
//  feval_tbl[is_sym] = &is_feval;
//  feval_tbl[was_sym] = &was_feval;
//  feval_tbl[newline_sym] = &newline_feval;
//  feval_tbl[semi_sym] = &semi_feval;

}
