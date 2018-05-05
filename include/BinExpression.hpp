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

  class AddExpression : public BinExpression {
  public:
    AddExpression(Expression* l, Expression* r);
    virtual Value* eval(); 
  };
    
}

#endif 
