calc: calc.l calc.y
	bison -d calc.y
	flex calc.l
	gcc calc.tab.c lex.yy.c -o calc -lfl

clean:
	rm -f calc calc.tab.c calc.tab.h lex.yy.c