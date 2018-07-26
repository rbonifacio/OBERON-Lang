#ifndef PROGRAM_H
#define PROGRAM_H

#include "Command.hpp"
#include "Procedure.hpp"
#include "VarDec.hpp"

#include <vector>

using namespace std; 

namespace OberonLang { 
  class Program : public Command {
  public:
    Program(Command* main);
    Program(vector<VarDec*> globalVars, vector<DecProcedure*> procedures, Command* main);
    void acceptVisit(IVisitor* visitor);
    // void accept(OBRVisitor* v); 
    void run();
    vector<VarDec*>* getGlobalVars() { return &_globalVars; }  
    vector<DecProcedure*>* getProcedures() { return &_procedures; }
    Command* getCommands() { return _main; }
  private:
    Command* _main; 
    vector<VarDec*> _globalVars; 
    vector<DecProcedure*> _procedures; 
  };
}

#endif 
