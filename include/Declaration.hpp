#ifndef DECLARATION_H
#define DECLARATION_H

#include "Types.hpp"

using namespace std;

class Declaration {
public:
  Declaration(TypeEnum t, string n) { this._type = t; this._name = n; }
  TypeEnum type() { return _type; }
  string name() { return _name; } 
private: 
  TypeEnum _type;
  string _name; 
}

#endif 
