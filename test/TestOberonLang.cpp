#include <iostream>
#include <vector>
#include <string>
#include "gtest/gtest.h"

#include "Expression.hpp"
#include "BinExpression.hpp"
#include "Environment.hpp"
#include "Command.hpp"
#include "Procedure.hpp"
#include "Declaration.hpp"
#include "Types.hpp"

using namespace std;
using namespace OberonLang; 

TEST (AddExpression, IntAdd) {
  IntValue *v1 = new IntValue(10);
  IntValue *v2 = new IntValue(5);
  AddExpression *add = new AddExpression(v1, v2);
  IntValue* result = (IntValue *)(add->eval());
  
  EXPECT_EQ (15, result->value());
}

TEST (AddExpression, RealAdd) {
  RealValue *v1 = new RealValue(10.4);
  RealValue *v2 = new RealValue(9.1);
  AddRealExpression *add = new AddRealExpression(v1, v2);
  RealValue *result = (RealValue *)(add->eval());
  
  EXPECT_EQ (19.5, result->value());
}


TEST (TestAssignment, SimpleAssignment) {
  IntValue *value = new IntValue(10);
  Assignment* assignment = new Assignment("x", value);
  assignment->run();
  
  EXPECT_EQ (10, ((IntValue*)Environment::instance()->lookup("x")->eval())->value());
}

TEST (SubExpression, SimpleSub) {
  IntValue *v1 = new IntValue(100);
  IntValue *v2 = new IntValue(200);
  SubExpression* sub = new SubExpression(v1, v2);
  IntValue *result = (IntValue *)sub->eval();
  
  EXPECT_EQ (-100, result->value());
}

TEST (SubExpression, RealSub) {
  RealValue *v1 = new RealValue(10.4);
  RealValue *v2 = new RealValue(9.1);
  SubRealExpression *sub = new SubRealExpression(v1, v2);
  RealValue *result = (RealValue *)(sub->eval());
  
  EXPECT_DOUBLE_EQ (1.3, result->value());
}

TEST (TimesExpression, IntTimes) {
  IntValue *v1 = new IntValue(98);
  IntValue *v2 = new IntValue(-172);
  TimesExpression* Times = new TimesExpression(v1, v2);
  IntValue *result = (IntValue *)Times->eval();
  
  EXPECT_EQ (-16856, result->value());
}

TEST (TimesExpression, RealTimes) {
  RealValue *v1 = new RealValue(0.34);
  RealValue *v2 = new RealValue(1.2);
  TimesRealExpression *times = new TimesRealExpression(v1, v2);
  RealValue *result = (RealValue *)(times->eval());
  
  EXPECT_DOUBLE_EQ (0.408, result->value());
}

TEST (DivExpression, SimpleDiv) {
  IntValue *v1 = new IntValue(87);
  IntValue *v2 = new IntValue(9);
  DivExpression* div = new DivExpression(v1, v2);
  IntValue *result = (IntValue *)div->eval();
  
  EXPECT_EQ (9, result->value());
}

TEST (DivExpression, RealDiv) {
  RealValue *v1 = new RealValue(123);
  RealValue *v2 = new RealValue(5);
  DivRealExpression *div = new DivRealExpression(v1, v2);
  RealValue *result = (RealValue *)(div->eval());
  
  EXPECT_DOUBLE_EQ (24.6, result->value());
}

TEST (RemExpression, SimpleRem) {
  IntValue *v1 = new IntValue(99);
  IntValue *v2 = new IntValue(23);
  RemExpression* rem = new RemExpression(v1, v2);
  IntValue *result = (IntValue *)rem->eval();
  
  EXPECT_EQ (7, result->value());
}

TEST (AndExpression, TrueTrue) {
  BooleanValue *v1 = new BooleanValue(true);
  BooleanValue *v2 = new BooleanValue(true);
  AndExpression *andExp = new AndExpression(v1, v2);
  BooleanValue *result = (BooleanValue *)andExp->eval();
  
  EXPECT_EQ (true, result->value());
}

TEST (AndExpression, TrueFalse) {
  BooleanValue *v1 = new BooleanValue(true);
  BooleanValue *v2 = new BooleanValue(false);
  AndExpression *andExp = new AndExpression(v1, v2);
  BooleanValue *result = (BooleanValue *)andExp->eval();
  
  EXPECT_EQ (false, result->value());
}

TEST (OrExpression, TrueTrue) {
  BooleanValue *v1 = new BooleanValue(true);
  BooleanValue *v2 = new BooleanValue(true);
  OrExpression *orExp = new OrExpression(v1, v2);
  BooleanValue *result = (BooleanValue *)orExp->eval();
  
  EXPECT_EQ (true, result->value());
}

TEST (OrExpression, TrueFalse) {
  BooleanValue *v1 = new BooleanValue(true);
  BooleanValue *v2 = new BooleanValue(false);
  OrExpression *orExp = new OrExpression(v1, v2);
  BooleanValue *result = (BooleanValue *)orExp->eval();
  
  EXPECT_EQ (true, result->value());
}

TEST (EQExpression, Equal) {
  IntValue *v1 = new IntValue(12);
  IntValue *v2 = new IntValue(12);
  EQExpression *exp = new EQExpression(v1, v2);
  BooleanValue *result = (BooleanValue *)exp->eval();
  
  EXPECT_EQ (true, result->value());
}

TEST (EQExpression, NotEqual) {
  IntValue *v1 = new IntValue(12);
  IntValue *v2 = new IntValue(13);
  EQExpression *exp = new EQExpression(v1, v2);
  BooleanValue *result = (BooleanValue *)exp->eval();
  
  EXPECT_EQ (false, result->value());
}

TEST (LTExpression, LessThan) {
  IntValue *v1 = new IntValue(12);
  IntValue *v2 = new IntValue(13);
  LTExpression *exp = new LTExpression(v1, v2);
  BooleanValue *result = (BooleanValue *)exp->eval();
  
  EXPECT_EQ (true, result->value());
}

TEST (LTExpression, Equal) {
  IntValue *v1 = new IntValue(12);
  IntValue *v2 = new IntValue(12);
  LTExpression *exp = new LTExpression(v1, v2);
  BooleanValue *result = (BooleanValue *)exp->eval();
  
  EXPECT_EQ (false, result->value());
}

TEST (LTExpression, Greater) {
  IntValue *v1 = new IntValue(13);
  IntValue *v2 = new IntValue(12);
  LTExpression *exp = new LTExpression(v1, v2);
  BooleanValue *result = (BooleanValue *)exp->eval();
  
  EXPECT_EQ (false, result->value());
}

TEST (Procedure, Print){
    string n = "Print";
    vector<Declaration> args;
    args.push_back(Declaration(integer , "x"));
    
    vector<Declaration> vars;
    IntValue *v = new IntValue(5);
    Command *body = new PrintCommand(v);
    DecProcedure *print = new DecProcedure(n,args,vars,body);
    vector<Expression*> pmts;
    pmts.push_back(new IntValue(10));
    ProcedureCall *call = new ProcedureCall(n,pmts);
    Environment::instance()->decProcedure(print);
    EXPECT_EQ (false, Environment::instance()->noVars());
    
    call->run();
    
    EXPECT_EQ (false, Environment::instance()->noVars());

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
