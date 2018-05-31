
#include <string>

#include "Expression.hpp"

using namespace std;

namespace OberonLang {
  class VarRef : public Expression {
  public:
    VarRef(string v) { this->_var = v; }
    Value* eval() {return Environment::instance()->lookup(_var)->eval();};
  private:
    string _var; 
  };
  
}
