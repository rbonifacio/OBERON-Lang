## Main compiler
CC := g++
BNFC := bnfc

## Directories
SRCDIR		:= src
HEADERDIR := include
BUILDDIR	:= build
BNFDIR		:= bnf
GENSRCDIR := gensrc

## Targets
MAINTARGET		:= bin/oberon
TESTERTARGET	:= bin/tester

## Extensions
SRCEXT		:= cpp
HEADEREXT := hpp

## Source requisites
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
BNFSOURCE := $(GENSRCDIR)/Absyn.C $(GENSRCDIR)/Makefile $(GENSRCDIR)/oberon.y $(GENSRCDIR)/Printer.C $(GENSRCDIR)/Skeleton.C $(GENSRCDIR)/Test.C $(GENSRCDIR)/Absyn.H $(GENSRCDIR)/oberon.l $(GENSRCDIR)/Parser.H $(GENSRCDIR)/Printer.H $(GENSRCDIR)/Skeleton.H

## Tester requisites
TESTEROBJ	:= $(BUILDDIR)/BinExpression.o $(BUILDDIR)/Expression.o $(BUILDDIR)/Command.o $(BUILDDIR)/Environment.o $(BUILDDIR)/Procedure.o $(BUILDDIR)/VarRef.o

## Objects targets
OBJECTS			:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
BNFOBJECTS	:= $(BUILDDIR)/Absyn.o $(BUILDDIR)/Lexer.o $(BUILDDIR)/Parser.o $(BUILDDIR)/Printer.o

## Flags
CXXFLAGS	:= -g -W -Wall -Wextra -Wno-unused-parameter -std=c++11 #-Wno-unused-parameter
LIB				:= -pthread -L lib
INC				:= -I $(HEADERDIR) -I $(GENSRCDIR)
GTEST			:= ${GTEST_DIR}

## Generate main program
$(MAINTARGET): $(OBJECTS) .bnfobjects
	$(CC) $(OBJECTS) $(BNFOBJECTS) -o $(MAINTARGET)

## Generate obj with dependency info
-include $(OBJECTS:.o=.d)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) .bnfsource
	$(CC) $(CXXFLAGS) $(INC) -c -o $@ $<
	printf "$(BUILDDIR)/" "%s" > $(BUILDDIR)/$*.d
	$(CC) $(CXXFLAGS) $(INC) -MM $< >> $(BUILDDIR)/$*.d

## Generate bnf source

.bnfsource: $(BNFDIR)/oberon.bnfc
	$(BNFC) -m -cpp $(BNFDIR)/oberon.bnfc -o $(GENSRCDIR)
	touch .bnfsource
	
## Generate bnf obj
.bnfobjects: .bnfsource
	make -C $(GENSRCDIR) all
	mv $(GENSRCDIR)/*.o $(BUILDDIR)
	touch .bnfobjects
	
## Generate tester
tester: $(OBJECTS)
	$(CC) $(CXXFLAGS) $(LIB) test/TestOberonLang.cpp $(INC) -o $(TESTERTARGET) $(GTEST)/libgtest.a $(TESTEROBJ)
	
	
## Clean
clean:
	rm -rf $(BUILDDIR)/* $(MAINTARGET) $(TESTERTARGET) $(GENSRCDIR)/* $(BNFDIR)/*.bak $(SRCDIR)/*.d .bnfobjects .bnfsource
	
.PHONY: clean 
