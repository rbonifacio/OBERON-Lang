#include <iostream> 
#include "gtest/gtest.h"

#include "Expression.hpp"
#include "BinExpression.hpp"
#include "Environment.hpp"
#include "Command.hpp"

using namespace OberonLang; 

TEST (AddExpression, SimpleAdd) {
  IntValue *v1 = new IntValue(10);
  IntValue *v2 = new IntValue(5);
  AddExpression* add = new AddExpression(v1, v2);
  IntValue* result = (IntValue *)(add->eval());
  
  EXPECT_EQ (15, result->value());
  
  delete v1;
  delete v2;
  delete add;
  delete result;
}

/* !TODO: desalocar memória */
TEST (TestAssignment, SimpleAssignment) {
  IntValue *value = new IntValue(10);
  Assignment* assignment = new Assignment("x", value);
  assignment->run();
  
  EXPECT_EQ (10, ((IntValue*)Environment::instance()->lookup("x")->eval())->value());
  
  delete value;
  delete assignment;
}

TEST (SubExpression, SimpleSub) {
  IntValue *v1 = new IntValue(100);
  IntValue *v2 = new IntValue(200);
  SubExpression* sub = new SubExpression(v1, v2);
  IntValue *result = (IntValue *)sub->eval();
  
  EXPECT_EQ (-100, result->value());
  
  delete v1;
  delete v2;
  delete result;
  delete sub;
}

TEST (MultExpression, SimpleMult) {
  IntValue *v1 = new IntValue(98);
  IntValue *v2 = new IntValue(-172);
  MultExpression* mult = new MultExpression(v1, v2);
  IntValue *result = (IntValue *)mult->eval();
  
  EXPECT_EQ (-16856, result->value());
  
  delete v1;
  delete v2;
  delete result;
  delete mult;
}

TEST (DivExpression, SimpleDiv) {
  IntValue *v1 = new IntValue(87);
  IntValue *v2 = new IntValue(9);
  DivExpression* div = new DivExpression(v1, v2);
  IntValue *result = (IntValue *)div->eval();
  
  EXPECT_EQ (9, result->value());
  
  delete v1;
  delete v2;
  delete result;
  delete div;
}


TEST (SraSlaExpression, NegativeValues) {
  IntValue *v1 = new IntValue(0x8000000000000000);
  IntValue *v2 = new IntValue(1);
  SrlExpression* srl = new SrlExpression(v1, v2);
  IntValue *result = (IntValue *)srl->eval();
  SllExpression *sll = new SllExpression(result, v2);
  IntValue *reverse = (IntValue *)sll->eval();
  
  EXPECT_EQ (0xc000000000000000, result->value());
  EXPECT_EQ (0x8000000000000000, reverse->value());
  
  delete v1;
  delete v2;
  delete srl;
  delete sll;
  delete result;
  delete reverse;
}


TEST (XorExpression, TrueFalse) {
  BooleanValue *v1 = new BooleanValue(true);
  BooleanValue *v2 = new BooleanValue(false);
  XorExpression *xorExp = new XorExpression(v1, v2);
  BooleanValue *result = (BooleanValue *)xorExp->eval();
  
  EXPECT_EQ (true, result->value());
  
  delete v1;
  delete v2;
  delete xorExp;
  delete result;
}

TEST (AndExpression, TrueTrue) {
  BooleanValue *v1 = new BooleanValue(true);
  BooleanValue *v2 = new BooleanValue(true);
  AndExpression *andExp = new AndExpression(v1, v2);
  BooleanValue *result = (BooleanValue *)andExp->eval();
  
  EXPECT_EQ (true, result->value());
  
  delete v1;
  delete v2;
  delete andExp;
  delete result;
}

TEST (AndExpression, TrueFalse) {
  BooleanValue *v1 = new BooleanValue(true);
  BooleanValue *v2 = new BooleanValue(false);
  AndExpression *andExp = new AndExpression(v1, v2);
  BooleanValue *result = (BooleanValue *)andExp->eval();
  
  EXPECT_EQ (false, result->value());
  
  delete v1;
  delete v2;
  delete andExp;
  delete result;
}

TEST (OrExpression, TrueTrue) {
  BooleanValue *v1 = new BooleanValue(true);
  BooleanValue *v2 = new BooleanValue(true);
  OrExpression *orExp = new OrExpression(v1, v2);
  BooleanValue *result = (BooleanValue *)orExp->eval();
  
  EXPECT_EQ (true, result->value());
  
  delete v1;
  delete v2;
  delete orExp;
  delete result;
}

TEST (OrExpression, TrueFalse) {
  BooleanValue *v1 = new BooleanValue(true);
  BooleanValue *v2 = new BooleanValue(false);
  OrExpression *orExp = new OrExpression(v1, v2);
  BooleanValue *result = (BooleanValue *)orExp->eval();
  
  EXPECT_EQ (true, result->value());
  
  delete v1;
  delete v2;
  delete orExp;
  delete result;
}

TEST (XorExpression, TrueTrue) {
  BooleanValue *v1 = new BooleanValue(true);
  BooleanValue *v2 = new BooleanValue(true);
  XorExpression *xorExp = new XorExpression(v1, v2);
  BooleanValue *result = (BooleanValue *)xorExp->eval();
  
  EXPECT_EQ (false, result->value());
  
  delete v1;
  delete v2;
  delete xorExp;
  delete result;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
