#include "PROCEDURE_H"

namespace OberonLang { 
  DecProcedure::DecProcedure(string n, list<Declaration> args, list<Declaration> vars, Command* cmd) {
    this->_name = n;
    this->_formalArgs = args;
    this->_locarVars = vars;
    this->_body = cmd; 
  }
}
