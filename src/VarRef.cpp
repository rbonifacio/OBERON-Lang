#include "VarRef.hpp"
#include "Environment.hpp"

namespace OberonLang {
  Value* VarRef::eval() {
    return Environment::instance()->lookup(this->_var);
  }

  void VarRef::accept(OBRVisitor* v) {
    //v->visit(this); 
  }
  
}
