#include <map>
#include <string>

#include "Environment.hpp"
using namespace std;
namespace OberonLang { 
  Environment* Environment::_instance = 0;
  
  Environment* Environment::instance() {
    if(_instance == 0) {
      _instance = new Environment(); 
    }
    return _instance; 
  }

  void Environment::env(string var, Value* value) {
    if(_env->empty()) {
      this->push();
    }
    _env->top()->insert( pair<string, Value*>(var, value) );
  }

  Value* Environment::lookup(string var) {
    return _env->top()->at(var);
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
        _procedures->insert(pair<string,DecProcedure*>(p->name(),p));
    }
    DecProcedure* Environment::lookupProcedure(string n){
        return _procedures->at(n);
    }
}

