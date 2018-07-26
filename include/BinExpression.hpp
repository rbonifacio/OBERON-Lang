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
    Expression* getLhs() { return lhs; };
    Expression* getRhs() { return rhs; };
    void acceptVisit(IVisitor* visitor);
    virtual Value* eval() = 0;
    virtual TypesEnum expType() = 0;
    virtual void accept(OBRVisitor* v) = 0;
    ~BinExpression() { delete lhs; delete rhs; }  
  };  
  
  #define __headerArithBinExp(infix)\
    class infix##Expression : public BinExpression {\
    public:\
      infix##Expression(Expression* l, Expression* r) : BinExpression(l, r) {};\
      void accept(OBRVisitor* v);\
      Value* eval();\
      TypesEnum expType();\
    };\
  
  __headerArithBinExp(Add);   // ~ AddExpression
  __headerArithBinExp(Sub);   // ~ SubExpression
  __headerArithBinExp(Times); // ~ TimesExpression
  __headerArithBinExp(Div);   // ~ DivExpression
  __headerArithBinExp(Rem);   // ~ RemExpression
  
  __headerArithBinExp(AddReal);   // ~ AddRealExpression
  __headerArithBinExp(SubReal);   // ~ SubRealExpression
  __headerArithBinExp(TimesReal); // ~ TimesRealExpression
  __headerArithBinExp(DivReal);   // ~ DivRealExpression
  
  __headerArithBinExp(EQ);   // ~ EQExpression
  __headerArithBinExp(NE);   // ~ NEExpression
  __headerArithBinExp(LT);   // ~ LTExpression
  __headerArithBinExp(LE);   // ~ LEExpression
  __headerArithBinExp(GT);   // ~ GTExpression
  __headerArithBinExp(GE);   // ~ GEExpression
  
  __headerArithBinExp(And);  // ~ AndExpression
  __headerArithBinExp(Or);   // ~ OrExpression
    
}
#endif 
