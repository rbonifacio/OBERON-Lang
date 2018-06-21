#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <cstdint>
#include <iostream>

#define TYPE_INTEGER  uint64_t
#define TYPE_BOOLEAN  bool
#define TYPE_REAL double

using namespace std;

namespace OberonLang {

  class Value;
  class IVisitor; 
  
  /* the base class of our Expression hierarchy */ 
  class Expression {
  public:
    virtual Value* eval() = 0;
    virtual ~Expression() { }
    virtual void acceptVisit(IVisitor* visitor) = 0;
  };

  /* the base class of our value hierarchy */   
  class Value : public Expression{
  public:
    virtual Value* eval() = 0;
    virtual void show() = 0;
    virtual void acceptVisit(IVisitor* visitor) = 0;
    virtual ~Value() { } 
  };

  class Undefined : public Value {
  public:
    Value* eval() { return this; }
    static Undefined* instance();
    void show(){ cout << "Variável indefinida!"; }
    void acceptVisit(IVisitor* visitor);
  private:
    Undefined() {}
    static Undefined* _undef_instance;
  };
    
  /* a parametric value class */   
  template <typename T>
  class GenericValue : public Value {
  public:
    GenericValue(T v) { _value = v; }
    Value* eval() { return this; } ;
    T value() { return _value; }
    void show(){ cout << _value; }
    virtual void acceptVisit(IVisitor* visitor) = 0;
    virtual ~GenericValue() { }  
  private:
    T _value; 
  };

  /* the Oberon numeric value, integers are unsigned */
  class IntValue : public GenericValue<TYPE_INTEGER> {
  public:
    IntValue(TYPE_INTEGER value) : GenericValue(value) {}
    friend ostream& operator<< (ostream& os, IntValue& v) { os << v.value(); return os; } 
    void acceptVisit(IVisitor* visitor);
    ~IntValue() { }
  };
  
  /* the Oberon real value */
  class RealValue : public GenericValue<TYPE_REAL> {
  public:
    RealValue(TYPE_REAL value) : GenericValue(value) {}
    friend ostream& operator<< (ostream& os, RealValue& v) { os << v.value(); return os; } 
    void acceptVisit(IVisitor* visitor);
    ~RealValue() { }
  };

  /* the Oberon boolean value */ 
  class BooleanValue : public GenericValue<bool> {
  public:
    BooleanValue(bool value) : GenericValue(value) {}
    friend ostream& operator<< (ostream& os, BooleanValue& v) { os << v.value(); return os; } 
    void acceptVisit(IVisitor* visitor);
    ~BooleanValue() { } 
  };
}
#endif 
