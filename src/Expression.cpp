#include "Expression.hpp"

namespace OberonLang {
  Undefined* Undefined::_undef_instance = 0;

  Undefined* Undefined::instance() {
    if(_undef_instance == 0) {
      _undef_instance = new Undefined(); 
    }
    return _undef_instance; 
  }
  
}
