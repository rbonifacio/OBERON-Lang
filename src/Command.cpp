#include "Command.hpp"
#include "Environment.hpp"
#include "Procedure.hpp"
#include "Expression.hpp"

#include <list>
#include <iostream>

using namespace std;

namespace OberonLang {
  void Assignment::run() {
    if(Environment::instance()->env(var) != Undefined::instance()) {
      Environment::instance()->env(var, expression->eval());
    }
    if (Environment::instance()->global(var) != Undefined::instance()) {
      Environment::instance()->global(var, expression->eval());
    }
    else {
      cout << "nao achou var " << var << endl;
      // in this case, we are assigning to a non declared variable!
      // TODO: throw new ....
    }
  }

  void BlockCommand::run() {
    for (auto it = commands.begin(); it != commands.end(); ++it) {
      (*it)->run();
    }
  }

  void PrintCommand::run() {
    auto v = expression->eval();
    v->show();
  }

  void ProcedureCall::run(){
    Environment::instance()->push();

    auto decProcedure = Environment::instance()->decProcedure(this->_name);
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

  void WhileCommand::run(){
    while (((BooleanValue*)this->_cond->eval())->value()){
      this->_cmds->run();
    }
  }

  void IfThenCommand::run(){
   if (((BooleanValue*)this->_cond->eval())->value()){
      this->_cmds->run();
   }
  }
  void IfThenElseCommand::run(){
   if (((BooleanValue*)this->_cond->eval())->value()){
      this->_cmds->run();
   }
   else{
     this->_cmds2->run();
   }
  }


}
