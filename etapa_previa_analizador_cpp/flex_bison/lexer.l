%{
/* lexer.l - Analizador léxico (flex) para un subconjunto de C */
#include <stdio.h>
#include "parser.tab.h"
extern int errores_lex;
%}

%option noyywrap
%option yylineno
%option nounput
%option noinput

%%

[ \t\r\n]+                         { /* espacios: se ignoran */ }
"//".*                             { /* comentario de línea */ }
"/*"([^*]|\*+[^*/])*\*+"/"         { /* comentario de bloque */ }

"#include"                         { yylval.num = yylineno; return T_INCLUDE; }
"#define"                          { yylval.num = yylineno; return T_DEFINE; }
"<"[A-Za-z0-9_./]+">"              { return T_LIBRERIA; }
\"[A-Za-z0-9_./]+\"                { return T_LIBRERIA; }

"int"                              { yylval.num = yylineno; return T_INT; }
"main"                             { return T_MAIN; }
"return"                           { return T_RETURN; }

[A-Za-z_][A-Za-z0-9_]*             { return T_ID; }
[0-9]+                             { return T_NUM; }

"+"|"-"|"*"|"/"|"("|")"|"{"|"}"|","|";"|"="   { return yytext[0]; }

.                                  {
    printf("❌ Error léxico en línea %d: carácter inválido '%s'.\n", yylineno, yytext);
    errores_lex++;
}

%%
