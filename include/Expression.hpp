#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <cstdint>
#include <iostream>
#include <string>

#include "Types.hpp"

#define TYPE_INTEGER  int64_t
#define TYPE_BOOLEAN  bool
#define TYPE_REAL double

using namespace std;

namespace OberonLang {

  class Value;
  class IVisitor; 
  // class OBRVisitor;
  
  /* the base class of our Expression hierarchy */ 
  class Expression  { 
  public:
    virtual Value* eval() = 0;
    virtual TypesEnum expType() = 0; 
    // virtual void accept(OBRVisitor* v) = 0; 
    virtual ~Expression() { }
    virtual void acceptVisit(IVisitor* visitor) = 0;
  };

  /* the base class of our value hierarchy */   
  class Value : public Expression{
  public:
    virtual Value* eval() = 0;
    virtual TypesEnum expType() = 0; 
    // virtual void accept(OBRVisitor* v) = 0; 
    virtual void show() = 0;
    virtual void acceptVisit(IVisitor* visitor) = 0;
    virtual ~Value() { } 
  };

  class Undefined : public Value {
  public:
    Value* eval() { return Undefined::instance(); }
    TypesEnum expType();
    static Undefined* instance();
    // void accept(OBRVisitor* v);
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
    virtual TypesEnum expType() = 0; 
    T value() { return _value; }
    // virtual void accept(OBRVisitor* v) = 0; 
    void show(){ cout << _value; }
    virtual void acceptVisit(IVisitor* visitor) = 0;
    virtual ~GenericValue() { }  
  protected:
    T _value; 
  };

  /* the Oberon numeric value, integers are unsigned */
  class IntValue : public GenericValue<TYPE_INTEGER> {
  public:
    IntValue(TYPE_INTEGER value) : GenericValue(value) {}
    Value *eval() { return new IntValue(this->_value); }
    TypesEnum expType();
    // void accept(OBRVisitor* v);
    friend ostream& operator<< (ostream& os, IntValue& v) { os << v.value(); return os; } 
    void acceptVisit(IVisitor* visitor);
    ~IntValue() { }
  };
  
  /* the Oberon real value */
  class RealValue : public GenericValue<TYPE_REAL> {
  public:
    RealValue(TYPE_REAL value) : GenericValue(value) {}
    Value *eval() { return new RealValue(this->_value); }
    TypesEnum expType();
    // void accept(OBRVisitor* v);
    friend ostream& operator<< (ostream& os, RealValue& v) { os << v.value(); return os; } 
    void acceptVisit(IVisitor* visitor);
    ~RealValue() { }
  };

  /* the Oberon boolean value */ 
  class BooleanValue : public GenericValue<bool> {
  public:
    BooleanValue(bool value) : GenericValue(value) {}
    Value *eval() { return new BooleanValue(this->_value); }
    TypesEnum expType();
    // void accept(OBRVisitor* v);
    friend ostream& operator<< (ostream& os, BooleanValue& v) { os << v.value(); return os; } 
    void acceptVisit(IVisitor* visitor);
    ~BooleanValue() { } 
  };
  
  /* the Oberon string value */ 
  class StringValue : public GenericValue<std::string> {
  public:
    StringValue(std::string value) : GenericValue(value) {}
    Value *eval() { return new StringValue(this->_value); }
    TypesEnum expType();
    // void accept(OBRVisitor* v);
    friend ostream& operator<< (ostream& os, StringValue& v) { os << v.value(); return os; } 
    void acceptVisit(IVisitor* visitor);
    ~StringValue() { } 
  };
}

// #include "Visitor.hpp"


#endif 
