#include "Command.hpp"
#include "Environment.hpp"
#include "Procedure.hpp"
#include "Expression.hpp"

#include <list>
#include <iostream>

using namespace std;

namespace OberonLang {
  void Assignment::run() {
    if(Environment::instance()->env(_var) != Undefined::instance()) {
    	Value *oldref = Environment::instance()->env(_var);
      Environment::instance()->env(_var, _expression->eval());
      delete oldref;
    }
    else if (Environment::instance()->global(_var) != Undefined::instance()) {
    	Value *oldref = Environment::instance()->global(_var);
      Environment::instance()->global(_var, _expression->eval());
      delete oldref;
    }
    else {
      cout << "nao achou var " << _var << endl;
      // in this case, we are assigning to a non declared variable!
      // TODO: throw new ....
    }
  }

  // void Assignment::accept(OBRVisitor* v) {
  //   v->visit(this); 
  // }

  void BlockCommand::run() {
    for (auto it = _commands->begin(); it != _commands->end(); ++it) {
      (*it)->run();
    }
  }

  // void BlockCommand::accept(OBRVisitor* v) {
  //   v->visit(this); 
  // }

  void PrintCommand::run() {
    auto v = _expression->eval();
    v->show();
    delete v;
  }

  // void PrintCommand::accept(OBRVisitor* v) {
  //   v->visit(this); 
  // }
  

  void ProcedureCall::run(){
    Environment::instance()->push();

    auto decProcedure = Environment::instance()->decProcedure(this->_name);
    int numberOfFormalArgs = decProcedure->formalArgs()->size();

    // map each formal argument to the actual argument of the procedure call.
    for(int i = 0; i < numberOfFormalArgs; i++) {
      auto formalArg = (*decProcedure->formalArgs())[i];
      auto arg = (*this->_args)[i]->eval();

      Environment::instance()->env(formalArg->name(), arg);
    }

    int numberOfLocalVars = decProcedure->localVars()->size();

    // map each formal argument to the actual argument of the procedure call.
    for(int i = 0; i < numberOfLocalVars; i++) {
      auto localVar = (*decProcedure->localVars())[i];
      Environment::instance()->env(localVar->name(), NULL);
    }

    // run the procedure body in the updated environment.
    decProcedure->body()->run();

    Environment::instance()->pop();
  }

  // void ProcedureCall::accept(OBRVisitor* v) {
  //   v->visit(this); 
  // }

  void WhileCommand::run(){
  	BooleanValue *cond = (BooleanValue*)this->_cond->eval();
    while (cond->value()){
    	delete cond;
      this->_cmds->run();
    	cond = (BooleanValue*)this->_cond->eval();
    }
    delete cond;
  }

  // void WhileCommand::accept(OBRVisitor* v) {
  //   v->visit(this); 
  // }

  void IfThenCommand::run(){
   BooleanValue *condEval = (BooleanValue*)this->_cond->eval();
   if (condEval->value()){
     this->thenCmd()->run();
   }
   delete condEval;
  }

  // void IfThenCommand::accept(OBRVisitor* v) {
  //   v->visit(this); 
  // }
  
  void IfThenElseCommand::run(){
   BooleanValue *condEval = (BooleanValue*)this->_cond->eval();
   if (condEval->value()){
     this->thenCmd()->run();
   }
   else{
     this->elseCmd()->run();
   }
   delete condEval;
  }


  // void IfThenElseCommand::accept(OBRVisitor* v) {
  //   v->visit(this); 
  // }
}
