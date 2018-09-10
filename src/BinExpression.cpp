#include "Expression.hpp"
#include "BinExpression.hpp"
#include "IVisitor.hpp"

namespace OberonLang {
  
  // void infix##Expression::accept(OBRVisitor* v) { \
  //  v->visit(this);\
  // }\
		
  /* 
     
   */
   #define STRINGIFY2(X) #X
   #define STRINGIFY(X) STRINGIFY2(X)
   
   #define __implementArithBinExp(infix, operator, valueTypeCpp, valueTypeOberon, valueTypeOberonReturn, oberonType) \
    Value* infix##Expression::eval() {\
    	valueTypeOberon *a1 = (valueTypeOberon *)lhs->eval();\
    	valueTypeOberon *a2 = (valueTypeOberon *)rhs->eval();\
      valueTypeCpp v1 = a1->value();\
      valueTypeCpp v2 = a2->value();\
      \
      \
      delete a1;\
      delete a2;\
      \
      return new valueTypeOberonReturn(v1 operator v2);\
    }\
    void infix##Expression::acceptVisit(IVisitor* visitor) {\
      visitor->visit(this);\
    }\
    \
    TypesEnum infix##Expression::expType() {\
      TypesEnum t1 = lhs->expType();\
      TypesEnum t2 = rhs->expType();\
      \
      return ((t1 == t2) && (t1 == oberonType)) ? oberonType : undef;\
    }\
  


  /* Integer binary expressions */
  __implementArithBinExp(Add,  +, TYPE_INTEGER, IntValue, IntValue, integer)   // ~ AddExpression
  __implementArithBinExp(Sub,  -, TYPE_INTEGER, IntValue, IntValue, integer)   // ~ SubExpression
  __implementArithBinExp(Times,*, TYPE_INTEGER, IntValue, IntValue, integer)   // ~ TimesExpression
  __implementArithBinExp(Div,  /, TYPE_INTEGER, IntValue, IntValue, integer)   // ~ DivExpression
  __implementArithBinExp(Rem,  %, TYPE_INTEGER, IntValue, IntValue, integer)   // ~ RemExpression
  
  /* Real binary expressions */
  __implementArithBinExp(AddReal,   +, TYPE_REAL, RealValue, RealValue, real)  // ~ AddRealExpression
  __implementArithBinExp(SubReal,   -, TYPE_REAL, RealValue, RealValue, real)  // ~ SubRealExpression
  __implementArithBinExp(TimesReal, *, TYPE_REAL, RealValue, RealValue, real)  // ~ TimesRealExpression
  __implementArithBinExp(DivReal,   /, TYPE_REAL, RealValue, RealValue, real)  // ~ DivRealExpression
  
  /* Relational Expressions for integers */
  __implementArithBinExp(EQ,  ==, TYPE_INTEGER, IntValue, BooleanValue, boolean)  // ~ EQExpression
  __implementArithBinExp(NE,  !=, TYPE_INTEGER, IntValue, BooleanValue, boolean)  // ~ NEExpression
  __implementArithBinExp(LT,   <, TYPE_INTEGER, IntValue, BooleanValue, boolean)  // ~ LTExpression
  __implementArithBinExp(LE,  <=, TYPE_INTEGER, IntValue, BooleanValue, boolean)  // ~ LEE/xpression
  __implementArithBinExp(GT,   >, TYPE_INTEGER, IntValue, BooleanValue, boolean)  // ~ GTExpression
  __implementArithBinExp(GE,  >=, TYPE_INTEGER, IntValue, BooleanValue, boolean)  // ~ GEExpression
  
  /* Logical binary expressions */
  __implementArithBinExp(And, &&, TYPE_BOOLEAN, BooleanValue, BooleanValue, boolean)  // ~ AndExpression
  __implementArithBinExp(Or,  ||, TYPE_BOOLEAN, BooleanValue, BooleanValue, boolean)  // ~ OrExpression


  // __acceptMethodBinExp(Add)
  // __acceptMethodBinExp(Sub)
  // __acceptMethodBinExp(Times)
  // __acceptMethodBinExp(Div)
  // __acceptMethodBinExp(Rem)

  // __acceptMethodBinExp(AddReal)
  // __acceptMethodBinExp(SubReal)
  // __acceptMethodBinExp(TimesReal)
  // __acceptMethodBinExp(DivReal)

  // __acceptMethodBinExp(EQ)
  // __acceptMethodBinExp(NE)
  // __acceptMethodBinExp(LT)
  // __acceptMethodBinExp(LE)
  // __acceptMethodBinExp(GT)
  // __acceptMethodBinExp(GE)

  // __acceptMethodBinExp(And)
  // __acceptMethodBinExp(Or);
  
}
