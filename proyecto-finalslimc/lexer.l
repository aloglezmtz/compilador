%{
/* lexer.l - Analizador léxico de SlimC (Flex)
 *  - directivas #include y #define, librerías <archivo.h>
 *  - palabras reservadas: const int double main return if else while
 *  - identificadores, enteros, flotantes (3.14) y cadenas ("texto")
 *  - operadores aritméticos, relacionales (== != < > <= >=) y lógicos (&& || !)
 *  - comentarios // y / * * / (no alteran yylineno)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

extern int errores_lex;
%}

%option noyywrap
%option yylineno
%option nounput
%option noinput

/* Después de #include se espera <libreria.h>; así '<' sigue siendo el operador relacional */
%x INCL

DIG     [0-9]
ID      [A-Za-z_][A-Za-z0-9_]*

%%

[ \t\r\n]+                          { /* espacios */ }
"//".*                              { /* comentario de una línea */ }
"/*"([^*]|\*+[^*/])*\*+"/"          { /* comentario multilínea: flex cuenta sus saltos de línea */ }
"/*"([^*]|\*+[^*/])*\**             { printf("❌ Error léxico en línea %d: comentario sin cerrar.\n", yylineno); errores_lex++; }

"#include"                          { BEGIN(INCL); yylval.linea = yylineno; return T_INCLUDE; }
<INCL>[ \t\r]+                      { /* espacios entre #include y la librería */ }
<INCL>"<"[A-Za-z0-9_./]+">"         { BEGIN(INITIAL); return T_LIBRERIA; }
<INCL>\"[A-Za-z0-9_./]+\"           { BEGIN(INITIAL); return T_LIBRERIA; }
<INCL>\n                            { BEGIN(INITIAL); }
<INCL>.                             { BEGIN(INITIAL); yyless(0); }

"#define"                           { yylval.linea = yylineno; return T_DEFINE; }
"#"[A-Za-z]+                        { printf("❌ Error léxico en línea %d: directiva '%s' no reconocida.\n", yylineno, yytext); errores_lex++; }

"const"                             { yylval.linea = yylineno; return T_CONST; }
"int"                               { yylval.linea = yylineno; return T_INT; }
"double"                            { yylval.linea = yylineno; return T_DOUBLE; }
"main"                              { yylval.id.s = strdup(yytext); yylval.id.linea = yylineno; return T_MAIN; }
"return"                            { yylval.linea = yylineno; return T_RETURN; }
"if"                                { yylval.linea = yylineno; return T_IF; }
"else"                              { return T_ELSE; }
"while"                             { yylval.linea = yylineno; return T_WHILE; }

{ID}                                { yylval.id.s = strdup(yytext); yylval.id.linea = yylineno; return T_ID; }
{DIG}+"."{DIG}+                     { yylval.e.tipo = TIPO_DOUBLE; yylval.e.linea = yylineno; return T_FLOAT; }
{DIG}+                              { yylval.e.tipo = TIPO_INT;    yylval.e.linea = yylineno; return T_NUM; }
\"([^\"\\\n]|\\.)*\"                { yylval.e.tipo = TIPO_STRING; yylval.e.linea = yylineno; return T_STRING; }
\"([^\"\\\n]|\\.)*                  { printf("❌ Error léxico en línea %d: cadena sin cerrar.\n", yylineno); errores_lex++; }

"=="                                { return T_EQ; }
"!="                                { return T_NE; }
"<="                                { return T_LE; }
">="                                { return T_GE; }
"&&"                                { return T_AND; }
"||"                                { return T_OR; }
[-+*/(){},;=<>!]                    { return yytext[0]; }

.                                   { printf("❌ Error léxico en línea %d: carácter inválido '%s'.\n", yylineno, yytext); errores_lex++; }

%%
