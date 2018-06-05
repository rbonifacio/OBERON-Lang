#ifndef PROCEDURE_H
#define PROCEDURE_H

#include <string>
#include <vector>

#include "Declaration.hpp"
#include "Command.hpp"

using namespace std;
namespace OberonLang {
    
    class DecProcedure : public Command {
    public:
      DecProcedure(string n, vector<Declaration> args, vector<Declaration> vars, Command* cmd);
      string name() { return _name; }
      void run();
      vector<Declaration> formalArgs() { return _formalArgs; }
      vector<Declaration> localVars() { return _localVars; }
      Command* body() { return _body; }
      ~DecProcedure();
    private:
      string _name;
      vector<Declaration> _formalArgs;
      vector<Declaration> _localVars;
      Command* _body;
    };
}

#endif 
