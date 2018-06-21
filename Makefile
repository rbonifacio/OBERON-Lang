## Main compiler
CC := g++
BNFC := bnfc

## Directories
SRCDIR := src
HEADERDIR := include
BUILDDIR := build
BINDIR := bin
BNFDIR := bnf
GENSRCDIR := gensrc

## Targets
MAINTARGET := bin/oberon
TESTERTARGET := bin/tester

## Extensions
SRCEXT := cpp
HEADEREXT := hpp

## Source requisites
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
BNFSOURCE := $(GENSRCDIR)/Absyn.C $(GENSRCDIR)/Makefile $(GENSRCDIR)/oberon.y $(GENSRCDIR)/Printer.C $(GENSRCDIR)/Skeleton.C $(GENSRCDIR)/Test.C $(GENSRCDIR)/Absyn.H $(GENSRCDIR)/oberon.l $(GENSRCDIR)/Parser.H $(GENSRCDIR)/Printer.H $(GENSRCDIR)/Skeleton.H

## Tester requisites
TESTEROBJ := $(BUILDDIR)/BinExpression.o $(BUILDDIR)/Expression.o $(BUILDDIR)/Command.o $(BUILDDIR)/Environment.o $(BUILDDIR)/Procedure.o $(BUILDDIR)/VarRef.o

## Objects targets
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
BNFOBJECTS := $(BUILDDIR)/Absyn.o $(BUILDDIR)/Lexer.o $(BUILDDIR)/Parser.o $(BUILDDIR)/Printer.o

## Flags
CXXFLAGS := -g -W -Wall -Wextra -Wno-unused-parameter -std=c++11 #-Wno-unused-parameter
LIB := -pthread -L lib
INC := -I $(HEADERDIR) -I $(GENSRCDIR)
GTEST := ${GTEST_DIR}
LLVMFLAGS := `llvm-config --cxxflags --ldflags --system-libs --libs core`

## Generate main program
$(MAINTARGET): $(OBJECTS) .bnfobjects .folders
	$(CC) $(OBJECTS) $(BNFOBJECTS) -o $(MAINTARGET)

## Generate obj with dependency info
-include $(OBJECTS:.o=.d)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) .folders .bnfsource
	$(CC) $(CXXFLAGS) $(LLVMFLAGS) $(INC) -c -o $@ $<
	printf "$(BUILDDIR)/" "%s" > $(BUILDDIR)/$*.d
	$(CC) $(CXXFLAGS) $(LLVMFLAGS) $(INC) -MM $< >> $(BUILDDIR)/$*.d

## Generate bnf source

.bnfsource: $(BNFDIR)/oberon.bnfc .folders
	$(BNFC) -m -cpp $(BNFDIR)/oberon.bnfc -o $(GENSRCDIR)
	touch .bnfsource

## Generate bnf obj
.bnfobjects: .bnfsource .folders
	make -C $(GENSRCDIR) all
	mv $(GENSRCDIR)/*.o $(BUILDDIR)
	touch .bnfobjects

## Generate folders
.folders:
	mkdir -p $(GENSRCDIR)
	mkdir -p $(BUILDDIR)
	mkdir -p $(BINDIR)
	touch .folders

## Generate tester
tester: $(OBJECTS) .folders
	$(CC) $(CXXFLAGS) $(LIB) test/TestOberonLang.cpp $(INC) -o $(TESTERTARGET) $(GTEST)/libgtest.a $(TESTEROBJ)


## Clean
clean:
	rm -rf $(BUILDDIR) $(BINDIR) -R
	rm -rf $(MAINTARGET) $(TESTERTARGET) $(BNFDIR)/*.bak .bnfobjects .folders

cleanAll:
	rm -rf $(BUILDDIR) $(GENSRCDIR) $(BINDIR) -R
	rm -rf $(MAINTARGET) $(TESTERTARGET) $(BNFDIR)/*.bak .bnfobjects .bnfsource .folders

.PHONY: clean
