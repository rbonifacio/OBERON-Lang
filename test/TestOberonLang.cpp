#include <iostream> 
#include "gtest/gtest.h"

#include "Expression.hpp"
#include "BinExpression.hpp"
#include "Environment.hpp"
#include "Command.hpp"

using namespace OberonLang; 

TEST (TestAddExpression, SimpleAdd) {
  IntValue* v1 = new IntValue(10);
  IntValue* v2 = new IntValue(5);
  AddExpression* add = new AddExpression(v1, v2);
  
  EXPECT_EQ (15, ((IntValue*)add->eval())->value());
}

TEST (TestAssignment, SimpleAssignment) {
  Assignment* assignment = new Assignment("x", new IntValue(10));
  assignment->run();
  
  EXPECT_EQ (10, ((IntValue*)Environment::instance()->lookup("x")->eval())->value());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
