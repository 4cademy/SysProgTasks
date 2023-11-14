all: myshell

lex.yy.c: scan.l
	flex scan.l

parse.tab.c parse.tab.h: parse.y
	bison -d parse.y

myshell: myshell.cpp lex.yy.c parse.tab.c parse.tab.h
	g++ myshell.cpp parse.tab.c lex.yy.c functions.c -o myshell -lreadline -lfl

clean:
	rm -f myshell.o lex.yy.c parse.tab.c parse.tab.h functions.o myshell