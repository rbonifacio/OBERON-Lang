#include "Program.hpp"

#include <iostream>
#include <vector>

#include "Environment.hpp"

using namespace std;

namespace OberonLang {

  Program::Program(Command* main) {
    this->_main = main; 
  }

  Program::Program(vector<VarDec*> globalVars, vector<DecProcedure*> procedures, Command* main) {
    this->_globalVars = globalVars; 
    this->_procedures = procedures; 
    this->_main = main; 
  }


  void Program::run() {
    for(auto it = this->_globalVars.begin(); it != this->_globalVars.end(); ++it) {
      cout << "globalvar: " << (*it)->name() << " added\n";
      // Environment::instance()->global((*it)->name(), Undefined::instance());
      Environment::instance()->global((*it)->name(), NULL); 
    }

    for(auto it = this->_procedures.begin(); it != this->_procedures.end(); ++it) {
      Environment::instance()->decProcedure((*it));
    }

    this->_main->run(); 
  }

}
