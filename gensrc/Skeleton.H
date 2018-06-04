#ifndef SKELETON_HEADER
#define SKELETON_HEADER
/* You might want to change the above name. */

#include "Absyn.H"


class Skeleton : public Visitor
{
public:
  void visitModuleDec(ModuleDec* p);
  void visitType(Type* p);
  void visitVarDec(VarDec* p);
  void visitFPmtDec(FPmtDec* p);
  void visitProcDec(ProcDec* p);
  void visitExp(Exp* p);
  void visitStmt(Stmt* p);
  void visitModule(Module* p);
  void visitTInt(TInt* p);
  void visitTBool(TBool* p);
  void visitDecl(Decl* p);
  void visitFPDecl(FPDecl* p);
  void visitPDec(PDec* p);
  void visitELt(ELt* p);
  void visitEGt(EGt* p);
  void visitEEq(EEq* p);
  void visitENEq(ENEq* p);
  void visitEAdd(EAdd* p);
  void visitESub(ESub* p);
  void visitEMul(EMul* p);
  void visitEDiv(EDiv* p);
  void visitEOr(EOr* p);
  void visitEAnd(EAnd* p);
  void visitCall(Call* p);
  void visitEVar(EVar* p);
  void visitEStr(EStr* p);
  void visitEInt(EInt* p);
  void visitEFalse(EFalse* p);
  void visitETrue(ETrue* p);
  void visitEDouble(EDouble* p);
  void visitSCall(SCall* p);
  void visitSAssignment(SAssignment* p);
  void visitSWhile(SWhile* p);
  void visitSIfThenElse(SIfThenElse* p);
  void visitSIfThen(SIfThen* p);
  void visitListExp(ListExp* p);
  void visitListStmt(ListStmt* p);
  void visitListIdent(ListIdent* p);
  void visitListVarDec(ListVarDec* p);
  void visitListFPmtDec(ListFPmtDec* p);
  void visitListProcDec(ListProcDec* p);

  void visit"Integer"("Integer" x);
  void visit"Char"("Char" x);
  void visit"Double"("Double" x);
  void visit"String"("String" x);
  void visit"Ident"("Ident" x);

};


#endif
