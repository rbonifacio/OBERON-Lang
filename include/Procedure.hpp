#ifndef PROCEDURE_H
#define PROCEDURE_H

#include <string>
#include <list>

#include "Declaration.hpp"
#include "Command.hpp"

using namespace std;

class DecProcedure {
public:
  DecProcedure(string n, list<Declaration> args, list<Declaration> vars, Command* cmd);
  string name() { return _name; }
  list<Declaration> formalArgs() { return _formalArgs; }
  list<Declaration> localVars() { return _localVars; }
  Command* body() { return _body; }
private:
  string _name;
  list<Declaration> _formalArgs; 
  list<Declaration> _localVars;
  Command* _body;  
};

#endif 
