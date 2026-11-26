/* slimc_manual.c - Versión de descenso recursivo en C del analizador SlimC.
 * Misma gramática y mismas verificaciones semánticas que lexer.l + parser.y
 * (comparten tabla_simbolos.c y semantica.c). Sirve como respaldo sin Flex/Bison
 * y como referencia para comparar salidas.
 *
 * Compilar: gcc slimc_manual.c tabla_simbolos.c semantica.c -o slimc_manual
 * Usar:     ./slimc_manual archivo.c        (opción --tokens muestra los tokens) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tabla_simbolos.h"
#include "semantica.h"

enum { K_EOF, K_INCLUDE, K_DEFINE, K_LIB, K_CONST, K_INT, K_DOUBLE, K_MAIN, K_RETURN, K_IF, K_ELSE,
       K_WHILE, K_ID, K_NUM, K_FLOAT, K_STR, K_EQ, K_NE, K_LE, K_GE, K_AND, K_OR, K_SYM };
static const char *K_NOM[] = { "EOF", "#include", "#define", "LIBRERIA", "const", "int", "double", "main",
    "return", "if", "else", "while", "ID", "NUM", "FLOAT", "STRING", "==", "!=", "<=", ">=", "&&", "||", "SIMBOLO" };

typedef struct { int k; char lex[160]; int linea; } Tok;
static Tok *tk = NULL; static int ntk = 0, ncap = 0, p = 0;
static int errores_lex = 0, errores_sint = 0, panico = 0;

/* ------------------------------------------------------------ léxico ---- */
static void push(int k, const char *lex, int len, int linea) {
    if (ntk == ncap) { ncap = ncap ? ncap * 2 : 256; tk = realloc(tk, ncap * sizeof(Tok)); if (!tk) exit(2); }
    if (len > 159) len = 159;
    memcpy(tk[ntk].lex, lex, len); tk[ntk].lex[len] = '\0';
    tk[ntk].k = k; tk[ntk].linea = linea; ntk++;
}

static void err_lex(int linea, const char *fmt, const char *arg) {
    printf("❌ Error léxico en línea %d: ", linea); printf(fmt, arg); printf("\n"); errores_lex++;
}

static void lex_todo(const char *s) {
    int linea = 1; const char *c = s;
    while (*c) {
        if (*c == '\n') { linea++; c++; continue; }
        if (isspace((unsigned char)*c)) { c++; continue; }
        if (c[0] == '/' && c[1] == '/') { while (*c && *c != '\n') c++; continue; }
        if (c[0] == '/' && c[1] == '*') {
            int l0 = linea, ok = 0; c += 2;
            while (*c) { if (c[0] == '*' && c[1] == '/') { c += 2; ok = 1; break; } if (*c == '\n') linea++; c++; }
            if (!ok) err_lex(l0, "comentario sin cerrar%s.", "");
            continue;
        }
        if (*c == '#') {
            const char *q = c + 1; while (isalpha((unsigned char)*q)) q++;
            int n = (int)(q - c);
            if (n == 8 && strncmp(c, "#include", 8) == 0) {
                push(K_INCLUDE, c, n, linea); c = q;
                const char *r = c; while (*r == ' ' || *r == '\t') r++;
                if (*r == '<' || *r == '"') {
                    char cierre = (*r == '<') ? '>' : '"'; const char *e = r + 1;
                    while (*e && *e != cierre && *e != '\n') e++;
                    if (*e == cierre) { push(K_LIB, r, (int)(e - r + 1), linea); c = e + 1; }
                }
            } else if (n == 7 && strncmp(c, "#define", 7) == 0) { push(K_DEFINE, c, n, linea); c = q; }
            else { char w[64]; int m = n > 63 ? 63 : n; memcpy(w, c, m); w[m] = 0; err_lex(linea, "directiva '%s' no reconocida.", w); c = q > c + 1 ? q : c + 1; }
            continue;
        }
        if (isalpha((unsigned char)*c) || *c == '_') {
            const char *q = c; while (isalnum((unsigned char)*q) || *q == '_') q++;
            int n = (int)(q - c), k = K_ID;
            if (n == 5 && !strncmp(c, "const", 5)) k = K_CONST;
            else if (n == 3 && !strncmp(c, "int", 3)) k = K_INT;
            else if (n == 6 && !strncmp(c, "double", 6)) k = K_DOUBLE;
            else if (n == 4 && !strncmp(c, "main", 4)) k = K_MAIN;
            else if (n == 6 && !strncmp(c, "return", 6)) k = K_RETURN;
            else if (n == 2 && !strncmp(c, "if", 2)) k = K_IF;
            else if (n == 4 && !strncmp(c, "else", 4)) k = K_ELSE;
            else if (n == 5 && !strncmp(c, "while", 5)) k = K_WHILE;
            push(k, c, n, linea); c = q; continue;
        }
        if (isdigit((unsigned char)*c)) {
            const char *q = c; while (isdigit((unsigned char)*q)) q++;
            int k = K_NUM;
            if (*q == '.' && isdigit((unsigned char)q[1])) { q++; while (isdigit((unsigned char)*q)) q++; k = K_FLOAT; }
            push(k, c, (int)(q - c), linea); c = q; continue;
        }
        if (*c == '"') {
            const char *q = c + 1;
            while (*q && *q != '"' && *q != '\n') { if (*q == '\\' && q[1] && q[1] != '\n') q++; q++; }
            if (*q == '"') { push(K_STR, c, (int)(q - c + 1), linea); c = q + 1; }
            else { err_lex(linea, "cadena sin cerrar%s.", ""); c = q; }
            continue;
        }
        if (c[0] == '=' && c[1] == '=') { push(K_EQ, c, 2, linea); c += 2; continue; }
        if (c[0] == '!' && c[1] == '=') { push(K_NE, c, 2, linea); c += 2; continue; }
        if (c[0] == '<' && c[1] == '=') { push(K_LE, c, 2, linea); c += 2; continue; }
        if (c[0] == '>' && c[1] == '=') { push(K_GE, c, 2, linea); c += 2; continue; }
        if (c[0] == '&' && c[1] == '&') { push(K_AND, c, 2, linea); c += 2; continue; }
        if (c[0] == '|' && c[1] == '|') { push(K_OR, c, 2, linea); c += 2; continue; }
        if (strchr("+-*/(){},;=<>!", *c)) { push(K_SYM, c, 1, linea); c++; continue; }
        { char w[2] = { *c, 0 }; err_lex(linea, "carácter inválido '%s'.", w); c++; }
    }
    push(K_EOF, "", 0, linea);
}

/* --------------------------------------------------------- sintáctico ---- */
static Tok *cur(void) { return &tk[p]; }
static void adv(void) { if (tk[p].k != K_EOF) p++; }
static int es_sym(char ch) { return cur()->k == K_SYM && cur()->lex[0] == ch; }
static int acepta_sym(char ch) { if (es_sym(ch)) { adv(); return 1; } return 0; }

static void alias(const Tok *t, char *buf) {
    switch (t->k) {
        case K_EOF: strcpy(buf, "fin de archivo"); break;
        case K_ID: strcpy(buf, "identificador"); break;
        case K_NUM: strcpy(buf, "número entero"); break;
        case K_FLOAT: strcpy(buf, "número flotante"); break;
        case K_STR: strcpy(buf, "cadena"); break;
        case K_LIB: strcpy(buf, "librería"); break;
        default: snprintf(buf, 170, "'%s'", t->lex);
    }
}
static void err_sint(const char *esperado) {
    if (panico) return;
    char a[180]; alias(cur(), a);
    printf("❌ Error sintáctico en línea %d (lexema '%s'): syntax error, unexpected %s, expecting %s\n",
           cur()->linea, cur()->k == K_EOF ? "fin de archivo" : cur()->lex, a, esperado);
    errores_sint++; panico = 1;
}
static int espera_sym(char ch) {
    if (acepta_sym(ch)) return 1;
    char e[8]; snprintf(e, sizeof e, "'%c'", ch); err_sint(e); return 0;
}
static void sync(void) {              /* modo pánico: hasta ';' o '}' */
    while (cur()->k != K_EOF && !es_sym('}')) { if (es_sym(';')) { adv(); break; } adv(); }
    panico = 0; sem_condicion_cancelar();
}
static void fin_sentencia(void) { if (!espera_sym(';')) sync(); }

static Expr expr(int minp);
static int tipo_de(const Tok *t) { return t->k == K_INT ? TIPO_INT : TIPO_DOUBLE; }
static int es_tipo(void) { return cur()->k == K_INT || cur()->k == K_DOUBLE; }

static int prec(const Tok *t) {
    switch (t->k) {
        case K_OR: return 1; case K_AND: return 2; case K_EQ: case K_NE: return 3;
        case K_LE: case K_GE: return 4;
        case K_SYM: switch (t->lex[0]) { case '<': case '>': return 4; case '+': case '-': return 5;
                                         case '*': case '/': return 6; }
    }
    return 0;
}

static Expr llamada(const char *nombre, int linea) {
    Expr r = { TIPO_ERROR, linea };
    ArgList *a = arglist_nueva();
    adv();                                              /* '(' */
    if (!es_sym(')')) { do { Expr e = expr(1); arglist_agregar(a, e.tipo); } while (acepta_sym(',')); }
    espera_sym(')');
    r.tipo = sem_llamada(nombre, linea, a); free(a);
    return r;
}

static Expr primario(void) {
    Expr e = { TIPO_ERROR, cur()->linea };
    Tok t = *cur();
    if (t.k == K_NUM) { adv(); e.tipo = TIPO_INT; return e; }
    if (t.k == K_FLOAT) { adv(); e.tipo = TIPO_DOUBLE; return e; }
    if (t.k == K_STR) { adv(); e.tipo = TIPO_STRING; return e; }
    if (t.k == K_ID) {
        adv();
        if (es_sym('(')) return llamada(t.lex, t.linea);
        e.tipo = sem_usar_variable(t.lex, t.linea); return e;
    }
    if (acepta_sym('(')) { e = expr(1); espera_sym(')'); return e; }
    if (es_sym('-')) { adv(); e = primario(); e.tipo = sem_binaria(e.tipo, TIPO_INT, e.linea); return e; }
    if (es_sym('!')) { adv(); e = primario(); e.tipo = sem_relacional(e.tipo, TIPO_INT, e.linea); return e; }
    err_sint("número, identificador o '('");
    return e;
}

static Expr expr(int minp) {
    Expr l = primario();
    while (prec(cur()) > 0 && prec(cur()) >= minp) {
        Tok op = *cur(); int pr = prec(&op); adv();
        Expr r = expr(pr + 1);
        if (op.k == K_SYM && strchr("+-*/", op.lex[0])) l.tipo = sem_binaria(l.tipo, r.tipo, l.linea);
        else l.tipo = sem_relacional(l.tipo, r.tipo, l.linea);
    }
    return l;
}

static void sentencia(void);

static void bloque(void) {
    if (!espera_sym('{')) { sync(); return; }
    sem_entrar_bloque();
    while (!es_sym('}') && cur()->k != K_EOF) { panico = 0; sentencia(); }
    panico = 0; espera_sym('}');
    sem_salir_bloque();
}

static void bloque_obligatorio(void) { if (es_sym('{')) bloque(); else { err_sint("'{'"); sync(); } }

static void condicion(const char *kw, int linea) {
    espera_sym('(');
    sem_condicion_inicio(kw);
    Expr e = expr(1);
    espera_sym(')');
    sem_condicion_fin(e.tipo, linea);
}

static void sentencia_if(void) {
    int linea = cur()->linea; adv();
    condicion("if", linea); bloque_obligatorio();
    if (cur()->k == K_ELSE) {
        adv();
        if (cur()->k == K_IF) sentencia_if(); else bloque_obligatorio();
    }
}

static void declaracion_const(void) {
    int linea = cur()->linea; adv();                    /* const */
    if (!es_tipo()) { err_sint("tipo 'int' o 'double'"); sync(); return; }
    int tipo = tipo_de(cur()); adv();
    if (cur()->k != K_ID) { err_sint("identificador"); sync(); return; }
    Tok id = *cur(); adv();
    Expr e = { TIPO_ERROR, linea };
    if (espera_sym('=')) e = expr(1);
    fin_sentencia();
    sem_definir_constante(id.lex, tipo, e.tipo, id.linea);
}

static void sentencia(void) {
    Tok t = *cur();
    if (t.k == K_CONST) { declaracion_const(); return; }
    if (t.k == K_INT || t.k == K_DOUBLE) {
        int tipo = tipo_de(&t); adv();
        if (cur()->k != K_ID) { err_sint("identificador"); sync(); return; }
        Tok id = *cur(); adv();
        Expr e = { TIPO_ERROR, id.linea }; int init = 0;
        if (acepta_sym('=')) { e = expr(1); init = 1; }
        fin_sentencia();
        sem_declarar_variable(tipo, id.lex, id.linea, init, e.tipo);
    } else if (t.k == K_RETURN) {
        adv(); Expr e = expr(1); fin_sentencia(); sem_retorno(e.tipo, t.linea);
    } else if (t.k == K_ID) {
        adv();
        if (acepta_sym('=')) { Expr e = expr(1); fin_sentencia(); sem_asignar(t.lex, t.linea, e.tipo); }
        else if (es_sym('(')) { llamada(t.lex, t.linea); fin_sentencia(); }
        else { err_sint("'=' o '('"); sync(); }
    } else if (t.k == K_IF) { sentencia_if(); }
    else if (t.k == K_WHILE) { adv(); condicion("while", t.linea); bloque_obligatorio(); }
    else if (es_sym('{')) { bloque(); }
    else if (es_sym(';')) { adv(); }
    else { err_sint("sentencia"); sync(); }
}

static void directiva(void) {
    Tok d = *cur(); adv();
    if (d.k == K_INCLUDE) {
        if (cur()->k == K_LIB) adv();
        else { printf("❌ Error línea %d: falta el nombre de la librería '<archivo.h>' después de #include.\n", d.linea); errores_sint++; }
        return;
    }
    if (cur()->k != K_ID) { printf("❌ Error línea %d: falta el identificador después de #define.\n", d.linea); errores_sint++; return; }
    Tok id = *cur(); adv();
    if (cur()->k == K_NUM || cur()->k == K_FLOAT || cur()->k == K_STR) {
        int tipo = cur()->k == K_NUM ? TIPO_INT : cur()->k == K_FLOAT ? TIPO_DOUBLE : TIPO_STRING;
        adv(); sem_definir_macro(id.lex, tipo, d.linea);
    } else if (acepta_sym('(')) {
        Expr e = expr(1); espera_sym(')'); sem_definir_macro(id.lex, e.tipo, d.linea);
    } else {
        printf("❌ Error línea %d: falta el valor (literal o expresión entre paréntesis) después del identificador en #define.\n", d.linea);
        errores_sint++;
    }
}

static void funcion(void) {
    Tok t0 = *cur(); int tipo = tipo_de(&t0); adv();
    char nombre[64] = ""; int tiene = 0, nl = t0.linea;
    if (cur()->k == K_ID || cur()->k == K_MAIN) { snprintf(nombre, sizeof nombre, "%.63s", cur()->lex); nl = cur()->linea; tiene = 1; adv(); }
    else { printf("❌ Error línea %d: falta el nombre (identificador) de la función después de '%s'.\n", t0.linea, t0.lex); errores_sint++; }
    if (!espera_sym('(')) { while (cur()->k != K_EOF && !es_sym('{')) adv(); panico = 0; }
    else {
        if (!es_sym(')')) {
            do {
                if (!es_tipo()) { err_sint("tipo 'int' o 'double'"); break; }
                int tp = tipo_de(cur()); adv();
                if (cur()->k != K_ID) { err_sint("identificador"); break; }
                sem_param_pendiente(tp, cur()->lex, cur()->linea); adv();
            } while (acepta_sym(','));
        }
        if (!espera_sym(')')) { while (cur()->k != K_EOF && !es_sym('{')) adv(); panico = 0; }
    }
    sem_iniciar_funcion(tipo, tiene ? nombre : NULL, nl);
    if (espera_sym('{')) {
        while (!es_sym('}') && cur()->k != K_EOF) { panico = 0; sentencia(); }
        panico = 0; espera_sym('}');
    } else { sync(); }
    sem_fin_funcion();
}

static void programa(void) {
    while (cur()->k == K_INCLUDE || cur()->k == K_DEFINE || cur()->k == K_CONST) {
        if (cur()->k == K_CONST) declaracion_const(); else directiva();
    }
    while (cur()->k != K_EOF) {
        if (es_tipo()) funcion();
        else { err_sint("tipo 'int' o 'double' o fin de archivo"); adv(); panico = 0; }
    }
    sem_fin_programa();
}

int main(int argc, char **argv) {
    int ver_tokens = 0; const char *archivo = NULL;
    for (int i = 1; i < argc; i++) { if (!strcmp(argv[i], "--tokens")) ver_tokens = 1; else archivo = argv[i]; }
    if (!archivo) { fprintf(stderr, "Uso: %s [--tokens] archivo.c\n", argv[0]); return 2; }
    FILE *f = fopen(archivo, "rb");
    if (!f) { perror("No se pudo abrir el archivo"); return 1; }
    fseek(f, 0, SEEK_END); long n = ftell(f); fseek(f, 0, SEEK_SET);
    char *src = malloc(n + 1); if (!src) return 2;
    size_t leidos = fread(src, 1, n, f); src[leidos] = '\0'; fclose(f);

    sem_iniciar();
    lex_todo(src);
    if (ver_tokens) {
        printf("\n=== Tokens (línea) ===\n");
        for (int i = 0; i < ntk && tk[i].k != K_EOF; i++) printf("%4d  %-9s %s\n", tk[i].linea, K_NOM[tk[i].k], tk[i].lex);
        printf("\n");
    }
    programa();
    sem_resumen(errores_lex, errores_sint);
    int ok = errores_lex + errores_sint + sem_errores() == 0;
    free(src); free(tk);
    return ok ? 0 : 1;
}
