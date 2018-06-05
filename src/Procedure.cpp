#include "Procedure.hpp"
#include "Environment.hpp"

namespace OberonLang { 
  DecProcedure::DecProcedure(string n, vector<VarDeclaration> args, vector<VarDeclaration> vars, Command* cmd) {
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
