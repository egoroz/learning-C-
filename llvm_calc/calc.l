%{
#include "calc.tab.h"
%}

%%
[0-9]+      { yylval = atoi(yytext); return NUM; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MUL; }
"/"         { return DIV; }
"("         { return LPAREN; }
")"         { return RPAREN; }
\n          { return EOL; }
[ \t]       ; /* Пропускаем пробелы */
.           { printf("Неизвестный символ: %s\n", yytext); }
%%