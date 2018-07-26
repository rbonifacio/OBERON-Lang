#include "Declaration.hpp"


namespace OberonLang {

  void Declaration::accept(OBRVisitor* v) {
    v->visit(this);
  }

}
