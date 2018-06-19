#ifndef DECLARATION_H
#define DECLARATION_H

#include "Types.hpp"
#include "Visitor.hpp"

using namespace std;

namespace OberonLang {
  class Declaration {
  public:
    Declaration(TypesEnum t, string n) { this->_type = t; this->_name = n; }
    TypesEnum type() { return _type; }
    void accept(OBRVisitor* v); 
    string name() { return _name; }
  private:
    TypesEnum _type;
    string _name;
  };
  
}



#endif 
