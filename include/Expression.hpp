#ifndef EXPRESSION_H
#define EXPRESSION_H

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

  /* the Oberon int value */
  class IntValue : public GenericValue<int> {
  public:
    IntValue(int value) : GenericValue(value) {} 
  };

  /* the Oberon boolean value */ 
  class BooleanValue : public GenericValue<bool> {
  public:
    BooleanValue(bool value) : GenericValue(value) {} 
  };
}
#endif 
