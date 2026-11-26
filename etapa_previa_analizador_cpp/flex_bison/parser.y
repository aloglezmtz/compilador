%{
/* parser.y - Analizador sintáctico (bison) para un subconjunto de C
 *
 *   programa : lista_directivas lista_funciones      (debe existir una 'main')
 */
#include <stdio.h>
#include <stdlib.h>

int  yylex(void);
void yyerror(const char *s);
extern FILE *yyin;
extern int   yylineno;
extern char *yytext;

int errores     = 0;   /* errores sintácticos */
int errores_lex = 0;   /* errores léxicos (los cuenta lexer.l) */
int tiene_main  = 0;

static void error_linea(int linea, const char *msg) {
    printf("❌ Error línea %d: %s\n", linea, msg);
    errores++;
}
%}

%error-verbose

%union { int num; }

%token T_EOF 0 "fin de archivo"
%token <num> T_INCLUDE "directiva '#include'"
%token <num> T_DEFINE  "directiva '#define'"
%token T_LIBRERIA      "libreria '<archivo.h>'"
%token <num> T_INT     "tipo 'int'"
%token T_MAIN          "'main'"
%token T_RETURN        "'return'"
%token T_ID            "identificador"
%token T_NUM           "número"
%token T_ERROR_LEX     "carácter inválido"

%left '+' '-'
%left '*' '/'

%start programa

%%

programa
    : lista_directivas lista_funciones
      {
          if (!tiene_main) {
              printf("❌ Error: falta la función 'main'.\n");
              errores++;
          }
      }
    ;

lista_directivas
    : /* vacío */
    | lista_directivas directiva
    ;

directiva
    : T_INCLUDE T_LIBRERIA
    | T_INCLUDE
      { error_linea($1, "falta el nombre de la librería '<archivo.h>' después de #include."); }
    | T_DEFINE T_ID T_NUM
    | T_DEFINE T_ID '(' expresion ')'
    | T_DEFINE T_ID
      { error_linea($1, "falta el valor (número o expresión entre paréntesis) después del identificador en #define."); }
    | T_DEFINE
      { error_linea($1, "falta el identificador después de #define."); }
    ;

lista_funciones
    : funcion
    | lista_funciones funcion
    ;

funcion
    : T_INT nombre_funcion '(' parametros_opt ')' bloque
    | T_INT
      { error_linea($1, "falta el nombre (identificador) de la función después de 'int'."); }
      '(' parametros_opt ')' bloque
    ;

nombre_funcion
    : T_ID
    | T_MAIN { tiene_main = 1; }
    ;

parametros_opt
    : /* vacío */
    | lista_parametros
    ;

lista_parametros
    : T_INT T_ID
    | lista_parametros ',' T_INT T_ID
    ;

bloque
    : '{' lista_sentencias '}'
    ;

lista_sentencias
    : /* vacío */
    | lista_sentencias sentencia
    ;

sentencia
    : T_INT T_ID ';'
    | T_INT T_ID '=' expresion ';'
    | T_ID '=' expresion ';'
    | llamada ';'
    | T_RETURN expresion ';'
    | ';'
    | error ';'   { yyerrok; }
    ;

llamada
    : T_ID '(' argumentos_opt ')'
    ;

argumentos_opt
    : /* vacío */
    | lista_argumentos
    ;

lista_argumentos
    : expresion
    | lista_argumentos ',' expresion
    ;

expresion
    : T_NUM
    | T_ID
    | llamada
    | expresion '+' expresion
    | expresion '-' expresion
    | expresion '*' expresion
    | expresion '/' expresion
    | '(' expresion ')'
    ;

%%

void yyerror(const char *s) {
    printf("❌ Error sintáctico en línea %d (lexema '%s'): %s\n", yylineno, yytext, s);
    errores++;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *archivo = fopen(argv[1], "r");
        if (!archivo) {
            perror("No se pudo abrir el archivo");
            return 1;
        }
        yyin = archivo;
    }

    int resultado = yyparse();

    if (argc > 1 && yyin) fclose(yyin);

    int total = errores + errores_lex;
    if (total == 0 && resultado == 0)
        printf("✅ Programa en C válido (ACCEPT).\n");
    else if (errores_lex == 0)
        printf("⚠️ Análisis finalizado con %d error(es) sintáctico(s).\n", errores);
    else
        printf("⚠️ Análisis finalizado con %d error(es) (%d léxico(s), %d sintáctico(s)).\n",
               total, errores_lex, errores);
    return (total == 0 && resultado == 0) ? 0 : 1;
}
