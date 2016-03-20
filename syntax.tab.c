/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 3 "syntax.y"

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <assert.h>
	#include "semantic.h"

	#define YYSTYPE Node* //不加这个在添加 %locations后YYSTYPE类型会变化

	Node* create_tree(Node* s);
	Node* add_Node1(Node* s1, char* str, int type);
    Node* add_Node2(Node* s1, Node* s2, char* str, int type);
	Node* add_Node3(Node* s1, Node* s2, Node* s3, char* str, int type);
	Node* add_Node4(Node* s1, Node* s2, Node* s3, Node* s4, char* str, int type);
	Node* add_Node5(Node* s1, Node* s2, Node* s3, Node* s4, Node* s5, char* str, int type);
	Node* add_Node7(Node* s1, Node* s2, Node* s3, Node* s4, Node* s5, Node* s6, Node* s7, char* str, int type);
	void traversal(Node* root, int n);
	void sem_traversal(Node* root);

	extern sem_helper sem_func_table[FT_SIZE];
	extern int ano_num;

	int synright = 1;//标志语法分析中是否有错误产生, 错误恢复也算作有错误，用于此时不输出语法分析树
	Node* root;



/* Line 268 of yacc.c  */
#line 99 "syntax.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     FLOAT = 259,
     ID = 260,
     PLUS = 261,
     MINUS = 262,
     STAR = 263,
     DIV = 264,
     SEMI = 265,
     COMMA = 266,
     ASSIGNOP = 267,
     RELOP = 268,
     AND = 269,
     OR = 270,
     DOT = 271,
     NOT = 272,
     TYPE = 273,
     LP = 274,
     RP = 275,
     LB = 276,
     RB = 277,
     LC = 278,
     RC = 279,
     STRUCT = 280,
     RETURN = 281,
     IF = 282,
     ELSE = 283,
     WHILE = 284,
     LOWER_THAN_ELSE = 285
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 184 "syntax.tab.c"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   250

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNRULES -- Number of states.  */
#define YYNSTATES  128

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    13,    16,    20,    24,
      27,    31,    33,    37,    39,    41,    47,    50,    51,    53,
      55,    57,    62,    67,    71,    75,    77,    80,    85,    86,
      89,    92,    94,    98,   104,   112,   118,   121,   124,   127,
     130,   133,   136,   137,   140,   144,   148,   150,   154,   158,
     160,   164,   168,   172,   176,   180,   184,   188,   192,   196,
     200,   203,   206,   211,   215,   220,   224,   226,   228,   230,
     235,   238,   242
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      32,     0,    -1,    33,    -1,    -1,    34,    33,    -1,    36,
      35,    10,    -1,    36,    10,    -1,    36,    41,    44,    -1,
      36,     1,    10,    -1,    36,     1,    -1,    36,    35,     1,
      -1,    40,    -1,    40,    11,    35,    -1,    18,    -1,    37,
      -1,    25,    38,    23,    47,    24,    -1,    25,    39,    -1,
      -1,     5,    -1,     5,    -1,     5,    -1,    40,    21,     3,
      22,    -1,     5,    19,    42,    20,    -1,     5,    19,    20,
      -1,    43,    11,    42,    -1,    43,    -1,    36,    40,    -1,
      23,    47,    45,    24,    -1,    -1,    46,    45,    -1,    51,
      10,    -1,    44,    -1,    26,    51,    10,    -1,    27,    19,
      51,    20,    46,    -1,    27,    19,    51,    20,    46,    28,
      46,    -1,    29,    19,    51,    20,    46,    -1,    51,     1,
      -1,     1,    10,    -1,     1,    28,    -1,     1,    27,    -1,
       1,    29,    -1,     1,    26,    -1,    -1,    48,    47,    -1,
      36,    49,    10,    -1,    36,     1,    10,    -1,    50,    -1,
      50,    11,    49,    -1,    50,     1,    49,    -1,    40,    -1,
      40,    12,    51,    -1,    51,    12,    51,    -1,    51,    14,
      51,    -1,    51,    15,    51,    -1,    51,    13,    51,    -1,
      51,     6,    51,    -1,    51,     7,    51,    -1,    51,     8,
      51,    -1,    51,     9,    51,    -1,    19,    51,    20,    -1,
       7,    51,    -1,    17,    51,    -1,     5,    19,    52,    20,
      -1,     5,    19,    20,    -1,    51,    21,    51,    22,    -1,
      51,    16,     5,    -1,     5,    -1,     3,    -1,     4,    -1,
      51,    21,    51,     1,    -1,     1,    20,    -1,    51,    11,
      52,    -1,    51,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    55,    55,    59,    60,    62,    63,    64,    65,    66,
      67,    69,    70,    74,    75,    77,    78,    80,    81,    83,
      87,    88,    90,    91,    93,    94,    96,   100,   102,   103,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   119,   120,   122,   123,   125,   126,   127,   129,
     130,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   154,   155
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "ID", "PLUS", "MINUS",
  "STAR", "DIV", "SEMI", "COMMA", "ASSIGNOP", "RELOP", "AND", "OR", "DOT",
  "NOT", "TYPE", "LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN",
  "IF", "ELSE", "WHILE", "LOWER_THAN_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", 0
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
     285
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    34,    34,
      34,    35,    35,    36,    36,    37,    37,    38,    38,    39,
      40,    40,    41,    41,    42,    42,    43,    44,    45,    45,
      46,    46,    46,    46,    46,    46,    46,    46,    46,    46,
      46,    46,    47,    47,    48,    48,    49,    49,    49,    50,
      50,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    52,    52
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     3,     3,     2,
       3,     1,     3,     1,     1,     5,     2,     0,     1,     1,
       1,     4,     4,     3,     3,     1,     2,     4,     0,     2,
       2,     1,     3,     5,     7,     5,     2,     2,     2,     2,
       2,     2,     0,     2,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     4,     3,     4,     3,     1,     1,     1,     4,
       2,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    13,    17,     0,     2,     3,     0,    14,    19,     0,
      16,     1,     4,     9,    20,     6,     0,    11,     0,    42,
       8,     0,    10,     5,     0,     0,    42,     7,     0,     0,
      42,    23,     0,     0,    25,    20,    12,     0,     0,     0,
      49,     0,     0,    15,    43,    26,    22,     0,    21,     0,
      67,    68,    66,     0,     0,     0,     0,     0,     0,    31,
       0,     0,     0,    45,     0,    44,     0,     0,    24,    37,
      70,    41,    39,    38,    40,     0,     0,    60,    61,     0,
       0,     0,     0,    27,    29,    36,     0,     0,     0,     0,
      30,     0,     0,     0,     0,     0,     0,    50,    48,    47,
      63,    72,     0,    59,    32,     0,     0,    55,    56,    57,
      58,    51,    54,    52,    53,    65,     0,     0,    62,     0,
       0,    69,    64,    71,    33,    35,     0,    34
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    16,    28,     7,     9,    10,    40,
      18,    33,    34,    59,    60,    61,    29,    30,    41,    42,
      62,   102
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -54
static const yytype_int16 yypact[] =
{
       1,   -54,     2,    24,   -54,     1,     5,   -54,    19,    40,
     -54,   -54,   -54,    58,    57,   -54,    11,    16,    55,     1,
     -54,   104,   -54,   -54,    77,   103,     1,   -54,    48,    88,
       1,   -54,    77,    93,   112,   -54,   -54,    92,    43,   115,
      33,   116,    64,   -54,   -54,   106,   -54,     1,   -54,   110,
     -54,   -54,   109,    13,    13,    13,    13,   113,   125,   -54,
     111,    43,    95,   -54,    13,   -54,    77,    77,   -54,   -54,
     -54,   -54,   -54,   -54,   -54,   114,   131,   229,    -8,   134,
     150,    13,    13,   -54,   -54,   -54,    13,    13,    13,    13,
     -54,    13,    13,    13,    13,   140,    13,   204,   -54,   -54,
     -54,   161,   132,   -54,   -54,   172,   188,   229,   229,    -8,
      -8,   204,   226,   215,   215,   -54,    78,    13,   -54,    54,
      54,   -54,   -54,   -54,   133,   -54,    54,   -54
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -54,   -54,   148,   -54,   159,     4,   -54,   -54,   -54,    -1,
     -54,   142,   -54,   173,   129,   -31,    26,   -54,    31,   -54,
     -53,    81
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -47
static const yytype_int8 yytable[] =
{
      77,    78,    79,    80,     6,    17,    13,     8,    95,     6,
      14,    97,    22,    96,    76,    15,    50,    51,    52,     1,
      53,    23,   101,    17,    11,    32,     2,    24,   105,   106,
      54,    45,    55,   107,   108,   109,   110,    25,   111,   112,
     113,   114,   -18,   116,    49,    64,    50,    51,    52,    39,
      53,    32,    38,    35,    25,    49,    44,    50,    51,    52,
      54,    53,    55,    19,   101,    66,    26,   -28,    20,    56,
      57,    54,    58,    55,   -46,    67,    21,    26,    26,   121,
      56,    57,    35,    58,    86,    87,    88,    89,   124,   125,
      91,    92,    93,    94,    95,   127,    85,    98,    99,    96,
     122,    86,    87,    88,    89,    90,    37,    91,    92,    93,
      94,    95,    43,    46,    48,    76,    96,    50,    51,    52,
      69,    53,     1,    47,    31,    63,    65,    25,    75,     2,
      70,    54,    81,    55,   100,    83,    71,    72,    73,    74,
      86,    87,    88,    89,    82,   115,    91,    92,    93,    94,
      95,    70,   118,    12,   103,    96,    86,    87,    88,    89,
     104,   126,    91,    92,    93,    94,    95,    86,    87,    88,
      89,    96,   117,    91,    92,    93,    94,    95,    86,    87,
      88,    89,    96,    36,    91,    92,    93,    94,    95,    68,
      84,    27,   119,    96,    86,    87,    88,    89,   123,     0,
      91,    92,    93,    94,    95,     0,     0,     0,   120,    96,
      86,    87,    88,    89,     0,     0,    91,    92,    93,    94,
      95,    86,    87,    88,    89,    96,     0,     0,    92,     0,
       0,    95,    86,    87,    88,    89,    96,    88,    89,     0,
       0,     0,    95,     0,     0,    95,     0,    96,     0,     0,
      96
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-54))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      53,    54,    55,    56,     0,     6,     1,     5,    16,     5,
       5,    64,     1,    21,     1,    10,     3,     4,     5,    18,
       7,    10,    75,    24,     0,    21,    25,    11,    81,    82,
      17,    32,    19,    86,    87,    88,    89,    21,    91,    92,
      93,    94,    23,    96,     1,    12,     3,     4,     5,     1,
       7,    47,    26,     5,    21,     1,    30,     3,     4,     5,
      17,     7,    19,    23,   117,     1,    23,    24,    10,    26,
      27,    17,    29,    19,    10,    11,    19,    23,    23,     1,
      26,    27,     5,    29,     6,     7,     8,     9,   119,   120,
      12,    13,    14,    15,    16,   126,     1,    66,    67,    21,
      22,     6,     7,     8,     9,    10,     3,    12,    13,    14,
      15,    16,    24,    20,    22,     1,    21,     3,     4,     5,
      10,     7,    18,    11,    20,    10,    10,    21,    19,    25,
      20,    17,    19,    19,    20,    24,    26,    27,    28,    29,
       6,     7,     8,     9,    19,     5,    12,    13,    14,    15,
      16,    20,    20,     5,    20,    21,     6,     7,     8,     9,
      10,    28,    12,    13,    14,    15,    16,     6,     7,     8,
       9,    21,    11,    12,    13,    14,    15,    16,     6,     7,
       8,     9,    21,    24,    12,    13,    14,    15,    16,    47,
      61,    18,    20,    21,     6,     7,     8,     9,   117,    -1,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    20,    21,
       6,     7,     8,     9,    -1,    -1,    12,    13,    14,    15,
      16,     6,     7,     8,     9,    21,    -1,    -1,    13,    -1,
      -1,    16,     6,     7,     8,     9,    21,     8,     9,    -1,
      -1,    -1,    16,    -1,    -1,    16,    -1,    21,    -1,    -1,
      21
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    25,    32,    33,    34,    36,    37,     5,    38,
      39,     0,    33,     1,     5,    10,    35,    40,    41,    23,
      10,    19,     1,    10,    11,    21,    23,    44,    36,    47,
      48,    20,    36,    42,    43,     5,    35,     3,    47,     1,
      40,    49,    50,    24,    47,    40,    20,    11,    22,     1,
       3,     4,     5,     7,    17,    19,    26,    27,    29,    44,
      45,    46,    51,    10,    12,    10,     1,    11,    42,    10,
      20,    26,    27,    28,    29,    19,     1,    51,    51,    51,
      51,    19,    19,    24,    45,     1,     6,     7,     8,     9,
      10,    12,    13,    14,    15,    16,    21,    51,    49,    49,
      20,    51,    52,    20,    10,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,     5,    51,    11,    20,    20,
      20,     1,    22,    52,    46,    46,    28,    46
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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
		  Type, Value, Location); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 55 "syntax.y"
    {
		root = (yyval) = create_tree((yyvsp[(1) - (1)]));
		}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 59 "syntax.y"
    {(yyval) = NULL;}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 60 "syntax.y"
    {(yyval) = add_Node2((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), "ExtDefList", 1);}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 62 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "ExtDef", 2);}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 63 "syntax.y"
    {(yyval) = add_Node2((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), "ExtDef", 3);}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 64 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "ExtDef", 4);}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 65 "syntax.y"
    {}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 66 "syntax.y"
    {}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 67 "syntax.y"
    {}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 69 "syntax.y"
    {(yyval) = add_Node1((yyvsp[(1) - (1)]), "ExtDecList", 5);}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 70 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "ExtDecList", 6);}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 74 "syntax.y"
    {(yyval) = add_Node1((yyvsp[(1) - (1)]), "Specifier", 7);}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 75 "syntax.y"
    {(yyval) = add_Node1((yyvsp[(1) - (1)]), "Specifier", 8);}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 77 "syntax.y"
    {(yyval) = add_Node5((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]), "StructSpecifier", 9);}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 78 "syntax.y"
    {(yyval) = add_Node2((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), "StructSpecifier", 0xa);}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 80 "syntax.y"
    {(yyval) = NULL;}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 81 "syntax.y"
    {(yyval) = add_Node1((yyvsp[(1) - (1)]), "OptTag", 0xb);}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 83 "syntax.y"
    {(yyval) = add_Node1((yyvsp[(1) - (1)]), "Tag", 0xc);}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 87 "syntax.y"
    {(yyval) = add_Node1((yyvsp[(1) - (1)]), "VarDec", 0xd);}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 88 "syntax.y"
    {(yyval) = add_Node4((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), "VarDec", 0xe);}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 90 "syntax.y"
    {(yyval) = add_Node4((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), "FunDec", 0xf);}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 91 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "FunDec", 0x10);}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 93 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "VarList", 0x11);}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 94 "syntax.y"
    {(yyval) = add_Node1((yyvsp[(1) - (1)]), "VarList", 0x12);}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 96 "syntax.y"
    {(yyval) = add_Node2((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), "ParamDec", 0x13);}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 100 "syntax.y"
    {(yyval) = add_Node4((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), "CompSt", 0x14);}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 102 "syntax.y"
    {(yyval) = NULL;}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 103 "syntax.y"
    {(yyval) = add_Node2((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), "StmtList", 0x15);}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 105 "syntax.y"
    {(yyval) = add_Node2((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), "Stmt", 0x16);}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 106 "syntax.y"
    {(yyval) = add_Node1((yyvsp[(1) - (1)]), "Stmt", 0x17);}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 107 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "Stmt", 0x18);}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 108 "syntax.y"
    {(yyval) = add_Node5((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]), "Stmt", 0x19);}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 109 "syntax.y"
    {(yyval) = add_Node7((yyvsp[(1) - (7)]), (yyvsp[(2) - (7)]), (yyvsp[(3) - (7)]), (yyvsp[(4) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)]), "Stmt", 0x1a);}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 110 "syntax.y"
    {(yyval) = add_Node5((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(3) - (5)]), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]), "Stmt", 0x1b);}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 111 "syntax.y"
    {}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 112 "syntax.y"
    {}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 113 "syntax.y"
    {}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 114 "syntax.y"
    {}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 115 "syntax.y"
    {}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 116 "syntax.y"
    {}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 119 "syntax.y"
    {(yyval) = NULL;}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 120 "syntax.y"
    {(yyval) = add_Node2((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), "DefList", 0x1c);}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 122 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "Def", 0x1d);}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 123 "syntax.y"
    {}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 125 "syntax.y"
    {(yyval) = add_Node1((yyvsp[(1) - (1)]), "DecList", 0x1e);}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 126 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "DecList", 0x1f);}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 127 "syntax.y"
    {}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 129 "syntax.y"
    {(yyval) = add_Node1((yyvsp[(1) - (1)]), "Dec", 0x20);}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 130 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "Dec", 0x21);}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 133 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "Exp", 0x22);}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 134 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "Exp", 0x23);}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 135 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "Exp", 0x24);}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 136 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "Exp", 0x25);}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 137 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "Exp", 0x26);}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 138 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "Exp", 0x27);}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 139 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "Exp", 0x28);}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 140 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "Exp", 0x29);}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 141 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "Exp", 0x2a);}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 142 "syntax.y"
    {(yyval) = add_Node2((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), "Exp", 0x2b);}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 143 "syntax.y"
    {(yyval) = add_Node2((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), "Exp", 0x2c);}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 144 "syntax.y"
    {(yyval) = add_Node4((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), "Exp", 0x2d);}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 145 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "Exp", 0x2e);}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 146 "syntax.y"
    {(yyval) = add_Node4((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]), "Exp", 0x2f);}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 147 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "Exp", 0x30);}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 148 "syntax.y"
    {(yyval) = add_Node1((yyvsp[(1) - (1)]), "Exp", 0x31);}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 149 "syntax.y"
    {(yyval) = add_Node1((yyvsp[(1) - (1)]), "Exp", 0x32);}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 150 "syntax.y"
    {(yyval) = add_Node1((yyvsp[(1) - (1)]), "Exp", 0x33);}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 151 "syntax.y"
    {synright = 0;}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 152 "syntax.y"
    {}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 154 "syntax.y"
    {(yyval) = add_Node3((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), "Args", 0x34);}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 155 "syntax.y"
    {(yyval) = add_Node1((yyvsp[(1) - (1)]), "Args", 0x35);}
    break;



/* Line 1806 of yacc.c  */
#line 2091 "syntax.tab.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
		      yytoken, &yylval, &yylloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
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
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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



/* Line 2067 of yacc.c  */
#line 158 "syntax.y"


#include "lex.yy.c"

Node* create_tree(Node* s) {
	Node* p = (Node *)malloc(sizeof(Node));
	p->flag = 0;
	strcpy(p->name, "Program");
	p->leftmost = s;
	p->right = NULL;
	if(s) 
		p->lineno = s->lineno;
	else 
		p->lineno = 1; //empty program

	if(s)
		s->right = NULL;

	p->pdt_type = 0;
	return p;
}

Node* add_Node1(Node* s1, char* str, int type) {
	Node* p = (void*)malloc(sizeof(Node));
	p->flag = 0;
	strcpy(p->name, str);
	p->lineno = s1->lineno;
	p->leftmost = s1;

	s1->right = NULL;

	root = p;
	p->pdt_type = type;

	return p;
}

Node* add_Node2(Node* s1, Node* s2, char* str, int type) {
	Node* p = (void*)malloc(sizeof(Node));
	p->flag = 0;
	strcpy(p->name, str);
	p->lineno = s1->lineno;
	p->leftmost = s1;

	if(s2 != NULL) {
		s1->right = s2;
		s2->right = NULL;
	}
	else {
		s1->right = NULL;
	}
	root = p;
	p->pdt_type = type;

	return p;
}

Node* add_Node3(Node* s1, Node* s2, Node* s3, char* str, int type) {
	Node* p = (void*)malloc(sizeof(Node));
	p->flag = 0;
	strcpy(p->name, str);
	p->lineno = s1->lineno;
	p->leftmost = s1;

	s1->right = s2;

	if(s3 != NULL) {
		s2->right = s3;
		s3->right = NULL;
	}
	else 
		s2->right = NULL;

	root = p;
	p->pdt_type = type;

	return p;
}

Node* add_Node4(Node* s1, Node* s2, Node* s3, Node* s4, char* str, int type) {
	Node* p = (void*)malloc(sizeof(Node));
	p->flag = 0;
	strcpy(p->name, str);
	p->lineno = s1->lineno;
	p->leftmost = s1;

	s1->right = s2;
	if(s2 && s3) { //s2, s3可能为空串
		s2->right = s3;
		s3->right = s4;
		s4->right = NULL;
	}
	else if(s2) {
		s1->right = s2;
		s2->right = s4;
	}
	else if(s3) {
		s1->right = s3;
		s3->right = s4;
	}

	root = p;
	p->pdt_type = type;

	return p;
}

Node* add_Node5(Node* s1, Node* s2, Node* s3, Node* s4, Node* s5, char* str, int type) {
	Node* p = (void*)malloc(sizeof(Node));
	p->flag = 0;
	strcpy(p->name, str);
	p->lineno = s1->lineno;
	p->leftmost = s1;

	s1->right = s2;

	if(s2 != NULL)
		s2->right = s3;
	else {
		s1->right = s3;

		/* 专门用来处理匿名结构体，这里给它手动设置名字，把名字首先赋给LC */
		/* 每次要开辟新的缓冲区，否则后面的匿名结构体名字会把前面的覆盖掉 */
		char* p = (void*)malloc(4);
		int i;
		for(i = 0; i < 4; i++)
			p[i] = '\0';
		sprintf(p, "%d", ++ano_num);
		s3->attr.blg_name = p;
	}

	s3->right = s4;

	if(s5 != NULL && s4 != NULL) {
		s4->right = s5;
		s5->right = NULL;
	}
	else if(s4 != NULL)
		s4->right = NULL;
	else if(s5 != NULL) 
		s3->right = s5;

	root = p;
	p->pdt_type = type;

	return p;
}

Node* add_Node7(Node* s1, Node* s2, Node* s3, Node* s4, Node* s5, Node* s6, Node* s7, char* str, int type) {
	Node* p = (void*)malloc(sizeof(Node));
	p->flag = 0;
	strcpy(p->name, str);
	p->lineno = s1->lineno;
	p->leftmost = s1;

	s1->right = s2;
	s2->right = s3;
	s3->right = s4;
	s4->right = s5;
	s5->right = s6;

	if(s7 != NULL) {
		s6->right = s7;
		s7->right = NULL;
	}
	else
		s6->right = NULL;
	
	root = p;
	p->pdt_type = type;

	return p;
}

void traversal(Node *root, int n) {
	int i;
	for(i = 0; i < n; i++)
		printf("  ");
	printf("%s", root->name);
	if(root->flag) {
		if(strcmp(root->name, "ID") == 0) 
			printf(": %s\n", root->id);
		else if(strcmp(root->name, "TYPE") == 0)
			printf(": %s\n", root->type);
		else if(strcmp(root->name, "INT") == 0)
			printf(": %d\n", root->d);
		else if(strcmp(root->name, "FLOAT") == 0)
			printf(": %f\n", root->f);
		else
			printf("\n");
	}
	else
		printf(" (%d)\n", root->lineno);
	Node* p = root->leftmost;
	while(p) {
		traversal(p, n+1);
		p = p->right;
	}
}

void sem_traversal(Node* root) {

	Node* p = root->leftmost;
	Node* last = root;

	while(p) {

		/* 当底层继承属性为空时，顶层才给底层传递继承属性 */
		if(!p->attr.blg_name)
			p->attr.blg_name = last->attr.blg_name;
		if(!p->inh)
			p->inh = last->inh;

		sem_traversal(p);
		last = p;
		assert(p);
		p = p->right;
	}

	assert(root);
	//printf("%d\n", root->pdt_type);
	sem_func_table[root->pdt_type](root);

}

yyerror(char* msg) {
	synright = 0;
	int lineno = yylineno;
	if(token_in_line == 1 && yylineno != root->lineno)
		lineno = root->lineno;
	fprintf(stderr, "Error type B at Line %d: %s \n", lineno, msg);
}

