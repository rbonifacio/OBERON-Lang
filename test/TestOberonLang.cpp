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
