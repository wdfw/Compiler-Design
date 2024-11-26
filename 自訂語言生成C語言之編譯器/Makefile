CC=g++
LDFLAGS=-std=c++11 -O3 -lm
SOURCES=*.cpp
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=codeGenerator
all: 
	bison -d yacc.y
	flex lex.l

	g++ main.c lex.yy.c yacc.tab.c -o  $(EXECUTABLE)

yacc_:
	bison -d yacc.y
	flex lex.l

	g++ main.c lex.yy.c yacc.tab.c -o  $(EXECUTABLE)

yacc:yacc_
	echo 
	./codeGenerator.out sample.qv

yaccs:yacc_
	echo 
	./codeGenerator.out sample.qv ww -s
exe:
	./codeGenerator.out sample.qv

clean:
	rm *.o -f
	rm yacc.tab.* -f
	rm lex.yy.* -f