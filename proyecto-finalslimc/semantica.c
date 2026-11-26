/* semantica.c - Análisis semántico: ámbitos, aridad, tipos (int/double), constantes,
 * condiciones y tipo de retorno. Cada función imprime sus errores con número de línea. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "semantica.h"

static int n_err = 0;
static const char *ctx_cond = NULL;      /* "if" / "while" mientras se analiza una condición */
static int  tipo_ret_actual = TIPO_INT;
static char func_actual[64] = "";
static int  tiene_main = 0;
static int  cont_bloques = 0;
static struct { int tipo; char nombre[64]; int linea; } pend[MAX_PARAMS];
static int n_pend = 0;

int sem_errores(void) { return n_err; }

void sem_error(int linea, const char *fmt, ...) {
    va_list ap;
    if (linea > 0) printf("❌ Error semántico en línea %d: ", linea);
    else           printf("❌ Error semántico: ");
    va_start(ap, fmt); vprintf(fmt, ap); va_end(ap);
    printf("\n");
    n_err++;
}

ArgList *arglist_nueva(void) {
    ArgList *a = calloc(1, sizeof(ArgList));
    if (!a) { fprintf(stderr, "Sin memoria\n"); exit(2); }
    return a;
}
void arglist_agregar(ArgList *a, int tipo) {
    if (a->n < MAX_PARAMS) a->tipos[a->n] = tipo;
    a->n++;
}

/* ¿se puede asignar un valor de tipo 'origen' a un destino de tipo 'destino'? */
static int asignable(int destino, int origen) {
    if (destino == TIPO_ERROR || origen == TIPO_ERROR) return 1;     /* ya se reportó */
    if (destino == TIPO_INT) return origen == TIPO_INT;
    if (destino == TIPO_DOUBLE) return origen == TIPO_INT || origen == TIPO_DOUBLE;
    return 0;
}

void sem_iniciar(void) {
    n_err = 0; ctx_cond = NULL; tiene_main = 0; cont_bloques = 0; n_pend = 0;
    func_actual[0] = '\0'; tipo_ret_actual = TIPO_INT;
    ts_iniciar();
    const char *libs[] = { "printf", "scanf" };            /* funciones de <stdio.h> */
    for (int i = 0; i < 2; i++) {
        Simbolo *s = ts_insertar(libs[i], CLS_FUNCION, TIPO_INT, 0);
        s->aridad = ARIDAD_VAR; s->predefinido = 1;
    }
}

/* ---- macros y constantes ---- */
void sem_definir_macro(const char *nombre, int tipo, int linea) {
    Simbolo *s = ts_buscar_actual(nombre);
    if (s) {
        if (s->clase == CLS_MACRO) sem_error(linea, "macro '%s' ya definida.", nombre);
        else sem_error(linea, "'%s' ya fue declarado en este ámbito.", nombre);
        return;
    }
    ts_insertar(nombre, CLS_MACRO, tipo, linea);
}

void sem_definir_constante(const char *nombre, int tipo_decl, int tipo_valor, int linea) {
    if (ts_buscar_actual(nombre)) {
        sem_error(linea, "'%s' ya fue declarado en este ámbito.", nombre);
        return;
    }
    if (!asignable(tipo_decl, tipo_valor))
        sem_error(linea, "tipo incompatible en la inicialización de la constante '%s' (se esperaba '%s', se recibió '%s').",
                  nombre, ts_nombre_tipo(tipo_decl), ts_nombre_tipo(tipo_valor));
    ts_insertar(nombre, CLS_CONSTANTE, tipo_decl, linea);
}

/* ---- funciones ---- */
void sem_param_pendiente(int tipo, const char *nombre, int linea) {
    if (n_pend < MAX_PARAMS) {
        pend[n_pend].tipo = tipo; pend[n_pend].linea = linea;
        strncpy(pend[n_pend].nombre, nombre, 63); pend[n_pend].nombre[63] = '\0';
        n_pend++;
    }
}

void sem_iniciar_funcion(int tipo, const char *nombre, int linea) {
    if (nombre) {
        Simbolo *f = ts_buscar_actual(nombre);
        if (f) {
            sem_error(linea, "función '%s' ya definida.", nombre);
        } else {
            f = ts_insertar(nombre, CLS_FUNCION, tipo, linea);
            f->aridad = n_pend;
            for (int i = 0; i < n_pend; i++) f->tipos_param[i] = pend[i].tipo;
            if (strcmp(nombre, "main") == 0) tiene_main = 1;
        }
    }
    ts_entrar_ambito(nombre ? nombre : "(sin nombre)");
    tipo_ret_actual = tipo;
    strncpy(func_actual, nombre ? nombre : "(sin nombre)", 63); func_actual[63] = '\0';
    cont_bloques = 0;
    for (int i = 0; i < n_pend; i++) {
        if (ts_buscar_actual(pend[i].nombre))
            sem_error(pend[i].linea, "parámetro '%s' duplicado en la función '%s'.", pend[i].nombre, func_actual);
        else
            ts_insertar(pend[i].nombre, CLS_PARAMETRO, pend[i].tipo, pend[i].linea);
    }
    n_pend = 0;
}

void sem_fin_funcion(void) {
    ts_volver_a_global();
    func_actual[0] = '\0'; ctx_cond = NULL; n_pend = 0;
}

void sem_fin_programa(void) {
    if (!tiene_main) sem_error(0, "no se encontró la función 'main'.");
}

void sem_entrar_bloque(void) {
    char nom[96];
    snprintf(nom, sizeof nom, "%s.bloque%d", func_actual[0] ? func_actual : "global", ++cont_bloques);
    ts_entrar_ambito(nom);
}
void sem_salir_bloque(void) { ts_salir_ambito(); }

/* ---- variables ---- */
void sem_declarar_variable(int tipo, const char *nombre, int linea, int tiene_init, int tipo_init) {
    if (ts_buscar_actual(nombre)) {
        sem_error(linea, "variable '%s' ya declarada en este ámbito.", nombre);
        return;
    }
    if (tiene_init && !asignable(tipo, tipo_init))
        sem_error(linea, "tipo incompatible en la inicialización de '%s' (se esperaba '%s', se recibió '%s').",
                  nombre, ts_nombre_tipo(tipo), ts_nombre_tipo(tipo_init));
    ts_insertar(nombre, CLS_VARIABLE, tipo, linea);
}

int sem_usar_variable(const char *nombre, int linea) {
    Simbolo *s = ts_buscar(nombre);
    if (!s) {
        if (ctx_cond) sem_error(linea, "variable '%s' no declarada en condición '%s'.", nombre, ctx_cond);
        else          sem_error(linea, "variable '%s' no declarada en el ámbito actual.", nombre);
        return TIPO_ERROR;
    }
    if (s->clase == CLS_FUNCION) {
        sem_error(linea, "'%s' es una función y no puede usarse como variable.", nombre);
        return TIPO_ERROR;
    }
    return s->tipo;
}

void sem_asignar(const char *nombre, int linea, int tipo_valor) {
    Simbolo *s = ts_buscar(nombre);
    if (!s) { sem_error(linea, "variable '%s' no declarada en el ámbito actual.", nombre); return; }
    if (s->clase == CLS_CONSTANTE) { sem_error(linea, "no se puede asignar un valor a la constante '%s'.", nombre); return; }
    if (s->clase == CLS_MACRO)     { sem_error(linea, "no se puede asignar un valor a la macro '%s'.", nombre); return; }
    if (s->clase == CLS_FUNCION)   { sem_error(linea, "no se puede asignar un valor a la función '%s'.", nombre); return; }
    if (!asignable(s->tipo, tipo_valor))
        sem_error(linea, "tipo incompatible en la asignación a '%s' (se esperaba '%s', se recibió '%s').",
                  nombre, ts_nombre_tipo(s->tipo), ts_nombre_tipo(tipo_valor));
}

int sem_llamada(const char *nombre, int linea, const ArgList *args) {
    Simbolo *s = ts_buscar(nombre);
    if (!s) { sem_error(linea, "función '%s' no declarada.", nombre); return TIPO_ERROR; }
    if (s->clase != CLS_FUNCION) { sem_error(linea, "'%s' no es una función.", nombre); return TIPO_ERROR; }
    if (s->aridad == ARIDAD_VAR) return s->tipo;                      /* printf: sin verificación */
    if (args->n != s->aridad) {
        sem_error(linea, "la función '%s' espera %d argumento(s), pero recibió %d.", nombre, s->aridad, args->n);
        return s->tipo;
    }
    for (int i = 0; i < args->n && i < MAX_PARAMS; i++)
        if (!asignable(s->tipos_param[i], args->tipos[i]))
            sem_error(linea, "tipo incompatible en argumento %d de '%s' (se esperaba '%s', se recibió '%s').",
                      i + 1, nombre, ts_nombre_tipo(s->tipos_param[i]), ts_nombre_tipo(args->tipos[i]));
    return s->tipo;
}

void sem_retorno(int tipo, int linea) {
    if (!func_actual[0]) return;
    if (!asignable(tipo_ret_actual, tipo))
        sem_error(linea, "tipo de retorno incompatible en '%s' (se esperaba '%s', se recibió '%s').",
                  func_actual, ts_nombre_tipo(tipo_ret_actual), ts_nombre_tipo(tipo));
}

/* ---- condiciones y expresiones ---- */
void sem_condicion_inicio(const char *sentencia) { ctx_cond = sentencia; }
void sem_condicion_cancelar(void) { ctx_cond = NULL; }
void sem_condicion_fin(int tipo, int linea) {
    const char *k = ctx_cond ? ctx_cond : "condición";
    ctx_cond = NULL;
    if (tipo == TIPO_STRING)
        sem_error(linea, "la condición del '%s' debe ser de tipo numérico (int o double).", k);
}

int sem_binaria(int t1, int t2, int linea) {
    if (t1 == TIPO_ERROR || t2 == TIPO_ERROR) return TIPO_ERROR;
    if (t1 == TIPO_STRING || t2 == TIPO_STRING) {
        sem_error(linea, "operación aritmética no válida con una cadena.");
        return TIPO_ERROR;
    }
    return (t1 == TIPO_DOUBLE || t2 == TIPO_DOUBLE) ? TIPO_DOUBLE : TIPO_INT;
}

int sem_relacional(int t1, int t2, int linea) {
    if (t1 == TIPO_STRING || t2 == TIPO_STRING)
        sem_error(linea, "comparación u operación lógica no válida con una cadena.");
    return TIPO_INT;
}

/* ---- resumen final ---- */
void sem_resumen(int errores_lex, int errores_sint) {
    ts_imprimir();
    int total = errores_lex + errores_sint + n_err;
    printf("\n=== Resumen del análisis ===\n");
    printf("Errores léxicos:     %d\n", errores_lex);
    printf("Errores sintácticos: %d\n", errores_sint);
    printf("Errores semánticos:  %d\n", n_err);
    printf("Total de errores:    %d\n", total);
    if (total == 0) printf("✅ Programa en C válido (ACCEPT).\n");
    else printf("⚠️ Análisis finalizado con %d error(es) (%d léxico(s), %d sintáctico(s), %d semántico(s)).\n",
                total, errores_lex, errores_sint, n_err);
}
