#ifndef PROCEDURE_H
#define PROCEDURE_H

#include <string>
#include <vector>

#include "VarDeclaration.hpp"
#include "Command.hpp"

using namespace std;
namespace OberonLang {
    
    class DecProcedure : public Command {
    public:
      DecProcedure(string n, vector<VarDeclaration> args, vector<VarDeclaration> vars, Command* cmd);
      string name() { return _name; }
      void run();
      vector<VarDeclaration> formalArgs() { return _formalArgs; }
      vector<VarDeclaration> localVars() { return _localVars; }
      Command* body() { return _body; }
      ~DecProcedure();
    private:
      string _name;
      vector<VarDeclaration> _formalArgs;
      vector<VarDeclaration> _localVars;
      Command* _body;
    };
}

#endif 
