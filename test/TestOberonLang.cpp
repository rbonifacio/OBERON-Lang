#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "gtest/gtest.h"

#include "Expression.hpp"
#include "BinExpression.hpp"
#include "Environment.hpp"
#include "Command.hpp"
#include "Procedure.hpp"
#include "Declaration.hpp"
#include "Types.hpp"
#include "VarRef.hpp"

#include "TCVisitor.hpp"

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

TEST (AddExpression, SelfRef) {
  IntValue *v0 = new IntValue(0);
  IntValue *v1 = new IntValue(1);
  v0 = (IntValue *)(new AddExpression(v0,v1))->eval();
  v0 = (IntValue *)(new AddExpression(v0,v1))->eval();

  EXPECT_EQ (2, v0->value());
}

TEST (TestAssignment, SimpleAssignment) {
  Environment::instance()->env("x", new IntValue(0));
  IntValue *value = new IntValue(10);
  Assignment* assignment = new Assignment("x", value);

  assignment->run();

  EXPECT_NE(Undefined::instance(), Environment::instance()->env("x"));

  EXPECT_EQ (10, ((IntValue*)Environment::instance()->env("x"))->value());
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

TEST (WhileCommand, Print) {

  Environment::instance()->global("sum", new IntValue(0));
  Environment::instance()->global("inc", new IntValue(10));

  GTExpression *exp = new GTExpression(new VarRef("inc"), new IntValue(0));

  AddExpression *add = new AddExpression(new VarRef("sum"), new VarRef("inc"));
  Assignment *assignment1 = new Assignment("sum", add);

  SubExpression *sub = new SubExpression(new VarRef("inc"), new IntValue(1));
  Assignment *assignment2 = new Assignment("inc", sub);

  list <Command*> cmds = {assignment1, assignment2};
  BlockCommand *bc = new BlockCommand(cmds);

  WhileCommand *wc = new WhileCommand(exp, bc);
  wc -> run();

  EXPECT_EQ (55, ((IntValue*)Environment :: instance()->global("sum"))->value());


  //
  // var soma = 0;
  // var inc = 10;
  // while(inc>0){
  // soma = soma+inc;
  // inc = inc -1;
  //}

}
TEST (IfThenCommand, True) {

  Environment::instance()->global("n", new IntValue(13));
  LTExpression *exp = new LTExpression(new VarRef("n"), new IntValue(15));

  Environment::instance()->env("x", new IntValue(0));
  IntValue *value = new IntValue(10);
  Assignment* assignment = new Assignment("x", value);

  list <Command*> cmds = {assignment};
  BlockCommand *bc = new BlockCommand(cmds);
  IfThenCommand *ifthen = new IfThenCommand(exp,bc);
  ifthen -> run();

  EXPECT_EQ (10, ((IntValue*)Environment::instance()->env("x"))->value());
  // n = 13
  // if(n<15){
  //  x = 10;
  //}
}
TEST (IfThenElseCommand, IFTrue) {

  Environment::instance()->global("n", new IntValue(13));
  LTExpression *exp = new LTExpression(new VarRef("n"), new IntValue(15));

  Environment::instance()->env("x", new IntValue(0));

  IntValue *value01 = new IntValue(10);
  Assignment* assignment = new Assignment("x", value01);

  IntValue *value02 = new IntValue(5);
  Assignment* assignment2 = new Assignment("x", value02);

  list <Command*> cmdsIf = {assignment};
  list <Command*> cmdsElse = {assignment2};

  BlockCommand *bcIf = new BlockCommand(cmdsIf);
  BlockCommand *bcElse = new BlockCommand(cmdsElse);

  IfThenElseCommand *ifthenElse = new IfThenElseCommand(exp,bcIf,bcElse);
  ifthenElse -> run();

  EXPECT_EQ (10, ((IntValue*)Environment::instance()->env("x"))->value());
   //n = 13
  // if(n<15){
  //  x = 10;
  //}
  //else{
  //  x = 5
  //}
}
TEST (IfThenElseCommand, ElseTrue) {

  Environment::instance()->global("n", new IntValue(13));
  LTExpression *exp = new LTExpression(new VarRef("n"), new IntValue(9));

  Environment::instance()->env("x", new IntValue(0));
  IntValue *value01 = new IntValue(10);
  Assignment* assignment = new Assignment("x", value01);

  IntValue *value02 = new IntValue(5);
  Assignment* assignment2 = new Assignment("x", value02);

  list <Command*> cmdsIf = {assignment};
  list <Command*> cmdsElse = {assignment2};

  BlockCommand *bcIf = new BlockCommand(cmdsIf);
  BlockCommand *bcElse = new BlockCommand(cmdsElse);

  IfThenElseCommand *ifthenElse = new IfThenElseCommand(exp,bcIf,bcElse);
  ifthenElse -> run();

  EXPECT_EQ (5, ((IntValue*)Environment::instance()->env("x"))->value());
  //n = 13
  // if(n<9){
  //  x = 10;
  //}
  //else{
  //  x = 5
  //}
}

TEST (Procedure, Print){
  // --------- test the execution of a procedure ------ //
  // it simulates a program like:
  // -------------------------------------------------- //
  // var res = 0;
  //
  //
  // def soma(x, y) begin
  //   res = x + y;
  // end.
  //
  // begin
  //  soma(5, 3)
  // end.
  // ------------------------------------------------------------ //

  // ----------------- declare the res global var --------------- //

  Environment::instance()->global("res", 0);

  // ----------------- Procedure declaration -------------------- //

  vector<Declaration> args;
  vector<Declaration> vars;
  args.push_back(Declaration(integer, "x"));
  args.push_back(Declaration(integer, "y"));

  Command *body = new Assignment("res", new AddExpression(new VarRef("x"), new VarRef("y")));

  DecProcedure *sum = new DecProcedure("sum", args, vars, body);

  Environment::instance()->decProcedure(sum);

  // ----------------- Procedure call -----------------------------//

  vector<Expression*> pmts;
  pmts.push_back(new IntValue(5));
  pmts.push_back(new IntValue(3));

  ProcedureCall *call = new ProcedureCall("sum", pmts);

  call->run();

  EXPECT_NE(Undefined::instance(), Environment::instance()->global("res"));

  EXPECT_EQ (8, ((IntValue*)Environment::instance()->global("res"))->value());
}


TEST (TCAddExpression, IntAdd) {
  IntValue *v1 = new IntValue(10);
  IntValue *v2 = new IntValue(5);
  AddExpression *add = new AddExpression(v1, v2);

  EXPECT_EQ (integer, add->expType());
}

TEST (TCAddExpression, RealAdd) {
  RealValue *v1 = new RealValue(10);
  RealValue *v2 = new RealValue(5);
  AddRealExpression *add = new AddRealExpression(v1, v2);

  EXPECT_EQ (real, add->expType());
}


TEST (TCVisitor, IntAdd) {
  IntValue *v1 = new IntValue(10);
  IntValue *v2 = new IntValue(5);
  AddExpression *add = new AddExpression(v1, v2);

  TCVisitor* v = new TCVisitor();
  add->acceptVisit(v);
  
  EXPECT_EQ (true, v->validType());
}


TEST (TCVisitor, InvalidIntAdd) {
  IntValue *v1 = new IntValue(10);
  BooleanValue *v2 = new BooleanValue(true);
  AddExpression *add = new AddExpression(v1, v2);

  TCVisitor* v = new TCVisitor();
  add->acceptVisit(v);
  
  EXPECT_EQ (false, v->validType());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
