#ifndef PROGRAM_H
#define PROGRAM_H

#include "Command.hpp"
#include "Procedure.hpp" 
#include "VarDec.hpp" 

#include <vector>

using namespace std; 

namespace OberonLang { 
  class Program : Command {
  public:
    Program(BlockCommand* main);
    Program(vector<VarDec*> globalVars, vector<DecProcedure*> procedures, BlockCommand* main); 
    void acceptVisit(IVisitor* visitor);
    void run();
    vector<VarDec*>* getGlobalVars() { return &_globalVars; }  
    vector<DecProcedure*>* getProcedures() { return &_procedures; }
    BlockCommand* getCommands() { return _main; }
  private:
    BlockCommand* _main; 
    vector<VarDec*> _globalVars; 
    vector<DecProcedure*> _procedures; 
  };
}

#endif 
