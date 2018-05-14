#include "Command.hpp"
#include "Environment.hpp"

#include <list>

using namespace std;

namespace OberonLang {
  void Assignment::run() {
    Environment::instance()->env(var, expression->eval());
  }

  void BlockCommand::run() {
    for (list<Command*>::iterator it= commands.begin(); it != commands.end(); ++it) {
      it->run();
    }
  }
  
}
