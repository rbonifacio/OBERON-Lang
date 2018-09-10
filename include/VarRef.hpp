#ifndef VAR_REF_H
#define VAR_REF_H

#include <string>

#include "Expression.hpp"

using namespace std;

namespace OberonLang {
  class VarRef : public Expression {
  public:
    explicit VarRef(string v) : _var(v) { }
    string name() { return _var; }
    void acceptVisit(IVisitor* visitor);
    Value* eval();
    TypesEnum expType(); 
    ~VarRef() { }
    // void accept(OBRVisitor* v); 
  private:
    string _var; 
  };
  
}
#endif
