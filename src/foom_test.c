#if 0
#include "foom_test.h"
extern FuncP func_tbl[100];
extern char * _symbols_[];
void da_binary(ast * a){

    printf("(");
    printf("%s:", _symbols_[a->op.binary.oper]);
    decend_ast(a->op.binary.left);
    printf(",");
    decend_ast(a->op.binary.right);
    printf(")");

}

void da_unary(ast * a){
  printf("(%s:", _symbols_[a->op.unary.oper]);
  decend_ast(a->op.unary.arg);
  printf(")");
}

void da_call_args(ast * a){
  ast_list * al;
  for(al = a->op.call.args;al->node;al = al->next) {
    decend_ast(al->node);
    if(al->next->node)
      printf(", ");
  }
}

void da_block(ast * a){
  ast_list * al;
  printf("{\n");
  if(a->op.block.stmts)
    for(al = a->op.block.stmts;al->node;al = al->next) {
      decend_ast(al->node);
      printf("\n");
    }
  else
    printf("**BLOCK ERROR**\n");
  printf("}\n");
}

void da_id(ast * a){
  printf("%s",a->op.Id);
  //printf("<member:%s>",a->op.Id);
}

void da_object(ast * a){
  if(a->op.obj) {
    object * o = a->op.obj;
    //obj_sym, int_sym, dec_sym, bool_sym, func_sym, bin_sym, list_sym, map_sym, str_sym,
    switch(o->type){
      case dec_sym: //TODO: make floats
      case int_sym:
        printf("%li",o->val.Int);
        break;
      case str_sym:
        printf("'%s'", o->val.Str?o->val.Str->val:"<none>");
        break;
      case bool_sym:
        printf("%s",o->name, o->val.Bool?"true":"false");
        break;
      case obj_sym:
        printf("<object:object %s>",o->name);
        break;
      case list_sym:
        printf("<object:list %s>",o->name);
        break;
      case map_sym:
        printf("<object:map %s>",o->name);
        break;
      case func_sym:
        printf("%s",o->name);
        break;
      default:
        printf("<object:unknown>");
    }
  } else
    printf("**OBJECT ERROR**\n");
}

void decend_ast(ast * a) {
  switch(a->tag) {
    case binary_ast: return func_tbl[a->op.binary.oper](a);
    case unary_ast: return func_tbl[a->op.unary.oper](a);
    case id_ast: return da_id(a);
    case obj_ast: return da_object(a);
    case list_ast: return da_call_args(a);
    case block_ast: return da_block(a);
  }
}
#endif
