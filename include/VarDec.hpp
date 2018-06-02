#ifndef VARDEC_H
#define VARDEC_H

#include <string> 
#include "Types.hpp" 

namespace OberonLang {
  class VarDec {
  public:
    VarDec(string name, TypesEnum type) { this->_name = name; this->_type = type; }
    string name() { return _name; }
    TypesEnum type() { return _type; }
  private:
    string _name;
    TypesEnum _type; 
  };
}

#endif
