lex.yy.c: scan.l parse.tab.h
	flex scan.l

parse.tab.c parse.tab.h: parse.y
	bison -d parse.y

myshell: myshell.cpp lex.yy.c parse.tab.c parse.tab.h
	g++ -o myshell myshell.cpp parse.tab.c lex.yy.c -lreadline -lfl

clean:
	rm -f lex.yy.c parse.tab.c parse.tab.h myshell