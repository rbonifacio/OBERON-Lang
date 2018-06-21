#ifndef VISITOR_H
#define VISITOR_H

#include "Expression.hpp"
#include "BinExpression.hpp"
#include "Command.hpp"
#include "Declaration.hpp"
#include "Procedure.hpp"
#include "VarDec.hpp"
#include "VarRef.hpp"
#include "Types.hpp"
#include "Program.hpp"

namespace OberonLang {
  class IVisitor {
  public:
    virtual void visit(Program* p) = 0;
//  virtual void visit(TypesEnum* p) = 0; // This visit can be unnecessary
    virtual void visit(IntValue* p) = 0;
    virtual void visit(RealValue* p) = 0;
    virtual void visit(BooleanValue* p) = 0;
    virtual void visit(Undefined* p) = 0;
    virtual void visit(Assignment* p) = 0;
    virtual void visit(ProcedureCall* p) = 0;
    virtual void visit(BlockCommand* p) = 0;
    virtual void visit(PrintCommand* p) = 0;
    virtual void visit(WhileCommand* p) = 0;
    virtual void visit(IfThenCommand* p) = 0;
    virtual void visit(IfThenElseCommand* p) = 0;
    virtual void visit(Declaration* p) = 0;
    virtual void visit(DecProcedure* p) = 0;
    virtual void visit(VarRef* p) = 0;
    virtual void visit(VarDec* p) = 0;
    virtual void visit(BinExpression* p) = 0;
    virtual void visit(AddExpression* p) = 0;
    virtual void visit(TimesExpression* p) = 0;
    virtual void visit(SubExpression* p) = 0;
    virtual void visit(DivExpression* p) = 0;
    virtual void visit(RemExpression* p) = 0;
    virtual void visit(AndExpression* p) = 0;
    virtual void visit(OrExpression* p) = 0;
    virtual void visit(LTExpression* p) = 0;
    virtual void visit(LEExpression* p) = 0;
    virtual void visit(GTExpression* p) = 0;
    virtual void visit(GEExpression* p) = 0;
    virtual void visit(EQExpression* p) = 0;
    virtual void visit(NEExpression* p) = 0;
  };
}

#endif 
