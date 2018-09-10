#include "Procedure.hpp"

namespace OberonLang { 
  DecProcedure::DecProcedure(string n, vector<Declaration*> *args, vector<Declaration*> *vars, Command* cmd) {
  // DecProcedure::DecProcedure(string n, vector<Declaration> args, vector<Declaration> vars, Command* cmd) {
    this->_name = n;
    this->_formalArgs = args;
    this->_localVars = vars;
    this->_body = cmd; 
  }

  // void DecProcedure::accept(OBRVisitor* v) {
  //   v->visit(this);
  // }
  
  DecProcedure::~DecProcedure() {
  	for(auto it = this->_formalArgs->begin(); it != this->_formalArgs->end(); ++it)
  		delete (*it);
  	delete this->_formalArgs;
  	for(auto it = this->_localVars->begin(); it != this->_localVars->end(); ++it)
  		delete (*it);
  	delete this->_localVars;
    delete this->_body;
  }
}
