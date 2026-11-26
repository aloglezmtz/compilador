/* tabla_simbolos.c - Implementación de la tabla de símbolos con pila de ámbitos.
 * Los símbolos se conservan después de cerrar su ámbito para poder imprimir
 * la tabla completa al final; solo son visibles los de los ámbitos abiertos. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabla_simbolos.h"

#define MAX_PROF 64

static Simbolo *cabeza = NULL;          /* lista: el más nuevo primero */
static int  pila_ids[MAX_PROF];
static char pila_nombres[MAX_PROF][64];
static int  prof = 0;
static int  ultimo_id = 0;

void ts_liberar(void) {
    while (cabeza) { Simbolo *n = cabeza->sig; free(cabeza); cabeza = n; }
}

void ts_iniciar(void) {
    ts_liberar();
    prof = 1; ultimo_id = 0;
    pila_ids[0] = 0;
    strcpy(pila_nombres[0], "global");
}

int ts_entrar_ambito(const char *nombre) {
    if (prof >= MAX_PROF) return pila_ids[prof - 1];
    pila_ids[prof] = ++ultimo_id;
    strncpy(pila_nombres[prof], nombre ? nombre : "?", 63);
    pila_nombres[prof][63] = '\0';
    return pila_ids[prof++];
}

void ts_salir_ambito(void)     { if (prof > 1) prof--; }
void ts_volver_a_global(void)  { prof = 1; }
int  ts_ambito_actual(void)    { return pila_ids[prof - 1]; }

static int visible(int id) {
    for (int i = 0; i < prof; i++) if (pila_ids[i] == id) return 1;
    return 0;
}

Simbolo *ts_buscar(const char *nombre) {
    for (Simbolo *s = cabeza; s; s = s->sig)
        if (strcmp(s->nombre, nombre) == 0 && visible(s->ambito)) return s;
    return NULL;
}

Simbolo *ts_buscar_actual(const char *nombre) {
    int id = ts_ambito_actual();
    for (Simbolo *s = cabeza; s; s = s->sig)
        if (s->ambito == id && strcmp(s->nombre, nombre) == 0) return s;
    return NULL;
}

Simbolo *ts_insertar(const char *nombre, Clase clase, int tipo, int linea) {
    Simbolo *s = calloc(1, sizeof(Simbolo));
    if (!s) { fprintf(stderr, "Sin memoria\n"); exit(2); }
    strncpy(s->nombre, nombre, 63);
    s->clase = clase; s->tipo = tipo; s->aridad = ARIDAD_NA; s->linea = linea;
    s->es_const = (clase == CLS_CONSTANTE || clase == CLS_MACRO);
    s->ambito = ts_ambito_actual();
    strncpy(s->ambito_nombre, pila_nombres[prof - 1], 63);
    s->sig = cabeza; cabeza = s;
    return s;
}

const char *ts_nombre_tipo(int tipo) {
    switch (tipo) {
        case TIPO_INT: return "int";
        case TIPO_DOUBLE: return "double";
        case TIPO_STRING: return "cadena";
        default: return "?";
    }
}

const char *ts_nombre_clase(Clase c) {
    switch (c) {
        case CLS_VARIABLE: return "variable";
        case CLS_CONSTANTE: return "constante";
        case CLS_MACRO: return "macro";
        case CLS_FUNCION: return "función";
        case CLS_PARAMETRO: return "parámetro";
    }
    return "?";
}

/* Ancho en caracteres (no bytes) para alinear texto con acentos */
static int ancho(const char *s) {
    int n = 0;
    for (; *s; s++) if (((unsigned char)*s & 0xC0) != 0x80) n++;
    return n;
}
static void col(const char *s, int w) {
    printf("%s", s);
    for (int i = ancho(s); i < w; i++) putchar(' ');
    putchar(' ');
}

static void imprimir_rec(const Simbolo *s) {
    if (!s) return;
    imprimir_rec(s->sig);                    /* orden de declaración */
    if (s->predefinido) return;
    char extra[48], lin[16];
    if (s->clase == CLS_FUNCION) snprintf(extra, sizeof extra, "aridad=%d", s->aridad);
    else if (s->es_const)        snprintf(extra, sizeof extra, "const");
    else                         snprintf(extra, sizeof extra, "-");
    snprintf(lin, sizeof lin, "%d", s->linea);
    col(s->nombre, 16); col(ts_nombre_clase(s->clase), 11); col(ts_nombre_tipo(s->tipo), 8);
    col(s->ambito_nombre, 16); col(extra, 10); printf("%s\n", lin);
}

void ts_imprimir(void) {
    printf("\n=== Tabla de símbolos ===\n");
    col("Nombre", 16); col("Clase", 11); col("Tipo", 8); col("Ámbito", 16); col("Aridad/Const", 10); printf("Línea\n");
    printf("--------------------------------------------------------------------------\n");
    imprimir_rec(cabeza);
}
