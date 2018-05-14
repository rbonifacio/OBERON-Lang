#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <cstdint>
#define TYPE_INTEGER  uint64_t
#define TYPE_BOOLEAN  bool
#define TYPE_REAL double

using namespace std;

namespace OberonLang {

  class Value;
  
  /* the base class of our Expression hierarchy */ 
  class Expression {
  public:
    virtual Value* eval() = 0;  
  };

  /* the base class of our value hierarchy */   
  class Value : public Expression{
  public:
    virtual Value* eval() = 0; 
  };

  /* a parametric value class */   
  template <typename T>
  class GenericValue : public Value {
  public:
    GenericValue(T v) { _value = v; }
    Value* eval() { return this; } ;
    T value() { return _value; } 
  private:
    T _value; 
  };

  /* the Oberon numeric value, integers are unsigned */
  class IntValue : public GenericValue<TYPE_INTEGER> {
  public:
    IntValue(TYPE_INTEGER value) : GenericValue(value) {} 
  };
  
  /* the Oberon real value */
  class RealValue : public GenericValue<TYPE_REAL> {
  public:
    RealValue(TYPE_REAL value) : GenericValue(value) {} 
  };

  /* the Oberon boolean value */ 
  class BooleanValue : public GenericValue<bool> {
  public:
    BooleanValue(bool value) : GenericValue(value) {} 
  };
}
#endif 
