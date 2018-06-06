/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include <string>
#include "Printer.H"
#define INDENT_WIDTH 2


//You may wish to change render
void PrintAbsyn::render(Char c)
{
  if (c == '{')
  {
     bufAppend('\n');
     indent();
     bufAppend(c);
     _n_ = _n_ + INDENT_WIDTH;
     bufAppend('\n');
     indent();
  }
  else if (c == '(' || c == '[')
     bufAppend(c);
  else if (c == ')' || c == ']')
  {
     backup();
     bufAppend(c);
  }
  else if (c == '}')
  {
     int t;
     _n_ = _n_ - INDENT_WIDTH;
     for (t=0; t<INDENT_WIDTH; t++) {
       backup();
     }
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == ',')
  {
     backup();
     bufAppend(c);
     bufAppend(' ');
  }
  else if (c == ';')
  {
     backup();
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == 0) return;
  else
  {
     bufAppend(' ');
     bufAppend(c);
     bufAppend(' ');
  }
}
void PrintAbsyn::render(String s_)
{
  const char *s = s_.c_str() ;
  if(strlen(s) > 0)
  {
    bufAppend(s);
    bufAppend(' ');
  }
}
void PrintAbsyn::render(char* s)
{
  if(strlen(s) > 0)
  {
    bufAppend(s);
    bufAppend(' ');
  }
}
void PrintAbsyn::indent()
{
  int n = _n_;
  while (n > 0)
  {
    bufAppend(' ');
    n--;
  }
}
void PrintAbsyn::backup()
{
  if (buf_[cur_ - 1] == ' ')
  {
    buf_[cur_ - 1] = 0;
    cur_--;
  }
}
PrintAbsyn::PrintAbsyn(void)
{
  _i_ = 0; _n_ = 0;
  buf_ = 0;
  bufReset();
}

PrintAbsyn::~PrintAbsyn(void)
{
}

char* PrintAbsyn::print(Visitable *v)
{
  _i_ = 0; _n_ = 0;
  bufReset();
  v->accept(this);
  return buf_;
}
void PrintAbsyn::visitModuleDec(ModuleDec*p) {} //abstract class

void PrintAbsyn::visitModule(Module* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("module");
  visitIdent(p->ident_1);
  if(p->listvardec_) {_i_ = 0; p->listvardec_->accept(this);}  if(p->listprocdec_) {_i_ = 0; p->listprocdec_->accept(this);}  render("begin");
  if(p->liststmt_) {_i_ = 0; p->liststmt_->accept(this);}  render("end");
  visitIdent(p->ident_2);
  render('.');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitType(Type*p) {} //abstract class

void PrintAbsyn::visitTInt(TInt* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("int");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitTBool(TBool* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("bool");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitTReal(TReal* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("real");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitVarDec(VarDec*p) {} //abstract class

void PrintAbsyn::visitDecl(Decl* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("var");
  if(p->listident_) {_i_ = 0; p->listident_->accept(this);}  render(':');
  _i_ = 0; p->type_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitFPmtDec(FPmtDec*p) {} //abstract class

void PrintAbsyn::visitFPDecl(FPDecl* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  if(p->listident_) {_i_ = 0; p->listident_->accept(this);}  render(':');
  _i_ = 0; p->type_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitProcDec(ProcDec*p) {} //abstract class

void PrintAbsyn::visitPDec(PDec* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("def");
  visitIdent(p->ident_);
  render('(');
  if(p->listfpmtdec_) {_i_ = 0; p->listfpmtdec_->accept(this);}  render(')');
  if(p->listvardec_) {_i_ = 0; p->listvardec_->accept(this);}  render("begin");
  if(p->liststmt_) {_i_ = 0; p->liststmt_->accept(this);}  render("end");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitExp(Exp*p) {} //abstract class

void PrintAbsyn::visitELt(ELt* p)
{
  int oldi = _i_;
  if (oldi > 1) render(_L_PAREN);

  _i_ = 1; p->exp_1->accept(this);
  render('<');
  _i_ = 2; p->exp_2->accept(this);

  if (oldi > 1) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEGt(EGt* p)
{
  int oldi = _i_;
  if (oldi > 1) render(_L_PAREN);

  _i_ = 1; p->exp_1->accept(this);
  render('>');
  _i_ = 2; p->exp_2->accept(this);

  if (oldi > 1) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEEq(EEq* p)
{
  int oldi = _i_;
  if (oldi > 1) render(_L_PAREN);

  _i_ = 1; p->exp_1->accept(this);
  render("==");
  _i_ = 2; p->exp_2->accept(this);

  if (oldi > 1) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitENEq(ENEq* p)
{
  int oldi = _i_;
  if (oldi > 1) render(_L_PAREN);

  _i_ = 1; p->exp_1->accept(this);
  render("!=");
  _i_ = 2; p->exp_2->accept(this);

  if (oldi > 1) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEAdd(EAdd* p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  _i_ = 2; p->exp_1->accept(this);
  render('+');
  _i_ = 3; p->exp_2->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitESub(ESub* p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  _i_ = 2; p->exp_1->accept(this);
  render('-');
  _i_ = 3; p->exp_2->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEOr(EOr* p)
{
  int oldi = _i_;
  if (oldi > 2) render(_L_PAREN);

  _i_ = 2; p->exp_1->accept(this);
  render("||");
  _i_ = 3; p->exp_2->accept(this);

  if (oldi > 2) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEMul(EMul* p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  _i_ = 3; p->exp_1->accept(this);
  render('*');
  _i_ = 4; p->exp_2->accept(this);

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEDiv(EDiv* p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  _i_ = 3; p->exp_1->accept(this);
  render('/');
  _i_ = 4; p->exp_2->accept(this);

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEAnd(EAnd* p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  _i_ = 3; p->exp_1->accept(this);
  render("&&");
  _i_ = 4; p->exp_2->accept(this);

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEVar(EVar* p)
{
  int oldi = _i_;
  if (oldi > 4) render(_L_PAREN);

  visitIdent(p->ident_);

  if (oldi > 4) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEStr(EStr* p)
{
  int oldi = _i_;
  if (oldi > 4) render(_L_PAREN);

  visitString(p->string_);

  if (oldi > 4) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEInt(EInt* p)
{
  int oldi = _i_;
  if (oldi > 4) render(_L_PAREN);

  visitInteger(p->integer_);

  if (oldi > 4) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEFalse(EFalse* p)
{
  int oldi = _i_;
  if (oldi > 4) render(_L_PAREN);

  render("false");

  if (oldi > 4) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitETrue(ETrue* p)
{
  int oldi = _i_;
  if (oldi > 4) render(_L_PAREN);

  render("true");

  if (oldi > 4) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEReal(EReal* p)
{
  int oldi = _i_;
  if (oldi > 4) render(_L_PAREN);

  visitDouble(p->double_);

  if (oldi > 4) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitStmt(Stmt*p) {} //abstract class

void PrintAbsyn::visitSCall(SCall* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->ident_);
  render('(');
  if(p->listexp_) {_i_ = 0; p->listexp_->accept(this);}  render(')');

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSAssignment(SAssignment* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitIdent(p->ident_);
  render(":=");
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSWhile(SWhile* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("while");
  render('(');
  _i_ = 0; p->exp_->accept(this);
  render(')');
  render("do");
  if(p->liststmt_) {_i_ = 0; p->liststmt_->accept(this);}  render("end");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSIfThenElse(SIfThenElse* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("if");
  render('(');
  _i_ = 0; p->exp_->accept(this);
  render(')');
  render("then");
  if(p->liststmt_1) {_i_ = 0; p->liststmt_1->accept(this);}  render("end");
  render("else");
  if(p->liststmt_2) {_i_ = 0; p->liststmt_2->accept(this);}  render("end");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSIfThen(SIfThen* p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("if");
  render('(');
  _i_ = 0; p->exp_->accept(this);
  render(')');
  render("then");
  if(p->liststmt_) {_i_ = 0; p->liststmt_->accept(this);}  render("end");

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListExp(ListExp *listexp)
{
  for (ListExp::const_iterator i = listexp->begin() ; i != listexp->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listexp->end() - 1) render(',');
  }
}void PrintAbsyn::visitListStmt(ListStmt *liststmt)
{
  for (ListStmt::const_iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != liststmt->end() - 1) render(';');
  }
}void PrintAbsyn::visitListIdent(ListIdent *listident)
{
  for (ListIdent::const_iterator i = listident->begin() ; i != listident->end() ; ++i)
  {
    visitIdent(*i) ;
    if (i != listident->end() - 1) render(',');
  }
}void PrintAbsyn::visitListVarDec(ListVarDec *listvardec)
{
  for (ListVarDec::const_iterator i = listvardec->begin() ; i != listvardec->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listvardec->end() - 1) render(';');
  }
}void PrintAbsyn::visitListFPmtDec(ListFPmtDec *listfpmtdec)
{
  for (ListFPmtDec::const_iterator i = listfpmtdec->begin() ; i != listfpmtdec->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listfpmtdec->end() - 1) render(',');
  }
}void PrintAbsyn::visitListProcDec(ListProcDec *listprocdec)
{
  for (ListProcDec::const_iterator i = listprocdec->begin() ; i != listprocdec->end() ; ++i)
  {
    (*i)->accept(this);
    render("");
  }
}void PrintAbsyn::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}
void PrintAbsyn::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}
void PrintAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}
void PrintAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}
void PrintAbsyn::visitIdent(String s)
{
  render(s);
}

ShowAbsyn::ShowAbsyn(void)
{
  buf_ = 0;
  bufReset();
}

ShowAbsyn::~ShowAbsyn(void)
{
}

char* ShowAbsyn::show(Visitable *v)
{
  bufReset();
  v->accept(this);
  return buf_;
}
void ShowAbsyn::visitModuleDec(ModuleDec* p) {} //abstract class

void ShowAbsyn::visitModule(Module* p)
{
  bufAppend('(');
  bufAppend("Module");
  bufAppend(' ');
  visitIdent(p->ident_1);
  bufAppend(' ');
  bufAppend('[');
  if (p->listvardec_)  p->listvardec_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->listprocdec_)  p->listprocdec_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->liststmt_)  p->liststmt_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  visitIdent(p->ident_2);
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitType(Type* p) {} //abstract class

void ShowAbsyn::visitTInt(TInt* p)
{
  bufAppend("TInt");
}
void ShowAbsyn::visitTBool(TBool* p)
{
  bufAppend("TBool");
}
void ShowAbsyn::visitTReal(TReal* p)
{
  bufAppend("TReal");
}
void ShowAbsyn::visitVarDec(VarDec* p) {} //abstract class

void ShowAbsyn::visitDecl(Decl* p)
{
  bufAppend('(');
  bufAppend("Decl");
  bufAppend(' ');
  bufAppend('[');
  if (p->listident_)  p->listident_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitFPmtDec(FPmtDec* p) {} //abstract class

void ShowAbsyn::visitFPDecl(FPDecl* p)
{
  bufAppend('(');
  bufAppend("FPDecl");
  bufAppend(' ');
  bufAppend('[');
  if (p->listident_)  p->listident_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->type_)  p->type_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitProcDec(ProcDec* p) {} //abstract class

void ShowAbsyn::visitPDec(PDec* p)
{
  bufAppend('(');
  bufAppend("PDec");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listfpmtdec_)  p->listfpmtdec_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->listvardec_)  p->listvardec_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->liststmt_)  p->liststmt_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitExp(Exp* p) {} //abstract class

void ShowAbsyn::visitELt(ELt* p)
{
  bufAppend('(');
  bufAppend("ELt");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEGt(EGt* p)
{
  bufAppend('(');
  bufAppend("EGt");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEEq(EEq* p)
{
  bufAppend('(');
  bufAppend("EEq");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitENEq(ENEq* p)
{
  bufAppend('(');
  bufAppend("ENEq");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEAdd(EAdd* p)
{
  bufAppend('(');
  bufAppend("EAdd");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitESub(ESub* p)
{
  bufAppend('(');
  bufAppend("ESub");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEOr(EOr* p)
{
  bufAppend('(');
  bufAppend("EOr");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEMul(EMul* p)
{
  bufAppend('(');
  bufAppend("EMul");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEDiv(EDiv* p)
{
  bufAppend('(');
  bufAppend("EDiv");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEAnd(EAnd* p)
{
  bufAppend('(');
  bufAppend("EAnd");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEVar(EVar* p)
{
  bufAppend('(');
  bufAppend("EVar");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(')');
}
void ShowAbsyn::visitEStr(EStr* p)
{
  bufAppend('(');
  bufAppend("EStr");
  bufAppend(' ');
  visitString(p->string_);
  bufAppend(')');
}
void ShowAbsyn::visitEInt(EInt* p)
{
  bufAppend('(');
  bufAppend("EInt");
  bufAppend(' ');
  visitInteger(p->integer_);
  bufAppend(')');
}
void ShowAbsyn::visitEFalse(EFalse* p)
{
  bufAppend("EFalse");
}
void ShowAbsyn::visitETrue(ETrue* p)
{
  bufAppend("ETrue");
}
void ShowAbsyn::visitEReal(EReal* p)
{
  bufAppend('(');
  bufAppend("EReal");
  bufAppend(' ');
  visitDouble(p->double_);
  bufAppend(')');
}
void ShowAbsyn::visitStmt(Stmt* p) {} //abstract class

void ShowAbsyn::visitSCall(SCall* p)
{
  bufAppend('(');
  bufAppend("SCall");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listexp_)  p->listexp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitSAssignment(SAssignment* p)
{
  bufAppend('(');
  bufAppend("SAssignment");
  bufAppend(' ');
  visitIdent(p->ident_);
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitSWhile(SWhile* p)
{
  bufAppend('(');
  bufAppend("SWhile");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->liststmt_)  p->liststmt_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitSIfThenElse(SIfThenElse* p)
{
  bufAppend('(');
  bufAppend("SIfThenElse");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  p->liststmt_1->accept(this);
  bufAppend(' ');
  p->liststmt_2->accept(this);
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitSIfThen(SIfThen* p)
{
  bufAppend('(');
  bufAppend("SIfThen");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->liststmt_)  p->liststmt_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitListExp(ListExp *listexp)
{
  for (ListExp::const_iterator i = listexp->begin() ; i != listexp->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listexp->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitListStmt(ListStmt *liststmt)
{
  for (ListStmt::const_iterator i = liststmt->begin() ; i != liststmt->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != liststmt->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitListIdent(ListIdent *listident)
{
  for (ListIdent::const_iterator i = listident->begin() ; i != listident->end() ; ++i)
  {
    visitIdent(*i) ;
    if (i != listident->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitListVarDec(ListVarDec *listvardec)
{
  for (ListVarDec::const_iterator i = listvardec->begin() ; i != listvardec->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listvardec->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitListFPmtDec(ListFPmtDec *listfpmtdec)
{
  for (ListFPmtDec::const_iterator i = listfpmtdec->begin() ; i != listfpmtdec->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listfpmtdec->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitListProcDec(ListProcDec *listprocdec)
{
  for (ListProcDec::const_iterator i = listprocdec->begin() ; i != listprocdec->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listprocdec->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitInteger(Integer i)
{
  char tmp[16];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}
void ShowAbsyn::visitDouble(Double d)
{
  char tmp[16];
  sprintf(tmp, "%g", d);
  bufAppend(tmp);
}
void ShowAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}
void ShowAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}
void ShowAbsyn::visitIdent(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}


