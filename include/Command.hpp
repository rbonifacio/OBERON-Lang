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
    virtual void accept(OBRVisitor* v) = 0; 
    virtual ~Command() { }
  };

  class Assignment : public Command {
  public:
    Assignment(string v, Expression* e) { _var = v; _expression = e; }
    void run();
    void accept(OBRVisitor* v);
    string var() { return _var; }
    Expression* expression() { return _expression; } 
    ~Assignment() { delete _expression; }
  private:
    string _var;
    Expression* _expression;
  };

  class ProcedureCall : public Command {
  public:
    ProcedureCall(string n, vector<Expression*> args) { this->_name = n; this->_args = args; }
    void accept(OBRVisitor* v);
    void run();
    string name() { return _name; }
    vector<Expression*> args() { return _args; }
    ~ProcedureCall() { }
  private:
    string _name;
    vector<Expression*> _args;
  };

  class BlockCommand : public Command {
  public:
    BlockCommand(list<Command*> cmds) { this->_commands = cmds; }
    void accept(OBRVisitor* v);
    void run();
    list<Command*> commands() { return _commands; } 
  private:
    list<Command*> _commands;
  };

  class PrintCommand : public Command {
  public:
    PrintCommand(Expression* exp) {this ->_expression = exp;}
    void accept(OBRVisitor* v);
    void run();
    Expression* expression() { return _expression; }
    ~PrintCommand() { delete _expression; }
  private:
    Expression* _expression;
  };

  class WhileCommand : public Command {
  public:
    WhileCommand(Expression* condition, BlockCommand* cmds) { this->_cond = condition; this->_cmds = cmds; }
    void accept(OBRVisitor* v);
    void run();
    Expression* condition() { return _cond; }
    BlockCommand* command() { return _cmds; }
    ~WhileCommand() {}
  private:
    Expression* _cond;
    BlockCommand* _cmds;
  };

  class IfThenCommand : public Command {
  public:
    IfThenCommand(Expression* condition, BlockCommand* cmds) { this->_cond = condition; this->_then = cmds; }
    void accept(OBRVisitor* v);
    void run();
    Expression* condition() { return _cond; }
    BlockCommand* thenCmd() { return _then; }
    ~IfThenCommand() {}
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
    void accept(OBRVisitor* v);
    void run();
    Expression* condition() { return _cond; }
    BlockCommand* thenCmd() { return _then; } 
    BlockCommand* elseCmd() { return _else; }
    ~IfThenElseCommand() {}
  private:
    Expression* _cond;
    BlockCommand* _then;
    BlockCommand* _else;
  };
  
}

#endif
