#include "Environment.hpp"
#include "TCVisitor.hpp"
#include "Types.hpp"

namespace OberonLang {
  void TCVisitor::visit(Undefined* exp) {
    this->_validType = false; 
  }
  void TCVisitor::visit(IntValue* exp) {
    this->_validType = true; 
  }
  void TCVisitor::visit(RealValue* exp) {
    this->_validType = true; 
  }
  void TCVisitor::visit(BooleanValue* exp) {
    this->_validType = true; 
  } 
  void TCVisitor::visit(StringValue* exp) {
    this->_validType = true; 
  } 
  
  void TCVisitor::visit(AddExpression* exp) {
    this->_validType = exp->expType() == integer; 
  }

  void TCVisitor::visit(SubExpression* exp) {
    this->_validType = exp->expType() == integer;  
  } 

  void TCVisitor::visit(TimesExpression* exp) {
     this->_validType = exp->expType() == integer; 
  }

  void TCVisitor::visit(DivExpression* exp) {
     this->_validType = exp->expType() == integer; 
  }

  void TCVisitor::visit(RemExpression* exp) {
     this->_validType = exp->expType() == integer; 
  }
  
  void TCVisitor::visit(AddRealExpression* exp) {
     this->_validType = exp->expType() == real; 
  }
    
  void TCVisitor::visit(SubRealExpression* exp) {
     this->_validType = exp->expType() == real; 
  }
  void TCVisitor::visit(TimesRealExpression* exp) {
     this->_validType = exp->expType() == real; 
  }
  
  void TCVisitor::visit(DivRealExpression* exp) {
     this->_validType = exp->expType() == real; 
  }
  
  void TCVisitor::visit(EQExpression* exp) {
     this->_validType = exp->expType() == boolean; 
  }
  
  void TCVisitor::visit(NEExpression* exp) {
     this->_validType = exp->expType() == boolean; 
  }
  void TCVisitor::visit(LTExpression* exp) {
     this->_validType = exp->expType() == boolean; 
  }
  
  void TCVisitor::visit(LEExpression* exp) {
     this->_validType = exp->expType() == boolean; 
  }

  void TCVisitor::visit(GTExpression* exp) {
     this->_validType = exp->expType() == boolean; 
  }
  
  void TCVisitor::visit(GEExpression* exp) {
     this->_validType = exp->expType() == boolean; 
  }

  void TCVisitor::visit(AndExpression* exp) {
     this->_validType = exp->expType() == boolean; 
  }
  
  void TCVisitor::visit(OrExpression* exp) {
     this->_validType = exp->expType() == boolean; 
  }

  void TCVisitor::visit(Assignment* cmd) {
    cmd->expression()->acceptVisit(this); // this is a simplification, mainly because declaration does not propagate its type. 
  }

  void TCVisitor::visit(ProcedureCall* cmd) {
    auto decProcedure = Environment::instance()->decProcedure(cmd->name());
    int numberOfFormalArgs = decProcedure->formalArgs()->size();
    int numberOfActualArgs = cmd->args()->size();
    if(numberOfActualArgs != numberOfFormalArgs) {
      this->_validType = false;
      return; 
    }
    
    for(int i = 0; i < numberOfFormalArgs; i++ ) {
     if((*decProcedure->formalArgs())[i]->type() != (*cmd->args())[i]->expType()) {
	this->_validType = false;
	return;
      }
    }
    decProcedure->body()->acceptVisit(this); 
  }
  
  void TCVisitor::visit(BlockCommand* cmd) {
    for (auto it = cmd->commands()->begin(); it != cmd->commands()->end(); ++it) {
      (*it)->acceptVisit(this);
      if(! this->_validType) { return ; } 
    }
     this->_validType = true; 
  }
  
  void TCVisitor::visit(PrintCommand* cmd) {
    cmd->expression()->acceptVisit(this); 
  }
  void TCVisitor::visit(WhileCommand* cmd) {
    if(cmd->condition()->expType() != boolean) {
      this->_validType = false;
      return; 
    }
    cmd->command()->acceptVisit(this); 
  }
  
  void TCVisitor::visit(IfThenCommand* cmd) {
    if(cmd->condition()->expType() != boolean) {
       this->_validType = false;
      return; 
    }
    cmd->thenCmd()->acceptVisit(this);  
  }
  
  void TCVisitor::visit(IfThenElseCommand* cmd) {
    if(cmd->condition()->expType() != boolean) {
      this->_validType = false;
      return; 
    }
    cmd->thenCmd()->acceptVisit(this);
    if(! this->_validType) { return; }
    cmd->elseCmd()->acceptVisit(this);
  }

  void TCVisitor::visit(Declaration* dec) { } 

  void TCVisitor::visit(DecProcedure* procedure) { }

  void TCVisitor::visit(VarRef* exp) { } 

  void TCVisitor::visit(Program* program) { } 

  void TCVisitor::visit(VarDec* exp) { }

  void TCVisitor::visit(BinExpression* exp) { exp->acceptVisit(this); }
}
