#include "Expression.hpp"
#include "BinExpression.hpp"

namespace OberonLang {

  AddExpression::AddExpression(Expression* l, Expression* r) : BinExpression(l, r) {}
  
  Value* AddExpression::eval() {
    int v1 = ((IntValue*)lhs->eval())->value();
    int v2 = ((IntValue*)rhs->eval())->value();

    return new IntValue(v1 + v2);
  }
  
}
