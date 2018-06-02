CC = g++
CCFLAGS = -g -W -Wall

FLEX = flex
FLEX_OPTS = -Poberon

BISON = bison
BISON_OPTS = -t -poberon

OBJS = Absyn.o Lexer.o Parser.o Printer.o

.PHONY: clean distclean

all: Testoberon

clean:
	rm -f *.o Testoberon oberon.aux oberon.log oberon.pdf oberon.dvi oberon.ps oberon

distclean: clean
	rm -f Absyn.C Absyn.H Test.C Parser.C Parser.H Lexer.C Skeleton.C Skeleton.H Printer.C Printer.H Makefile oberon.l oberon.y oberon.tex 

gensrc:
	bnfc --cpp oberon.bnfc 

Testoberon: ${OBJS} Test.o
	@echo "Linking Testoberon..."
	${CC} ${CCFLAGS} ${OBJS} Test.o -o Testoberon
	@echo "Moving files..."
	mv oberon.l ../gensrc
	mv oberon.y ../gensrc
	mv *.H ../gensrc
	mv *.C ../gensrc
	mv *.o ../build 
	

Absyn.o: Absyn.C Absyn.H
	${CC} ${CCFLAGS} -c Absyn.C

Lexer.C: oberon.l
	${FLEX} -oLexer.C oberon.l

Parser.C: oberon.y
	${BISON} oberon.y -o Parser.C

Lexer.o: Lexer.C Parser.H
	${CC} ${CCFLAGS} -c Lexer.C

Parser.o: Parser.C Absyn.H
	${CC} ${CCFLAGS} -c Parser.C

Printer.o: Printer.C Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Printer.C

Skeleton.o: Skeleton.C Skeleton.H Absyn.H
	${CC} ${CCFLAGS} -c Skeleton.C

Test.o: Test.C Parser.H Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Test.C

