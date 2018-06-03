#ifndef BNFVISITOR_H
#define BNFVISITOR_H

#include <vector>
#include <list>
#include <iostream>
#include "Absyn.H"
#include "Expression.hpp"
#include "BinExpression.hpp"
#include "Types.hpp"
#include "Declaration.hpp"
#include "Procedure.hpp"
#include "VarRef.hpp"

namespace OberonLang {
  class BNFVisitor : public Visitor {
  public:
    BNFVisitor();
    BNFVisitor(const BNFVisitor& orig);
    
    
    void visitModuleDec(ModuleDec *p) { }
    void visitType(Type *p) { }
    void visitVarDec(VarDec *p) { }
    void visitFPmtDec(FPmtDec *p) { }
    void visitProcDec(ProcDec *p) { }
    void visitExp(Exp *p) { }
    void visitStmt(Stmt *p) { }
    void visitModule(Module *p) { cout << "Module não suportado\n"; } // !TODO
    void visitTInt(TInt *p);
    void visitTBool(TBool *p);
    void visitDecl(Decl *p);
    void visitFPDecl(FPDecl *p) { } // !TODO
    void visitPDec(PDec *p); // !TODO
    void visitELt(ELt *p);
    void visitEGt(EGt *p);
    void visitEEq(EEq *p);
    void visitENEq(ENEq *p);
    void visitEAdd(EAdd *p);
    void visitESub(ESub *p);
    void visitEMul(EMul *p);
    void visitEDiv(EDiv *p);
    void visitEOr(EOr *p);
    void visitEAnd(EAnd *p);
    void visitCall(Call *p);
    void visitEVar(EVar *p);
    void visitEStr(EStr *p) { cout << "StringExpression não suportado\n"; } // !TODO
    void visitEInt(EInt *p);
    void visitEFalse(EFalse *p);
    void visitETrue(ETrue *p);
    void visitEDouble(EDouble *p);
    void visitSCall(SCall *p);
    void visitSAssignment(SAssignment *p);
    void visitSWhile(SWhile *p); //!TODO
    void visitSIfThenElse(SIfThenElse *p) { } //!TODO
    void visitSIfThen(SIfThen *p) { } //!TODO
    void visitListExp(ListExp *p) { }
    void visitListStmt(ListStmt *p) { }
    void visitListIdent(ListIdent *p) { }
    void visitListVarDec(ListVarDec *p) { }
    void visitListFPmtDec(ListFPmtDec *p) { }
    void visitListProcDec(ListProcDec *p) { }
    void visitInteger(Integer x);
    void visitChar(Char x) { }
    void visitDouble(Double x);
    void visitString(String x) { cout << "String não suportado\n"; } // !TODO, não temos uma classe de valor para string
    void visitIdent(Ident x);
    
    virtual  ~BNFVisitor();
  private:
  	
  	// As visitors can't return, these variables will store the results of a visitor.
    Expression *visitorReturn;
    Command *visitorCommandReturn;
    TypesEnum visitorTypeReturn;
    vector<Declaration> *visitorDeclarationListReturn;
    
    // When an expression is parsed we don't know if there will be reals
    bool doubleFlag = 0; // Detects if a double occourred in an expression
  };
}
#endif /* BNFVISITOR_HPP */

