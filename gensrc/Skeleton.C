/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "Skeleton.H"



void Skeleton::visitModuleDec(ModuleDec* t) {} //abstract class
void Skeleton::visitType(Type* t) {} //abstract class
void Skeleton::visitVarDec(VarDec* t) {} //abstract class
void Skeleton::visitFPmtDec(FPmtDec* t) {} //abstract class
void Skeleton::visitProcDec(ProcDec* t) {} //abstract class
void Skeleton::visitExp(Exp* t) {} //abstract class
void Skeleton::visitStmt(Stmt* t) {} //abstract class

void Skeleton::visitModule(Module *module)
{
  /* Code For Module Goes Here */

  visitIdent(module->ident_1);
  module->listvardec_->accept(this);
  module->listprocdec_->accept(this);
  module->liststmt_->accept(this);
  visitIdent(module->ident_2);

}

void Skeleton::visitTInt(TInt *tint)
{
  /* Code For TInt Goes Here */


}

void Skeleton::visitTBool(TBool *tbool)
{
  /* Code For TBool Goes Here */


}

void Skeleton::visitDecl(Decl *decl)
{
  /* Code For Decl Goes Here */

  decl->listident_->accept(this);
  decl->type_->accept(this);

}

void Skeleton::visitFPDecl(FPDecl *fpdecl)
{
  /* Code For FPDecl Goes Here */

  fpdecl->listident_->accept(this);
  fpdecl->type_->accept(this);

}

void Skeleton::visitPDec(PDec *pdec)
{
  /* Code For PDec Goes Here */

  visitIdent(pdec->ident_);
  pdec->listfpmtdec_->accept(this);
  pdec->listvardec_->accept(this);
  pdec->liststmt_->accept(this);

}

void Skeleton::visitELt(ELt *elt)
{
  /* Code For ELt Goes Here */

  elt->exp_1->accept(this);
  elt->exp_2->accept(this);

}

void Skeleton::visitEGt(EGt *egt)
{
  /* Code For EGt Goes Here */

  egt->exp_1->accept(this);
  egt->exp_2->accept(this);

}

void Skeleton::visitEEq(EEq *eeq)
{
  /* Code For EEq Goes Here */

  eeq->exp_1->accept(this);
  eeq->exp_2->accept(this);

}

void Skeleton::visitENEq(ENEq *eneq)
{
  /* Code For ENEq Goes Here */

  eneq->exp_1->accept(this);
  eneq->exp_2->accept(this);

}

void Skeleton::visitEAdd(EAdd *eadd)
{
  /* Code For EAdd Goes Here */

  eadd->exp_1->accept(this);
  eadd->exp_2->accept(this);

}

void Skeleton::visitESub(ESub *esub)
{
  /* Code For ESub Goes Here */

  esub->exp_1->accept(this);
  esub->exp_2->accept(this);

}

void Skeleton::visitEMul(EMul *emul)
{
  /* Code For EMul Goes Here */

  emul->exp_1->accept(this);
  emul->exp_2->accept(this);

}

void Skeleton::visitEDiv(EDiv *ediv)
{
  /* Code For EDiv Goes Here */

  ediv->exp_1->accept(this);
  ediv->exp_2->accept(this);

}

void Skeleton::visitEOr(EOr *eor)
{
  /* Code For EOr Goes Here */

  eor->exp_1->accept(this);
  eor->exp_2->accept(this);

}

void Skeleton::visitEAnd(EAnd *eand)
{
  /* Code For EAnd Goes Here */

  eand->exp_1->accept(this);
  eand->exp_2->accept(this);

}

void Skeleton::visitCall(Call *call)
{
  /* Code For Call Goes Here */

  visitIdent(call->ident_);
  call->listexp_->accept(this);

}

void Skeleton::visitEVar(EVar *evar)
{
  /* Code For EVar Goes Here */

  visitIdent(evar->ident_);

}

void Skeleton::visitEStr(EStr *estr)
{
  /* Code For EStr Goes Here */

  visitString(estr->string_);

}

void Skeleton::visitEInt(EInt *eint)
{
  /* Code For EInt Goes Here */

  visitInteger(eint->integer_);

}

void Skeleton::visitEFalse(EFalse *efalse)
{
  /* Code For EFalse Goes Here */


}

void Skeleton::visitETrue(ETrue *etrue)
{
  /* Code For ETrue Goes Here */


}

void Skeleton::visitEDouble(EDouble *edouble)
{
  /* Code For EDouble Goes Here */

  visitDouble(edouble->double_);

}

void Skeleton::visitSCall(SCall *scall)
{
  /* Code For SCall Goes Here */

  visitIdent(scall->ident_);
  scall->listexp_->accept(this);

}

void Skeleton::visitSAssignment(SAssignment *sassignment)
{
  /* Code For SAssignment Goes Here */

  visitIdent(sassignment->ident_);
  sassignment->exp_->accept(this);

}

void Skeleton::visitSWhile(SWhile *swhile)
{
  /* Code For SWhile Goes Here */

  swhile->exp_->accept(this);
  swhile->liststmt_->accept(this);

}

void Skeleton::visitSIfThenElse(SIfThenElse *sifthenelse)
{
  /* Code For SIfThenElse Goes Here */

  sifthenelse->exp_->accept(this);
  sifthenelse->liststmt_->accept(this);
  sifthenelse->stmt_->accept(this);

}

void Skeleton::visitSIfThen(SIfThen *sifthen)
{
  /* Code For SIfThen Goes Here */

  sifthen->exp_->accept(this);
  sifthen->liststmt_->accept(this);

}


void Skeleton::visitListExp(ListExp* listexp)
{
  for (ListExp::iterator i = listexp->begin() ; i != listexp->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListStmt(ListStmt* liststmt)
{
  for (ListStmt::iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListIdent(ListIdent* listident)
{
  for (ListIdent::iterator i = listident->begin() ; i != listident->end() ; ++i)
  {
    visitIdent(*i) ;
  }
}

void Skeleton::visitListVarDec(ListVarDec* listvardec)
{
  for (ListVarDec::iterator i = listvardec->begin() ; i != listvardec->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListFPmtDec(ListFPmtDec* listfpmtdec)
{
  for (ListFPmtDec::iterator i = listfpmtdec->begin() ; i != listfpmtdec->end() ; ++i)
  {
    (*i)->accept(this);
  }
}

void Skeleton::visitListProcDec(ListProcDec* listprocdec)
{
  for (ListProcDec::iterator i = listprocdec->begin() ; i != listprocdec->end() ; ++i)
  {
    (*i)->accept(this);
  }
}


void Skeleton::visitInteger(Integer x)
{
  /* Code for Integer Goes Here */
}

void Skeleton::visitChar(Char x)
{
  /* Code for Char Goes Here */
}

void Skeleton::visitDouble(Double x)
{
  /* Code for Double Goes Here */
}

void Skeleton::visitString(String x)
{
  /* Code for String Goes Here */
}

void Skeleton::visitIdent(Ident x)
{
  /* Code for Ident Goes Here */
}



