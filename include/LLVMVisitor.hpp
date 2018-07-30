#ifndef LLVMVISITOR_H
#define LLVMVISITOR_H

#include "IVisitor.hpp"

#include "llvm/IR/GlobalVariable.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APInt.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
// #include <algorithm>
// #include <cctype>
// #include <cstdio>
// #include <cstdlib>
#include <map>
// #include <memory>
#include <string>
#include <vector>
#include <stack>

namespace OberonLang {

  static llvm::LLVMContext TheContext;
  static llvm::IRBuilder<> Builder(TheContext);
  static std::unique_ptr<llvm::Module> TheModule;

  class Scope {
  public:
    llvm::BasicBlock* getBlock() { return block; }
    void setBlock(llvm::BasicBlock* brick) { block = brick;  }
    std::map<std::string, llvm::Value*>* getVariables() { return &variables; }
    Scope() { variables = std::map<std::string, llvm::Value*>(); }
  private:        
    llvm::BasicBlock* block;
    std::map<std::string, llvm::Value*> variables;
  };

  class LLVMVisitor : public IVisitor {
  public:
    void visit(Program* p) {
      std::vector<llvm::Type*> argumentsTypes;      
      llvm::FunctionType *ftype = llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), llvm::makeArrayRef(argumentsTypes), false);
      mainFunction = llvm::Function::Create(ftype, llvm::Function::ExternalLinkage, "main", &*TheModule);
      llvm::BasicBlock* mainBlock = llvm::BasicBlock::Create(TheContext, "entry", mainFunction);
      
      Scope* mainScope = new Scope();
      pushScope(mainScope);
      currentScope()->setBlock(mainBlock);

      std::vector<VarDec*>* globalVars = p->getGlobalVars();
      std::vector<DecProcedure*>* procedures = p->getProcedures();
      Command* commands = p->getCommands();

      std::vector<VarDec*>::iterator itGlobalVars = globalVars->begin(); 
      for (; itGlobalVars != globalVars->end(); ++itGlobalVars) {
        llvm::GlobalValue* globalVar = new llvm::GlobalVariable(typeOf((*itGlobalVars)->type()), false, llvm::GlobalVariable::CommonLinkage, initializerConst((*itGlobalVars)->type()), (*itGlobalVars)->name());
        if (!globalVar) {
          LogErrorV("Can not create the variable.");      
        }
        globalVariables[(*itGlobalVars)->name()] = globalVar;
        accumulator.push_back(globalVar);
      }

      // Iterator for procedures declaration;
      std::vector<DecProcedure*>::iterator itProcedures = procedures->begin(); 
      for (; itProcedures != procedures->end(); ++itProcedures) {
        this->visit(*itProcedures);
      }
      
      // Iterator for commands;
      // this->visit(commands);

      llvm::ReturnInst::Create(TheContext, mainBlock);
      accumulator.push_back(mainFunction);
      // llvm::legacy::PassManager pm;
      // pm.add(llvm::createPrintModulePass());

    }
//  void visit(TypesEnum* p) { } // This visit can be unnecessary
    void visit(Command* p) {
      p->acceptVisit(this);
    }
    void visit(IntValue* p) {
      accumulator.push_back(llvm::ConstantInt::get(TheContext, llvm::APInt(32, p->value(), true)));  
    }
    void visit(RealValue* p) { }
    void visit(BooleanValue* p) { }
    void visit(StringValue* p) { }
    void visit(Undefined* p) { }

    void visit(Assignment* p) {
      llvm::StoreInst* assign; 
      llvm::LoadInst* varRef;
      if (currentScope()->getVariables()->find(p->name()) != currentScope()->getVariables()->end()) {
        VarRef* ref = new VarRef(p->name());      
        this->visit(ref);
        varRef = (llvm::LoadInst*) accumulator.back();  
        assign = new llvm::StoreInst(varRef, (*currentScope()->getVariables())[p->name()], false, currentScope()->getBlock());
      } else if (globalVariables.find(p->name()) != globalVariables.end()) {
        this->visit(new VarRef(p->name()));
        varRef = (llvm::LoadInst*) accumulator.back();  
        assign = new llvm::StoreInst(varRef, globalVariables[p->name()], false, currentScope()->getBlock());
      } else {
        LogErrorV("Undeclared variable");
      }
      accumulator.push_back(assign);  
    }
    void visit(ProcedureCall* p) { }
    void visit(BlockCommand* p) {
      llvm::Value* standart = NULL;    
      std::list<Command*>::iterator itCommands = p->getCommands()->begin();
      for (; itCommands != p->getCommands()->end(); ++itCommands) {
        // Make the visitor for all commands before uncomment this line      
        // this->visit(*itCommands);
      }
      accumulator.push_back(standart);
    }
    void visit(PrintCommand* p) { }

    void visit(WhileCommand* p) { }
    void visit(IfThenCommand* p) { }
    void visit(IfThenElseCommand* p) { }

    void visit(Declaration* p) {
        llvm::AllocaInst* var = new llvm::AllocaInst(typeOf(p->type()), 0, NULL, p->name(), currentScope()->getBlock());  
        if (!var) {
          LogErrorV("Can not create the variable.");      
        }
        (*currentScope()->getVariables())[p->name()] = var;
        accumulator.push_back(var);  
    }
    
    void visit(DecProcedure* p) {
      std::vector<llvm::Type*> argumentsTypes;      
      std::vector<Declaration*>::iterator itArguments = p->formalArgsPointer()->begin();
      for (; itArguments != p->formalArgsPointer()->end(); ++itArguments) {
        argumentsTypes.push_back(typeOf((*itArguments)->type()));  
      }
      llvm::FunctionType *procedureType = llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), llvm::makeArrayRef(argumentsTypes), false);
      llvm::Function* procedure = llvm::Function::Create(procedureType, llvm::GlobalValue::ExternalLinkage, p->name(), &*TheModule);
      llvm::BasicBlock* procedureBlock = llvm::BasicBlock::Create(TheContext, "entry", procedure, 0);

      Scope* procedureScope = new Scope();
      pushScope(procedureScope);
      currentScope()->setBlock(procedureBlock);

      llvm::Function::arg_iterator argumentsValues = procedure->arg_begin();
      llvm::Value* argValue;
      itArguments = p->formalArgsPointer()->begin();
      for (auto &Arg: procedure->args()) {
        Arg.setName((*itArguments)->name());
        (*currentScope()->getVariables())[(*itArguments)->name()] = &Arg;
        itArguments++;
      }
      
      // visit commands
      // this->visit(p->body());

      llvm::ReturnInst::Create(TheContext, procedureBlock);
      accumulator.push_back(procedure);
      dropScope();
    }

    void visit(VarRef* p) {
      llvm::LoadInst* valueRef;       
      if (currentScope()->getVariables()->find(p->name()) != currentScope()->getVariables()->end()) {
        valueRef = new llvm::LoadInst((*currentScope()->getVariables())[p->name()], "", false, currentScope()->getBlock());      
      }  else if (globalVariables.find(p->name()) != globalVariables.end()) {
        valueRef = new llvm::LoadInst((*currentScope()->getVariables())[p->name()], "", false, currentScope()->getBlock());      
      } else {
        LogErrorV("Undeclared variable");    
      }
      accumulator.push_back(valueRef);
    }

    void visit(VarDec* p) { }

		void visit(AddRealExpression *p) {}
		void visit(SubRealExpression *p) {}
		void visit(TimesRealExpression *p) {}
		void visit(DivRealExpression *p) {}
    void visit(BinExpression* p) { }
    void visit(AddExpression* p) { }
    void visit(TimesExpression* p) { }
    void visit(SubExpression* p) { }
    void visit(DivExpression* p) { }
    void visit(RemExpression* p) { }
    void visit(AndExpression* p) { }
    void visit(OrExpression* p) { }
    void visit(LTExpression* p) { }
    void visit(LEExpression* p) { }
    void visit(GTExpression* p) { }
    void visit(GEExpression* p) { }
    void visit(EQExpression* p) { }
    void visit(NEExpression* p) { }
    LLVMVisitor(Program* p) { 
      accumulator = std::vector<llvm::Value*>();
      scopes = std::stack<Scope*>();
      globalVariables = std::map<std::string, llvm::Value*>();
      program = p;
      TheModule = llvm::make_unique<llvm::Module>("main", TheContext);
    }
    void codegen() {
      this->visit(program);
      std::vector<llvm::Value*>::iterator itValues = accumulator.begin();
      for (; itValues != accumulator.end(); ++itValues) {
        (*itValues)->print(llvm::errs());      
      }
    }
  private:
    std::vector<llvm::Value*> accumulator; 
    std::stack<Scope*> scopes;
    llvm::Function* mainFunction;
    std::map<std::string, llvm::Value*> globalVariables;
    Program* program;

    Scope* currentScope() { return scopes.top(); }
    void dropScope() { scopes.pop(); }  
    void pushScope(Scope* scope) { scopes.push(scope); }

    static llvm::Type* typeOf(TypesEnum tp) {
      if (tp == TypesEnum::integer) {
        return llvm::Type::getInt32Ty(TheContext);      
      } else if (tp == TypesEnum::real) {
        return llvm::Type::getDoubleTy(TheContext);      
      }  else {
        return llvm::Type::getInt1Ty(TheContext);      
      }    
    }

    static llvm::Constant* initializerConst(TypesEnum tp) {
      if (tp == TypesEnum::integer) {
        return llvm::ConstantInt::get(typeOf(tp), (uint64_t) 0, true);      
      } else if (tp == TypesEnum::real) {
        return llvm::ConstantFP::get(typeOf(tp), (double) 0.0);      
      }  else {
        return llvm::ConstantInt::get(typeOf(tp), (uint64_t) 0, true);      
      }    
    }
    
    llvm::Value* LogErrorV(const char *Str) {
      std::cout << "Error: " << Str << std::endl;
      return nullptr;
    }
  };
}

#endif 
