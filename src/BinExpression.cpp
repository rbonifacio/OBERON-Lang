#include "Expression.hpp"
#include "BinExpression.hpp"

namespace OberonLang {
  
  /* 
     Macro que implementa expressões binárias aritméticas simples.
     infix: o nome da expressão, esse nome será usado como infixo
     operator: a operação equivalente em C++
     valueType: o tipo dos dados que serão manipulados
   */
   
  #define __implementArithBinExp(infix, operator, valueType)\
  Value* infix##Expression::eval() {\
    int64_t v1 = ((valueType*)lhs->eval())->value();\
    int64_t v2 = ((valueType*)rhs->eval())->value();\
    \
    return new valueType(v1 operator v2);\
  }\
  
  __implementArithBinExp(Add,  +, IntValue);      // ~ AddExpression
  __implementArithBinExp(Sub,  -, IntValue);      // ~ SubExpression
  __implementArithBinExp(Mult, *, IntValue);      // ~ MultExpression
  __implementArithBinExp(Div,  /, IntValue);      // ~ DivExpression
  __implementArithBinExp(Srl, >>, IntValue);      // ~ SrlExpression
  __implementArithBinExp(Sll, <<, IntValue);      // ~ SllExpression
  __implementArithBinExp(And, &&, BooleanValue);  // ~ AndExpression
  __implementArithBinExp(Or,  ||, BooleanValue);  // ~ OrExpression
  __implementArithBinExp(Xor,  ^, BooleanValue);  // ~ XorExpression
  
}
