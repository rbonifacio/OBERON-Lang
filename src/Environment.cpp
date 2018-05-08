#include <map>
#include <string>

#include "Environment.hpp"

namespace OberonLang { 
  Environment* Environment::_instance = 0;
  
  Environment* Environment::instance() {
    if(_instance == 0) {
      _instance = new Environment(); 
    }
    return _instance; 
  }

  void Environment::env(std::string var, Value* value) {
    if(_env->empty()) {
      this->push();
    }
    _env->top()->insert( std::pair<std::string, Value*>(var, value) ); 
  }

  Value* Environment::lookup(std::string var) {
    return _env->top()->at(var);
  }

  void Environment::push() {
    _env->push(new std::map<std::string, Value*>());
  }

  void Environment::pop() {
    _env->pop(); 
  }
}

