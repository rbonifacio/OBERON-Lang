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
    ~Environment() {
    	_env_instance = 0;
    	
    	// Delete _env
		  while(!this->_env->empty()){
		  	map<string, Value*> *el = this->_env->top();
				for(auto it = el->begin(); it != el->end(); ++it){
					delete it->second;
				}
				delete el;
				this->_env->pop();
		  }
		  delete this->_env; 
		  
		  // Delete _procedures
		  for(auto it = this->_procedures->begin(); it != this->_procedures->end(); ++it)
		  	delete it->second;
		  delete this->_procedures; 
		  
		  // Delete _globals
		  for(auto it = this->_globals->begin(); it != this->_globals->end(); ++it)
		  	delete it->second;
		  delete this->_globals;
    }
  private:
    Environment();
    static Environment* _env_instance;            // according to the singleton design pattern
    stack< map<string, Value*>* >* _env;
    map<string, DecProcedure*>* _procedures;
    map<string, Value*>* _globals;
  };

}

#endif
