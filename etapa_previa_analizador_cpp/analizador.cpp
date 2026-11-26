// ============================================================================
//  analizador.cpp  -  Analizador léxico + sintáctico para un subconjunto de C
//  Compiladores · Universidad de Guadalajara
//
//  Equivalente en C++ (sin flex/bison) de lo que el profe mostró en clase:
//      programa : lista_directivas lista_funciones funcion_main
//  Se ejecuta en terminal (Windows/Linux/macOS) con salida de color oscura.
//
//  Compilar:  g++ -std=c++17 -O2 analizador.cpp -o analizador
//  Usar:      analizador prueba.c            (salida igual que la del profe)
//             analizador --tokens prueba.c   (agrega la tabla de tokens)
//             analizador --ui prueba.c       (interfaz completa)
//             analizador --ascii prueba.c    (sin emojis, consolas viejas)
//             analizador --sin-color prueba.c
// ============================================================================
#include <cctype>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

// ---------------------------------------------------------------- tokens ----
enum Tok {
    T_EOF, T_INCLUDE, T_DEFINE, T_LIBRERIA, T_INT, T_MAIN, T_RETURN,
    T_ID, T_NUM, T_LPAREN, T_RPAREN, T_LBRACE, T_RBRACE, T_COMMA, T_SEMI,
    T_ASSIGN, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_ERROR_LEX
};

struct Token { Tok t; string lex; int line, col; };

// Nombre amigable (igual que los alias de %token en parser.y)
static string alias(Tok t, const string& lex = "") {
    switch (t) {
        case T_EOF:       return "fin de archivo";
        case T_INCLUDE:   return "directiva '#include'";
        case T_DEFINE:    return "directiva '#define'";
        case T_LIBRERIA:  return "librería '<archivo.h>'";
        case T_INT:       return "tipo 'int'";
        case T_MAIN:      return "'main'";
        case T_RETURN:    return "'return'";
        case T_ID:        return "identificador";
        case T_NUM:       return "número";
        case T_ERROR_LEX: return "carácter inválido";
        default:          return "'" + lex + "'";
    }
}
static const char* nombreTok(Tok t) {
    static const char* n[] = {"EOF","T_INCLUDE","T_DEFINE","T_LIBRERIA","T_INT","T_MAIN",
        "T_RETURN","T_ID","T_NUM","'('","')'","'{'","'}'","','","';'","'='","'+'","'-'",
        "'*'","'/'","T_ERROR_LEX"};
    return n[t];
}

// ----------------------------------------------------------- presentación ---
struct Estilo {
    bool color = true, emoji = true;
    string R() const { return color ? "\033[0m"  : ""; }
    string rojo() const { return color ? "\033[91m" : ""; }
    string verde() const { return color ? "\033[92m" : ""; }
    string amar() const { return color ? "\033[93m" : ""; }
    string cian() const { return color ? "\033[96m" : ""; }
    string mag() const { return color ? "\033[95m" : ""; }
    string gris() const { return color ? "\033[90m" : ""; }
    string neg() const { return color ? "\033[1m" : ""; }
    string ok() const { return emoji ? "\xE2\x9C\x85" : "[OK]"; }
    string mal() const { return emoji ? "\xE2\x9D\x8C" : "[ERROR]"; }
    string aviso() const { return emoji ? "\xE2\x9A\xA0\xEF\xB8\x8F" : "[AVISO]"; }
};
static Estilo E;

// ---------------------------------------------------------------- léxico ----
static int erroresLex = 0;

static vector<Token> analizarLexico(const string& s) {
    vector<Token> v;
    size_t i = 0; int line = 1, col = 1;
    auto avanza = [&](size_t n = 1) {
        for (size_t k = 0; k < n && i < s.size(); ++k, ++i) {
            if (s[i] == '\n') { line++; col = 1; } else col++;
        }
    };
    auto push = [&](Tok t, const string& lx, int l, int c) { v.push_back({t, lx, l, c}); };

    while (i < s.size()) {
        char c = s[i];
        if (isspace((unsigned char)c)) { avanza(); continue; }
        // comentarios
        if (c == '/' && i + 1 < s.size() && s[i+1] == '/') {
            while (i < s.size() && s[i] != '\n') avanza();
            continue;
        }
        if (c == '/' && i + 1 < s.size() && s[i+1] == '*') {
            int l0 = line; avanza(2);
            bool cerrado = false;
            while (i < s.size()) {
                if (s[i] == '*' && i + 1 < s.size() && s[i+1] == '/') { avanza(2); cerrado = true; break; }
                avanza();
            }
            if (!cerrado) {
                printf("%s %sError léxico en línea %d: comentario sin cerrar.%s\n",
                       E.mal().c_str(), E.rojo().c_str(), l0, E.R().c_str());
                erroresLex++;
            }
            continue;
        }
        int l0 = line, c0 = col;
        if (c == '#') {
            size_t j = i + 1;
            while (j < s.size() && isalpha((unsigned char)s[j])) j++;
            string w = s.substr(i, j - i);
            Tok t = (w == "#include") ? T_INCLUDE : (w == "#define") ? T_DEFINE : T_ERROR_LEX;
            avanza(j - i);
            if (t == T_ERROR_LEX) {
                printf("%s %sError léxico en línea %d: directiva desconocida '%s'.%s\n",
                       E.mal().c_str(), E.rojo().c_str(), l0, w.c_str(), E.R().c_str());
                erroresLex++;
            }
            push(t, w, l0, c0);
            continue;
        }
        if ((c == '<' || c == '"') && !v.empty() && v.back().t == T_INCLUDE) {
            char cierre = (c == '<') ? '>' : '"';
            size_t j = i + 1;
            while (j < s.size() && s[j] != cierre && s[j] != '\n') j++;
            if (j < s.size() && s[j] == cierre) {
                string w = s.substr(i, j - i + 1);
                avanza(j - i + 1);
                push(T_LIBRERIA, w, l0, c0);
                continue;
            }
        }
        if (isalpha((unsigned char)c) || c == '_') {
            size_t j = i;
            while (j < s.size() && (isalnum((unsigned char)s[j]) || s[j] == '_')) j++;
            string w = s.substr(i, j - i);
            Tok t = (w == "int") ? T_INT : (w == "main") ? T_MAIN : (w == "return") ? T_RETURN : T_ID;
            avanza(j - i);
            push(t, w, l0, c0);
            continue;
        }
        if (isdigit((unsigned char)c)) {
            size_t j = i;
            while (j < s.size() && isdigit((unsigned char)s[j])) j++;
            string w = s.substr(i, j - i);
            avanza(j - i);
            push(T_NUM, w, l0, c0);
            continue;
        }
        Tok t = T_ERROR_LEX;
        switch (c) {
            case '(': t = T_LPAREN; break;  case ')': t = T_RPAREN; break;
            case '{': t = T_LBRACE; break;  case '}': t = T_RBRACE; break;
            case ',': t = T_COMMA;  break;  case ';': t = T_SEMI;   break;
            case '=': t = T_ASSIGN; break;  case '+': t = T_PLUS;   break;
            case '-': t = T_MINUS;  break;  case '*': t = T_STAR;   break;
            case '/': t = T_SLASH;  break;
        }
        string w(1, c);
        avanza();
        if (t == T_ERROR_LEX) {
            printf("%s %sError léxico en línea %d: carácter inválido '%s'.%s\n",
                   E.mal().c_str(), E.rojo().c_str(), l0, w.c_str(), E.R().c_str());
            erroresLex++;
        }
        push(t, w, l0, c0);
    }
    v.push_back({T_EOF, "", line, col});
    return v;
}

// ------------------------------------------------------------- sintáctico ---
class Parser {
public:
    explicit Parser(vector<Token> t) : tk(move(t)) {
        // Los caracteres inválidos ya se reportaron en el léxico: se descartan.
        vector<Token> limpio;
        for (auto& x : tk) if (x.t != T_ERROR_LEX) limpio.push_back(x);
        tk = move(limpio);
    }
    int errores = 0;

    void programa() {
        while (cur().t == T_INCLUDE || cur().t == T_DEFINE) directiva();
        int mains = 0;
        while (cur().t == T_INT) { if (funcion()) mains++; }
        if (cur().t != T_EOF) {
            errSint("tipo 'int' o fin de archivo");
            sync();
            while (cur().t != T_EOF) {
                if (cur().t == T_INT) { if (funcion()) mains++; }
                else { advance(); }
            }
        }
        if (mains == 0) {
            printf("%s %sError: falta la función 'main'.%s\n", E.mal().c_str(), E.rojo().c_str(), E.R().c_str());
            errores++;
        }
    }

private:
    vector<Token> tk; size_t p = 0; bool panico = false;

    const Token& cur() const { return tk[p]; }
    void advance() { if (tk[p].t != T_EOF) p++; }
    bool accept(Tok t) { if (cur().t == t) { advance(); return true; } return false; }

    // Mensaje de error de línea (reglas de recuperación específicas)
    void errLinea(int linea, const string& msg) {
        printf("%s %sError línea %d: %s%s\n", E.mal().c_str(), E.rojo().c_str(), linea, msg.c_str(), E.R().c_str());
        errores++;
    }
    // Equivalente a yyerror() con %error-verbose
    void errSint(const string& esperado) {
        if (panico) return;
        const Token& t = cur();
        string lx = (t.t == T_EOF) ? "fin de archivo" : t.lex;
        printf("%s %sError sintáctico en línea %d (lexema '%s'): syntax error, unexpected %s, expecting %s%s\n",
               E.mal().c_str(), E.rojo().c_str(), t.line, lx.c_str(), alias(t.t, t.lex).c_str(),
               esperado.c_str(), E.R().c_str());
        errores++;
        panico = true;
    }
    void finSentencia() { if (!expect(T_SEMI, "';'")) sync(); }
    bool expect(Tok t, const string& desc) {
        if (accept(t)) return true;
        errSint(desc);
        return false;
    }
    // Recuperación en modo pánico: avanza hasta ';' (lo consume) o '}' / EOF
    void sync() {
        while (cur().t != T_EOF && cur().t != T_RBRACE) {
            if (cur().t == T_SEMI) { advance(); break; }
            advance();
        }
        panico = false;
    }
    void saltaLinea(int linea) { while (cur().t != T_EOF && cur().line == linea) advance(); }

    void directiva() {
        Token d = cur(); advance();
        if (d.t == T_INCLUDE) {
            if (!accept(T_LIBRERIA)) {
                errLinea(d.line, "falta el nombre de la librería '<archivo.h>' después de #include.");
                saltaLinea(d.line);
            }
        } else {
            if (cur().t != T_ID) {
                errLinea(d.line, "falta el identificador después de #define.");
                saltaLinea(d.line); return;
            }
            advance();
            if (accept(T_NUM)) return;
            if (accept(T_LPAREN)) {
                expr(); 
                if (!accept(T_RPAREN)) { errLinea(d.line, "falta ')' en el #define."); saltaLinea(d.line); }
                return;
            }
            errLinea(d.line, "falta el valor (número o expresión entre paréntesis) después del identificador en #define.");
            saltaLinea(d.line);
        }
    }

    // Devuelve true si la función es 'main'
    bool funcion() {
        Token kw = cur(); advance();            // int
        bool esMain = false;
        if (cur().t == T_ID || cur().t == T_MAIN) {
            esMain = (cur().t == T_MAIN);
            advance();
        } else {
            errLinea(kw.line, "falta el nombre (identificador) de la función después de 'int'.");
            while (cur().t != T_EOF && cur().t != T_LBRACE) {
                if (cur().t == T_INT && cur().line > kw.line) return false;
                advance();
            }
            if (cur().t == T_EOF) return false;
            bloque();
            return false;
        }
        if (!expect(T_LPAREN, "'('")) { sync(); }
        if (cur().t != T_RPAREN) {
            do {
                if (!expect(T_INT, "tipo 'int'")) break;
                if (!expect(T_ID, "identificador")) break;
            } while (accept(T_COMMA));
        }
        if (!expect(T_RPAREN, "')'")) {
            while (cur().t != T_LBRACE && cur().t != T_EOF) advance();
            panico = false;
        }
        bloque();
        return esMain;
    }

    void bloque() {
        if (!expect(T_LBRACE, "'{'")) { sync(); return; }
        while (cur().t != T_RBRACE && cur().t != T_EOF) { panico = false; sentencia(); }
        panico = false;
        expect(T_RBRACE, "'}'");
    }

    void sentencia() {
        switch (cur().t) {
            case T_INT:
                advance();
                if (!expect(T_ID, "identificador")) { sync(); return; }
                if (accept(T_ASSIGN)) expr();
                finSentencia();
                break;
            case T_RETURN:
                advance(); expr(); finSentencia();
                break;
            case T_ID:
                advance();
                if (accept(T_ASSIGN)) expr();
                else if (cur().t == T_LPAREN) llamada();
                else { errSint("'=' o '('"); sync(); return; }
                finSentencia();
                break;
            case T_SEMI:
                advance(); break;
            default:
                errSint("sentencia (declaración, asignación, llamada o 'return')");
                sync();
        }
    }

    void llamada() {                            // ya estamos en '('
        expect(T_LPAREN, "'('");
        if (cur().t != T_RPAREN) {
            do { expr(); } while (accept(T_COMMA));
        }
        expect(T_RPAREN, "')'");
    }

    static int prec(Tok t) { return (t == T_PLUS || t == T_MINUS) ? 1 : (t == T_STAR || t == T_SLASH) ? 2 : 0; }

    void expr(int minPrec = 1) {
        primario();
        while (prec(cur().t) >= minPrec && prec(cur().t) > 0) {
            int pr = prec(cur().t); advance();
            expr(pr + 1);
        }
    }
    void primario() {
        if (accept(T_NUM)) return;
        if (cur().t == T_ID) {
            advance();
            if (cur().t == T_LPAREN) llamada();
            return;
        }
        if (accept(T_LPAREN)) { expr(); expect(T_RPAREN, "')'"); return; }
        errSint("número, identificador o '('");
    }
};

// -------------------------------------------------------------- interfaz ----
static void banner() {
    string bar(70, '=');
    printf("%s%s%s\n", E.cian().c_str(), bar.c_str(), E.R().c_str());
    printf("%s%s  ANALIZADOR LÉXICO Y SINTÁCTICO  -  subconjunto de C%s\n", E.neg().c_str(), E.cian().c_str(), E.R().c_str());
    printf("%s  Compiladores - Universidad de Guadalajara%s\n", E.gris().c_str(), E.R().c_str());
    printf("%s%s%s\n", E.cian().c_str(), bar.c_str(), E.R().c_str());
}
static void mostrarCódigo(const string& src) {
    printf("\n%s-- Código fuente --%s\n", E.amar().c_str(), E.R().c_str());
    istringstream in(src); string l; int n = 1;
    while (getline(in, l)) {
        if (!l.empty() && l.back() == '\r') l.pop_back();
        printf("%s%3d%s  %s\n", E.amar().c_str(), n++, E.R().c_str(), l.c_str());
    }
}
static void mostrarTokens(const vector<Token>& v) {
    printf("\n%s-- Tokens (linea:col) --%s\n", E.amar().c_str(), E.R().c_str());
    for (auto& t : v) {
        if (t.t == T_EOF) break;
        const char* col = (t.t == T_ERROR_LEX) ? "\033[91m" : (t.t == T_ID || t.t == T_NUM) ? "\033[92m"
                         : (t.t == T_INT || t.t == T_MAIN || t.t == T_RETURN) ? "\033[95m" : "\033[96m";
        printf("%s%4d:%-3d%s  %s%-12s%s  %s\n", E.gris().c_str(), t.line, t.col, E.R().c_str(),
               E.color ? col : "", nombreTok(t.t), E.R().c_str(), t.lex.c_str());
    }
}

int main(int argc, char** argv) {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); DWORD m = 0;
    if (GetConsoleMode(h, &m)) SetConsoleMode(h, m | 0x0004);   // colores ANSI
#endif
    bool tokens = false, ui = false; string archivo;
    for (int i = 1; i < argc; ++i) {
        string a = argv[i];
        if (a == "--tokens") tokens = true;
        else if (a == "--ui") { ui = true; tokens = true; }
        else if (a == "--ascii") E.emoji = false;
        else if (a == "--sin-color") E.color = false;
        else if (a == "--ayuda" || a == "-h") {
            printf("Uso: analizador [--tokens] [--ui] [--ascii] [--sin-color] archivo.c\n"); return 0;
        } else archivo = a;
    }
    if (archivo.empty()) {
        printf("Archivo a analizar [prueba.c]: ");
        getline(cin, archivo);
        if (archivo.empty()) archivo = "prueba.c";
    }
    ifstream f(archivo, ios::binary);
    if (!f) { perror("No se pudo abrir el archivo"); return 1; }
    stringstream ss; ss << f.rdbuf();
    string src = ss.str();

    if (ui) { banner(); printf("%sArchivo:%s %s\n", E.gris().c_str(), E.R().c_str(), archivo.c_str()); mostrarCódigo(src); }

    if (ui) printf("\n%s-- Análisis --%s\n", E.amar().c_str(), E.R().c_str());
    vector<Token> v = analizarLexico(src);
    if (tokens) mostrarTokens(v);
    if (tokens) printf("\n");

    Parser p(v);
    p.programa();
    int total = p.errores + erroresLex;
    if (total == 0)
        printf("%s %sPrograma en C válido (ACCEPT).%s\n", E.ok().c_str(), E.verde().c_str(), E.R().c_str());
    else if (erroresLex == 0)
        printf("%s %sAnálisis finalizado con %d error(es) sintáctico(s).%s\n",
               E.aviso().c_str(), E.amar().c_str(), p.errores, E.R().c_str());
    else
        printf("%s %sAnálisis finalizado con %d error(es) (%d léxico(s), %d sintáctico(s)).%s\n",
               E.aviso().c_str(), E.amar().c_str(), total, erroresLex, p.errores, E.R().c_str());
    return total == 0 ? 0 : 1;
}
