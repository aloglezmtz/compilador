/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "parser.y"

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

#line 93 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "fin de archivo"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_INCLUDE = 3,                  /* "directiva '#include'"  */
  YYSYMBOL_T_DEFINE = 4,                   /* "directiva '#define'"  */
  YYSYMBOL_T_LIBRERIA = 5,                 /* "librería '<archivo.h>'"  */
  YYSYMBOL_T_CONST = 6,                    /* "'const'"  */
  YYSYMBOL_T_INT = 7,                      /* "tipo 'int'"  */
  YYSYMBOL_T_DOUBLE = 8,                   /* "tipo 'double'"  */
  YYSYMBOL_T_MAIN = 9,                     /* "'main'"  */
  YYSYMBOL_T_RETURN = 10,                  /* "'return'"  */
  YYSYMBOL_T_IF = 11,                      /* "'if'"  */
  YYSYMBOL_T_ELSE = 12,                    /* "'else'"  */
  YYSYMBOL_T_WHILE = 13,                   /* "'while'"  */
  YYSYMBOL_T_ID = 14,                      /* "identificador"  */
  YYSYMBOL_T_NUM = 15,                     /* "número entero"  */
  YYSYMBOL_T_FLOAT = 16,                   /* "número flotante"  */
  YYSYMBOL_T_STRING = 17,                  /* "cadena"  */
  YYSYMBOL_T_EQ = 18,                      /* "'=='"  */
  YYSYMBOL_T_NE = 19,                      /* "'!='"  */
  YYSYMBOL_T_LE = 20,                      /* "'<='"  */
  YYSYMBOL_T_GE = 21,                      /* "'>='"  */
  YYSYMBOL_T_AND = 22,                     /* "'&&'"  */
  YYSYMBOL_T_OR = 23,                      /* "'||'"  */
  YYSYMBOL_24_ = 24,                       /* '<'  */
  YYSYMBOL_25_ = 25,                       /* '>'  */
  YYSYMBOL_26_ = 26,                       /* '+'  */
  YYSYMBOL_27_ = 27,                       /* '-'  */
  YYSYMBOL_28_ = 28,                       /* '*'  */
  YYSYMBOL_29_ = 29,                       /* '/'  */
  YYSYMBOL_30_ = 30,                       /* '!'  */
  YYSYMBOL_UMENOS = 31,                    /* UMENOS  */
  YYSYMBOL_32_ = 32,                       /* '('  */
  YYSYMBOL_33_ = 33,                       /* ')'  */
  YYSYMBOL_34_ = 34,                       /* '='  */
  YYSYMBOL_35_ = 35,                       /* ';'  */
  YYSYMBOL_36_ = 36,                       /* '}'  */
  YYSYMBOL_37_ = 37,                       /* ','  */
  YYSYMBOL_38_ = 38,                       /* '{'  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_programa = 40,                  /* programa  */
  YYSYMBOL_prelude = 41,                   /* prelude  */
  YYSYMBOL_item_prelude = 42,              /* item_prelude  */
  YYSYMBOL_directiva = 43,                 /* directiva  */
  YYSYMBOL_valor_macro = 44,               /* valor_macro  */
  YYSYMBOL_declaracion_const = 45,         /* declaracion_const  */
  YYSYMBOL_tipo = 46,                      /* tipo  */
  YYSYMBOL_funciones_opt = 47,             /* funciones_opt  */
  YYSYMBOL_funcion = 48,                   /* funcion  */
  YYSYMBOL_49_1 = 49,                      /* $@1  */
  YYSYMBOL_50_2 = 50,                      /* $@2  */
  YYSYMBOL_nombre_funcion = 51,            /* nombre_funcion  */
  YYSYMBOL_parametros_opt = 52,            /* parametros_opt  */
  YYSYMBOL_lista_parametros = 53,          /* lista_parametros  */
  YYSYMBOL_parametro = 54,                 /* parametro  */
  YYSYMBOL_cuerpo_funcion = 55,            /* cuerpo_funcion  */
  YYSYMBOL_bloque = 56,                    /* bloque  */
  YYSYMBOL_57_3 = 57,                      /* $@3  */
  YYSYMBOL_lista_sentencias = 58,          /* lista_sentencias  */
  YYSYMBOL_sentencia = 59,                 /* sentencia  */
  YYSYMBOL_declaracion = 60,               /* declaracion  */
  YYSYMBOL_sentencia_if = 61,              /* sentencia_if  */
  YYSYMBOL_62_4 = 62,                      /* $@4  */
  YYSYMBOL_63_5 = 63,                      /* $@5  */
  YYSYMBOL_resto_if = 64,                  /* resto_if  */
  YYSYMBOL_sentencia_while = 65,           /* sentencia_while  */
  YYSYMBOL_66_6 = 66,                      /* $@6  */
  YYSYMBOL_67_7 = 67,                      /* $@7  */
  YYSYMBOL_llamada = 68,                   /* llamada  */
  YYSYMBOL_lista_args_opt = 69,            /* lista_args_opt  */
  YYSYMBOL_lista_args = 70,                /* lista_args  */
  YYSYMBOL_expresion = 71                  /* expresion  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   281

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  142

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   279


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    30,     2,     2,     2,     2,     2,     2,
      32,    33,    28,    26,    37,    27,     2,    29,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    35,
      24,    34,    25,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    36,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    76,    76,    81,    82,    86,    87,    91,    92,    95,
      97,    99,   102,   108,   109,   110,   114,   119,   120,   125,
     126,   131,   130,   135,   134,   140,   145,   146,   150,   151,
     155,   156,   160,   164,   168,   168,   173,   174,   178,   179,
     180,   182,   183,   185,   186,   187,   188,   189,   194,   196,
     201,   201,   201,   206,   207,   208,   212,   212,   212,   218,
     223,   224,   228,   229,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"fin de archivo\"", "error", "\"invalid token\"",
  "\"directiva '#include'\"", "\"directiva '#define'\"",
  "\"librería '<archivo.h>'\"", "\"'const'\"", "\"tipo 'int'\"",
  "\"tipo 'double'\"", "\"'main'\"", "\"'return'\"", "\"'if'\"",
  "\"'else'\"", "\"'while'\"", "\"identificador\"", "\"número entero\"",
  "\"número flotante\"", "\"cadena\"", "\"'=='\"", "\"'!='\"", "\"'<='\"",
  "\"'>='\"", "\"'&&'\"", "\"'||'\"", "'<'", "'>'", "'+'", "'-'", "'*'",
  "'/'", "'!'", "UMENOS", "'('", "')'", "'='", "';'", "'}'", "','", "'{'",
  "$accept", "programa", "prelude", "item_prelude", "directiva",
  "valor_macro", "declaracion_const", "tipo", "funciones_opt", "funcion",
  "$@1", "$@2", "nombre_funcion", "parametros_opt", "lista_parametros",
  "parametro", "cuerpo_funcion", "bloque", "$@3", "lista_sentencias",
  "sentencia", "declaracion", "sentencia_if", "$@4", "$@5", "resto_if",
  "sentencia_while", "$@6", "$@7", "llamada", "lista_args_opt",
  "lista_args", "expresion", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-124)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -124,     9,    71,  -124,    12,     0,    30,  -124,  -124,  -124,
     108,  -124,    49,  -124,  -124,     5,     6,     4,  -124,  -124,
    -124,  -124,    46,  -124,    -1,  -124,  -124,  -124,    30,    21,
      24,  -124,  -124,  -124,    46,    46,    46,  -124,   154,    46,
      56,    39,    51,  -124,    30,    46,  -124,  -124,   170,    46,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      46,  -124,    78,  -124,  -124,    30,    57,    60,    52,   218,
    -124,   252,   252,   104,   104,   242,   230,   104,   104,    20,
      20,  -124,  -124,  -124,    45,  -124,  -124,  -124,    46,  -124,
    -124,    45,   218,    33,  -124,    59,    46,    79,    80,   -31,
    -124,  -124,  -124,  -124,    96,  -124,  -124,  -124,  -124,  -124,
      99,  -124,   100,  -124,  -124,    46,  -124,    50,  -124,  -124,
      46,    46,   118,    44,    46,  -124,   186,   202,  -124,  -124,
     136,  -124,  -124,  -124,    76,    76,   137,  -124,    -3,  -124,
    -124,  -124
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,    19,     1,     8,    12,     0,     4,     5,     6,
       0,     7,    11,    17,    18,     0,     0,     0,    20,    13,
      14,    15,     0,     9,     0,    25,    27,    26,    28,     0,
      67,    64,    65,    66,     0,     0,     0,    68,     0,     0,
       0,     0,    29,    30,    28,    60,    83,    82,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    10,     0,    32,    23,     0,     0,     0,    61,    62,
      69,    78,    79,    76,    77,    80,    81,    74,    75,    70,
      71,    72,    73,    16,     0,    31,    21,    59,     0,    36,
      24,     0,    63,     0,    22,     0,     0,     0,     0,     0,
      46,    33,    34,    39,     0,    45,    37,    38,    43,    44,
       0,    47,     0,    50,    56,     0,    36,     0,    41,    42,
       0,     0,     0,     0,     0,    48,     0,     0,    40,    35,
       0,    51,    57,    49,     0,     0,    53,    58,     0,    52,
      54,    55
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -124,  -124,  -124,  -124,  -124,  -124,   146,    -6,  -124,  -124,
    -124,  -124,  -124,   106,  -124,    86,    61,  -123,  -124,    53,
    -124,  -124,    28,  -124,  -124,  -124,  -124,  -124,  -124,   -91,
    -124,  -124,   -29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     7,     8,    23,   103,    40,    10,    18,
      91,    84,    29,    41,    42,    43,    90,   105,   116,    93,
     106,   107,   108,   120,   134,   139,   109,   121,   135,    37,
      67,    68,    38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      15,    45,   110,   115,    17,    46,    47,    48,    97,     3,
      62,   136,   137,    26,    12,   140,    69,    11,    27,    24,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,   110,    39,    95,   102,    28,    13,    14,     6,
      13,    14,    25,    96,    97,    95,    98,    99,    59,    60,
       6,    13,    14,    44,    96,    97,    45,    98,    99,    92,
      30,    31,    32,    33,    19,    20,    21,   112,   100,   101,
      63,   102,    64,    34,     4,     5,    35,     6,    36,   100,
     129,    22,   102,    89,   124,   125,   122,   104,    65,    88,
      86,   126,   127,    87,   111,   130,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    -2,    16,
     117,   113,   114,    83,   102,    13,    14,   104,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      57,    58,    59,    60,   118,   119,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,     9,   138,
      66,    85,    94,   128,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,   141,     0,     0,   123,
       0,   133,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,     0,     0,     0,    61,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
       0,     0,     0,    70,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,     0,     0,     0,   131,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,     0,     0,     0,   132,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    49,    50,
      51,    52,    53,     0,    55,    56,    57,    58,    59,    60,
      49,    50,    51,    52,     0,     0,    55,    56,    57,    58,
      59,    60,    51,    52,     0,     0,    55,    56,    57,    58,
      59,    60
};

static const yytype_int16 yycheck[] =
{
       6,    32,    93,    34,    10,    34,    35,    36,    11,     0,
      39,   134,   135,     9,    14,   138,    45,     5,    14,    14,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,   123,    34,     1,    38,    32,     7,     8,     6,
       7,     8,    36,    10,    11,     1,    13,    14,    28,    29,
       6,     7,     8,    32,    10,    11,    32,    13,    14,    88,
      14,    15,    16,    17,    15,    16,    17,    96,    35,    36,
      14,    38,    33,    27,     3,     4,    30,     6,    32,    35,
      36,    32,    38,    38,    34,    35,   115,    93,    37,    37,
      33,   120,   121,    33,    35,   124,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,     0,     1,
      14,    32,    32,    35,    38,     7,     8,   123,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      26,    27,    28,    29,    35,    35,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,     2,    12,
      44,    65,    91,    35,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,   138,    -1,    -1,   116,
      -1,    35,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    -1,    33,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    -1,    33,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    -1,    33,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    -1,    33,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    18,    19,
      20,    21,    22,    -1,    24,    25,    26,    27,    28,    29,
      18,    19,    20,    21,    -1,    -1,    24,    25,    26,    27,
      28,    29,    20,    21,    -1,    -1,    24,    25,    26,    27,
      28,    29
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    40,    41,     0,     3,     4,     6,    42,    43,    45,
      47,     5,    14,     7,     8,    46,     1,    46,    48,    15,
      16,    17,    32,    44,    14,    36,     9,    14,    32,    51,
      14,    15,    16,    17,    27,    30,    32,    68,    71,    34,
      46,    52,    53,    54,    32,    32,    71,    71,    71,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    33,    71,    14,    33,    37,    52,    69,    70,    71,
      33,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    35,    50,    54,    33,    33,    37,    38,
      55,    49,    71,    58,    55,     1,    10,    11,    13,    14,
      35,    36,    38,    45,    46,    56,    59,    60,    61,    65,
      68,    35,    71,    32,    32,    34,    57,    14,    35,    35,
      62,    66,    71,    58,    34,    35,    71,    71,    35,    36,
      71,    33,    33,    35,    63,    67,    56,    56,    12,    64,
      56,    61
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    41,    42,    42,    43,    43,    43,
      43,    43,    43,    44,    44,    44,    45,    46,    46,    47,
      47,    49,    48,    50,    48,    48,    51,    51,    52,    52,
      53,    53,    54,    55,    57,    56,    58,    58,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    60,    60,
      62,    63,    61,    64,    64,    64,    66,    67,    65,    68,
      69,    69,    70,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     2,     1,     1,     2,     1,     3,
       5,     2,     1,     1,     1,     1,     6,     1,     1,     0,
       2,     0,     7,     0,     6,     2,     1,     1,     0,     1,
       1,     3,     2,     3,     0,     4,     0,     2,     1,     1,
       4,     2,     3,     1,     1,     1,     1,     2,     3,     5,
       0,     0,     8,     0,     2,     2,     0,     0,     7,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= T_EOF)
    {
      yychar = T_EOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programa: prelude funciones_opt  */
#line 76 "parser.y"
                                      { sem_fin_programa(); }
#line 1550 "parser.tab.c"
    break;

  case 8: /* directiva: "directiva '#include'"  */
#line 93 "parser.y"
        { printf("❌ Error línea %d: falta el nombre de la librería '<archivo.h>' después de #include.\n", (yyvsp[0].linea));
          errores_sint++; }
#line 1557 "parser.tab.c"
    break;

  case 9: /* directiva: "directiva '#define'" "identificador" valor_macro  */
#line 96 "parser.y"
        { sem_definir_macro((yyvsp[-1].id).s, (yyvsp[0].e).tipo, (yyvsp[-2].linea)); free((yyvsp[-1].id).s); }
#line 1563 "parser.tab.c"
    break;

  case 10: /* directiva: "directiva '#define'" "identificador" '(' expresion ')'  */
#line 98 "parser.y"
        { sem_definir_macro((yyvsp[-3].id).s, (yyvsp[-1].e).tipo, (yyvsp[-4].linea)); free((yyvsp[-3].id).s); }
#line 1569 "parser.tab.c"
    break;

  case 11: /* directiva: "directiva '#define'" "identificador"  */
#line 100 "parser.y"
        { printf("❌ Error línea %d: falta el valor (literal o expresión entre paréntesis) después del identificador en #define.\n", (yyvsp[-1].linea));
          errores_sint++; free((yyvsp[0].id).s); }
#line 1576 "parser.tab.c"
    break;

  case 12: /* directiva: "directiva '#define'"  */
#line 103 "parser.y"
        { printf("❌ Error línea %d: falta el identificador después de #define.\n", (yyvsp[0].linea));
          errores_sint++; }
#line 1583 "parser.tab.c"
    break;

  case 13: /* valor_macro: "número entero"  */
#line 108 "parser.y"
                 { (yyval.e) = (yyvsp[0].e); }
#line 1589 "parser.tab.c"
    break;

  case 14: /* valor_macro: "número flotante"  */
#line 109 "parser.y"
                 { (yyval.e) = (yyvsp[0].e); }
#line 1595 "parser.tab.c"
    break;

  case 15: /* valor_macro: "cadena"  */
#line 110 "parser.y"
                 { (yyval.e) = (yyvsp[0].e); }
#line 1601 "parser.tab.c"
    break;

  case 16: /* declaracion_const: "'const'" tipo "identificador" '=' expresion ';'  */
#line 115 "parser.y"
        { sem_definir_constante((yyvsp[-3].id).s, (yyvsp[-4].e).tipo, (yyvsp[-1].e).tipo, (yyvsp[-3].id).linea); free((yyvsp[-3].id).s); }
#line 1607 "parser.tab.c"
    break;

  case 17: /* tipo: "tipo 'int'"  */
#line 119 "parser.y"
                 { (yyval.e).tipo = TIPO_INT;    (yyval.e).linea = (yyvsp[0].linea); }
#line 1613 "parser.tab.c"
    break;

  case 18: /* tipo: "tipo 'double'"  */
#line 120 "parser.y"
                 { (yyval.e).tipo = TIPO_DOUBLE; (yyval.e).linea = (yyvsp[0].linea); }
#line 1619 "parser.tab.c"
    break;

  case 21: /* $@1: %empty  */
#line 131 "parser.y"
        { sem_iniciar_funcion((yyvsp[-4].e).tipo, (yyvsp[-3].id).s, (yyvsp[-3].id).linea); free((yyvsp[-3].id).s); }
#line 1625 "parser.tab.c"
    break;

  case 22: /* funcion: tipo nombre_funcion '(' parametros_opt ')' $@1 cuerpo_funcion  */
#line 133 "parser.y"
        { sem_fin_funcion(); }
#line 1631 "parser.tab.c"
    break;

  case 23: /* $@2: %empty  */
#line 135 "parser.y"
        { printf("❌ Error línea %d: falta el nombre (identificador) de la función después del tipo.\n", (yyvsp[-3].e).linea);
          errores_sint++;
          sem_iniciar_funcion((yyvsp[-3].e).tipo, NULL, (yyvsp[-3].e).linea); }
#line 1639 "parser.tab.c"
    break;

  case 24: /* funcion: tipo '(' parametros_opt ')' $@2 cuerpo_funcion  */
#line 139 "parser.y"
        { sem_fin_funcion(); }
#line 1645 "parser.tab.c"
    break;

  case 25: /* funcion: error '}'  */
#line 141 "parser.y"
        { ts_volver_a_global(); sem_condicion_cancelar(); yyerrok; }
#line 1651 "parser.tab.c"
    break;

  case 26: /* nombre_funcion: "identificador"  */
#line 145 "parser.y"
                 { (yyval.id) = (yyvsp[0].id); }
#line 1657 "parser.tab.c"
    break;

  case 27: /* nombre_funcion: "'main'"  */
#line 146 "parser.y"
                 { (yyval.id) = (yyvsp[0].id); }
#line 1663 "parser.tab.c"
    break;

  case 32: /* parametro: tipo "identificador"  */
#line 160 "parser.y"
                 { sem_param_pendiente((yyvsp[-1].e).tipo, (yyvsp[0].id).s, (yyvsp[0].id).linea); free((yyvsp[0].id).s); }
#line 1669 "parser.tab.c"
    break;

  case 34: /* $@3: %empty  */
#line 168 "parser.y"
          { sem_entrar_bloque(); }
#line 1675 "parser.tab.c"
    break;

  case 35: /* bloque: '{' $@3 lista_sentencias '}'  */
#line 168 "parser.y"
                                                        { sem_salir_bloque(); }
#line 1681 "parser.tab.c"
    break;

  case 40: /* sentencia: "identificador" '=' expresion ';'  */
#line 181 "parser.y"
        { sem_asignar((yyvsp[-3].id).s, (yyvsp[-3].id).linea, (yyvsp[-1].e).tipo); free((yyvsp[-3].id).s); }
#line 1687 "parser.tab.c"
    break;

  case 42: /* sentencia: "'return'" expresion ';'  */
#line 184 "parser.y"
        { sem_retorno((yyvsp[-1].e).tipo, (yyvsp[-2].linea)); }
#line 1693 "parser.tab.c"
    break;

  case 47: /* sentencia: error ';'  */
#line 190 "parser.y"
        { sem_condicion_cancelar(); yyerrok; }
#line 1699 "parser.tab.c"
    break;

  case 48: /* declaracion: tipo "identificador" ';'  */
#line 195 "parser.y"
        { sem_declarar_variable((yyvsp[-2].e).tipo, (yyvsp[-1].id).s, (yyvsp[-1].id).linea, 0, TIPO_ERROR); free((yyvsp[-1].id).s); }
#line 1705 "parser.tab.c"
    break;

  case 49: /* declaracion: tipo "identificador" '=' expresion ';'  */
#line 197 "parser.y"
        { sem_declarar_variable((yyvsp[-4].e).tipo, (yyvsp[-3].id).s, (yyvsp[-3].id).linea, 1, (yyvsp[-1].e).tipo); free((yyvsp[-3].id).s); }
#line 1711 "parser.tab.c"
    break;

  case 50: /* $@4: %empty  */
#line 201 "parser.y"
               { sem_condicion_inicio("if"); }
#line 1717 "parser.tab.c"
    break;

  case 51: /* $@5: %empty  */
#line 201 "parser.y"
                                                             { sem_condicion_fin((yyvsp[-1].e).tipo, (yyvsp[-4].linea)); }
#line 1723 "parser.tab.c"
    break;

  case 56: /* $@6: %empty  */
#line 212 "parser.y"
                  { sem_condicion_inicio("while"); }
#line 1729 "parser.tab.c"
    break;

  case 57: /* $@7: %empty  */
#line 212 "parser.y"
                                                                   { sem_condicion_fin((yyvsp[-1].e).tipo, (yyvsp[-4].linea)); }
#line 1735 "parser.tab.c"
    break;

  case 59: /* llamada: "identificador" '(' lista_args_opt ')'  */
#line 219 "parser.y"
        { (yyval.e).tipo = sem_llamada((yyvsp[-3].id).s, (yyvsp[-3].id).linea, (yyvsp[-1].args)); (yyval.e).linea = (yyvsp[-3].id).linea; free((yyvsp[-3].id).s); free((yyvsp[-1].args)); }
#line 1741 "parser.tab.c"
    break;

  case 60: /* lista_args_opt: %empty  */
#line 223 "parser.y"
                     { (yyval.args) = arglist_nueva(); }
#line 1747 "parser.tab.c"
    break;

  case 61: /* lista_args_opt: lista_args  */
#line 224 "parser.y"
                    { (yyval.args) = (yyvsp[0].args); }
#line 1753 "parser.tab.c"
    break;

  case 62: /* lista_args: expresion  */
#line 228 "parser.y"
                                 { (yyval.args) = arglist_nueva(); arglist_agregar((yyval.args), (yyvsp[0].e).tipo); }
#line 1759 "parser.tab.c"
    break;

  case 63: /* lista_args: lista_args ',' expresion  */
#line 229 "parser.y"
                                 { arglist_agregar((yyvsp[-2].args), (yyvsp[0].e).tipo); (yyval.args) = (yyvsp[-2].args); }
#line 1765 "parser.tab.c"
    break;

  case 64: /* expresion: "número entero"  */
#line 233 "parser.y"
                                 { (yyval.e) = (yyvsp[0].e); }
#line 1771 "parser.tab.c"
    break;

  case 65: /* expresion: "número flotante"  */
#line 234 "parser.y"
                                 { (yyval.e) = (yyvsp[0].e); }
#line 1777 "parser.tab.c"
    break;

  case 66: /* expresion: "cadena"  */
#line 235 "parser.y"
                                 { (yyval.e) = (yyvsp[0].e); }
#line 1783 "parser.tab.c"
    break;

  case 67: /* expresion: "identificador"  */
#line 236 "parser.y"
                                 { (yyval.e).tipo = sem_usar_variable((yyvsp[0].id).s, (yyvsp[0].id).linea); (yyval.e).linea = (yyvsp[0].id).linea; free((yyvsp[0].id).s); }
#line 1789 "parser.tab.c"
    break;

  case 68: /* expresion: llamada  */
#line 237 "parser.y"
                                 { (yyval.e) = (yyvsp[0].e); }
#line 1795 "parser.tab.c"
    break;

  case 69: /* expresion: '(' expresion ')'  */
#line 238 "parser.y"
                                 { (yyval.e) = (yyvsp[-1].e); }
#line 1801 "parser.tab.c"
    break;

  case 70: /* expresion: expresion '+' expresion  */
#line 239 "parser.y"
                                 { (yyval.e).tipo = sem_binaria((yyvsp[-2].e).tipo, (yyvsp[0].e).tipo, (yyvsp[-2].e).linea);    (yyval.e).linea = (yyvsp[-2].e).linea; }
#line 1807 "parser.tab.c"
    break;

  case 71: /* expresion: expresion '-' expresion  */
#line 240 "parser.y"
                                 { (yyval.e).tipo = sem_binaria((yyvsp[-2].e).tipo, (yyvsp[0].e).tipo, (yyvsp[-2].e).linea);    (yyval.e).linea = (yyvsp[-2].e).linea; }
#line 1813 "parser.tab.c"
    break;

  case 72: /* expresion: expresion '*' expresion  */
#line 241 "parser.y"
                                 { (yyval.e).tipo = sem_binaria((yyvsp[-2].e).tipo, (yyvsp[0].e).tipo, (yyvsp[-2].e).linea);    (yyval.e).linea = (yyvsp[-2].e).linea; }
#line 1819 "parser.tab.c"
    break;

  case 73: /* expresion: expresion '/' expresion  */
#line 242 "parser.y"
                                 { (yyval.e).tipo = sem_binaria((yyvsp[-2].e).tipo, (yyvsp[0].e).tipo, (yyvsp[-2].e).linea);    (yyval.e).linea = (yyvsp[-2].e).linea; }
#line 1825 "parser.tab.c"
    break;

  case 74: /* expresion: expresion '<' expresion  */
#line 243 "parser.y"
                                 { (yyval.e).tipo = sem_relacional((yyvsp[-2].e).tipo, (yyvsp[0].e).tipo, (yyvsp[-2].e).linea); (yyval.e).linea = (yyvsp[-2].e).linea; }
#line 1831 "parser.tab.c"
    break;

  case 75: /* expresion: expresion '>' expresion  */
#line 244 "parser.y"
                                 { (yyval.e).tipo = sem_relacional((yyvsp[-2].e).tipo, (yyvsp[0].e).tipo, (yyvsp[-2].e).linea); (yyval.e).linea = (yyvsp[-2].e).linea; }
#line 1837 "parser.tab.c"
    break;

  case 76: /* expresion: expresion "'<='" expresion  */
#line 245 "parser.y"
                                 { (yyval.e).tipo = sem_relacional((yyvsp[-2].e).tipo, (yyvsp[0].e).tipo, (yyvsp[-2].e).linea); (yyval.e).linea = (yyvsp[-2].e).linea; }
#line 1843 "parser.tab.c"
    break;

  case 77: /* expresion: expresion "'>='" expresion  */
#line 246 "parser.y"
                                 { (yyval.e).tipo = sem_relacional((yyvsp[-2].e).tipo, (yyvsp[0].e).tipo, (yyvsp[-2].e).linea); (yyval.e).linea = (yyvsp[-2].e).linea; }
#line 1849 "parser.tab.c"
    break;

  case 78: /* expresion: expresion "'=='" expresion  */
#line 247 "parser.y"
                                 { (yyval.e).tipo = sem_relacional((yyvsp[-2].e).tipo, (yyvsp[0].e).tipo, (yyvsp[-2].e).linea); (yyval.e).linea = (yyvsp[-2].e).linea; }
#line 1855 "parser.tab.c"
    break;

  case 79: /* expresion: expresion "'!='" expresion  */
#line 248 "parser.y"
                                 { (yyval.e).tipo = sem_relacional((yyvsp[-2].e).tipo, (yyvsp[0].e).tipo, (yyvsp[-2].e).linea); (yyval.e).linea = (yyvsp[-2].e).linea; }
#line 1861 "parser.tab.c"
    break;

  case 80: /* expresion: expresion "'&&'" expresion  */
#line 249 "parser.y"
                                 { (yyval.e).tipo = sem_relacional((yyvsp[-2].e).tipo, (yyvsp[0].e).tipo, (yyvsp[-2].e).linea); (yyval.e).linea = (yyvsp[-2].e).linea; }
#line 1867 "parser.tab.c"
    break;

  case 81: /* expresion: expresion "'||'" expresion  */
#line 250 "parser.y"
                                 { (yyval.e).tipo = sem_relacional((yyvsp[-2].e).tipo, (yyvsp[0].e).tipo, (yyvsp[-2].e).linea); (yyval.e).linea = (yyvsp[-2].e).linea; }
#line 1873 "parser.tab.c"
    break;

  case 82: /* expresion: '!' expresion  */
#line 251 "parser.y"
                                 { (yyval.e).tipo = sem_relacional((yyvsp[0].e).tipo, TIPO_INT, (yyvsp[0].e).linea); (yyval.e).linea = (yyvsp[0].e).linea; }
#line 1879 "parser.tab.c"
    break;

  case 83: /* expresion: '-' expresion  */
#line 252 "parser.y"
                                 { (yyval.e).tipo = sem_binaria((yyvsp[0].e).tipo, TIPO_INT, (yyvsp[0].e).linea);    (yyval.e).linea = (yyvsp[0].e).linea; }
#line 1885 "parser.tab.c"
    break;


#line 1889 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= T_EOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == T_EOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 255 "parser.y"


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
