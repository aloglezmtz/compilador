%code requires {
#include "semantica.h"
}

%{
/* parser.y - Gramática, recuperación de errores y acciones semánticas de SlimC (Bison)
 *
 *   programa : prelude funciones_opt
 *   prelude  : (#include | #define | const tipada)*     funciones: tipo nombre(params) { ... }
 *   sentencias: declaraciones, asignación, llamadas, return, if/else, while, bloques
 * La tabla de símbolos está en tabla_simbolos.c y las verificaciones en semantica.c.
 * Se requiere Bison >= 3.0 (usa %define parse.error verbose y %code requires). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int  yylex(void);
void yyerror(const char *s);
extern FILE *yyin;
extern int   yylineno;
extern char *yytext;

int errores_lex  = 0;    /* los incrementa lexer.l */
int errores_sint = 0;
%}

%define parse.error verbose

%union {
    Ident    id;
    Expr     e;
    int      linea;
    ArgList *args;
}

%token T_EOF 0 "fin de archivo"
%token <linea> T_INCLUDE "directiva '#include'"
%token <linea> T_DEFINE  "directiva '#define'"
%token T_LIBRERIA        "librería '<archivo.h>'"
%token <linea> T_CONST   "'const'"
%token <linea> T_INT     "tipo 'int'"
%token <linea> T_DOUBLE  "tipo 'double'"
%token <id>    T_MAIN    "'main'"
%token <linea> T_RETURN  "'return'"
%token <linea> T_IF      "'if'"
%token T_ELSE            "'else'"
%token <linea> T_WHILE   "'while'"
%token <id>    T_ID      "identificador"
%token <e>     T_NUM     "número entero"
%token <e>     T_FLOAT   "número flotante"
%token <e>     T_STRING  "cadena"
%token T_EQ "'=='"
%token T_NE "'!='"
%token T_LE "'<='"
%token T_GE "'>='"
%token T_AND "'&&'"
%token T_OR "'||'"

%left T_OR
%left T_AND
%left T_EQ T_NE
%left '<' '>' T_LE T_GE
%left '+' '-'
%left '*' '/'
%right '!' UMENOS

%type <e>    tipo valor_macro expresion llamada
%type <id>   nombre_funcion
%type <args> lista_args lista_args_opt

%start programa

%%

programa
    : prelude funciones_opt           { sem_fin_programa(); }
    ;

/* ---------- preprocesador y constantes globales ---------- */
prelude
    : /* vacío */
    | prelude item_prelude
    ;

item_prelude
    : directiva
    | declaracion_const
    ;

directiva
    : T_INCLUDE T_LIBRERIA
    | T_INCLUDE
        { printf("❌ Error línea %d: falta el nombre de la librería '<archivo.h>' después de #include.\n", $1);
          errores_sint++; }
    | T_DEFINE T_ID valor_macro
        { sem_definir_macro($2.s, $3.tipo, $1); free($2.s); }
    | T_DEFINE T_ID '(' expresion ')'
        { sem_definir_macro($2.s, $4.tipo, $1); free($2.s); }
    | T_DEFINE T_ID
        { printf("❌ Error línea %d: falta el valor (literal o expresión entre paréntesis) después del identificador en #define.\n", $1);
          errores_sint++; free($2.s); }
    | T_DEFINE
        { printf("❌ Error línea %d: falta el identificador después de #define.\n", $1);
          errores_sint++; }
    ;

valor_macro
    : T_NUM      { $$ = $1; }
    | T_FLOAT    { $$ = $1; }
    | T_STRING   { $$ = $1; }
    ;

declaracion_const
    : T_CONST tipo T_ID '=' expresion ';'
        { sem_definir_constante($3.s, $2.tipo, $5.tipo, $3.linea); free($3.s); }
    ;

tipo
    : T_INT      { $$.tipo = TIPO_INT;    $$.linea = $1; }
    | T_DOUBLE   { $$.tipo = TIPO_DOUBLE; $$.linea = $1; }
    ;

/* ---------- funciones ---------- */
funciones_opt
    : /* vacío */
    | funciones_opt funcion
    ;

funcion
    : tipo nombre_funcion '(' parametros_opt ')'
        { sem_iniciar_funcion($1.tipo, $2.s, $2.linea); free($2.s); }
      cuerpo_funcion
        { sem_fin_funcion(); }
    | tipo '(' parametros_opt ')'
        { printf("❌ Error línea %d: falta el nombre (identificador) de la función después del tipo.\n", $1.linea);
          errores_sint++;
          sem_iniciar_funcion($1.tipo, NULL, $1.linea); }
      cuerpo_funcion
        { sem_fin_funcion(); }
    | error '}'
        { ts_volver_a_global(); sem_condicion_cancelar(); yyerrok; }
    ;

nombre_funcion
    : T_ID       { $$ = $1; }
    | T_MAIN     { $$ = $1; }
    ;

parametros_opt
    : /* vacío */
    | lista_parametros
    ;

lista_parametros
    : parametro
    | lista_parametros ',' parametro
    ;

parametro
    : tipo T_ID  { sem_param_pendiente($1.tipo, $2.s, $2.linea); free($2.s); }
    ;

cuerpo_funcion
    : '{' lista_sentencias '}'
    ;

bloque
    : '{' { sem_entrar_bloque(); } lista_sentencias '}' { sem_salir_bloque(); }
    ;

/* ---------- sentencias ---------- */
lista_sentencias
    : /* vacío */
    | lista_sentencias sentencia
    ;

sentencia
    : declaracion
    | declaracion_const
    | T_ID '=' expresion ';'
        { sem_asignar($1.s, $1.linea, $3.tipo); free($1.s); }
    | llamada ';'
    | T_RETURN expresion ';'
        { sem_retorno($2.tipo, $1); }
    | sentencia_if
    | sentencia_while
    | bloque
    | ';'
    | error ';'
        { sem_condicion_cancelar(); yyerrok; }
    ;

declaracion
    : tipo T_ID ';'
        { sem_declarar_variable($1.tipo, $2.s, $2.linea, 0, TIPO_ERROR); free($2.s); }
    | tipo T_ID '=' expresion ';'
        { sem_declarar_variable($1.tipo, $2.s, $2.linea, 1, $4.tipo); free($2.s); }
    ;

sentencia_if
    : T_IF '(' { sem_condicion_inicio("if"); } expresion ')' { sem_condicion_fin($4.tipo, $1); }
      bloque resto_if
    ;

resto_if
    : /* vacío */
    | T_ELSE bloque
    | T_ELSE sentencia_if
    ;

sentencia_while
    : T_WHILE '(' { sem_condicion_inicio("while"); } expresion ')' { sem_condicion_fin($4.tipo, $1); }
      bloque
    ;

/* ---------- expresiones ---------- */
llamada
    : T_ID '(' lista_args_opt ')'
        { $$.tipo = sem_llamada($1.s, $1.linea, $3); $$.linea = $1.linea; free($1.s); free($3); }
    ;

lista_args_opt
    : /* vacío */   { $$ = arglist_nueva(); }
    | lista_args    { $$ = $1; }
    ;

lista_args
    : expresion                  { $$ = arglist_nueva(); arglist_agregar($$, $1.tipo); }
    | lista_args ',' expresion   { arglist_agregar($1, $3.tipo); $$ = $1; }
    ;

expresion
    : T_NUM                      { $$ = $1; }
    | T_FLOAT                    { $$ = $1; }
    | T_STRING                   { $$ = $1; }
    | T_ID                       { $$.tipo = sem_usar_variable($1.s, $1.linea); $$.linea = $1.linea; free($1.s); }
    | llamada                    { $$ = $1; }
    | '(' expresion ')'          { $$ = $2; }
    | expresion '+' expresion    { $$.tipo = sem_binaria($1.tipo, $3.tipo, $1.linea);    $$.linea = $1.linea; }
    | expresion '-' expresion    { $$.tipo = sem_binaria($1.tipo, $3.tipo, $1.linea);    $$.linea = $1.linea; }
    | expresion '*' expresion    { $$.tipo = sem_binaria($1.tipo, $3.tipo, $1.linea);    $$.linea = $1.linea; }
    | expresion '/' expresion    { $$.tipo = sem_binaria($1.tipo, $3.tipo, $1.linea);    $$.linea = $1.linea; }
    | expresion '<' expresion    { $$.tipo = sem_relacional($1.tipo, $3.tipo, $1.linea); $$.linea = $1.linea; }
    | expresion '>' expresion    { $$.tipo = sem_relacional($1.tipo, $3.tipo, $1.linea); $$.linea = $1.linea; }
    | expresion T_LE expresion   { $$.tipo = sem_relacional($1.tipo, $3.tipo, $1.linea); $$.linea = $1.linea; }
    | expresion T_GE expresion   { $$.tipo = sem_relacional($1.tipo, $3.tipo, $1.linea); $$.linea = $1.linea; }
    | expresion T_EQ expresion   { $$.tipo = sem_relacional($1.tipo, $3.tipo, $1.linea); $$.linea = $1.linea; }
    | expresion T_NE expresion   { $$.tipo = sem_relacional($1.tipo, $3.tipo, $1.linea); $$.linea = $1.linea; }
    | expresion T_AND expresion  { $$.tipo = sem_relacional($1.tipo, $3.tipo, $1.linea); $$.linea = $1.linea; }
    | expresion T_OR expresion   { $$.tipo = sem_relacional($1.tipo, $3.tipo, $1.linea); $$.linea = $1.linea; }
    | '!' expresion              { $$.tipo = sem_relacional($2.tipo, TIPO_INT, $2.linea); $$.linea = $2.linea; }
    | '-' expresion %prec UMENOS { $$.tipo = sem_binaria($2.tipo, TIPO_INT, $2.linea);    $$.linea = $2.linea; }
    ;

%%

void yyerror(const char *s) {
    printf("❌ Error sintáctico en línea %d (lexema '%s'): %s\n", yylineno, yytext, s);
    errores_sint++;
}

int main(int argc, char **argv) {
    if (argc < 2) { fprintf(stderr, "Uso: %s archivo.c\n", argv[0]); return 2; }
    FILE *archivo = fopen(argv[1], "r");
    if (!archivo) { perror("No se pudo abrir el archivo"); return 1; }
    yyin = archivo;

    sem_iniciar();
    int resultado = yyparse();
    fclose(archivo);

    sem_resumen(errores_lex, errores_sint);
    return (resultado == 0 && errores_lex == 0 && errores_sint == 0 && sem_errores() == 0) ? 0 : 1;
}
