#include "IVisitor.hpp"

namespace OberonLang {
  void Expression::acceptVisit(IVisitor* visitor) { }
  void Value::acceptVisit(IVisitor* visitor) { }
  // void GenericValue::acceptVisit(IVisitor* visitor) { }
  void IntValue::acceptVisit(IVisitor* visitor) { visitor->visit(this); }
  void RealValue::acceptVisit(IVisitor* visitor) { visitor->visit(this); }
  void BooleanValue::acceptVisit(IVisitor* visitor) { visitor->visit(this); }
  void Undefined::acceptVisit(IVisitor* visitor) { visitor->visit(this); }
  void VarDec::acceptVisit(IVisitor* visitor) { visitor->visit(this); }
  void VarRef::acceptVisit(IVisitor* visitor) { visitor->visit(this); }
  void Declaration::acceptVisit(IVisitor* visitor) { visitor->visit(this); }
  void Program::acceptVisit(IVisitor* visitor) { visitor->visit(this); }
  void Assignment::acceptVisit(IVisitor* visitor) { visitor->visit(this); }
  void ProcedureCall::acceptVisit(IVisitor* visitor) { visitor->visit(this); }
  void BlockCommand::acceptVisit(IVisitor* visitor) { visitor->visit(this); }
  void PrintCommand::acceptVisit(IVisitor* visitor) { visitor->visit(this); }
  void WhileCommand::acceptVisit(IVisitor* visitor) { visitor->visit(this); }
  void IfThenCommand::acceptVisit(IVisitor* visitor) { visitor->visit(this); }
  void IfThenElseCommand::acceptVisit(IVisitor* visitor) { visitor->visit(this); }
  void DecProcedure::acceptVisit(IVisitor* visitor) { visitor->visit(this); }
  void BinExpression::acceptVisit(IVisitor* visitor) { visitor->visit(this); }
}
