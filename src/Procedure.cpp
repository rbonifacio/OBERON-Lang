#include "Procedure.hpp"

namespace OberonLang { 
  DecProcedure::DecProcedure(string n, vector<Declaration> args, vector<Declaration> vars, Command* cmd) {
  // DecProcedure::DecProcedure(string n, vector<Declaration> args, vector<Declaration> vars, Command* cmd) {
    this->_name = n;
    this->_formalArgs = args;
    this->_localVars = vars;
    this->_body = cmd; 
  }

  DecProcedure::~DecProcedure() {
    delete _body; 
  }
}
