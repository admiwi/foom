#include "foom_test.h"

extern char * _symbols_[];
void da_binary(ast * a){
  printf("BINARY(%s:", _symbols_[a->op.binary.oper]);
  decend_ast(a->op.binary.left);
  printf(", ");
  decend_ast(a->op.binary.right);
  printf(")");
}

void da_unary(ast * a){
  printf("UNARY(%s:", _symbols_[a->op.unary.oper]);
  decend_ast(a->op.unary.arg);
  printf(")");
}

void da_func_call(ast * a){
  ast_list * al;
  //if((a->op.call)) {
    printf("CALL to %s :",a->op.call.obj->name);
    for(al = a->op.call.arguments;al;al = al->next)
      decend_ast(al->node);
  //}
}

void da_block(ast * a){
  ast_list * al;
  printf("BLOCK START\n");
  if(a->op.block.stmts)
    for(al = a->op.block.stmts;al;al = al->next) {
      decend_ast(al->node);
      printf("\n");
    }
  else
    printf("**BLOCK ERROR**\n");
  printf("BLOCK END\n");
}

void da_object(ast * a){
  if(a->op.obj) {
    object * o = a->op.obj;
    //obj_sym, int_sym, dec_sym, bool_sym, func_sym, bin_sym, list_sym, map_sym, str_sym,
    switch(o->type){
      case dec_sym: //TODO: make floats
      case int_sym:
        printf("<object:integer %s=%li>\n",o->name, o->val.Int);
        break;
      case str_sym:
        printf("<object:string %s='%s'>\n",o->name, o->val.Str);
        break;
      case bool_sym:
        printf("<object:boolean %s=%s>\n",o->name, o->val.Bool?"true":"false");
        break;
      case obj_sym:
        printf("<object:object %s>\n",o->name);
        break;
      case list_sym:
        printf("<object:list %s>\n",o->name);
        break;
      case map_sym:
        printf("<object:map %s>\n",o->name);
        break;
      case func_sym:
        printf("<object:func %s>\n",o->name);
        break;
      default:
        printf("<object:unknown %s>\n",o->name);
    }
  } else
    printf("**OBJECT ERROR**\n");
}

void decend_ast(ast * a) {
  switch(a->tag) {
    case binary_ast: return da_binary(a);
    case unary_ast: return da_unary(a);
    case obj_ast: return da_object(a);
    case func_call_ast: return da_func_call(a);
    case block_ast: return da_block(a);
  }
}
