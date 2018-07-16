#ifndef CFG_VISITOR_H
#define CFG_VISITOR_H

#define TOP 2
#define CONSTANT 1
#define BOTTOM 0

#include <iostream>
#include <map>
#include <set>

#include "IVisitor.hpp"

namespace OberonLang {
class CFGVisitor : public IVisitor {
public:
  void visit(Program *p) {
    procedureCount = 0;
    for (auto procedure = p->getProcedures()->begin();
      procedure != p->getProcedures()->end(); ++procedure) {
      this->visit(*procedure);
    }

    visitCount = 0;

    // diferent of the vector scope of variables, that the first index is
    // the scope of global variables, the vector of graph start with procedures
    // and the main program is the last index of vector.
    this->superGraph->push_back(new std::map<int, std::set<int>>());
    setCurrentGraph(this->procedureCount);
    setCurrentScope(varState);

    this->visit(p->getCommands());

    visitCount++;

    std::map<std::string, char>::iterator itActualScope = varState->begin();
    std::map<std::string, char>::iterator itProgramScope = getCurrentScope()->begin();
    std::map<std::string, char> *newScope = new std::map<std::string, char>();
    while (itActualScope != varState->end()) {
      if (itActualScope->second == itProgramScope->second) {
        (*newScope)[itActualScope->first] = itActualScope->second;
      } else if (itActualScope->second == TOP && itProgramScope->second == CONSTANT) {
        (*newScope)[itActualScope->first] = CONSTANT;
      } else {
        (*newScope)[itActualScope->first] = itActualScope->second & itProgramScope->second;
      }
      itActualScope++;
      itProgramScope++;
    }
    std::cout << "\nVariables in MainProgram that can be replaced: " << std::endl;
    analiseScope(newScope);
  };

  //  void visit(TypesEnum* p) { }; // This visit can be unnecessary

  void visit(IntValue *p) {
    lastTypeOfValue = CONSTANT;
  };

  void visit(RealValue *p) {
    lastTypeOfValue = CONSTANT;
  };

  void visit(BooleanValue *p) {
    lastTypeOfValue = CONSTANT;
  };

  void visit(Undefined *p) {
    lastTypeOfValue = TOP;
  };

  void visit(Command *p) { p->acceptVisit(this); };

  void visit(Assignment *p) {
    auto index = getCurrentScope()->find("p" +
      std::to_string(procedureCount) + "_" + p->name());
    
    if (index != getCurrentScope()->end()) {
      if (index->second == TOP) {
        this->visit(p->getValue());
        index->second = lastTypeOfValue;
      } else if (index->second == 1) {
        index->second = BOTTOM;
      }
    } else {
      index = getCurrentScope()->find("g_" + p->name());
      if (index != getCurrentScope()->end()) {
        if (index->second == TOP) {
          this->visit(p->getValue());
          index->second = lastTypeOfValue;
        }
        else if (index->second == 1) {
          index->second = BOTTOM;
        }
      } else {
        std::cout << "Undeclared varible" << std::endl;
        exit(-1);
      }
    }

    (*getCurrentGraph())[visitCount].insert(visitCount + 1);
    visitCount++;
  };

  void visit(ProcedureCall *p) {
    std::map<std::string, char> *actualScope = getCurrentScope();

    // need to think how is the better way to work in this expression
    int storedVisitCount = visitCount;
    int storedProcedureCount = procedureCount;
    this->procedureCount = (*this->procedureNames)[p->name()];

    setCurrentGraph(this->procedureCount);

    this->visitCount = 0;
    this->visit((*program->getProcedures())[procedureCount]->body());
    // look how the other command should be now

    std::map<std::string, char> *procedureScope = getCurrentScope();
    std::map<std::string, char>::iterator itActualScope = actualScope->begin();
    std::map<std::string, char>::iterator itProcedureScope = procedureScope->begin();
    std::map<std::string, char> *newScope = new std::map<std::string, char>();
    while (itActualScope != actualScope->end()) {
      if (itActualScope->second == itProcedureScope->second) {
        (*newScope)[itActualScope->first] = itActualScope->second;
      } else if (itActualScope->second == TOP && itProcedureScope->second == CONSTANT) {
        (*newScope)[itActualScope->first] = CONSTANT;
      } else {
        (*newScope)[itActualScope->first] = itActualScope->second & itProcedureScope->second;
      }
      itActualScope++;
      itProcedureScope++;
    }
    setCurrentScope(newScope);

    this->procedureCount = storedProcedureCount;
    this->visitCount = storedVisitCount;
    setCurrentGraph(this->procedureCount);
    (*getCurrentGraph())[visitCount].insert(visitCount + 1);
    this->visitCount++;

    std::cout << "\nVariables in " + p->name() + " that can be replaced: " << std::endl;
    analiseScope(newScope);
  };

  void visit(BlockCommand *p) {
    // can make the in out groups based on blockCommand.
    // this can help to make local or global replacements
    std::map<std::string, char> *actualScope = getCurrentScope();
    std::map<std::string, char> *newScope = new std::map<std::string, char>();
    newScope->insert(actualScope->begin(), actualScope->end());
    setCurrentScope(newScope);

    list<Command *>::iterator command;
    for (command = p->getCommands()->begin(); command != p->getCommands()->end(); ++command) {
      this->visit(*command);
    }

    // I dont if should set the current scope how the actualScope
  };

  void visit(PrintCommand *p) {
      // Dont know if this is realy necessary
      // visitCount++;
  };

  void visit(WhileCommand *p) {
    std::map<std::string, char> *actualScope = getCurrentScope();

    (*getCurrentGraph())[visitCount].insert(visitCount + 1);
    visitCount++;
    int storedVisitCount = visitCount;
    this->visit(p->getCommands());
    (*getCurrentGraph())[visitCount].insert(storedVisitCount + 1);
    (*getCurrentGraph())[storedVisitCount].insert(visitCount + 1);

    std::map<std::string, char> *whileScope = getCurrentScope();
    std::map<std::string, char>::iterator itActualScope = actualScope->begin();
    std::map<std::string, char>::iterator itWhileScope = whileScope->begin();
    std::map<std::string, char> *newScope = new std::map<std::string, char>();
    while (itActualScope != actualScope->end()) {
      (*newScope)[itActualScope->first] = (itActualScope->second & itWhileScope->second) & itWhileScope->second;
      itActualScope++;
      itWhileScope++;
    }
    // the better place to replace the constanst is in program, procedureCall expressions
    // ifThen, ifThenElse, While commands

    setCurrentScope(newScope);

    std::cout << "\nVariables in WhileCommand that can be replaced: " << std::endl;
    analiseScope(newScope);
  };

  void visit(IfThenCommand *p) {
    std::map<std::string, char> *actualScope = getCurrentScope();
    // can verify if the expression of codition have a constant value;
    (*getCurrentGraph())[visitCount].insert(visitCount + 1);
    visitCount++;
    int storedVisitCount = visitCount;
    this->visit(p->getCommands());
    (*getCurrentGraph())[storedVisitCount].insert(visitCount + 1);

    std::map<std::string, char> *ifScope = getCurrentScope();
    std::map<std::string, char>::iterator itActualScope = actualScope->begin();
    std::map<std::string, char>::iterator itIfScope = ifScope->begin();
    std::map<std::string, char> *newScope = new std::map<std::string, char>();
    while (itActualScope != actualScope->end()) {
      (*newScope)[itActualScope->first] = itActualScope->second & itIfScope->second;
      itActualScope++;
      itIfScope++;
    }
    setCurrentScope(newScope);

    std::cout << "\nVariables in IfThenCommand that can be replaced: " << std::endl;
    analiseScope(newScope);
  };

  void visit(IfThenElseCommand *p) {
    std::map<std::string, char> *actualScope = getCurrentScope();

    (*getCurrentGraph())[visitCount].insert(visitCount + 1);
    visitCount++;
    int storedVisitCount = visitCount;
    this->visit(p->getTrueConditionCommands());
    int trueConditionVisitCount = visitCount;

    std::map<std::string, char> *ifTrueScope = getCurrentScope();

    this->visit(p->getFalseConditionCommands());
    int falseConditionVisitCount = visitCount;

    std::map<std::string, char> *ifFalseScope = getCurrentScope();
    std::map<std::string, char>::iterator itIfTrueScope = ifTrueScope->begin();
    std::map<std::string, char>::iterator itIfFalseScope = ifFalseScope->begin();
    std::map<std::string, char>::iterator itActualScope = actualScope->begin();
    std::map<std::string, char> *newScope = new std::map<std::string, char>();
    while (itIfTrueScope != ifTrueScope->end()) {
      (*newScope)[itIfTrueScope->first] = (itIfTrueScope->second & itIfFalseScope->second) & itActualScope->second;
      itIfTrueScope++;
      itIfFalseScope++;
      itActualScope++;
    }
    setCurrentScope(newScope);

    (*getCurrentGraph())[storedVisitCount].insert(trueConditionVisitCount + 1);
    (*getCurrentGraph())[trueConditionVisitCount].erase(trueConditionVisitCount + 1);
    (*getCurrentGraph())[trueConditionVisitCount].insert(falseConditionVisitCount + 1);

    std::cout << "\nVariables in IfThenElseCommand that can be replaced: " << std::endl;
    analiseScope(newScope);
  };

  void visit(Declaration *p){};

  void visit(DecProcedure *p) {
    // Dont make sense diference a variable of an argument
    this->superGraph->push_back(new std::map<int, std::set<int>>());

    visitCount = 0;

    procedureCount++;
  };

  void visit(Expression *p) { p->acceptVisit(this); };

  void visit(VarRef *p) {
    auto index = getCurrentScope()->find("p" +
      std::to_string(procedureCount) + "_" + p->name());
    if (index != getCurrentScope()->end()) {
      lastTypeOfValue = index->second;
    } else {
      index = getCurrentScope()->find("g_" + p->name());
      if (index != getCurrentScope()->end()) {
        lastTypeOfValue = index->second;
      } else {
        std::cout << "Undeclared varible" << std::endl;
        exit(-1);
      }
    }
  };

  void visit(VarDec *p){};

  void visit(BinExpression *p) {
    char lhs;
    char rhs;
    this->visit(p->getLhs());
    lhs = lastTypeOfValue;
    this->visit(p->getRhs());
    rhs = lastTypeOfValue;

    if (lhs == BOTTOM || rhs == BOTTOM) {
      lastTypeOfValue = BOTTOM;
    } else if (lhs == TOP || rhs == TOP) {
      lastTypeOfValue = TOP;
    } else {
      lastTypeOfValue = CONSTANT;
    }
  };

  //  maybe to be necessary copy the implementation on BinExpression for all BinExpressions
  void visit(AddExpression *p) {
    char lhs;
    char rhs;
    this->visit(p->getLhs());
    lhs = lastTypeOfValue;
    this->visit(p->getRhs());
    rhs = lastTypeOfValue;

    if (lhs == BOTTOM || rhs == BOTTOM) {
      lastTypeOfValue = BOTTOM;
    } else if (lhs == TOP || rhs == TOP) {
      lastTypeOfValue = TOP;
    } else {
      lastTypeOfValue = CONSTANT;
    }
  };

  void visit(TimesExpression *p) {
    char lhs;
    char rhs;
    this->visit(p->getLhs());
    lhs = lastTypeOfValue;
    this->visit(p->getRhs());
    rhs = lastTypeOfValue;

    if (lhs == BOTTOM || rhs == BOTTOM) {
      lastTypeOfValue = BOTTOM;
    } else if (lhs == TOP || rhs == TOP) {
      lastTypeOfValue = TOP;
    } else {
      lastTypeOfValue = CONSTANT;
    }
  };

  void visit(SubExpression *p) {
    char lhs;
    char rhs;
    this->visit(p->getLhs());
    lhs = lastTypeOfValue;
    this->visit(p->getRhs());
    rhs = lastTypeOfValue;

    if (lhs == BOTTOM || rhs == BOTTOM) {
      lastTypeOfValue = BOTTOM;
    } else if (lhs == TOP || rhs == TOP) {
      lastTypeOfValue = TOP;
    } else {
      lastTypeOfValue = CONSTANT;
    }
  };

  void visit(DivExpression *p) {
    char lhs;
    char rhs;
    this->visit(p->getLhs());
    lhs = lastTypeOfValue;
    this->visit(p->getRhs());
    rhs = lastTypeOfValue;

    if (lhs == BOTTOM || rhs == BOTTOM) {
      lastTypeOfValue = BOTTOM;
    } else if (lhs == TOP || rhs == TOP) {
      lastTypeOfValue = TOP;
    } else {
      lastTypeOfValue = CONSTANT;
    }
  };

  void visit(RemExpression *p) {
    char lhs;
    char rhs;
    this->visit(p->getLhs());
    lhs = lastTypeOfValue;
    this->visit(p->getRhs());
    rhs = lastTypeOfValue;

    if (lhs == BOTTOM || rhs == BOTTOM) {
      lastTypeOfValue = BOTTOM;
    } else if (lhs == TOP || rhs == TOP) {
      lastTypeOfValue = TOP;
    } else {
      lastTypeOfValue = CONSTANT;
    }
  };

  void visit(AndExpression *p) {
    char lhs;
    char rhs;
    this->visit(p->getLhs());
    lhs = lastTypeOfValue;
    this->visit(p->getRhs());
    rhs = lastTypeOfValue;

    if (lhs == BOTTOM || rhs == BOTTOM) {
      lastTypeOfValue = BOTTOM;
    } else if (lhs == TOP || rhs == TOP) {
      lastTypeOfValue = TOP;
    } else {
      lastTypeOfValue = CONSTANT;
    }
  };

  void visit(OrExpression *p) {
    char lhs;
    char rhs;
    this->visit(p->getLhs());
    lhs = lastTypeOfValue;
    this->visit(p->getRhs());
    rhs = lastTypeOfValue;

    if (lhs == BOTTOM || rhs == BOTTOM) {
      lastTypeOfValue = BOTTOM;
    } else if (lhs == TOP || rhs == TOP) {
      lastTypeOfValue = TOP;
    } else {
      lastTypeOfValue = CONSTANT;
    }
  };

  void visit(LTExpression *p) {
    char lhs;
    char rhs;
    this->visit(p->getLhs());
    lhs = lastTypeOfValue;
    this->visit(p->getRhs());
    rhs = lastTypeOfValue;

    if (lhs == BOTTOM || rhs == BOTTOM) {
      lastTypeOfValue = BOTTOM; 
    } else if (lhs == TOP || rhs == TOP) {
      lastTypeOfValue = TOP;
    } else {
      lastTypeOfValue = CONSTANT;
    }
  };

  void visit(LEExpression *p) {
    char lhs;
    char rhs;
    this->visit(p->getLhs());
    lhs = lastTypeOfValue;
    this->visit(p->getRhs());
    rhs = lastTypeOfValue;

    if (lhs == BOTTOM || rhs == BOTTOM) {
      lastTypeOfValue = BOTTOM;
    } else if (lhs == TOP || rhs == TOP) {
      lastTypeOfValue = TOP;
    } else {
      lastTypeOfValue = CONSTANT;
    }
  };

  void visit(GTExpression *p) {
    char lhs;
    char rhs;
    this->visit(p->getLhs());
    lhs = lastTypeOfValue;
    this->visit(p->getRhs());
    rhs = lastTypeOfValue;

    if (lhs == BOTTOM || rhs == BOTTOM) {
      lastTypeOfValue = BOTTOM;
    } else if (lhs == TOP || rhs == TOP) {
      lastTypeOfValue = TOP;
    } else {
      lastTypeOfValue = CONSTANT;
    }
  };

  void visit(GEExpression *p) {
    char lhs;
    char rhs;
    this->visit(p->getLhs());
    lhs = lastTypeOfValue;
    this->visit(p->getRhs());
    rhs = lastTypeOfValue;

    if (lhs == BOTTOM || rhs == BOTTOM) {
      lastTypeOfValue = BOTTOM;
    } else if (lhs == TOP || rhs == TOP) {
      lastTypeOfValue = TOP;
    } else {
      lastTypeOfValue = CONSTANT;
    }
  };

  void visit(NEExpression *p) {
    char lhs;
    char rhs;
    this->visit(p->getLhs());
    lhs = lastTypeOfValue;
    this->visit(p->getRhs());
    rhs = lastTypeOfValue;

    if (lhs == BOTTOM || rhs == BOTTOM) {
      lastTypeOfValue = BOTTOM;
    } else if (lhs == TOP || rhs == TOP) {
      lastTypeOfValue = TOP;
    } else {
      lastTypeOfValue = CONSTANT;
    }
  };

  void visit(EQExpression *p) {
    char lhs;
    char rhs;
    this->visit(p->getLhs());
    lhs = lastTypeOfValue;
    this->visit(p->getRhs());
    rhs = lastTypeOfValue;

    if (lhs == BOTTOM || rhs == BOTTOM) {
      lastTypeOfValue = BOTTOM;
    } else if (lhs == TOP || rhs == TOP) {
      lastTypeOfValue = TOP;
    } else {
      lastTypeOfValue = CONSTANT;
    }
  };

  CFGVisitor(Program *p) {
    program = p;
    varCount = 0;
    procedureCount = 0;
    visitCount = 0;
    lastTypeOfValue = TOP;
    superGraph = new std::vector<std::map<int, std::set<int>> *>();
    varState = new std::map<std::string, char>();
    procedureNames = new std::map<std::string, int>();
    varNames = new std::map<std::string, int>();
    scopes = new std::vector<std::tuple<std::map<std::string, char> *, std::map<std::string, char> *>>();
    mapAllVariables();
    // printVarNames();
    printSuperGraph();
  };

  std::map<std::string, char> *getCurrentScope() {
    return this->currentScope;
  }

  void setCurrentScope(std::map<std::string, char> *scope) {
    this->currentScope = scope;
  }

  std::map<int, std::set<int>> *getCurrentGraph() {
    return this->currentGraph;
  }

  void setCurrentGraph(int number_of_graph) {
    this->currentGraph = (*this->superGraph)[number_of_graph];
  }

private:
  int varCount;
  int procedureCount;
  int visitCount;
  char lastTypeOfValue;
  Program *program;
  // Can join the map and vector in a unique map
  std::map<std::string, int> *varNames;
  std::map<std::string, char> *varState;

  std::vector<std::tuple<std::map<std::string, char> *, std::map<std::string, char> *>> *scopes;
  std::map<std::string, int> *procedureNames;
  std::vector<std::map<int, std::set<int>> *> *superGraph;
  std::map<std::string, char> *currentScope;
  std::map<int, std::set<int>> *currentGraph;

  void mapAllVariables() {
    procedureCount = 0;

    for (auto globalVar = program->getGlobalVars()->begin();
      globalVar != program->getGlobalVars()->end(); ++globalVar) {
      std::string varName = "g_" + (*globalVar)->name();
      (*this->varState)[varName] = TOP;
    }

    for (auto procedure = program->getProcedures()->begin();
      procedure != program->getProcedures()->end(); ++procedure) {

      (*this->procedureNames)[(*procedure)->name()] = procedureCount;

      for (auto var = (*procedure)->formalArgs().begin();
        var != (*procedure)->formalArgs().end(); ++var) {
        std::string varName = "p" + std::to_string(procedureCount) + "_" + (*var).name();
        (*this->varState)[varName] = CONSTANT;
      }

      for (auto var = (*procedure)->localVars().begin();
        var != (*procedure)->localVars().end(); ++var) {
        std::string varName = "p" + std::to_string(procedureCount) + "_" + (*var).name();
        (*this->varState)[varName] = TOP;
        varCount++;
      }

      procedureCount++;
    }

    this->visit(this->program);
  }

  void printVarNames() {
    std::map<std::string, int>::iterator itVarNames = varNames->begin();
    std::cout << "\n";
    for (; itVarNames != varNames->end(); ++itVarNames) {
      std::cout << itVarNames->first + ": " + std::to_string(itVarNames->second) << std::endl;
    }
  }

  void printSuperGraph() {
    std::vector<std::map<int, std::set<int>> *>::iterator itSuperGraph =
      this->superGraph->begin();

    for (; itSuperGraph != this->superGraph->end(); ++itSuperGraph) {
      std::cout << "Super graph size: " + std::to_string((*itSuperGraph)->size()) << std::endl;
      std::map<int, std::set<int>>::iterator itGraph = (*itSuperGraph)->begin();
      for (; itGraph != (*itSuperGraph)->end(); ++itGraph) {
        std::set<int>::iterator itSet = itGraph->second.begin();
        for (; itSet != itGraph->second.end(); ++itSet) {
          std::cout << std::to_string(itGraph->first) + ": " +
            std::to_string(*itSet)
            << std::endl;
        }
      }
    }
  }

  void analiseScope(std::map<std::string, char> *scope) {
    std::map<std::string, char>::iterator itScope = scope->begin();
    for (; itScope != scope->end(); ++itScope) {
      if (itScope->second == CONSTANT) {
        std::cout << itScope->first + ": " + std::to_string(itScope->second) << std::endl;
      }
    }
  }
};
} // namespace OberonLang

#endif