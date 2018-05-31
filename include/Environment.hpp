#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <map>
#include <stack>
#include <string>

#include "Expression.hpp"
#include "Procedure.hpp"
#include "Command.hpp"

using namespace std;
namespace OberonLang {

  class Environment {
  public:
    static Environment* instance();
    void env(string var, Value* value);
    Value* env(string var);
    void global(string var, Value* value);
    Value* global(string var);
    Value* lookup(string var); 
    void decProcedure(DecProcedure* p);
    DecProcedure* decProcedure(string n);
    void push();                                   //it should be called after a procedure call
    void pop();                                    //it should be called after returning
    ~Environment() { delete _env; delete _procedures; }
  private:
    Environment();
    static Environment* _env_instance;            // according to the singleton design pattern
    stack< map<string, Value*>* >* _env;
    map<string, DecProcedure*>* _procedures;
    map<string, Value*>* _globals;
  };

}

#endif
