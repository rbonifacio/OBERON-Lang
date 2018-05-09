#ifndef BIN_EXPRESSION_H
#define BIN_EXPRESSION_H

#include "Expression.hpp"

namespace OberonLang {

  class BinExpression : public Expression {
  protected:
    Expression* lhs;
    Expression* rhs;
  public:
    BinExpression(Expression* l, Expression* r) { lhs = l; rhs = r; };
    virtual Value* eval() = 0;
  };  
  
  #define __headerArithBinExp(infix)\
  class infix##Expression : public BinExpression {\
  public:\
    infix##Expression(Expression* l, Expression* r) : BinExpression(l, r) {};\
    Value* eval();\
  };\
  
  __headerArithBinExp(Add);  // ~ AddExpression
  __headerArithBinExp(Sub);  // ~ SubExpression
  __headerArithBinExp(Mult); // ~ MultExpression
  __headerArithBinExp(Div);  // ~ DivExpression
  __headerArithBinExp(Srl);  // ~ SrlExpression
  __headerArithBinExp(Sll);  // ~ SllExpression
  __headerArithBinExp(And);  // ~ AndExpression
  __headerArithBinExp(Or);   // ~ OrExpression
  __headerArithBinExp(Xor);  // ~ XorExpression
    
}
#endif 
