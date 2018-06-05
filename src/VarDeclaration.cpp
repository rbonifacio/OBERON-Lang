#include "VarDeclaration.hpp"
#include "Environment.hpp"

namespace OberonLang {
  void VarDeclaration::run() {
    if(Environment::instance()->lookup(_name) == Undefined::instance()) {
      Environment::instance()->env(_name, _value);
    } else {
      // TODO: Throw Variable conflit exceptions
    }
  }
}