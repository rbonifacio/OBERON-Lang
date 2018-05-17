
#ifndef COMMAND_H
#define COMMAND_H

#include "Expression.hpp"

#include <string>
#include <list>
#include <vector>

using namespace std;

namespace OberonLang {

  class Command {
  public:
    virtual void run() = 0; 
  };

  class Assignment : public Command {
  public:
    Assignment(string v, Expression* e) { var = v; expression = e; }
    void run();
  private:
    string var;
    Expression* expression; 
  };

  class ProcedureCall : public Command {
  public:
    ProcedureCall(string n, vector<Expression*> args) { this->_name = n; this->_args = args; }
    void run(); 
  private:
    string _name;
    vector<Expression*> _args;
  };
    
  class BlockCommand : public Command {
  public:
    BlockCommand(list<Command*> cmds) { this->commands = cmds; }
    void run(); 
  private:
    list<Command*> commands;
  };
    
    class PrintCommand : public Command{
        public:
        PrintCommand(Expression* exp) {this -> expression = exp;}
        void run();
        
        private:
        Expression* expression;
    };
}

#endif 
