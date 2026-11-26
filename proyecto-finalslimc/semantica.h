/* semantica.h - Verificaciones semánticas de SlimC (compartidas por Bison y la versión manual) */
#ifndef SEMANTICA_H
#define SEMANTICA_H
#include "tabla_simbolos.h"

typedef struct { char *s; int linea; } Ident;   /* identificador con su línea */
typedef struct { int tipo; int linea; } Expr;   /* tipo de una expresión y su línea */
typedef struct { int n; int tipos[MAX_PARAMS]; } ArgList;

ArgList *arglist_nueva(void);
void arglist_agregar(ArgList *a, int tipo);

void sem_iniciar(void);
int  sem_errores(void);
void sem_error(int linea, const char *fmt, ...);

void sem_definir_macro(const char *nombre, int tipo, int linea);
void sem_definir_constante(const char *nombre, int tipo_decl, int tipo_valor, int linea);
void sem_param_pendiente(int tipo, const char *nombre, int linea);
void sem_iniciar_funcion(int tipo, const char *nombre, int linea);   /* nombre NULL = función sin nombre */
void sem_fin_funcion(void);
void sem_fin_programa(void);
void sem_entrar_bloque(void);
void sem_salir_bloque(void);

void sem_declarar_variable(int tipo, const char *nombre, int linea, int tiene_init, int tipo_init);
int  sem_usar_variable(const char *nombre, int linea);
void sem_asignar(const char *nombre, int linea, int tipo_valor);
int  sem_llamada(const char *nombre, int linea, const ArgList *args);
void sem_retorno(int tipo, int linea);

void sem_condicion_inicio(const char *sentencia);     /* "if" o "while" */
void sem_condicion_fin(int tipo, int linea);
void sem_condicion_cancelar(void);
int  sem_binaria(int t1, int t2, int linea);          /* + - * / */
int  sem_relacional(int t1, int t2, int linea);       /* < > <= >= == != && || ! */

void sem_resumen(int errores_lex, int errores_sint);
#endif
