#ifndef VISITOR_H
#define VISITOR_H

#include "Expression.hpp"
#include "BinExpression.hpp"
#include "VarRef.hpp"
#include "Command.hpp"
#include "Declaration.hpp"
#include "Procedure.hpp"

// #include "Types.hpp"

namespace OberonLang {
  
  class Undefined;
  class IntValue;
  class RealValue;
  class AddExpression;
  class SubExpression;
  class TimesExpression;
  class DivExpression;
  class RemExpression;
  class AddRealExpression;
  class SubRealExpression;
  class TimesRealExpressio;
  class DivRealExpression;
  class EQExpression;
  class NEExpression;
  class LTExpression;
  class LEExpression;
  class GTExpression;
  class GEEXpression;
  class AndExpression;
  class OrExpression; 
  class Assignment;
  class ProcedureCall;
  class BlockCommand; 
  class PrintCommand; 
  class WhileCommand;
  class IfThenCommand;
  class IfThenElseCommand;
  class Declaration;
  class DecProcedure; 

  class OBRVisitor {
  public:
    virtual void visit(Undefined* exp) = 0;
    virtual void visit(IntValue* exp) = 0;
    virtual void visit(RealValue* exp) = 0;
    virtual void visit(BooleanValue* exp) = 0; 

    virtual void visit(AddExpression* exp) = 0;
    virtual void visit(SubExpression* exp) = 0; 
    virtual void visit(TimesExpression* exp) = 0; 
    virtual void visit(DivExpression* exp) = 0; 
    virtual void visit(RemExpression* exp) = 0; 

    virtual void visit(AddRealExpression* exp) = 0;
    virtual void visit(SubRealExpression* exp) = 0; 
    virtual void visit(TimesRealExpression* exp) = 0; 
    virtual void visit(DivRealExpression* exp) = 0; 

    virtual void visit(EQExpression* exp) = 0; 
    virtual void visit(NEExpression* exp) = 0; 
    virtual void visit(LTExpression* exp) = 0;
    virtual void visit(LEExpression* exp) = 0; 
    virtual void visit(GTExpression* exp) = 0;
    virtual void visit(GEExpression* exp) = 0;

    virtual void visit(AndExpression* exp) = 0;
    virtual void visit(OrExpression* exp) = 0; 

    //  virtual void visit(VarRef* exp) = 0;

    virtual void visit(Assignment* cmd) = 0;
    virtual void visit(ProcedureCall* cmd) = 0;
    virtual void visit(BlockCommand* cmd) = 0;
    virtual void visit(PrintCommand* cmd) = 0;
    virtual void visit(WhileCommand* cmd) = 0;
    virtual void visit(IfThenCommand* cmd) = 0;
    virtual void visit(IfThenElseCommand* cmd) = 0;

    virtual void visit(Declaration* dec) = 0; 

    virtual void visit(DecProcedure* procedure) = 0;

    // virtual void visit(TypesEnum type) = 0;
  };

}

#endif 
