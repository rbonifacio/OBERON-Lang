#ifndef COMMAND_H
#define COMMAND_H

#include "Expression.hpp"

#include <string>
#include <list>
#include <vector>

using namespace std;

namespace OberonLang {
  
  class Command  {
  public:
    virtual void run() = 0;
    // virtual void accept(OBRVisitor* v) = 0; 
    virtual ~Command() { }
    virtual void acceptVisit(IVisitor* visitor) = 0;
  };

  class Assignment : public Command {
  public:
    Assignment(string v, Expression* e) { _var = v; _expression = e; }
    void run();
    void acceptVisit(IVisitor* visitor);
    // void accept(OBRVisitor* v);
    string name() { return _var; } // !TODO: Escolher qual usar
    string var() { return _var; }
    Expression* getValue() { return _expression; } // !TODO: Escolher qual usar
    Expression* expression() { return _expression; } 
    ~Assignment() { delete _expression; }
  private:
    string _var;
    Expression* _expression;
  };

  class ProcedureCall : public Command {
  public:
    ProcedureCall(string n, vector<Expression*> *args) { this->_name = n; this->_args = args; }
    // void accept(OBRVisitor* v);
    void acceptVisit(IVisitor* visitor);
    void run();
    string name() { return _name; };
    vector<Expression*> *args() { return _args; }
    ~ProcedureCall() { 
    	for(auto it = this->_args->begin(); it != this->_args->end(); ++it)
    		delete *it;
    delete this->_args; }
  private:
    string _name;
    vector<Expression*> *_args;
  };

  class BlockCommand : public Command {
  public:
    void acceptVisit(IVisitor* visitor);
    // void accept(OBRVisitor* v);
    void run();
    list<Command*>* getCommands() { return _commands; } // !TODO: Talvez apenas um getCommands seja necessário
    list<Command*>* commands() { return _commands; } 
    BlockCommand(list<Command*> *cmds) { this->_commands = cmds; }
    ~BlockCommand() { 
    	
    	for(auto it = _commands->begin(); it != _commands->end(); ++it){
    		delete *it;
    	}
    	delete _commands; 
    
    }
  private:
    list<Command*> *_commands;
  };

  class PrintCommand : public Command {
  public:
    void acceptVisit(IVisitor* visitor);
    // void accept(OBRVisitor* v);
    PrintCommand(Expression* exp) {this ->_expression = exp;}
    void run();
    Expression* expression() { return _expression; }
    ~PrintCommand() { delete _expression; }
  private:
    Expression* _expression;
  };

  class WhileCommand : public Command {
  public:
    WhileCommand(Expression* condition, BlockCommand* cmds) { this->_cond = condition; this->_cmds = cmds; }
    void acceptVisit(IVisitor* visitor);
    // void accept(OBRVisitor* v);
    void run();
    Expression* condition() { return _cond; }
    BlockCommand* command() { return _cmds; }
    BlockCommand* getCommands() { return _cmds; }; // !TODO: Remover algum deles
    ~WhileCommand() { delete _cond; delete _cmds; }
  private:
    Expression* _cond;
    BlockCommand* _cmds;
  };

  class IfThenCommand : public Command {
  public:
    void acceptVisit(IVisitor* visitor);
    // void accept(OBRVisitor* v);
    IfThenCommand(Expression* condition, BlockCommand* cmds) { this->_cond = condition; this->_then = cmds; }
    void run();
    Expression* condition() { return _cond; }
    BlockCommand* thenCmd() { return _then; } // !TODO: Escolher qual usar
    BlockCommand* getCommands() { return _then; };
    ~IfThenCommand() { delete _cond; delete _then; }
  private:
    Expression* _cond;
    BlockCommand* _then;
  };

  class IfThenElseCommand : public Command {
  public:
    IfThenElseCommand(Expression* cond, BlockCommand* cmds1, BlockCommand* cmds2) {
      this->_cond = cond;
      this->_then = cmds1;
      this->_else = cmds2;
    }
    // void accept(OBRVisitor* v);
    void acceptVisit(IVisitor* visitor);
    void run();
    BlockCommand* getTrueConditionCommands() { return _then; }; // !TODO: Escolher qual usar
    BlockCommand* thenCmd() { return _then; } 
    BlockCommand* getFalseConditionCommands() { return _else; }; // !TODO: Escolher qual usar
    BlockCommand* elseCmd() { return _else; }
    Expression* condition() { return _cond; }
    ~IfThenElseCommand() { delete _cond; delete _then; delete _else; }
  private:
    Expression* _cond;
    BlockCommand* _then;
    BlockCommand* _else;
  };
  
}

#endif
