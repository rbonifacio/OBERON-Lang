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
    }
    
    void BNFVisitor::visitTInt(TInt *p) {
    	visitorTypeReturn = integer;
    }
    
    void BNFVisitor::visitTBool(TBool *p) {
    	visitorTypeReturn = boolean;
    }
    
    void BNFVisitor::visitDecl(Decl *p) {
    	p->type_->accept(this); // Returns in visitorTypeReturn
    	visitorDeclarationListReturn = new vector<Declaration>;
    	if(p->listident_){
    		for(
    			ListIdent::const_iterator element = p->listident_->begin(); 
    			element != p->listident_->end() ; 
    			++element
    			)
    		{
    			visitorDeclarationListReturn->push_back(Declaration(visitorTypeReturn, *element));
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
    __implementBNFVisitorBinExpression(EAdd, Add, AddReal);     // Implements visitEAdd
    __implementBNFVisitorBinExpression(ESub, Sub, SubReal);     // Implements visitESub
    __implementBNFVisitorBinExpression(EMul, Times, TimesReal); // Implements visitETimes
    __implementBNFVisitorBinExpression(EDiv, Div, DivReal);     // Implements visitEDiv
    
    // Those are only integers, we should have relational expressions for real but we don't
    __implementBNFVisitorBinExpression(EEq, EQ, EQ);     // Implements visitEEq
    __implementBNFVisitorBinExpression(ENEq, NE, NE);    // Implements visitENEq
    __implementBNFVisitorBinExpression(ELt, LT, LT);     // Implements visitELt
    __implementBNFVisitorBinExpression(EGt, GT, GT);     // Implements visitEGt
    
    /* Logic binary expressions */
    __implementBNFVisitorBinExpression(EAnd, And, And);  // Implements visitEAnd
    __implementBNFVisitorBinExpression(EOr, Or, Or);     // Implements visitEAnd
    
    void BNFVisitor::visitCall(Call *p) {
    	vector<Expression*> pmts;
    	if(p->listexp_){
		  	for(uint32_t i=0 ; i < p->listexp_->size() ; i++){
    			p->listexp_->at(i)->accept(this);
		  		pmts.push_back(visitorReturn);
		  	}
			}
			visitorCommandReturn = new ProcedureCall(p->ident_, pmts);
    }
    
    void BNFVisitor::visitEInt(EInt *p) {
    	BNFVisitor::visitInteger(p->integer_);
    }
    
    void BNFVisitor::visitEVar(EVar *p) {
    	visitorReturn = new VarRef(p->ident_);
    }
    
    void BNFVisitor::visitEDouble(EDouble *p) {
    	BNFVisitor::visitDouble(p->double_);
    }
    
    void BNFVisitor::visitSCall(SCall *p) {
    	vector<Expression*> pmts;
    	if(p->listexp_){
		  	for(uint32_t i=0 ; i < p->listexp_->size() ; i++){
    			p->listexp_->at(i)->accept(this);
		  		pmts.push_back(visitorReturn);
		  	}
			}
			visitorCommandReturn = new ProcedureCall(p->ident_, pmts);
    }
    
    void BNFVisitor::visitSAssignment(SAssignment *p) { 
    	p->exp_->accept(this);
    	visitorCommandReturn = new Assignment(p->ident_, visitorReturn);
    }
    
    void BNFVisitor::visitSWhile(SWhile *p) { // Should be [Stmt] not Stmt in BNF
    	//new WhileCommand(conditionalExpression, blockOfCommands);
    }
    
    void BNFVisitor::visitPDec(PDec *p) {
    	vector<Declaration> args;
    	vector<Declaration> vars;
    	Command *body;
    	
//    	if(p->liststmt_){
//		  	for(uint32_t i=0 ; i < p->liststmt_->size() ; i++){
//    			p->liststmt_->at(i)->accept(this);
//		  		pmts.push_back(visitorReturn);
//		  	}
//			}
//    	
//			new DecProcedure(p->ident_, args, vars, body);
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
    
    void BNFVisitor::visitIdent(Ident x) {
    	
    }
}

