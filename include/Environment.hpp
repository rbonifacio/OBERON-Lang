#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <map>
#include <stack> 
#include <string> 

#include "Expression.hpp"
#include "Procedure.hpp"
using namespace std;
namespace OberonLang {

  class Environment {
  public:
    static Environment* instance(); 
    void env(string var, Value* value);
    void decProcedure(DecProcedure* p);
    Value* lookup(string var);
    DecProcedure* lookupProcedure(string n);
    void push();                                   //it should be called after a procedure call
    void pop();                                    //it should be called after returning 
    ~Environment() { delete _env; }
  private:
    Environment() { _env = new stack< map<string, Value*>* >(); }
    static Environment* _instance;                 // according to the singleton design pattern
    stack< map<string, Value*>* >* _env;
    map<string,DecProcedure*>* _procedures;
      
  };
    

}

#endif 
