#include "Command.hpp"
#include "Environment.hpp"

namespace OberonLang {
  void Assignment::run() {
    Environment::instance()->env(var, expression->eval());
  }
}
