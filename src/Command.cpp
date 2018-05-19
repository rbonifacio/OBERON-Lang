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
    for (auto it= commands.begin(); it != commands.end(); ++it) {
      (*it)->run();
    }
  }
    
  void PrintCommand::run() {
    auto v = expression->eval(); 
    cout << v;
  }
    
  void ProcedureCall::run(){
    Environment::instance()->push();
    
    auto decProcedure = Environment::instance()->lookupProcedure(this->_name);
    int numberOfFormalArgs = decProcedure->formalArgs().size();
        
    // map each formal argument to the actual argument of the procedure call.
    for(int i = 0; i < numberOfFormalArgs; i++) {
      auto formalArg = decProcedure->formalArgs()[i];
      auto arg = this->_args[i]->eval();
            
      Environment::instance()->env(formalArg.name(), arg);
    }
    // run the procedure body in the updated environment. 
    decProcedure->body()->run();

    Environment::instance()->pop();
  }
  
}
