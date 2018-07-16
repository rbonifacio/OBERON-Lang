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
    virtual ~Command() { }
    virtual void acceptVisit(IVisitor* visitor) = 0;
  };

  class Assignment : public Command {
  public:
    Assignment(string v, Expression* e) { var = v; expression = e; }
    void run();
    void acceptVisit(IVisitor* visitor);
    string name() { return var; }
    Expression* getValue() { return expression; }
    ~Assignment() { delete expression; }
  private:
    string var;
    Expression* expression;
  };

  class ProcedureCall : public Command {
  public:
    ProcedureCall(string n, vector<Expression*> args) { this->_name = n; this->_args = args; }
    void run();
    string name() { return _name; };
    void acceptVisit(IVisitor* visitor);
    ~ProcedureCall() { }
  private:
    string _name;
    vector<Expression*> _args;
  };

  class BlockCommand : public Command {
  public:
    BlockCommand(list<Command*> cmds) { this->commands = cmds; }
    void acceptVisit(IVisitor* visitor);
    void run();
    list<Command*>* getCommands() { return &commands; }
  private:
    list<Command*> commands;
  };

  class PrintCommand : public Command {
  public:
    PrintCommand(Expression* exp) {this -> expression = exp;}
    void acceptVisit(IVisitor* visitor);
    void run();
    ~PrintCommand() { delete expression; }
  private:
    Expression* expression;
  };

  class WhileCommand : public Command {
  public:
    WhileCommand(Expression* condition, BlockCommand* cmds) { this->_cond = condition; this->_cmds = cmds; }
    void acceptVisit(IVisitor* visitor);
    BlockCommand* getCommands() { return _cmds; };
    void run();
    ~WhileCommand() {}
  private:
    Expression* _cond;
    BlockCommand* _cmds;
  };
  class IfThenCommand : public Command {
  public:
    IfThenCommand(Expression* condition, BlockCommand* cmds) { this->_cond = condition; this->_cmds = cmds; }
    void acceptVisit(IVisitor* visitor);
    BlockCommand* getCommands() { return _cmds; };
    void run();
    ~IfThenCommand() {}
  private:
    Expression* _cond;
    BlockCommand* _cmds;
  };
  class IfThenElseCommand : public Command {
  public:
    IfThenElseCommand(Expression* condition, BlockCommand* cmds, BlockCommand* cmds2) {
      this->_cond = condition;
      this->_cmds = cmds;
      this->_cmds2 = cmds2;}
    void run();
    BlockCommand* getTrueConditionCommands() { return _cmds; };
    BlockCommand* getFalseConditionCommands() { return _cmds2; };
    void acceptVisit(IVisitor* visitor);
    ~IfThenElseCommand() {}
  private:
    Expression* _cond;
    BlockCommand* _cmds;
    BlockCommand* _cmds2;
  };

}

#endif
