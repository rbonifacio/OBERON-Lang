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
    Program(Command* main);
    Program(vector<VarDec*> globalVars, vector<DecProcedure*> procedures, Command* main); 
    void acceptVisit(IVisitor* visitor);
    void run();
  private:
    Command* _main; 
    vector<VarDec*> _globalVars; 
    vector<DecProcedure*> _procedures; 
  };
}

#endif 
