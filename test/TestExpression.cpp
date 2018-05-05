#include "gtest/gtest.h"

#include "Expression.hpp"
#include "BinExpression.hpp"

using namespace OberonLang; 

TEST (AddExpression, PositiveValues) {
  IntValue* v1 = new IntValue(10);
  IntValue* v2 = new IntValue(5);
  //AddExpression* add = new AddExpression(v1, v2);
  
  
  EXPECT_EQ (10, v1->value());
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
