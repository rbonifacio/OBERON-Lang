#include "Command.hpp"
#include "Environment.hpp"
#include "Procedure.hpp"
#include "Expression.hpp"

#include <list>
#include <iostream>

using namespace std;

namespace OberonLang {
  void Assignment::run() {
    Environment::instance()->env(var, expression->eval());
  }

  void BlockCommand::run() {
    for (list<Command*>::iterator it= commands.begin(); it != commands.end(); ++it) {
      (*it)->run();
    }
  }
    
    void PrintCommand::run() {
        cout << expression -> eval();
    }
    
    void ProcedureCall::run(){
        Environment::instance()->push();
        DecProcedure* decProcedure = Environment::instance()->lookupProcedure(this->_name);
        
        int numberOfFormalArgs = decProcedure->formalArgs().size();
        
        // map each formal argument to the actual argument of the procedure call.
        for(int i = 0; i < numberOfFormalArgs; i++) {
            Declaration formalArg = decProcedure->formalArgs()[i];
            Value* arg = this->_args[i]->eval();
            
            Environment::instance()->env(formalArg.name(), arg);
        }
        decProcedure->body()->run();
        Environment::instance()->pop();

    }
  
}
