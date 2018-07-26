#include "IVisitor.hpp"


namespace OberonLang {
  // class Undefined;
  // class IntValue;
  // class RealValue;
  // class AddExpression;
  // class SubExpression;
  // class TimesExpression;
  // class DivExpression;
  // class RemExpression;
  // class AddRealExpression;
  // class SubRealExpression;
  // class TimesRealExpressio;
  // class DivRealExpression;
  // class EQExpression;
  // class NEExpression;
  // class LTExpression;
  // class LEExpression;
  // class GTExpression;
  // class GEEXpression;
  // class AndExpression;
  // class OrExpression; 
  // class Assignment;
  // class ProcedureCall;
  // class BlockCommand; 
  // class PrintCommand; 
  // class WhileCommand;
  // class IfThenCommand;
  // class IfThenElseCommand;
  // class Declaration;
  // class DecProcedure; 

  class TCVisitor : public IVisitor {
  public:
    TCVisitor() { _validType = false; }
    
    void visit(Undefined* exp);
    void visit(IntValue* exp);
    void visit(RealValue* exp);
    void visit(BooleanValue* exp); 

    void visit(AddExpression* exp);
    void visit(SubExpression* exp); 
    void visit(TimesExpression* exp); 
    void visit(DivExpression* exp); 
    void visit(RemExpression* exp); 

    void visit(AddRealExpression* exp);
    void visit(SubRealExpression* exp); 
    void visit(TimesRealExpression* exp); 
    void visit(DivRealExpression* exp); 

    void visit(EQExpression* exp); 
    void visit(NEExpression* exp); 
    void visit(LTExpression* exp);
    void visit(LEExpression* exp); 
    void visit(GTExpression* exp);
    void visit(GEExpression* exp);

    void visit(AndExpression* exp);
    void visit(OrExpression* exp); 

    void visit(VarRef* exp);

    void visit(Assignment* cmd);
    void visit(ProcedureCall* cmd);
    void visit(BlockCommand* cmd);
    void visit(PrintCommand* cmd);
    void visit(WhileCommand* cmd);
    void visit(IfThenCommand* cmd);
    void visit(IfThenElseCommand* cmd);
    void visit(Declaration* dec);
    
    void visit(DecProcedure* procedure);

    void visit(Program* program);
    void visit(VarDec* exp);
    void visit(BinExpression* exp); 

    bool validType() { return _validType; }
  private:
    bool _validType; 
  };

}
