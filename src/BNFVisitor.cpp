/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BNFVisitor.cpp
 * Author: rbonifacio
 * 
 * Created on June 2, 2018, 11:38 AM
 */

#include "BNFVisitor.hpp"

namespace OberonLang {
    BNFVisitor::BNFVisitor() {
    }

    BNFVisitor::BNFVisitor(const BNFVisitor& orig) {
    }

    BNFVisitor::~BNFVisitor() {
    	delete programReturn; 
    }
    
    void BNFVisitor::runProgram(ModuleDec *p){
      p->accept(this);
      if(programReturn){
        programReturn->run();
      }
    }
    
    void BNFVisitor::visitModule(Module *p) {
      vector<VarDec*> globalVars;
      vector<DecProcedure*> procedures;
      BlockCommand *main;
      
      /* Iterate to build globalVars */
      if(p->listvardecl_){
        for(auto it = p->listvardecl_->begin(); it != p->listvardecl_->end(); ++it){
          (*it)->accept(this);
          if(visitorDeclarationListReturn){
            for(auto dec = visitorDeclarationListReturn->begin(); dec != visitorDeclarationListReturn->end(); ++dec){
              globalVars.push_back(new VarDec(dec->name(), dec->type()));
            }
          }
          delete visitorDeclarationListReturn;
        }
      }
      
      /* Iterate to build procedures */
      if(p->listprocdec_){
        for(auto it = p->listprocdec_->begin(); it != p->listprocdec_->end(); ++it){
          (*it)->accept(this);
          procedures.push_back(decProcedureReturn);
        }
      }
      
      /* Iterate to build BlockCommand */
      p->liststmt_->accept(this);
      main = visitorBlkCmd;
      
      programReturn = new Program(globalVars, procedures, main);
    }
    
    void BNFVisitor::visitTInt(TInt *p) {
      visitorTypeReturn = integer;
    }
    
    void BNFVisitor::visitTBool(TBool *p) {
      visitorTypeReturn = boolean;
    }
    
    void BNFVisitor::visitTReal(TReal *p) {
      visitorTypeReturn = real;
    }
    
    void BNFVisitor::visitDecl(Decl *p) {
      p->type_->accept(this); // Returns in visitorTypeReturn
      visitorDeclarationListReturn = new vector<Declaration>;
      if(p->listident_){
        for(auto it = p->listident_->begin(); it != p->listident_->end(); ++it) {
          visitorDeclarationListReturn->push_back(Declaration(visitorTypeReturn, *it));
        }
      }
    }
    
    void BNFVisitor::visitFPDecl(FPDecl *p) {
      p->type_->accept(this); // Returns in visitorTypeReturn
      visitorDeclarationListReturn = new vector<Declaration>;
      if(p->listident_){
        for(auto it = p->listident_->begin(); it != p->listident_->end(); ++it) {
          visitorDeclarationListReturn->push_back(Declaration(visitorTypeReturn, *it));
        }
      }
    }
    
    #define __implementBNFVisitorBinExpression(BNFClassName, ASTInfix, ASTRealInfix)\
    void BNFVisitor::visit##BNFClassName(BNFClassName *p) { \
      Expression *lhs, *rhs;\
      doubleFlag = false;\
      p->exp_1->accept(this);\
      lhs = visitorReturn;\
      p->exp_2->accept(this);\
      rhs = visitorReturn;\
      if(doubleFlag) visitorReturn = new ASTRealInfix##Expression(lhs, rhs);\
      else visitorReturn = new ASTInfix##Expression(lhs, rhs);\
    }
    
    
    // Those can have real or integers
    __implementBNFVisitorBinExpression(EAdd, Add, AddReal)     // Implements visitEAdd
    __implementBNFVisitorBinExpression(ESub, Sub, SubReal)     // Implements visitESub
    __implementBNFVisitorBinExpression(EMul, Times, TimesReal) // Implements visitETimes
    __implementBNFVisitorBinExpression(EDiv, Div, DivReal)     // Implements visitEDiv
    
    // Those are only integers, we should have relational expressions for real but we don't
    __implementBNFVisitorBinExpression(EEq, EQ, EQ)     // Implements visitEEq
    __implementBNFVisitorBinExpression(ENEq, NE, NE)    // Implements visitENEq
    __implementBNFVisitorBinExpression(ELt, LT, LT)     // Implements visitELt
    __implementBNFVisitorBinExpression(EGt, GT, GT)     // Implements visitEGt
    
    /* Logic binary expressions */
    __implementBNFVisitorBinExpression(EAnd, And, And)  // Implements visitEAnd
    __implementBNFVisitorBinExpression(EOr, Or, Or)     // Implements visitEAnd
    
//    void BNFVisitor::visitCall(Call *p) {
//      vector<Expression*> pmts;
//      if(p->listexp_){
//        for(auto it = p->listexp_->begin(); it != p->listexp_->end(); ++it) {
//          (*it)->accept(this);
//          pmts.push_back(visitorReturn);
//        }
//      }
//      visitorCommandReturn = new ProcedureCall(p->ident_, pmts);
//    }
    
    void BNFVisitor::visitEInt(EInt *p) {
      BNFVisitor::visitInteger(p->integer_);
    }
    
    void BNFVisitor::visitEStr(EStr *p) { 
      BNFVisitor::visitString(p->string_);
    }
    
    void BNFVisitor::visitEVar(EVar *p) {
      visitorReturn = new VarRef(p->ident_);
    }
    
    void BNFVisitor::visitEReal(EReal *p) {
      BNFVisitor::visitDouble(p->double_);
    }
    
    void BNFVisitor::visitSPrint(SPrint *p) {
      p->exp_->accept(this);
      visitorCommandReturn = new PrintCommand(visitorReturn);
    }
    
    void BNFVisitor::visitSCall(SCall *p) {
      vector<Expression*> *pmts = new vector<Expression*>;
      if(p->listexp_){
        for(auto it = p->listexp_->begin(); it != p->listexp_->end(); ++it) {
          (*it)->accept(this);
          pmts->push_back(visitorReturn);
        }
      }
      visitorCommandReturn = new ProcedureCall(p->ident_, pmts);
    }
    
    void BNFVisitor::visitSAssignment(SAssignment *p) { 
      p->exp_->accept(this);
      visitorCommandReturn = new Assignment(p->ident_, visitorReturn);
    }
    
    void BNFVisitor::visitSWhile(SWhile *p) {
    	Expression *condition;
    	BlockCommand *whileBlock;
    	
    	p->liststmt_->accept(this);
    	whileBlock = visitorBlkCmd;
    	
      p->exp_->accept(this);
      condition = visitorReturn;
      
      visitorCommandReturn = new WhileCommand(condition, whileBlock);
    }
    
    void BNFVisitor::visitSIfThen(SIfThen *p) {
    	BlockCommand *blkThen;
    	Expression *condition;
    	
    	p->exp_->accept(this);
    	condition = visitorReturn;
    	
    	p->liststmt_->accept(this);
    	blkThen = visitorBlkCmd;
    	
    	visitorCommandReturn = new IfThenCommand(condition, blkThen);
    }
    
    void BNFVisitor::visitSIfThenElse(SIfThenElse *p) {
    	BlockCommand *blkThen, *blkElse;
    	Expression *condition;
    	
    	p->exp_->accept(this);
    	condition = visitorReturn;
    	
    	p->liststmt_1->accept(this);
    	blkThen = visitorBlkCmd;
    	
    	p->liststmt_2->accept(this);
    	blkElse = visitorBlkCmd;
    	
    	visitorCommandReturn = new IfThenElseCommand(condition, blkThen, blkElse);
    }
    
    void BNFVisitor::visitListStmt(ListStmt *p){
      list<Command *> *commands = new list<Command *>;
      if(p){
        for(auto it = p->begin(); it != p->end(); ++it) {
          (*it)->accept(this);
          commands->push_back(visitorCommandReturn);
        }
      }
      visitorBlkCmd = new BlockCommand(commands);
    }
    
    void BNFVisitor::visitPDec(PDec *p) {
      vector<Declaration*> *args = new vector<Declaration*>;
      vector<Declaration*> *vars = new vector<Declaration*>;
      BlockCommand *body;
      
      p->liststmt_->accept(this);
      body = visitorBlkCmd;
      
      if(p->listvardecl_){
        for(auto it = p->listvardecl_->begin(); it != p->listvardecl_->end(); ++it){
          (*it)->accept(this);
          if(visitorDeclarationListReturn){
            for(auto dec = visitorDeclarationListReturn->begin(); dec != visitorDeclarationListReturn->end(); ++dec){
              vars->push_back(new Declaration(dec->type(), dec->name()));
            }
          }
          delete visitorDeclarationListReturn;
        }
      }
      
      if(p->listfpmtdec_){
        for(auto it = p->listfpmtdec_->begin(); it != p->listfpmtdec_->end(); ++it){
          (*it)->accept(this);
          if(visitorDeclarationListReturn){
            for(auto dec = visitorDeclarationListReturn->begin(); dec != visitorDeclarationListReturn->end(); ++dec){
              args->push_back(new Declaration(dec->type(), dec->name()));
            }
          }
          delete visitorDeclarationListReturn;
        }
      }
              
      decProcedureReturn = new DecProcedure(p->ident_, args, vars, body);
    }
    
    void BNFVisitor::visitEFalse(EFalse *p) { 
      visitorReturn = new BooleanValue(false);
    }
    
    void BNFVisitor::visitETrue(ETrue *p) { 
      visitorReturn = new BooleanValue(true);
    }
    
    void BNFVisitor::visitInteger(Integer x) { 
      visitorReturn = new IntValue(x);
    }
    
    void BNFVisitor::visitDouble(Double x) { 
      visitorReturn = new RealValue(x);
    }
    
    void BNFVisitor::visitString(String x){
    	visitorReturn = new StringValue(x);
    }
    
    void BNFVisitor::visitIdent(Ident x) {
      
    }
}

