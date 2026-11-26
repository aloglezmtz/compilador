/* tabla_simbolos.h - Tabla de símbolos con ámbitos para SlimC */
#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

#define TIPO_ERROR  0   /* tipo desconocido: evita errores en cascada */
#define TIPO_INT    1
#define TIPO_DOUBLE 2
#define TIPO_STRING 3
#define MAX_PARAMS  16
#define ARIDAD_NA   (-1)  /* no aplica (variables) */
#define ARIDAD_VAR  (-2)  /* función variádica (printf) */

typedef enum { CLS_VARIABLE, CLS_CONSTANTE, CLS_MACRO, CLS_FUNCION, CLS_PARAMETRO } Clase;

typedef struct Simbolo {
    char nombre[64];
    Clase clase;
    int tipo;                    /* tipo de dato o tipo de retorno */
    int aridad;                  /* funciones: número de parámetros */
    int tipos_param[MAX_PARAMS]; /* funciones: tipo de cada parámetro */
    int es_const;                /* 1 si es const o macro */
    int ambito;                  /* id del ámbito donde se declaró */
    char ambito_nombre[64];
    int linea;
    int predefinido;             /* 1 = biblioteca (printf), no se imprime */
    struct Simbolo *sig;
} Simbolo;

void ts_iniciar(void);
void ts_liberar(void);
int  ts_entrar_ambito(const char *nombre);
void ts_salir_ambito(void);
void ts_volver_a_global(void);
int  ts_ambito_actual(void);
Simbolo *ts_buscar(const char *nombre);         /* visible desde el ámbito actual */
Simbolo *ts_buscar_actual(const char *nombre);  /* solo en el ámbito actual */
Simbolo *ts_insertar(const char *nombre, Clase clase, int tipo, int linea);
void ts_imprimir(void);
const char *ts_nombre_tipo(int tipo);
const char *ts_nombre_clase(Clase c);

#endif
