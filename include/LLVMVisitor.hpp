#ifndef LLVMVISITOR_H
#define LLVMVISITOR_H

#include "IVisitor.hpp"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/DerivedTypes.h"

#include <map>
#include <string>
#include <vector>
#include <stack>

namespace OberonLang {

  static llvm::LLVMContext TheContext;
  static llvm::IRBuilder<> Builder(TheContext);
  static llvm::Module* TheModule;

  class LLVMVisitor : public IVisitor {
  public:
    void visit(Expression *p) {
      p->acceptVisit(this);
    }
    void visit(AddRealExpression *p) {
      p->getLhs()->acceptVisit(this);
      llvm::Value* lhs = accumulator->back();
      p->getRhs()->acceptVisit(this);
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        accumulator->push_back(Builder.CreateFAdd(lhs, rhs, "addrealtmp"));
      } else {
        accumulator->push_back(LogErrorV("invalid binary operator"));
      }
    }

    void visit(SubRealExpression *p) {
      p->getLhs()->acceptVisit(this);
      llvm::Value* lhs = accumulator->back();
      p->getRhs()->acceptVisit(this);
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        accumulator->push_back(Builder.CreateFSub(lhs, rhs, "subrealtmp"));
      } else {
        accumulator->push_back(LogErrorV("invalid binary operator"));
      }
    }

    void visit(TimesRealExpression *p) {
      p->getLhs()->acceptVisit(this);
      llvm::Value* lhs = accumulator->back();
      p->getRhs()->acceptVisit(this);
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        accumulator->push_back(Builder.CreateFMul(lhs, rhs, "mulrealtmp"));
      } else {
        accumulator->push_back(LogErrorV("invalid binary operator"));
      }
    }

    void visit(DivRealExpression *p) {
      p->getLhs()->acceptVisit(this);
      llvm::Value* lhs = accumulator->back();
      p->getRhs()->acceptVisit(this);
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        accumulator->push_back(Builder.CreateFDiv(lhs, rhs, "divrealtmp"));
      } else {
        accumulator->push_back(LogErrorV("invalid binary operator"));
      }
    }

    void visit(BinExpression* p) {
      p->acceptVisit(this);
    }

    void visit(AddExpression* p) {
      p->getLhs()->acceptVisit(this);
      llvm::Value* lhs = accumulator->back();
      p->getRhs()->acceptVisit(this);
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        llvm::Value* addIntTmp = Builder.CreateAdd(lhs, rhs, "addinttmp");
        accumulator->push_back(addIntTmp);
      } else {
        accumulator->push_back(LogErrorV("invalid binary operator"));
      }
    }

    void visit(SubExpression* p) {
      p->getLhs()->acceptVisit(this);
      llvm::Value* lhs = accumulator->back();
      p->getRhs()->acceptVisit(this);
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        accumulator->push_back(Builder.CreateSub(lhs, rhs, "subinttmp"));
      } else {
        accumulator->push_back(LogErrorV("invalid binary operator"));
      }
    }

    void visit(TimesExpression* p) {
      p->getLhs()->acceptVisit(this);
      llvm::Value* lhs = accumulator->back();
      p->getRhs()->acceptVisit(this);
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        accumulator->push_back(Builder.CreateMul(lhs, rhs, "mulinttmp"));
      } else {
        accumulator->push_back(LogErrorV("invalid binary operator"));
      }
    }

    void visit(DivExpression* p) {
      p->getLhs()->acceptVisit(this);
      llvm::Value* lhs = accumulator->back();
      p->getRhs()->acceptVisit(this);
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        accumulator->push_back(Builder.CreateSDiv(lhs, rhs, "divinttmp"));
      } else {
        accumulator->push_back(LogErrorV("invalid binary operator"));
      }
    }

    void visit(RemExpression* p) {
      p->getLhs()->acceptVisit(this);
      llvm::Value* lhs = accumulator->back();
      p->getRhs()->acceptVisit(this);
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        accumulator->push_back(Builder.CreateSRem(lhs, rhs, "remtmp"));
      } else {
        accumulator->push_back(LogErrorV("invalid binary operator"));
      }
    }

    void visit(AndExpression* p) {
      p->getLhs()->acceptVisit(this);
      llvm::Value* lhs = accumulator->back();
      p->getRhs()->acceptVisit(this);
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        llvm::Value* cmp = Builder.CreateAnd(lhs, rhs, "andtmp");
        accumulator->push_back(Builder.CreateICmpNE(cmp, Builder.getInt32(0), "booltmp"));
      } else {
        accumulator->push_back(LogErrorV("invalid binary operator"));
      }
    }

    void visit(OrExpression* p) {
      p->getLhs()->acceptVisit(this);
      llvm::Value* lhs = accumulator->back();
      p->getRhs()->acceptVisit(this);
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        llvm::Value* cmp = Builder.CreateOr(lhs, rhs, "ortmp");
        accumulator->push_back(Builder.CreateICmpNE(cmp, Builder.getInt32(0), "booltmp"));
      } else {
        accumulator->push_back(LogErrorV("invalid binary operator"));
      }
    }

    void visit(LTExpression* p) {
      p->getLhs()->acceptVisit(this);
      llvm::Value* lhs = accumulator->back();
      p->getRhs()->acceptVisit(this);
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        llvm::Value* cmp = Builder.CreateFCmpULT(lhs, rhs, "lttmp");
        accumulator->push_back(Builder.CreateICmpNE(cmp, Builder.getInt32(0), "booltmp"));
      } else {
        accumulator->push_back(LogErrorV("invalid binary operator"));
      }
    }

    void visit(LEExpression* p) {
      p->getLhs()->acceptVisit(this);
      llvm::Value* lhs = accumulator->back();
      p->getRhs()->acceptVisit(this);
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        llvm::Value* cmp = Builder.CreateFCmpULE(lhs, rhs, "letmp");
        accumulator->push_back(Builder.CreateICmpNE(cmp, Builder.getInt32(0), "booltmp"));
      } else {
        accumulator->push_back(LogErrorV("invalid binary operator"));
      }
    }

    void visit(GTExpression* p) {
      p->getLhs()->acceptVisit(this);
      llvm::Value* lhs = accumulator->back();
      p->getRhs()->acceptVisit(this);
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        llvm::Value* cmp = Builder.CreateFCmpUGT(lhs, rhs, "gttmp");
        accumulator->push_back(Builder.CreateICmpNE(cmp, Builder.getInt32(0), "booltmp"));
      } else {
        accumulator->push_back(LogErrorV("invalid binary operator"));
      }
    }

    void visit(GEExpression* p) {
      p->getLhs()->acceptVisit(this);
      llvm::Value* lhs = accumulator->back();
      p->getRhs()->acceptVisit(this);
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        llvm::Value* cmp = Builder.CreateFCmpUGE(lhs, rhs, "getmp");
        accumulator->push_back(Builder.CreateICmpNE(cmp, Builder.getInt32(0), "booltmp"));
      } else {
        accumulator->push_back(LogErrorV("invalid binary operator"));
      }
    }

    void visit(EQExpression* p) {
      p->getLhs()->acceptVisit(this);
      llvm::Value* lhs = accumulator->back();
      p->getRhs()->acceptVisit(this);
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        llvm::Value* cmp = Builder.CreateFCmpUEQ(lhs, rhs, "eqtmp");
        accumulator->push_back(Builder.CreateICmpNE(cmp, Builder.getInt32(0), "booltmp"));
      } else {
        accumulator->push_back(LogErrorV("invalid binary operator"));
      }
    }

    void visit(NEExpression* p) {
      p->getLhs()->acceptVisit(this);
      llvm::Value* lhs = accumulator->back();
      p->getRhs()->acceptVisit(this);
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        llvm::Value* cmp = Builder.CreateFCmpUNE(lhs, rhs, "netmp");
        accumulator->push_back(Builder.CreateICmpNE(cmp, Builder.getInt32(0), "booltmp"));
      } else {
        accumulator->push_back(LogErrorV("invalid binary operator"));
      }
    }

    void visit(Program* p) {
      llvm::FunctionType *mainFunctionType = llvm::FunctionType::get(
        llvm::Type::getVoidTy(TheContext), false);
      llvm::Function* mainFunction = llvm::Function::Create(
        mainFunctionType, llvm::Function::ExternalLinkage, "main", &*TheModule);

      for (auto itGlobalVars = p->getGlobalVars()->begin();
        itGlobalVars != p->getGlobalVars()->end(); ++itGlobalVars) {
        TheModule->getOrInsertGlobal((*itGlobalVars)->name(),
          typeOf((*itGlobalVars)->type()));
        llvm::GlobalVariable* globalVar = TheModule->getGlobalVariable(
          (*itGlobalVars)->name());
        if (!globalVar) {
          accumulator->push_back(LogErrorV("Can not create the variable."));
        } else {
          globalVar->setLinkage(llvm::GlobalValue::CommonLinkage);
          globalVar->setAlignment(4);
          globalVar->setInitializer(initializerConst((*itGlobalVars)->type()));
          accumulator->push_back(globalVar);
        }
      }

      for (auto itProcedures = p->getProcedures()->begin();
        itProcedures != p->getProcedures()->end(); ++itProcedures) {
        this->visit(*itProcedures);
      }

      // Set the current function to create the basic blocks correctly
      currentFunction = mainFunction;

      this->visit(p->commands());

      Builder.CreateRetVoid();
      llvm::verifyFunction(*mainFunction);
    }
//  void visit(TypesEnum* p) { } // This visit can be unnecessary
    void visit(Command* p) {
      p->acceptVisit(this);
    }
    void visit(IntValue* p) {
      accumulator->push_back(llvm::ConstantInt::get(TheContext, llvm::APInt(32, p->value(), true)));
    }
    void visit(RealValue* p) {
      accumulator->push_back(llvm::ConstantFP::get(TheContext, llvm::APFloat(p->value())));
    }
    void visit(BooleanValue* p) {
      accumulator->push_back(llvm::ConstantInt::get(TheContext, llvm::APInt(1, p->value())));
    }
    void visit(StringValue* p) {

    }
    void visit(Undefined* p) {

    }
    void visit(Assignment* p) {
      VarRef* ref = new VarRef(p->name());
      this->visit(ref);
      llvm::Value* lhs = accumulator->back();
      this->visit(p->expression());
      llvm::Value* rhs = accumulator->back();

      if (lhs && rhs) {
        accumulator->push_back(Builder.CreateStore(rhs, lhs));
      } else {
        accumulator->push_back(LogErrorV("Invalid assignment"));
      }
      delete ref;
    }

    void visit(VarRef* p) {
      llvm::Value* currentVariable = nullptr;
      for (auto &Arg: currentFunction->args()) {
        if (Arg.getName() == p->name()) {
          currentVariable = &Arg;
        }
      }
      if (!currentVariable)
        currentVariable = TheModule->getGlobalVariable(p->name());

      if (!currentVariable)
        accumulator->push_back(LogErrorV("Variable not found"));
      else
        accumulator->push_back(currentVariable);
    }

    void visit(ProcedureCall* p) {
      llvm::Function *procedure = TheModule->getFunction(p->name());
      if (procedure) {
        if (p->args()->size() == procedure->arg_size()) {
          std::vector<llvm::Value*> argumentsValues;
          for (auto itArguments = p->args()->begin();
            itArguments != p->args()->end(); ++itArguments) {
            this->visit((*itArguments));
            llvm::Value* argValue = accumulator->back();
            argumentsValues.push_back(argValue);
            if (!argValue)
              break;
          }
          if (!accumulator->back()) {
            accumulator->push_back(LogErrorV("Invalid argument"));
          } else {
            accumulator->push_back(Builder.CreateCall(procedure, argumentsValues, "calltmp"));
          }
        } else {
          accumulator->push_back(LogErrorV("Wrong number of params"));
        }
      } else {
        accumulator->push_back(LogErrorV("Invalid Procedure"));
      }
    }
    void visit(BlockCommand* p) {
      countBB++;
      std::string nameOfBB = "BB_";
      nameOfBB.append(std::to_string(countBB));
      llvm::BasicBlock* currentBB = llvm::BasicBlock::Create(
        TheContext, nameOfBB, currentFunction);
      Builder.SetInsertPoint(currentBB);
      currentBlock = currentBB;
      for (auto itCommands = p->commands()->begin();
        itCommands != p->commands()->end(); ++itCommands) {
        this->visit(*itCommands);
      }
      accumulator->push_back(currentBB);
    }
    void visit(PrintCommand* p) { }

    void visit(WhileCommand* p) { }
    void visit(IfThenCommand* p) {
      this->visit(p->condition());
      llvm::Value* cond = accumulator->back();
      llvm::BasicBlock* beforeIf = currentBlock;
      this->visit(p->thenCmd());
      llvm::BasicBlock* thenBB = (llvm::BasicBlock*) accumulator->back();
      llvm::BasicBlock* afterThen = currentBlock;

      if (cond && thenBB) {
        llvm::BasicBlock* mergeBB = llvm::BasicBlock::Create(
          TheContext, "mergeBB", currentFunction);
        Builder.SetInsertPoint(beforeIf);
        Builder.CreateCondBr(cond, thenBB, mergeBB);
        Builder.SetInsertPoint(afterThen);
        Builder.CreateBr(mergeBB);
        Builder.SetInsertPoint(mergeBB);
        llvm::PHINode* phi = Builder.CreatePHI(
          llvm::Type::getVoidTy(TheContext), 1, "ifthentmp");
        phi->addIncoming(nullptr, thenBB);
        accumulator->push_back(phi);
      } else {
        accumulator->push_back(LogErrorV("Invalid conditional statment"));
      }
    }
    void visit(IfThenElseCommand* p) {
      this->visit(p->condition());
      llvm::Value* cond = accumulator->back();
      llvm::BasicBlock* beforeIf = currentBlock;
      this->visit(p->thenCmd());
      llvm::BasicBlock* thenBB = (llvm::BasicBlock*) accumulator->back();
      llvm::BasicBlock* afterThen = currentBlock;
      this->visit(p->elseCmd());
      llvm::BasicBlock* elseBB = (llvm::BasicBlock*) accumulator->back();
      llvm::BasicBlock* afterElse = currentBlock;

      if (cond && thenBB && elseBB) {
        llvm::BasicBlock* mergeBB = llvm::BasicBlock::Create(
          TheContext, "mergeBB", currentFunction);
        Builder.SetInsertPoint(beforeIf);
        Builder.CreateCondBr(cond, thenBB, elseBB);
        Builder.SetInsertPoint(afterThen);
        Builder.CreateBr(mergeBB);
        Builder.SetInsertPoint(afterElse);
        Builder.CreateBr(mergeBB);
        Builder.SetInsertPoint(mergeBB);
        llvm::PHINode* phi = Builder.CreatePHI(
          llvm::Type::getVoidTy(TheContext), 2, "ifthenelsetmp");
        phi->addIncoming(nullptr, thenBB);
        phi->addIncoming(nullptr, elseBB);
        accumulator->push_back(phi);
      } else {
        accumulator->push_back(LogErrorV("Invalid conditional statment"));
      }
    }

    void visit(Declaration* p) {

    }

    void visit(DecProcedure* p) {
      std::vector<llvm::Type*> argumentsTypes;
      for (auto itArguments = p->formalArgs()->begin();
        itArguments != p->formalArgs()->end(); itArguments++) {
        argumentsTypes.push_back(typeOf((*itArguments)->type()));
      }

      llvm::FunctionType *procedureType = llvm::FunctionType::get(
        llvm::Type::getVoidTy(TheContext), argumentsTypes, false);
      llvm::Function* procedure = llvm::Function::Create(
        procedureType, llvm::Function::ExternalLinkage, p->name(), &*TheModule);

      unsigned argumentIndex = 0;
      for (auto &Arg: procedure->args()) {
        Arg.setName((*p->formalArgs())[argumentIndex++]->name());
      }

      // Set the current function to create the basic blocks correctly
      currentFunction = procedure;

      this->visit(p->body());

      Builder.CreateRetVoid();

      llvm::verifyFunction(*procedure);
      accumulator->push_back(procedure);
    }

    void visit(VarDec* p) { }

    LLVMVisitor(Program* p, char* module_name) {
      accumulator = new std::vector<llvm::Value*>;
      program = p;
      TheModule = new llvm::Module (module_name, TheContext);
    }
    void codegen() {
      this->visit(program);
      TheModule->print(llvm::errs(), nullptr);
      // std::vector<llvm::Value*>::iterator itValues = accumulator->begin();
      // for (; itValues != accumulator->end(); ++itValues) {
      //   (*itValues)->print(llvm::errs());
      // }
    }

    ~LLVMVisitor() {
      delete TheModule;
      // for (auto itValues = accumulator->begin();
      //   itValues != accumulator->end(); ++itValues) {
      //   (*itValues)->deleteValue();
      // }
      delete accumulator;
    }
  private:
    std::vector<llvm::Value*>* accumulator;
    llvm::Function* currentFunction;
    llvm::BasicBlock* currentBlock;
    int countBB = -1;
    Program* program;

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
