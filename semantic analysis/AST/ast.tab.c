/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     STRING_LETTER = 259,
     BINARY = 260,
     OCTAL = 261,
     DECIMAL = 262,
     ARY = 263,
     COMMA = 264,
     CHARACTER = 265,
     INT = 266,
     BEGIN_VARDECL = 267,
     END_VARDECL = 268,
     CHAR = 269,
     SC = 270,
     BGN = 271,
     END = 272,
     OB = 273,
     CB = 274,
     AT = 275,
     IF = 276,
     ASSIGNMENT = 277,
     ELSE = 278,
     PLUS = 279,
     MINUS = 280,
     MUL = 281,
     DIV = 282,
     MOD = 283,
     EQUAL = 284,
     GREATER = 285,
     LESSER = 286,
     GREATER_EQUAL = 287,
     LESSER_EQUAL = 288,
     NOT_EQUAL = 289,
     FOR = 290,
     DO = 291,
     TO = 292,
     INC = 293,
     DEC = 294,
     WHILE = 295,
     BEGIN_PROGRAM = 296,
     END_PROGRAM = 297,
     PRINT = 298,
     TEN = 299,
     EIGHT = 300,
     TWO = 301,
     QUOTES = 302,
     PLUS_ASSIGN = 303,
     MINUS_ASSIGN = 304,
     MUL_ASSIGN = 305,
     DIV_ASSIGN = 306,
     MOD_ASSIGN = 307,
     SCAN = 308,
     IFX = 309
   };
#endif
/* Tokens.  */
#define ID 258
#define STRING_LETTER 259
#define BINARY 260
#define OCTAL 261
#define DECIMAL 262
#define ARY 263
#define COMMA 264
#define CHARACTER 265
#define INT 266
#define BEGIN_VARDECL 267
#define END_VARDECL 268
#define CHAR 269
#define SC 270
#define BGN 271
#define END 272
#define OB 273
#define CB 274
#define AT 275
#define IF 276
#define ASSIGNMENT 277
#define ELSE 278
#define PLUS 279
#define MINUS 280
#define MUL 281
#define DIV 282
#define MOD 283
#define EQUAL 284
#define GREATER 285
#define LESSER 286
#define GREATER_EQUAL 287
#define LESSER_EQUAL 288
#define NOT_EQUAL 289
#define FOR 290
#define DO 291
#define TO 292
#define INC 293
#define DEC 294
#define WHILE 295
#define BEGIN_PROGRAM 296
#define END_PROGRAM 297
#define PRINT 298
#define TEN 299
#define EIGHT 300
#define TWO 301
#define QUOTES 302
#define PLUS_ASSIGN 303
#define MINUS_ASSIGN 304
#define MUL_ASSIGN 305
#define DIV_ASSIGN 306
#define MOD_ASSIGN 307
#define SCAN 308
#define IFX 309




/* Copy the first part of user declarations.  */
#line 1 "ast.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
ASTNode* root = NULL;
void yyerror(const char* s);
int yylex(void);
extern FILE* yyin;
extern FILE* yyout;

int scan_count=0;
int print_count=0;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 16 "ast.y"
{
    int ival;
    char* str;
    ASTNode* ast;
}
/* Line 193 of yacc.c.  */
#line 225 "ast.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 238 "ast.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   176

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNRULES -- Number of states.  */
#define YYNSTATES  176

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    12,    20,    21,    23,    25,    27,
      29,    32,    33,    35,    37,    39,    41,    43,    45,    47,
      51,    54,    55,    57,    59,    61,    70,    83,    96,    99,
     100,   102,   104,   114,   122,   126,   129,   132,   133,   137,
     138,   140,   142,   144,   152,   155,   156,   160,   161,   165,
     166,   171,   176,   181,   186,   191,   196,   201,   203,   207,
     211,   215,   219,   223,   225,   227,   233,   239,   245,   251,
     257,   263,   267,   271,   275,   279,   283,   287
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      56,     0,    -1,    41,    57,    61,    42,    -1,    12,    58,
      13,    -1,    18,    59,     9,    60,    19,    15,    58,    -1,
      -1,     3,    -1,     8,    -1,    11,    -1,    14,    -1,    62,
      61,    -1,    -1,    79,    -1,    66,    -1,    67,    -1,    70,
      -1,    63,    -1,    71,    -1,    75,    -1,    16,    64,    17,
      -1,    65,    64,    -1,    -1,    79,    -1,    71,    -1,    75,
      -1,    21,    18,    83,    19,    16,    64,    17,    15,    -1,
      21,    18,    83,    19,    16,    64,    17,    23,    16,    64,
      17,    15,    -1,    35,     3,    22,    80,    68,    69,    80,
      36,    16,    64,    17,    15,    -1,    37,    80,    -1,    -1,
      38,    -1,    39,    -1,    40,    18,    83,    19,    36,    16,
      64,    17,    15,    -1,    43,    47,    72,    47,    73,    19,
      15,    -1,    43,    19,    15,    -1,     4,    72,    -1,    20,
      72,    -1,    -1,     9,    74,    73,    -1,    -1,     3,    -1,
      82,    -1,    10,    -1,    53,    47,    76,    47,    78,    19,
      15,    -1,    20,    77,    -1,    -1,     9,    20,    77,    -1,
      -1,     9,     3,    78,    -1,    -1,     3,    22,    80,    15,
      -1,     3,    48,    80,    15,    -1,     3,    49,    80,    15,
      -1,     3,    50,    80,    15,    -1,     3,    51,    80,    15,
      -1,     3,    52,    80,    15,    -1,     3,    22,    10,    15,
      -1,    81,    -1,    81,    24,    81,    -1,    81,    25,    81,
      -1,    81,    26,    81,    -1,    81,    27,    81,    -1,    81,
      28,    81,    -1,     3,    -1,    82,    -1,    18,     7,     9,
      44,    19,    -1,    18,     6,     9,    45,    19,    -1,    18,
       5,     9,    46,    19,    -1,    18,     5,     9,    45,    19,
      -1,    18,     5,     9,    44,    19,    -1,    18,     6,     9,
      44,    19,    -1,    83,    29,    83,    -1,    83,    34,    83,
      -1,    83,    30,    83,    -1,    83,    31,    83,    -1,    83,
      32,    83,    -1,    83,    33,    83,    -1,    81,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    43,    43,    50,    53,    59,    62,    63,    66,    67,
      70,    73,    76,    77,    78,    79,    80,    81,    82,    85,
      88,    89,    92,    93,    94,    97,   100,   105,   116,   117,
     120,   121,   124,   129,   133,   136,   139,   143,   146,   150,
     153,   154,   155,   158,   164,   168,   171,   175,   178,   182,
     185,   186,   187,   188,   189,   190,   191,   194,   197,   198,
     199,   200,   201,   202,   203,   206,   207,   208,   209,   210,
     211,   214,   215,   216,   217,   218,   219,   220
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "STRING_LETTER", "BINARY", "OCTAL",
  "DECIMAL", "ARY", "COMMA", "CHARACTER", "INT", "BEGIN_VARDECL",
  "END_VARDECL", "CHAR", "SC", "BGN", "END", "OB", "CB", "AT", "IF",
  "ASSIGNMENT", "ELSE", "PLUS", "MINUS", "MUL", "DIV", "MOD", "EQUAL",
  "GREATER", "LESSER", "GREATER_EQUAL", "LESSER_EQUAL", "NOT_EQUAL", "FOR",
  "DO", "TO", "INC", "DEC", "WHILE", "BEGIN_PROGRAM", "END_PROGRAM",
  "PRINT", "TEN", "EIGHT", "TWO", "QUOTES", "PLUS_ASSIGN", "MINUS_ASSIGN",
  "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "SCAN", "IFX", "$accept",
  "program", "var_dec", "decl", "data", "type", "statements", "statement",
  "blck_stmt", "statements_1", "stmt_1", "if_stmt", "for_stmt", "to_part",
  "update", "while_stmt", "print_stmt", "str", "additional", "xyz",
  "scan_stmt", "pqr", "tuv", "additional_1", "assign", "expr", "arith",
  "int_const", "relational", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    57,    58,    58,    59,    59,    60,    60,
      61,    61,    62,    62,    62,    62,    62,    62,    62,    63,
      64,    64,    65,    65,    65,    66,    66,    67,    68,    68,
      69,    69,    70,    71,    71,    72,    72,    72,    73,    73,
      74,    74,    74,    75,    76,    76,    77,    77,    78,    78,
      79,    79,    79,    79,    79,    79,    79,    80,    81,    81,
      81,    81,    81,    81,    81,    82,    82,    82,    82,    82,
      82,    83,    83,    83,    83,    83,    83,    83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     3,     7,     0,     1,     1,     1,     1,
       2,     0,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     0,     1,     1,     1,     8,    12,    12,     2,     0,
       1,     1,     9,     7,     3,     2,     2,     0,     3,     0,
       1,     1,     1,     7,     2,     0,     3,     0,     3,     0,
       4,     4,     4,     4,     4,     4,     4,     1,     3,     3,
       3,     3,     3,     1,     1,     5,     5,     5,     5,     5,
       5,     3,     3,     3,     3,     3,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     5,    11,     1,     0,     0,     0,    21,
       0,     0,     0,     0,     0,     0,    11,    16,    13,    14,
      15,    17,    18,    12,     6,     7,     0,     3,     0,     0,
       0,     0,     0,     0,     0,    21,    23,    24,    22,     0,
       0,     0,     0,    37,    45,     2,    10,     0,    63,     0,
       0,     0,    57,    64,     0,     0,     0,     0,     0,    19,
      20,    77,     0,     0,     0,    34,    37,    37,     0,    47,
       0,     8,     9,     0,    56,     0,     0,     0,    50,     0,
       0,     0,     0,     0,    51,    52,    53,    54,    55,     0,
       0,     0,     0,     0,     0,     0,    29,     0,    35,    36,
      39,     0,    44,    49,     0,     0,     0,     0,    58,    59,
      60,    61,    62,    21,    71,    73,    74,    75,    76,    72,
       0,     0,     0,     0,     0,    47,     0,     0,     5,     0,
       0,     0,     0,     0,     0,     0,    28,    30,    31,     0,
      21,    40,    42,    39,    41,     0,    46,    49,     0,     4,
      69,    68,    67,    70,    66,    65,     0,     0,     0,    38,
      33,    48,    43,    25,     0,     0,     0,    21,    21,    32,
       0,     0,     0,     0,    26,    27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     4,     7,    26,    73,    15,    16,    17,    34,
      35,    18,    19,   121,   139,    20,    36,    68,   124,   143,
      37,    70,   102,   127,    38,    51,    52,    53,    62
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -36
static const yytype_int16 yypact[] =
{
     -26,    22,    55,    57,    53,   -36,    69,    60,   -12,    27,
      58,    25,    61,    -6,    56,    62,    53,   -36,   -36,   -36,
     -36,   -36,   -36,   -36,   -36,   -36,   101,   -36,     6,     9,
       9,     9,     9,     9,   103,    27,   -36,   -36,   -36,     9,
      99,     9,   107,     3,   104,   -36,   -36,    40,   -36,   108,
      84,   110,    88,   -36,   111,   112,   113,   114,   115,   -36,
     -36,    88,    52,     9,    68,   -36,     3,     3,    87,   122,
      89,   -36,   -36,   116,   -36,   128,   129,   130,   -36,     9,
       9,     9,     9,     9,   -36,   -36,   -36,   -36,   -36,   124,
       9,     9,     9,     9,     9,     9,   105,   109,   -36,   -36,
     132,   123,   -36,   135,   131,    63,   -23,   106,    91,    91,
     -36,   -36,   -36,    27,    12,   -36,   -36,   -36,   -36,    12,
       9,    14,   133,     8,   134,   122,   144,   136,    57,   137,
     138,   139,   140,   141,   142,   145,   -36,   -36,   -36,     9,
      27,   -36,   -36,   132,   -36,   148,   -36,   135,   149,   -36,
     -36,   -36,   -36,   -36,   -36,   -36,    10,   118,   150,   -36,
     -36,   -36,   -36,   -36,   152,   153,   151,    27,    27,   -36,
     154,   155,   158,   159,   -36,   -36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -36,   -36,   -36,    20,   -36,   -36,   160,   -36,   -36,   -35,
     -36,   -36,   -36,   -36,   -36,   -36,    13,    28,    32,   -36,
      15,   -36,    26,     5,    16,   -28,   -33,    42,   -27
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      60,    54,    55,    56,    57,    58,    61,    66,    61,    48,
      28,   141,    48,    42,    64,     1,    49,    21,   142,    22,
      23,   132,   133,    67,    50,   163,    50,    50,    40,    21,
       8,    22,    23,   164,     3,    96,    29,    30,    31,    32,
      33,    43,    91,    92,    93,    94,   108,   109,   110,   111,
     112,    71,   137,   138,    72,     5,     8,    61,    61,    61,
      61,    61,    61,   114,   115,   116,   117,   118,   119,     9,
      13,    89,    24,    27,    10,     6,    39,    25,   135,    41,
      14,    90,    91,    92,    93,    94,    95,    97,    11,    75,
      76,    77,   136,    12,    98,    99,    13,    90,    91,    92,
      93,    94,    95,    44,    45,   158,    14,   129,   130,   131,
      47,   157,    79,    80,    81,    82,    83,    81,    82,    83,
      59,    63,    65,    74,    69,    78,    84,    85,    86,    87,
      88,   101,   170,   171,   100,   104,   103,   105,   106,   107,
     113,   123,   120,   125,   126,   122,   128,   147,   149,   140,
     134,   146,   161,   145,   165,   148,   150,   151,   152,   153,
     154,   155,   156,   160,   162,   144,   169,   166,   167,   168,
       0,   172,   173,   174,   175,   159,    46
};

static const yytype_int16 yycheck[] =
{
      35,    29,    30,    31,    32,    33,    39,     4,    41,     3,
      22,     3,     3,    19,    41,    41,    10,     4,    10,     4,
       4,    44,    45,    20,    18,    15,    18,    18,     3,    16,
       3,    16,    16,    23,    12,    63,    48,    49,    50,    51,
      52,    47,    30,    31,    32,    33,    79,    80,    81,    82,
      83,    11,    38,    39,    14,     0,     3,    90,    91,    92,
      93,    94,    95,    90,    91,    92,    93,    94,    95,    16,
      43,    19,     3,    13,    21,    18,    18,     8,   113,    18,
      53,    29,    30,    31,    32,    33,    34,    19,    35,     5,
       6,     7,   120,    40,    66,    67,    43,    29,    30,    31,
      32,    33,    34,    47,    42,   140,    53,    44,    45,    46,
       9,   139,    24,    25,    26,    27,    28,    26,    27,    28,
      17,    22,    15,    15,    20,    15,    15,    15,    15,    15,
      15,     9,   167,   168,    47,    19,    47,     9,     9,     9,
      16,     9,    37,    20,     9,    36,    15,     3,   128,    16,
      44,   125,   147,    19,    36,    19,    19,    19,    19,    19,
      19,    19,    17,    15,    15,   123,    15,    17,    16,    16,
      -1,    17,    17,    15,    15,   143,    16
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    41,    56,    12,    57,     0,    18,    58,     3,    16,
      21,    35,    40,    43,    53,    61,    62,    63,    66,    67,
      70,    71,    75,    79,     3,     8,    59,    13,    22,    48,
      49,    50,    51,    52,    64,    65,    71,    75,    79,    18,
       3,    18,    19,    47,    47,    42,    61,     9,     3,    10,
      18,    80,    81,    82,    80,    80,    80,    80,    80,    17,
      64,    81,    83,    22,    83,    15,     4,    20,    72,    20,
      76,    11,    14,    60,    15,     5,     6,     7,    15,    24,
      25,    26,    27,    28,    15,    15,    15,    15,    15,    19,
      29,    30,    31,    32,    33,    34,    80,    19,    72,    72,
      47,     9,    77,    47,    19,     9,     9,     9,    81,    81,
      81,    81,    81,    16,    83,    83,    83,    83,    83,    83,
      37,    68,    36,     9,    73,    20,     9,    78,    15,    44,
      45,    46,    44,    45,    44,    64,    80,    38,    39,    69,
      16,     3,    10,    74,    82,    19,    77,     3,    19,    58,
      19,    19,    19,    19,    19,    19,    17,    80,    64,    73,
      15,    78,    15,    15,    23,    36,    17,    16,    16,    15,
      64,    64,    17,    17,    15,    15
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 43 "ast.y"
    {
    root = createProgramNode((yyvsp[(2) - (4)].ast), (yyvsp[(3) - (4)].ast));
    (yyval.ast) = root;
    printf("Successfully parsed !!!\n");
;}
    break;

  case 3:
#line 50 "ast.y"
    { (yyval.ast) = (yyvsp[(2) - (3)].ast); ;}
    break;

  case 4:
#line 53 "ast.y"
    { 
    (yyval.ast) = createStatementListNode(
        createVarDeclNode((yyvsp[(2) - (7)].ast)->data.str_value, (yyvsp[(4) - (7)].ast)),
        (yyvsp[(7) - (7)].ast)
    );
;}
    break;

  case 5:
#line 59 "ast.y"
    { (yyval.ast) = NULL; ;}
    break;

  case 6:
#line 62 "ast.y"
    { (yyval.ast) = createIDNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 7:
#line 63 "ast.y"
    { (yyval.ast) = createIDNode((yyvsp[(1) - (1)].str));;}
    break;

  case 8:
#line 66 "ast.y"
    { (yyval.ast) = createTypeNode("int"); ;}
    break;

  case 9:
#line 67 "ast.y"
    { (yyval.ast) = createTypeNode("char"); ;}
    break;

  case 10:
#line 70 "ast.y"
    { 
    (yyval.ast) = createStatementListNode((yyvsp[(1) - (2)].ast), (yyvsp[(2) - (2)].ast)); 
;}
    break;

  case 11:
#line 73 "ast.y"
    { (yyval.ast) = NULL; ;}
    break;

  case 12:
#line 76 "ast.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 13:
#line 77 "ast.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 14:
#line 78 "ast.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 15:
#line 79 "ast.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 16:
#line 80 "ast.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 17:
#line 81 "ast.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 18:
#line 82 "ast.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 19:
#line 85 "ast.y"
    { (yyval.ast) = (yyvsp[(2) - (3)].ast); ;}
    break;

  case 20:
#line 88 "ast.y"
    { (yyval.ast) = createStatementListNode((yyvsp[(1) - (2)].ast), (yyvsp[(2) - (2)].ast)); ;}
    break;

  case 21:
#line 89 "ast.y"
    { (yyval.ast) = NULL; ;}
    break;

  case 22:
#line 92 "ast.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 23:
#line 93 "ast.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 24:
#line 94 "ast.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 25:
#line 97 "ast.y"
    {
    (yyval.ast) = createIfNode((yyvsp[(3) - (8)].ast), (yyvsp[(6) - (8)].ast), NULL);
;}
    break;

  case 26:
#line 100 "ast.y"
    {
    (yyval.ast) = createIfNode((yyvsp[(3) - (12)].ast), (yyvsp[(6) - (12)].ast), (yyvsp[(10) - (12)].ast));
;}
    break;

  case 27:
#line 105 "ast.y"
    {
    (yyval.ast) = createForNode(
        createAssignNode(createIDNode((yyvsp[(2) - (12)].str)), NODE_ASSIGN, (yyvsp[(4) - (12)].ast)),
        (yyvsp[(5) - (12)].ast),
        (yyvsp[(6) - (12)].ast),
        (yyvsp[(7) - (12)].ast),
        (yyvsp[(10) - (12)].ast)
    );
;}
    break;

  case 28:
#line 116 "ast.y"
    { (yyval.ast) = (yyvsp[(2) - (2)].ast); ;}
    break;

  case 29:
#line 117 "ast.y"
    { (yyval.ast) = NULL; ;}
    break;

  case 30:
#line 120 "ast.y"
    { (yyval.ast) = createIDNode("inc"); ;}
    break;

  case 31:
#line 121 "ast.y"
    { (yyval.ast) = createIDNode("dec"); ;}
    break;

  case 32:
#line 124 "ast.y"
    {
    (yyval.ast) = createWhileNode((yyvsp[(3) - (9)].ast), (yyvsp[(7) - (9)].ast));
;}
    break;

  case 33:
#line 129 "ast.y"
    { 
    (yyval.ast) = createPrintNode((yyvsp[(3) - (7)].ast), (yyvsp[(5) - (7)].ast));
    if (print_count != 0) yyerror("PRINT STATEMENT ERROR\n");
;}
    break;

  case 34:
#line 133 "ast.y"
    { (yyval.ast) = createPrintNode(NULL, NULL); ;}
    break;

  case 35:
#line 136 "ast.y"
    { 
    (yyval.ast) = createStringConcatNode((yyvsp[(1) - (2)].str), (yyvsp[(2) - (2)].ast)); 
;}
    break;

  case 36:
#line 139 "ast.y"
    { 
    (yyval.ast) = createFormatNode((yyvsp[(2) - (2)].ast)); 
    print_count += 1;
;}
    break;

  case 37:
#line 143 "ast.y"
    { (yyval.ast) = createStringNode(""); ;}
    break;

  case 38:
#line 146 "ast.y"
    { 
    (yyval.ast) = createStatementListNode2((yyvsp[(2) - (3)].ast), (yyvsp[(3) - (3)].ast)); 
    print_count--;
;}
    break;

  case 39:
#line 150 "ast.y"
    { (yyval.ast) = NULL; ;}
    break;

  case 40:
#line 153 "ast.y"
    { (yyval.ast) = createIDNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 41:
#line 154 "ast.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 42:
#line 155 "ast.y"
    { (yyval.ast) = createCharNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 43:
#line 158 "ast.y"
    {
    (yyval.ast) = createScanNode((yyvsp[(3) - (7)].ast), (yyvsp[(5) - (7)].ast));
    if (scan_count != 0) yyerror("Invalid scan stmt");
;}
    break;

  case 44:
#line 164 "ast.y"
    { 
    (yyval.ast) = createFormatNode((yyvsp[(2) - (2)].ast));
    scan_count += 1;
;}
    break;

  case 45:
#line 168 "ast.y"
    { (yyval.ast) = createStringNode(""); ;}
    break;

  case 46:
#line 171 "ast.y"
    { 
    (yyval.ast) = createStringConcatNode((yyvsp[(1) - (3)].str), createFormatNode((yyvsp[(3) - (3)].ast))); 
    scan_count += 1;
;}
    break;

  case 47:
#line 175 "ast.y"
    { (yyval.ast) = NULL; ;}
    break;

  case 48:
#line 178 "ast.y"
    { 
    (yyval.ast) = createStatementListNode2(createIDNode((yyvsp[(2) - (3)].str)), (yyvsp[(3) - (3)].ast)); 
    scan_count -= 1;
;}
    break;

  case 49:
#line 182 "ast.y"
    { (yyval.ast) = NULL; ;}
    break;

  case 50:
#line 185 "ast.y"
    {(yyval.ast) = createAssignNode(createIDNode((yyvsp[(1) - (4)].str)), NODE_ASSIGN, (yyvsp[(3) - (4)].ast));;}
    break;

  case 51:
#line 186 "ast.y"
    {(yyval.ast) = createAssignNode(createIDNode((yyvsp[(1) - (4)].str)), NODE_ADD_ASSIGN, (yyvsp[(3) - (4)].ast));;}
    break;

  case 52:
#line 187 "ast.y"
    {(yyval.ast) = createAssignNode(createIDNode((yyvsp[(1) - (4)].str)), NODE_SUB_ASSIGN, (yyvsp[(3) - (4)].ast));;}
    break;

  case 53:
#line 188 "ast.y"
    {(yyval.ast) = createAssignNode(createIDNode((yyvsp[(1) - (4)].str)), NODE_MUL_ASSIGN, (yyvsp[(3) - (4)].ast));;}
    break;

  case 54:
#line 189 "ast.y"
    {(yyval.ast) = createAssignNode(createIDNode((yyvsp[(1) - (4)].str)), NODE_DIV_ASSIGN, (yyvsp[(3) - (4)].ast));;}
    break;

  case 55:
#line 190 "ast.y"
    {(yyval.ast) = createAssignNode(createIDNode((yyvsp[(1) - (4)].str)), NODE_MOD_ASSIGN, (yyvsp[(3) - (4)].ast));;}
    break;

  case 56:
#line 191 "ast.y"
    {(yyval.ast) = createAssignNode(createIDNode((yyvsp[(1) - (4)].str)), NODE_ASSIGN, createCharNode((yyvsp[(3) - (4)].str)));;}
    break;

  case 57:
#line 194 "ast.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 58:
#line 197 "ast.y"
    { (yyval.ast) = createOperatorNode(NODE_ADD, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 59:
#line 198 "ast.y"
    { (yyval.ast) = createOperatorNode(NODE_SUB, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 60:
#line 199 "ast.y"
    { (yyval.ast) = createOperatorNode(NODE_MUL, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 61:
#line 200 "ast.y"
    { (yyval.ast) = createOperatorNode(NODE_DIV, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 62:
#line 201 "ast.y"
    { (yyval.ast) = createOperatorNode(NODE_MOD, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 63:
#line 202 "ast.y"
    { (yyval.ast) = createIDNode((yyvsp[(1) - (1)].str)); ;}
    break;

  case 64:
#line 203 "ast.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;

  case 65:
#line 206 "ast.y"
    { (yyval.ast) = createNumberNode(atoi((yyvsp[(2) - (5)].str))); (yyval.ast)->base = 10; ;}
    break;

  case 66:
#line 207 "ast.y"
    {  (yyval.ast) = createNumberNode(strtol((yyvsp[(2) - (5)].str), NULL, 8)); (yyval.ast)->base = 8; ;}
    break;

  case 67:
#line 208 "ast.y"
    { (yyval.ast) = createNumberNode(strtol((yyvsp[(2) - (5)].str), NULL, 2)); (yyval.ast)->base = 2;;}
    break;

  case 68:
#line 209 "ast.y"
    { (yyval.ast) = createNumberNode(strtol((yyvsp[(2) - (5)].str), NULL, 8)); (yyval.ast)->base = 8;;}
    break;

  case 69:
#line 210 "ast.y"
    { (yyval.ast) = createNumberNode(strtol((yyvsp[(2) - (5)].str), NULL, 10));(yyval.ast)->base = 10; ;}
    break;

  case 70:
#line 211 "ast.y"
    { (yyval.ast) = createNumberNode(strtol((yyvsp[(2) - (5)].str), NULL, 10)); (yyval.ast)->base = 10;;}
    break;

  case 71:
#line 214 "ast.y"
    { (yyval.ast) = createOperatorNode(NODE_EQ, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 72:
#line 215 "ast.y"
    { (yyval.ast) = createOperatorNode(NODE_NEQ, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 73:
#line 216 "ast.y"
    { (yyval.ast) = createOperatorNode(NODE_GT, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 74:
#line 217 "ast.y"
    { (yyval.ast) = createOperatorNode(NODE_LT, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 75:
#line 218 "ast.y"
    { (yyval.ast) = createOperatorNode(NODE_GTE, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 76:
#line 219 "ast.y"
    { (yyval.ast) = createOperatorNode(NODE_LTE, (yyvsp[(1) - (3)].ast), (yyvsp[(3) - (3)].ast)); ;}
    break;

  case 77:
#line 220 "ast.y"
    { (yyval.ast) = (yyvsp[(1) - (1)].ast); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2011 "ast.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 223 "ast.y"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Maaf karo nhi khul rhi file tumhari\n");
        return 1;
    }

    yyparse();
    if(root) {
        printf("\nGeneralized List AST:\n");
        printAST(root);
        freeAST(root);
    }
    fclose(yyin);
    return 0;
}

void yyerror(const char* s){
    printf("Syntax Error !!!\n");
    exit(1);
}

