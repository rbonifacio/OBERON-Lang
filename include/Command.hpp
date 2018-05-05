
#ifndef COMMAND_H
#define COMMAND_H

#include "Expression.hpp"

#include <string>

namespace OberonLang {

  class Command {
  public:
    virtual void run() = 0; 
  };

  class Assignment : public Command {
  public:
    Assignment(string v, Expression* e) { var = v; expression = e; }
  private:
    string var;
    Expression* expression; 
  }
}

#endif 
