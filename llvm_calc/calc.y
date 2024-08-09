%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token NUM PLUS MINUS MUL DIV LPAREN RPAREN EOL

%left PLUS MINUS
%left MUL DIV

%%

input: /* пустая строка */
     | input line EOL { printf("Результат: %d\n", $2); }
     ;

line: expression
     ;

expression:  NUM         { $$ = $1; }
           | expression PLUS expression    { $$ = $1 + $3; }
           | expression MINUS expression   { $$ = $1 - $3; }
           | expression MUL expression    { $$ = $1 * $3; }
           | expression DIV expression    { 
                if ($3 == 0) { 
                    yyerror("Деление на ноль"); 
                } else {
                    $$ = $1 / $3; 
                }
             }
           | LPAREN expression RPAREN  { $$ = $2; }
           ;

%%

void yyerror(const char *s) {
  fprintf(stderr, "Ошибка: %s\n", s);
  exit(1);
}

int main() {
  yyparse();
  return 0;
}