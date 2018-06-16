#ifndef PARSER_HEADER_FILE
#define PARSER_HEADER_FILE

#include<vector>
#include<string>


class ModuleDec;
class Type;
class VarDecl;
class FPmtDec;
class ProcDec;
class Exp;
class Stmt;
class ListExp;
class ListStmt;
class ListIdent;
class ListVarDecl;
class ListFPmtDec;
class ListProcDec;

typedef union
{
  int int_;
  char char_;
  double double_;
  char* string_;
  ModuleDec* moduledec_;
  Type* type_;
  VarDecl* vardecl_;
  FPmtDec* fpmtdec_;
  ProcDec* procdec_;
  Exp* exp_;
  Stmt* stmt_;
  ListExp* listexp_;
  ListStmt* liststmt_;
  ListIdent* listident_;
  ListVarDecl* listvardecl_;
  ListFPmtDec* listfpmtdec_;
  ListProcDec* listprocdec_;
} YYSTYPE;

ModuleDec* pModuleDec(FILE *inp);
ModuleDec* pModuleDec(const char *str);
Type* pType(FILE *inp);
Type* pType(const char *str);
VarDecl* pVarDecl(FILE *inp);
VarDecl* pVarDecl(const char *str);
FPmtDec* pFPmtDec(FILE *inp);
FPmtDec* pFPmtDec(const char *str);
ProcDec* pProcDec(FILE *inp);
ProcDec* pProcDec(const char *str);
Exp* pExp(FILE *inp);
Exp* pExp(const char *str);
Stmt* pStmt(FILE *inp);
Stmt* pStmt(const char *str);
ListExp* pListExp(FILE *inp);
ListExp* pListExp(const char *str);
ListStmt* pListStmt(FILE *inp);
ListStmt* pListStmt(const char *str);
ListIdent* pListIdent(FILE *inp);
ListIdent* pListIdent(const char *str);
ListVarDecl* pListVarDecl(FILE *inp);
ListVarDecl* pListVarDecl(const char *str);
ListFPmtDec* pListFPmtDec(FILE *inp);
ListFPmtDec* pListFPmtDec(const char *str);
ListProcDec* pListProcDec(FILE *inp);
ListProcDec* pListProcDec(const char *str);



#define _ERROR_ 258
#define _SYMB_0 259
#define _SYMB_1 260
#define _SYMB_2 261
#define _SYMB_3 262
#define _SYMB_4 263
#define _SYMB_5 264
#define _SYMB_6 265
#define _SYMB_7 266
#define _SYMB_8 267
#define _SYMB_9 268
#define _SYMB_10 269
#define _SYMB_11 270
#define _SYMB_12 271
#define _SYMB_13 272
#define _SYMB_14 273
#define _SYMB_15 274
#define _SYMB_16 275
#define _SYMB_17 276
#define _SYMB_18 277
#define _SYMB_19 278
#define _SYMB_20 279
#define _SYMB_21 280
#define _SYMB_22 281
#define _SYMB_23 282
#define _SYMB_24 283
#define _SYMB_25 284
#define _SYMB_26 285
#define _SYMB_27 286
#define _SYMB_28 287
#define _SYMB_29 288
#define _SYMB_30 289
#define _SYMB_31 290
#define _SYMB_32 291
#define _STRING_ 292
#define _INTEGER_ 293
#define _DOUBLE_ 294
#define _IDENT_ 295

extern YYSTYPE yylval;

#endif
