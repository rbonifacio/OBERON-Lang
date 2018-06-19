#include "Expression.hpp"

namespace OberonLang {
  Undefined* Undefined::_undef_instance = 0;

  Undefined* Undefined::instance() {
    if(_undef_instance == 0) {
      _undef_instance = new Undefined(); 
    }
    return _undef_instance; 
  }

  
  void Undefined::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void IntValue::accept(OBRVisitor* v) {
    v->visit(this); 
  }

  void RealValue::accept(OBRVisitor* v) {
    v->visit(this); 
  }
  
  void BooleanValue::accept(OBRVisitor* v) {
    v->visit(this); 
  }

}
