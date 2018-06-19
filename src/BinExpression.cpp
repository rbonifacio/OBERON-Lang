#include "Expression.hpp"
#include "BinExpression.hpp"

namespace OberonLang {
  
  /* 
     
   */
   
  #define __implementArithBinExp(infix, operator, valueTypeCpp, valueTypeOberon, valueTypeOberonReturn)\
    Value* infix##Expression::eval() {\
      valueTypeCpp v1 = ((valueTypeOberon *)lhs->eval())->value();\
      valueTypeCpp v2 = ((valueTypeOberon *)rhs->eval())->value();\
      \
      return new valueTypeOberonReturn(v1 operator v2);\
    }\

  void AddExpression::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void SubExpression::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void TimesExpression::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void DivExpression::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void RemExpression::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void AddRealExpression::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void SubRealExpression::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void TimesRealExpression::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void DivRealExpression::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void EQExpression::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void NEExpression::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void LTExpression::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void LEExpression::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void GTExpression::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void GEExpression::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void AndExpression::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void OrExpression::accept(OBRVisitor* v) {
    v->visit(this); 
  }


  /* Integer binary expressions */
  __implementArithBinExp(Add,  +, TYPE_INTEGER, IntValue, IntValue);   // ~ AddExpression
  __implementArithBinExp(Sub,  -, TYPE_INTEGER, IntValue, IntValue);   // ~ SubExpression
  __implementArithBinExp(Times,*, TYPE_INTEGER, IntValue, IntValue);   // ~ TimesExpression
  __implementArithBinExp(Div,  /, TYPE_INTEGER, IntValue, IntValue);   // ~ DivExpression
  __implementArithBinExp(Rem,  %, TYPE_INTEGER, IntValue, IntValue);   // ~ RemExpression
  
  /* Real binary expressions */
  __implementArithBinExp(AddReal,   +, TYPE_REAL, RealValue, RealValue);  // ~ AddRealExpression
  __implementArithBinExp(SubReal,   -, TYPE_REAL, RealValue, RealValue);  // ~ SubRealExpression
  __implementArithBinExp(TimesReal, *, TYPE_REAL, RealValue, RealValue);  // ~ TimesRealExpression
  __implementArithBinExp(DivReal,   /, TYPE_REAL, RealValue, RealValue);  // ~ DivRealExpression
  
  /* Relational Expressions for integers */
  __implementArithBinExp(EQ,  ==, TYPE_INTEGER, IntValue, BooleanValue);  // ~ EQExpression
  __implementArithBinExp(NE,  !=, TYPE_INTEGER, IntValue, BooleanValue);  // ~ NEExpression
  __implementArithBinExp(LT,   <, TYPE_INTEGER, IntValue, BooleanValue);  // ~ LTExpression
  __implementArithBinExp(LE,  <=, TYPE_INTEGER, IntValue, BooleanValue);  // ~ LEE/xpression
  __implementArithBinExp(GT,   >, TYPE_INTEGER, IntValue, BooleanValue);  // ~ GTExpression
  __implementArithBinExp(GE,  >=, TYPE_INTEGER, IntValue, BooleanValue);  // ~ GEExpression
  
  /* Logical binary expressions */
  __implementArithBinExp(And, &&, TYPE_BOOLEAN, BooleanValue, BooleanValue);  // ~ AndExpression
  __implementArithBinExp(Or,  ||, TYPE_BOOLEAN, BooleanValue, BooleanValue);  // ~ OrExpression

  // __acceptArithBinExp(Add);
  // __acceptArithBinExp(Sub);
  // __acceptArithBinExp(Times);
  // __acceptArithBinExp(Div);
  // __acceptArithBinExp(Rem);
  
}
