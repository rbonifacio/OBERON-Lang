#include <map>
#include <string>

#include "Environment.hpp"

using namespace std;

namespace OberonLang { 
  Environment* Environment::_env_instance = 0;
  
  Environment* Environment::instance() {
    if(_env_instance == 0) {
      _env_instance = new Environment(); 
    }
    return _env_instance; 
  }
  
  Environment::Environment()  {
    _env = new stack< map<string, Value*>* >();
    _globals = new map<string, Value*>();
    _procedures = new map<string,DecProcedure*>();

    this->push();
  }
    
  void Environment::env(string var, Value* value) {
    if(_env->empty()) {
      this->push();
    }
    _env->top()->insert( pair<string, Value*>(var, value) );
  }

  Value* Environment::env(string var) {
    if(_env == 0 || _env->top() == 0 || _env->top()->count(var) == 0) {
      return Undefined::instance(); 
    }
    return _env->top()->at(var);
  }

  void Environment::global(string var, Value* value) {
    if(_globals == 0) {
      _globals = new map<string, Value*>();
    }
    _globals->insert( pair<string, Value*>(var, value) );
  }

  Value* Environment::global(string var) {
    return _globals->count(var) > 0 ? _globals->at(var) : Undefined::instance(); 
  }
  
  void Environment::push() {
    _env->push(new map<string, Value*>());
  }

  void Environment::pop() {
    _env->pop(); 
  }

  void Environment::decProcedure(DecProcedure* p){
    if(_procedures == 0){
      _procedures = new map<string,DecProcedure*>();
    }
    _procedures->insert(pair<string, DecProcedure*>(p->name(), p));
  }

  DecProcedure* Environment::decProcedure(string n){
    return _procedures->at(n);
  }
  
}

