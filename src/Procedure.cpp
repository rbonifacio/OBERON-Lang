#include "Procedure.hpp"
#include "Environment.hpp"

namespace OberonLang { 
  DecProcedure::DecProcedure(string n, vector<Declaration> args, vector<Declaration> vars, Command* cmd) {
    this->_name = n;
    this->_formalArgs = args;
    this->_localVars = vars;
    this->_body = cmd; 
  }
  
  void DecProcedure::run() {
      Environment::instance()->decProcedure(this);
  }

  DecProcedure::~DecProcedure() {
    delete _body; 
  }
}
