#ifndef LLVMVISITOR_H
#define LLVMVISITOR_H

// #include "Expression.hpp"
// #include "BinExpression.hpp"
// #include "Command.hpp"
// #include "Declaration.hpp"
// #include "Procedure.hpp"
// #include "VarDec.hpp"
// #include "VarRef.hpp"
// #include "Types.hpp"
// #include "Program.hpp"

#include "Visitor.hpp"
#include "BNFVisitor.hpp"  

#include <map>
#include <stack>  
#include <vector>

#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/DerivedTypes.h>  
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Constants.h>

namespace OberonLang {
  class Scope {
  public:
    llvm::BasicBlock* getBlock() { return block; }
    std::map<std::string, llvm::Value*>* getVariables() { return &variables; }
  private:        
    llvm::BasicBlock* block;
    std::map<std::string, llvm::Value*> variables;
  };

  class LLVMVisitor : public IVisitor {
  public:
    void visit(Program* p) { }
//  void visit(TypesEnum* p) { } // This visit can be unnecessary
    void visit(IntValue* p) {
      accumulator.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), p->value(), true);  
    }
    void visit(RealValue* p) { }
    void visit(BooleanValue* p) { }
    void visit(Undefined* p) { }
    void visit(Assignment* p) { }
    void visit(ProcedureCall* p) { }
    void visit(BlockCommand* p) { }
    void visit(PrintCommand* p) { }
    void visit(WhileCommand* p) { }
    void visit(IfThenCommand* p) { }
    void visit(IfThenElseCommand* p) { }
    void visit(Declaration* p) { }
    void visit(DecProcedure* p) { }
    void visit(VarRef* p) { }
    void visit(VarDec* p) { }
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
  private:
    std::vector<llvm::Value*> accumulator; 
    static llvm::LLVMContext TheContext;
    std::stack<Scope*> scopes;
    llvm::Function* mainFunction;
    llvm::Module* module;
    std::map<std::string, llvm::Value*> globalVariables;

    static llvm::Type* typeOf(TypesEnum tp) {
      if (tp == TypesEnum::integer) {
        return llvm::Type::getInt32Ty(TheContext);      
      } else if (tp == TypesEnum::real) {
        return llvm::Type::getDoubleTy(TheContext);      
      }  else {
        return llvm::Type::getInt1Ty(TheContext);      
      }    
    } 
  };
}

#endif 
