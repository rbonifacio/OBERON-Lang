#ifndef VAR_DECLARATION_H
#define VAR_DECLARATION_H

#include "Types.hpp"
#include "Command.hpp"

using namespace std;

namespace OberonLang {
    
    class VarDeclaration : public Command {
    public:
      VarDeclaration(TypesEnum t, string n) { this->_type = t; this->_name = n; this->_value = NULL; }
      VarDeclaration(TypesEnum t, string n, Expression* v) { this->_type = t; this->_name = n; this->_value = v->eval(); }
      TypesEnum type() { return _type; }
      string name() { return _name; }
      void run();
    private:
      TypesEnum _type;
      string _name;
      Value* _value;
    };
}
#endif 
