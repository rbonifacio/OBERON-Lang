
#include <string>

#include "Expression.hpp"

using namespace std;

namespace OberonLang {
  class VarRef : public Expression {
  public:
    VarRef(string v) { this->var = v; }
    Value* eval() { return Environment::instance()->env(var)->eval(); } 
  private:
    string var; 
  };
  
}
