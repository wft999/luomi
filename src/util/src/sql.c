/*
** 2000-05-29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Driver template for the LEMON parser generator.
**
** The "lemon" program processes an LALR(1) input grammar file, then uses
** this template to construct a parser.  The "lemon" program inserts text
** at each "%%" line.  Also, any "P-a-r-s-e" identifer prefix (without the
** interstitial "-" characters) contained in this template is changed into
** the value of the %name directive from the grammar.  Otherwise, the content
** of this template is copied straight through into the generate parser
** source file.
**
** The following is the concatenation of all %include directives from the
** input grammar file:
*/
#include <stdio.h>
#include <assert.h>
/************ Begin %include sections from the grammar ************************/
#line 23 "sql.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "tsql.h"
#include "tutil.h"
#line 39 "sql.c"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
/**************** End makeheaders token definitions ***************************/

/* The next sections is a series of control #defines.
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       (also known as: "terminal symbols") have fall-back
**                       values which should be used if the original symbol
**                       would not parse.  This permits keywords to sometimes
**                       be used as identifiers, for example.
**    YYACTIONTYPE       is the data type used for "action codes" - numbers
**                       that indicate what to do in response to the next
**                       token.
**    ParseTOKENTYPE     is the data type used for minor type for terminal
**                       symbols.  Background: A "minor type" is a semantic
**                       value associated with a terminal or non-terminal
**                       symbols.  For example, for an "ID" terminal symbol,
**                       the minor type might be the name of the identifier.
**                       Each non-terminal can have a different minor type.
**                       Terminal symbols all have the same minor type, though.
**                       This macros defines the minor type for terminal 
**                       symbols.
**    YYMINORTYPE        is the data type used for all minor types.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_PARAM     Code to pass %extra_argument as a subroutine parameter
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    ParseCTX_*         As ParseARG_ except for %extra_context
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYNTOKEN           Number of terminal symbols
**    YY_MAX_SHIFT       Maximum value for shift actions
**    YY_MIN_SHIFTREDUCE Minimum value for shift-reduce actions
**    YY_MAX_SHIFTREDUCE Maximum value for shift-reduce actions
**    YY_ERROR_ACTION    The yy_action[] code for syntax error
**    YY_ACCEPT_ACTION   The yy_action[] code for accept
**    YY_NO_ACTION       The yy_action[] code for no-op
**    YY_MIN_REDUCE      Minimum value for reduce actions
**    YY_MAX_REDUCE      Maximum value for reduce actions
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/************* Begin control #defines *****************************************/
#define YYCODETYPE unsigned char
#define YYNOCODE 242
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE SSQLToken
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  SCreateDBInfo yy82;
  int64_t yy85;
  tFieldList* yy155;
  SQuerySQL* yy216;
  tSQLExpr* yy222;
  tVariantList* yy264;
  int yy328;
  TAOS_FIELD yy339;
  SLimitVal yy350;
  tSQLExprList* yy390;
  tSQLExprListList* yy402;
  tVariant yy406;
  SCreateTableSQL* yy450;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL SSqlInfo* pInfo;
#define ParseARG_PDECL ,SSqlInfo* pInfo
#define ParseARG_PARAM ,pInfo
#define ParseARG_FETCH SSqlInfo* pInfo=yypParser->pInfo;
#define ParseARG_STORE yypParser->pInfo=pInfo;
#define ParseCTX_SDECL
#define ParseCTX_PDECL
#define ParseCTX_PARAM
#define ParseCTX_FETCH
#define ParseCTX_STORE
#define YYFALLBACK 1
#define YYNSTATE             227
#define YYNRULE              184
#define YYNTOKEN             189
#define YY_MAX_SHIFT         226
#define YY_MIN_SHIFTREDUCE   361
#define YY_MAX_SHIFTREDUCE   544
#define YY_ERROR_ACTION      545
#define YY_ACCEPT_ACTION     546
#define YY_NO_ACTION         547
#define YY_MIN_REDUCE        548
#define YY_MAX_REDUCE        731
/************* End control #defines *******************************************/
#define YY_NLOOKAHEAD ((int)(sizeof(yy_lookahead)/sizeof(yy_lookahead[0])))

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N <= YY_MAX_SHIFT             Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   N between YY_MIN_SHIFTREDUCE       Shift to an arbitrary state then
**     and YY_MAX_SHIFTREDUCE           reduce by rule N-YY_MIN_SHIFTREDUCE.
**
**   N == YY_ERROR_ACTION               A syntax error has occurred.
**
**   N == YY_ACCEPT_ACTION              The parser accepts its input.
**
**   N == YY_NO_ACTION                  No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
**   N between YY_MIN_REDUCE            Reduce by rule N-YY_MIN_REDUCE
**     and YY_MAX_REDUCE
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as either:
**
**    (A)   N = yy_action[ yy_shift_ofst[S] + X ]
**    (B)   N = yy_default[S]
**
** The (A) formula is preferred.  The B formula is used instead if
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X.
**
** The formulas above are for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (485)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   117,  393,  546,  226,   93,   10,  643,  429,  116,  394,
 /*    10 */   119,  138,  393,   38,   40,   93,   32,   33,  143,  710,
 /*    20 */   394,   26,  119,  119,  192,   36,   34,   37,   35,  636,
 /*    30 */   142,  710,  709,   31,   30,  217,  216,   29,   28,   27,
 /*    40 */    38,   40,  627,   32,   33,  640,  117,  665,   26,  187,
 /*    50 */   118,  192,   36,   34,   37,   35,  189,  139,   59,  123,
 /*    60 */    31,   30,  137,  225,   29,   28,   27,   38,   40,   93,
 /*    70 */    32,   33,   20,  706,   93,   26,  705,   20,  192,   36,
 /*    80 */    34,   37,   35,   61,  113,  111,   82,   31,   30,  140,
 /*    90 */    57,   29,   28,   27,   23,  151,   40,  625,   32,   33,
 /*   100 */   152,  628,  625,   26,  704,  393,  192,   36,   34,   37,
 /*   110 */    35,   11,  664,  394,  491,   31,   30,   60,  134,   29,
 /*   120 */    28,   27,  472,  473,   31,   30,  493,  136,   29,   28,
 /*   130 */    27,   81,   80,  130,   36,   34,   37,   35,  224,  223,
 /*   140 */   381,  131,   31,   30,  135,  208,   29,   28,   27,  362,
 /*   150 */   363,  364,  365,  366,  367,  368,  369,  370,  371,  372,
 /*   160 */    22,   20,  494,   17,  207,  206,  205,  204,  203,  202,
 /*   170 */   201,  200,  199,  198,   20,   72,   73,   79,  179,  124,
 /*   180 */   150,  175,  160,  221,  215,   74,  625,    7,  133,  209,
 /*   190 */    62,  103,  628,  159,  157,   32,   33,  220,  527,  625,
 /*   200 */    26,  628,   24,  192,   36,   34,   37,   35,  106,  107,
 /*   210 */    65,  528,   31,   30,  153,   24,   29,   28,   27,  125,
 /*   220 */   612,   20,  601,  602,  603,  604,  605,  606,  607,  608,
 /*   230 */   609,  610,  611,  147,  504,  445,  219,  495,  442,  498,
 /*   240 */   443,  501,  444,  147,  504,  126,  624,  495,  497,  498,
 /*   250 */   500,  501,  451,  147,  504,   58,  626,  495,  496,  498,
 /*   260 */   499,  501,   29,   28,   27,  144,  145,  155,  146,  191,
 /*   270 */   154,  165,   56,  214,  213,  144,  145,  463,  173,  454,
 /*   280 */   170,   42,   45,  464,  521,  144,  145,   15,   14,  505,
 /*   290 */    48,  435,  434,   14,  127,   42,   21,  196,    2,   46,
 /*   300 */   128,   21,   71,   70,  129,   49,    9,    8,  447,  121,
 /*   310 */   448,   78,   77,  115,  122,  120,  724,  613,   39,  731,
 /*   320 */   675,  674,  158,  148,  729,  446,  671,  503,   39,  670,
 /*   330 */   149,  180,  619,  218,  642,   90,  657,  503,   39,  656,
 /*   340 */   102,  104,  502,  105,  587,  197,   84,  503,  176,  114,
 /*   350 */   212,  723,  502,   88,   68,  722,  720,  108,  109,  578,
 /*   360 */   577,   75,  502,  575,  574,  156,  110,  572,  571,  570,
 /*   370 */   563,  178,  112,  567,  565,  459,  645,  181,  185,  658,
 /*   380 */    50,   47,   41,  637,  190,  188,  186,   22,  184,  182,
 /*   390 */    25,  211,   44,  194,  222,   53,   51,   94,  543,  540,
 /*   400 */   161,  132,   63,   66,  579,   83,  573,  569,   54,   85,
 /*   410 */    95,   98,   96,    1,  101,   99,   97,  623,  162,  100,
 /*   420 */    55,  163,  164,  539,  166,  167,  169,  168,  538,  171,
 /*   430 */   172,  531,  174,   12,   13,  541,  177,   89,  460,   91,
 /*   440 */   141,  465,    4,  183,   92,    5,   64,  412,  411,  506,
 /*   450 */    18,    3,   19,   16,  193,    6,  195,  410,  409,  408,
 /*   460 */   407,  406,  405,  404,   42,  403,  402,   43,  397,   21,
 /*   470 */   210,  431,  430,  428,   52,   76,  395,  374,  548,  547,
 /*   480 */   547,   67,   69,   86,   87,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */   230,    1,  189,  190,  192,  230,  192,    5,  230,    9,
 /*    10 */   230,  241,    1,   13,   14,  192,   16,   17,  238,  239,
 /*    20 */     9,   21,  230,  230,   24,   25,   26,   27,   28,  216,
 /*    30 */   238,  239,  239,   33,   34,   33,   34,   37,   38,   39,
 /*    40 */    13,   14,  211,   16,   17,  231,  230,  235,   21,  237,
 /*    50 */   230,   24,   25,   26,   27,   28,  233,  241,  235,  230,
 /*    60 */    33,   34,  191,  192,   37,   38,   39,   13,   14,  192,
 /*    70 */    16,   17,  192,  230,  192,   21,  230,  192,   24,   25,
 /*    80 */    26,   27,   28,  218,   61,   62,   63,   33,   34,  199,
 /*    90 */    90,   37,   38,   39,  229,  215,   14,  217,   16,   17,
 /*   100 */   215,  211,  217,   21,  230,    1,   24,   25,   26,   27,
 /*   110 */    28,   44,  235,    9,   87,   33,   34,  235,  230,   37,
 /*   120 */    38,   39,  101,  102,   33,   34,    1,   60,   37,   38,
 /*   130 */    39,   64,   65,   66,   25,   26,   27,   28,   57,   58,
 /*   140 */    59,   74,   33,   34,  230,   57,   37,   38,   39,   45,
 /*   150 */    46,   47,   48,   49,   50,   51,   52,   53,   54,   55,
 /*   160 */    93,  192,   37,   75,   76,   77,   78,   79,   80,   81,
 /*   170 */    82,   83,   84,   85,  192,   61,   62,   63,  111,  230,
 /*   180 */   199,  114,  115,   69,  215,   71,  217,   86,  121,  199,
 /*   190 */    89,   90,  211,  126,  127,   16,   17,  215,   87,  217,
 /*   200 */    21,  211,   91,   24,   25,   26,   27,   28,   61,   62,
 /*   210 */    63,   87,   33,   34,   60,   91,   37,   38,   39,  230,
 /*   220 */   198,  192,  200,  201,  202,  203,  204,  205,  206,  207,
 /*   230 */   208,  209,  210,    1,    2,    2,  192,    5,    5,    7,
 /*   240 */     7,    9,    9,    1,    2,  230,  217,    5,    5,    7,
 /*   250 */     7,    9,   91,    1,    2,   94,  212,    5,    5,    7,
 /*   260 */     7,    9,   37,   38,   39,   33,   34,   34,   56,   37,
 /*   270 */   116,  115,  125,  119,  120,   33,   34,   87,  122,   37,
 /*   280 */   124,   91,   91,   87,   87,   33,   34,   91,   91,   87,
 /*   290 */    91,   87,   87,   91,  230,   91,   91,   87,   86,  108,
 /*   300 */   230,   91,  117,  118,  230,  106,  117,  118,    5,  230,
 /*   310 */     7,   67,   68,  230,  230,  230,  211,  211,   86,  192,
 /*   320 */   213,  213,  192,  213,  192,   92,  213,   95,   86,  213,
 /*   330 */   213,  192,  214,  213,  192,  192,  236,   95,   86,  236,
 /*   340 */   219,  192,  110,  192,  192,  192,   56,   95,  113,  192,
 /*   350 */   192,  192,  110,  193,  192,  192,  192,  192,  192,  192,
 /*   360 */   192,  192,  110,  192,  192,  192,  192,  192,  192,  192,
 /*   370 */   192,  240,  192,  192,  192,   95,  193,  232,  232,  193,
 /*   380 */   105,  107,  104,  228,   99,  103,   98,   93,   97,   96,
 /*   390 */   109,   72,   77,  193,   72,  125,  193,  227,    9,    5,
 /*   400 */   123,  193,  196,  196,  195,  194,  193,  193,  125,  194,
 /*   410 */   226,  223,  225,  197,  220,  222,  224,  216,    5,  221,
 /*   420 */   125,  123,   70,    5,  123,    5,   70,  123,    5,  123,
 /*   430 */    70,   76,  115,   86,   86,    9,  113,  112,   87,   86,
 /*   440 */     1,   87,  100,   86,   86,  100,   67,    9,    5,   87,
 /*   450 */    91,   86,   91,   86,   88,   86,   88,    5,    5,    5,
 /*   460 */     1,    5,    5,    5,   91,    5,    5,   16,   73,   91,
 /*   470 */    15,    5,    5,   87,   86,   70,   73,   56,    0,  242,
 /*   480 */   242,  118,  118,   21,   21,  242,  242,  242,  242,  242,
 /*   490 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   500 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   510 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   520 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   530 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   540 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   550 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   560 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   570 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   580 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   590 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   600 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   610 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   620 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   630 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   640 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   650 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   660 */   242,  242,  242,  242,  242,  242,  242,  242,  242,  242,
 /*   670 */   242,  242,  242,  242,
};
#define YY_SHIFT_COUNT    (226)
#define YY_SHIFT_MIN      (0)
#define YY_SHIFT_MAX      (478)
static const unsigned short int yy_shift_ofst[] = {
 /*     0 */    67,   88,  232,  252,   11,   11,   11,   11,   11,   11,
 /*    10 */     0,  104,  252,  252,  252,  233,  233,  233,   11,   11,
 /*    20 */    11,   11,  485,  242,  252,  252,  252,  252,  252,  252,
 /*    30 */   252,  252,  252,  252,  252,  252,  252,  252,  252,  252,
 /*    40 */   252,  252,  233,  233,  233,    2,    2,    2,    2,    2,
 /*    50 */     2,  101,    2,   11,   11,   11,   11,   11,   11,   21,
 /*    60 */    21,  161,   11,   11,   11,   11,   11,   11,   11,   11,
 /*    70 */    11,   11,   11,   11,   11,   11,   11,   11,   11,   11,
 /*    80 */    11,   11,   11,   11,   11,   11,   11,   11,  235,  290,
 /*    90 */   290,  280,  280,  290,  275,  274,  278,  285,  282,  288,
 /*   100 */   291,  293,  281,  294,  290,  290,  319,  319,  290,  315,
 /*   110 */   290,  322,  290,  322,  485,   27,   54,   54,   54,   54,
 /*   120 */    54,   82,  179,  109,  109,  109,   91,   91,   91,   91,
 /*   130 */   114,  147,  154,  156,  225,  225,   23,   81,  111,  124,
 /*   140 */   190,  196,  197,  202,  243,  253,  125,  212,  191,  199,
 /*   150 */   204,  205,  210,  185,  189,  303,  244,  270,  389,  283,
 /*   160 */   295,  394,  277,  413,  298,  352,  418,  301,  420,  304,
 /*   170 */   356,  423,  306,  360,  355,  317,  347,  348,  323,  325,
 /*   180 */   426,  351,  353,  439,  357,  354,  358,  359,  342,  361,
 /*   190 */   345,  362,  365,  367,  366,  369,  368,  379,  438,  443,
 /*   200 */   452,  453,  454,  459,  456,  457,  458,  460,  461,  373,
 /*   210 */   395,  455,  451,  363,  364,  378,  466,  467,  386,  388,
 /*   220 */   378,  405,  403,  462,  463,  421,  478,
};
#define YY_REDUCE_COUNT (114)
#define YY_REDUCE_MIN   (-230)
#define YY_REDUCE_MAX   (216)
static const short yy_reduce_ofst[] = {
 /*     0 */  -187,   22, -220, -208, -188, -177, -120, -115,  -31,  -18,
 /*    10 */  -186, -129, -230, -184, -207, -110,  -19,  -10, -123, -118,
 /*    20 */    44,   29, -135, -225, -222, -180, -171, -157, -154, -126,
 /*    30 */  -112,  -86,  -51,  -11,   15,   64,   70,   74,   79,   83,
 /*    40 */    84,   85, -169,  105,  106,  107,  108,  110,  113,  116,
 /*    50 */   117,  118,  120,  127,  130,  132,  139,  142,  143,  100,
 /*    60 */   103,  121,  149,  151,  152,  153,  157,  158,  159,  162,
 /*    70 */   163,  164,  165,  166,  167,  168,  169,  171,  172,  173,
 /*    80 */   174,  175,  176,  177,  178,  180,  181,  182,  131,  160,
 /*    90 */   183,  145,  146,  186,  155,  170,  184,  187,  192,  188,
 /*   100 */   193,  198,  194,  201,  200,  203,  206,  207,  208,  209,
 /*   110 */   213,  211,  214,  215,  216,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   545,  586,  712,  712,  545,  545,  545,  545,  545,  545,
 /*    10 */   644,  560,  545,  545,  712,  545,  545,  545,  545,  545,
 /*    20 */   545,  545,  639,  545,  545,  545,  545,  545,  545,  545,
 /*    30 */   545,  545,  545,  545,  545,  545,  545,  545,  545,  545,
 /*    40 */   545,  545,  545,  545,  545,  545,  545,  545,  545,  545,
 /*    50 */   545,  545,  545,  545,  545,  545,  545,  545,  545,  661,
 /*    60 */   661,  545,  545,  545,  545,  545,  545,  545,  545,  545,
 /*    70 */   545,  545,  545,  545,  545,  576,  545,  545,  545,  545,
 /*    80 */   545,  545,  545,  545,  545,  545,  545,  545,  545,  562,
 /*    90 */   562,  545,  545,  562,  668,  672,  666,  654,  662,  653,
 /*   100 */   649,  648,  676,  545,  562,  562,  585,  585,  562,  545,
 /*   110 */   562,  583,  562,  583,  600,  545,  716,  717,  677,  711,
 /*   120 */   667,  695,  694,  707,  701,  700,  699,  698,  697,  696,
 /*   130 */   545,  545,  545,  545,  703,  702,  545,  545,  545,  545,
 /*   140 */   545,  545,  545,  545,  545,  545,  545,  679,  673,  669,
 /*   150 */   545,  545,  545,  545,  545,  545,  545,  545,  545,  545,
 /*   160 */   545,  545,  545,  545,  545,  545,  545,  545,  545,  545,
 /*   170 */   545,  545,  545,  545,  545,  545,  545,  545,  713,  545,
 /*   180 */   545,  545,  545,  545,  545,  545,  545,  663,  545,  655,
 /*   190 */   545,  545,  545,  545,  545,  545,  620,  545,  545,  545,
 /*   200 */   545,  545,  545,  545,  545,  545,  545,  545,  545,  588,
 /*   210 */   545,  545,  545,  545,  545,  721,  545,  545,  545,  614,
 /*   220 */   719,  545,  545,  566,  564,  545,  545,
};
/********** End of lemon-generated parsing tables *****************************/

/* The next table maps tokens (terminal symbols) into fallback tokens.  
** If a construct like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
**
** This feature can be used, for example, to cause some keywords in a language
** to revert to identifiers if they keyword does not apply in the context where
** it appears.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
    0,  /*          $ => nothing */
    0,  /*         ID => nothing */
    1,  /*       BOOL => ID */
    1,  /*    TINYINT => ID */
    1,  /*   SMALLINT => ID */
    1,  /*    INTEGER => ID */
    1,  /*     BIGINT => ID */
    1,  /*      FLOAT => ID */
    1,  /*     DOUBLE => ID */
    1,  /*     STRING => ID */
    1,  /*  TIMESTAMP => ID */
    1,  /*     BINARY => ID */
    1,  /*      NCHAR => ID */
    0,  /*         OR => nothing */
    0,  /*        AND => nothing */
    0,  /*        NOT => nothing */
    0,  /*         EQ => nothing */
    0,  /*         NE => nothing */
    0,  /*     ISNULL => nothing */
    0,  /*    NOTNULL => nothing */
    0,  /*         IS => nothing */
    1,  /*       LIKE => ID */
    1,  /*       GLOB => ID */
    0,  /*    BETWEEN => nothing */
    0,  /*         IN => nothing */
    0,  /*         GT => nothing */
    0,  /*         GE => nothing */
    0,  /*         LT => nothing */
    0,  /*         LE => nothing */
    0,  /*     BITAND => nothing */
    0,  /*      BITOR => nothing */
    0,  /*     LSHIFT => nothing */
    0,  /*     RSHIFT => nothing */
    0,  /*       PLUS => nothing */
    0,  /*      MINUS => nothing */
    0,  /*     DIVIDE => nothing */
    0,  /*      TIMES => nothing */
    0,  /*       STAR => nothing */
    0,  /*      SLASH => nothing */
    0,  /*        REM => nothing */
    0,  /*     CONCAT => nothing */
    0,  /*     UMINUS => nothing */
    0,  /*      UPLUS => nothing */
    0,  /*     BITNOT => nothing */
    0,  /*       SHOW => nothing */
    0,  /*  DATABASES => nothing */
    0,  /*     MNODES => nothing */
    0,  /*     DNODES => nothing */
    0,  /*      USERS => nothing */
    0,  /*    MODULES => nothing */
    0,  /*    QUERIES => nothing */
    0,  /* CONNECTIONS => nothing */
    0,  /*    STREAMS => nothing */
    0,  /*    CONFIGS => nothing */
    0,  /*     SCORES => nothing */
    0,  /*     GRANTS => nothing */
    0,  /*        DOT => nothing */
    0,  /*     TABLES => nothing */
    0,  /*    STABLES => nothing */
    0,  /*    VGROUPS => nothing */
    0,  /*       DROP => nothing */
    0,  /*      TABLE => nothing */
    1,  /*   DATABASE => ID */
    0,  /*       USER => nothing */
    0,  /*        USE => nothing */
    0,  /*   DESCRIBE => nothing */
    0,  /*      ALTER => nothing */
    0,  /*       PASS => nothing */
    0,  /*  PRIVILEGE => nothing */
    0,  /*      DNODE => nothing */
    1,  /*         IP => ID */
    0,  /*      LOCAL => nothing */
    0,  /*         IF => nothing */
    0,  /*     EXISTS => nothing */
    0,  /*     CREATE => nothing */
    0,  /*       KEEP => nothing */
    0,  /*      CACHE => nothing */
    0,  /*    REPLICA => nothing */
    0,  /*       DAYS => nothing */
    0,  /*       ROWS => nothing */
    0,  /*    ABLOCKS => nothing */
    0,  /*    TBLOCKS => nothing */
    0,  /*      CTIME => nothing */
    0,  /*       CLOG => nothing */
    0,  /*       COMP => nothing */
    0,  /*  PRECISION => nothing */
    0,  /*         LP => nothing */
    0,  /*         RP => nothing */
    0,  /*       TAGS => nothing */
    0,  /*      USING => nothing */
    0,  /*         AS => nothing */
    0,  /*      COMMA => nothing */
    0,  /*       NULL => nothing */
    0,  /*     SELECT => nothing */
    0,  /*       FROM => nothing */
    0,  /*   VARIABLE => nothing */
    0,  /*   INTERVAL => nothing */
    0,  /*       FILL => nothing */
    0,  /*    SLIDING => nothing */
    0,  /*      ORDER => nothing */
    0,  /*         BY => nothing */
    1,  /*        ASC => ID */
    1,  /*       DESC => ID */
    0,  /*      GROUP => nothing */
    0,  /*     HAVING => nothing */
    0,  /*      LIMIT => nothing */
    1,  /*     OFFSET => ID */
    0,  /*     SLIMIT => nothing */
    0,  /*    SOFFSET => nothing */
    0,  /*      WHERE => nothing */
    1,  /*        NOW => ID */
    0,  /*     INSERT => nothing */
    0,  /*       INTO => nothing */
    0,  /*     VALUES => nothing */
    0,  /*      RESET => nothing */
    0,  /*      QUERY => nothing */
    0,  /*        ADD => nothing */
    0,  /*     COLUMN => nothing */
    0,  /*        TAG => nothing */
    0,  /*     CHANGE => nothing */
    0,  /*        SET => nothing */
    0,  /*       KILL => nothing */
    0,  /* CONNECTION => nothing */
    0,  /*      COLON => nothing */
    0,  /*     STREAM => nothing */
    0,  /*       GATE => nothing */
    0,  /*     UPDATE => nothing */
    0,  /*     DELETE => nothing */
    1,  /*      ABORT => ID */
    1,  /*      AFTER => ID */
    1,  /*     ATTACH => ID */
    1,  /*     BEFORE => ID */
    1,  /*      BEGIN => ID */
    1,  /*    CASCADE => ID */
    1,  /*    CLUSTER => ID */
    1,  /*   CONFLICT => ID */
    1,  /*       COPY => ID */
    1,  /*   DEFERRED => ID */
    1,  /* DELIMITERS => ID */
    1,  /*     DETACH => ID */
    1,  /*       EACH => ID */
    1,  /*        END => ID */
    1,  /*    EXPLAIN => ID */
    1,  /*       FAIL => ID */
    1,  /*        FOR => ID */
    1,  /*     IGNORE => ID */
    1,  /*  IMMEDIATE => ID */
    1,  /*  INITIALLY => ID */
    1,  /*    INSTEAD => ID */
    1,  /*      MATCH => ID */
    1,  /*        KEY => ID */
    1,  /*         OF => ID */
    1,  /*      RAISE => ID */
    1,  /*    REPLACE => ID */
    1,  /*   RESTRICT => ID */
    1,  /*        ROW => ID */
    1,  /*  STATEMENT => ID */
    1,  /*    TRIGGER => ID */
    1,  /*       VIEW => ID */
    1,  /*        ALL => ID */
    1,  /*      COUNT => ID */
    1,  /*        SUM => ID */
    1,  /*        AVG => ID */
    1,  /*        MIN => ID */
    1,  /*        MAX => ID */
    1,  /*      FIRST => ID */
    1,  /*       LAST => ID */
    1,  /*        TOP => ID */
    1,  /*     BOTTOM => ID */
    1,  /*     STDDEV => ID */
    1,  /* PERCENTILE => ID */
    1,  /* APERCENTILE => ID */
    1,  /* LEASTSQUARES => ID */
    1,  /*  HISTOGRAM => ID */
    1,  /*       DIFF => ID */
    1,  /*     SPREAD => ID */
    1,  /*       WAVG => ID */
    1,  /*     INTERP => ID */
    1,  /*   LAST_ROW => ID */
    1,  /*       SEMI => ID */
    1,  /*       NONE => ID */
    1,  /*       PREV => ID */
    1,  /*     LINEAR => ID */
    1,  /*     IMPORT => ID */
    1,  /*     METRIC => ID */
    1,  /*     TBNAME => ID */
    1,  /*       JOIN => ID */
    1,  /*    METRICS => ID */
    1,  /*     STABLE => ID */
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
**
** After the "shift" half of a SHIFTREDUCE action, the stateno field
** actually contains the reduce action for the second half of the
** SHIFTREDUCE.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number, or reduce action in SHIFTREDUCE */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  yyStackEntry *yytos;          /* Pointer to top element of the stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyhwm;                    /* High-water mark of the stack */
#endif
#ifndef YYNOERRORRECOVERY
  int yyerrcnt;                 /* Shifts left before out of the error */
#endif
  ParseARG_SDECL                /* A place to hold %extra_argument */
  ParseCTX_SDECL                /* A place to hold %extra_context */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
  yyStackEntry yystk0;          /* First stack entry */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
  yyStackEntry *yystackEnd;            /* Last entry in the stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#if defined(YYCOVERAGE) || !defined(NDEBUG)
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  /*    0 */ "$",
  /*    1 */ "ID",
  /*    2 */ "BOOL",
  /*    3 */ "TINYINT",
  /*    4 */ "SMALLINT",
  /*    5 */ "INTEGER",
  /*    6 */ "BIGINT",
  /*    7 */ "FLOAT",
  /*    8 */ "DOUBLE",
  /*    9 */ "STRING",
  /*   10 */ "TIMESTAMP",
  /*   11 */ "BINARY",
  /*   12 */ "NCHAR",
  /*   13 */ "OR",
  /*   14 */ "AND",
  /*   15 */ "NOT",
  /*   16 */ "EQ",
  /*   17 */ "NE",
  /*   18 */ "ISNULL",
  /*   19 */ "NOTNULL",
  /*   20 */ "IS",
  /*   21 */ "LIKE",
  /*   22 */ "GLOB",
  /*   23 */ "BETWEEN",
  /*   24 */ "IN",
  /*   25 */ "GT",
  /*   26 */ "GE",
  /*   27 */ "LT",
  /*   28 */ "LE",
  /*   29 */ "BITAND",
  /*   30 */ "BITOR",
  /*   31 */ "LSHIFT",
  /*   32 */ "RSHIFT",
  /*   33 */ "PLUS",
  /*   34 */ "MINUS",
  /*   35 */ "DIVIDE",
  /*   36 */ "TIMES",
  /*   37 */ "STAR",
  /*   38 */ "SLASH",
  /*   39 */ "REM",
  /*   40 */ "CONCAT",
  /*   41 */ "UMINUS",
  /*   42 */ "UPLUS",
  /*   43 */ "BITNOT",
  /*   44 */ "SHOW",
  /*   45 */ "DATABASES",
  /*   46 */ "MNODES",
  /*   47 */ "DNODES",
  /*   48 */ "USERS",
  /*   49 */ "MODULES",
  /*   50 */ "QUERIES",
  /*   51 */ "CONNECTIONS",
  /*   52 */ "STREAMS",
  /*   53 */ "CONFIGS",
  /*   54 */ "SCORES",
  /*   55 */ "GRANTS",
  /*   56 */ "DOT",
  /*   57 */ "TABLES",
  /*   58 */ "STABLES",
  /*   59 */ "VGROUPS",
  /*   60 */ "DROP",
  /*   61 */ "TABLE",
  /*   62 */ "DATABASE",
  /*   63 */ "USER",
  /*   64 */ "USE",
  /*   65 */ "DESCRIBE",
  /*   66 */ "ALTER",
  /*   67 */ "PASS",
  /*   68 */ "PRIVILEGE",
  /*   69 */ "DNODE",
  /*   70 */ "IP",
  /*   71 */ "LOCAL",
  /*   72 */ "IF",
  /*   73 */ "EXISTS",
  /*   74 */ "CREATE",
  /*   75 */ "KEEP",
  /*   76 */ "CACHE",
  /*   77 */ "REPLICA",
  /*   78 */ "DAYS",
  /*   79 */ "ROWS",
  /*   80 */ "ABLOCKS",
  /*   81 */ "TBLOCKS",
  /*   82 */ "CTIME",
  /*   83 */ "CLOG",
  /*   84 */ "COMP",
  /*   85 */ "PRECISION",
  /*   86 */ "LP",
  /*   87 */ "RP",
  /*   88 */ "TAGS",
  /*   89 */ "USING",
  /*   90 */ "AS",
  /*   91 */ "COMMA",
  /*   92 */ "NULL",
  /*   93 */ "SELECT",
  /*   94 */ "FROM",
  /*   95 */ "VARIABLE",
  /*   96 */ "INTERVAL",
  /*   97 */ "FILL",
  /*   98 */ "SLIDING",
  /*   99 */ "ORDER",
  /*  100 */ "BY",
  /*  101 */ "ASC",
  /*  102 */ "DESC",
  /*  103 */ "GROUP",
  /*  104 */ "HAVING",
  /*  105 */ "LIMIT",
  /*  106 */ "OFFSET",
  /*  107 */ "SLIMIT",
  /*  108 */ "SOFFSET",
  /*  109 */ "WHERE",
  /*  110 */ "NOW",
  /*  111 */ "INSERT",
  /*  112 */ "INTO",
  /*  113 */ "VALUES",
  /*  114 */ "RESET",
  /*  115 */ "QUERY",
  /*  116 */ "ADD",
  /*  117 */ "COLUMN",
  /*  118 */ "TAG",
  /*  119 */ "CHANGE",
  /*  120 */ "SET",
  /*  121 */ "KILL",
  /*  122 */ "CONNECTION",
  /*  123 */ "COLON",
  /*  124 */ "STREAM",
  /*  125 */ "GATE",
  /*  126 */ "UPDATE",
  /*  127 */ "DELETE",
  /*  128 */ "ABORT",
  /*  129 */ "AFTER",
  /*  130 */ "ATTACH",
  /*  131 */ "BEFORE",
  /*  132 */ "BEGIN",
  /*  133 */ "CASCADE",
  /*  134 */ "CLUSTER",
  /*  135 */ "CONFLICT",
  /*  136 */ "COPY",
  /*  137 */ "DEFERRED",
  /*  138 */ "DELIMITERS",
  /*  139 */ "DETACH",
  /*  140 */ "EACH",
  /*  141 */ "END",
  /*  142 */ "EXPLAIN",
  /*  143 */ "FAIL",
  /*  144 */ "FOR",
  /*  145 */ "IGNORE",
  /*  146 */ "IMMEDIATE",
  /*  147 */ "INITIALLY",
  /*  148 */ "INSTEAD",
  /*  149 */ "MATCH",
  /*  150 */ "KEY",
  /*  151 */ "OF",
  /*  152 */ "RAISE",
  /*  153 */ "REPLACE",
  /*  154 */ "RESTRICT",
  /*  155 */ "ROW",
  /*  156 */ "STATEMENT",
  /*  157 */ "TRIGGER",
  /*  158 */ "VIEW",
  /*  159 */ "ALL",
  /*  160 */ "COUNT",
  /*  161 */ "SUM",
  /*  162 */ "AVG",
  /*  163 */ "MIN",
  /*  164 */ "MAX",
  /*  165 */ "FIRST",
  /*  166 */ "LAST",
  /*  167 */ "TOP",
  /*  168 */ "BOTTOM",
  /*  169 */ "STDDEV",
  /*  170 */ "PERCENTILE",
  /*  171 */ "APERCENTILE",
  /*  172 */ "LEASTSQUARES",
  /*  173 */ "HISTOGRAM",
  /*  174 */ "DIFF",
  /*  175 */ "SPREAD",
  /*  176 */ "WAVG",
  /*  177 */ "INTERP",
  /*  178 */ "LAST_ROW",
  /*  179 */ "SEMI",
  /*  180 */ "NONE",
  /*  181 */ "PREV",
  /*  182 */ "LINEAR",
  /*  183 */ "IMPORT",
  /*  184 */ "METRIC",
  /*  185 */ "TBNAME",
  /*  186 */ "JOIN",
  /*  187 */ "METRICS",
  /*  188 */ "STABLE",
  /*  189 */ "program",
  /*  190 */ "cmd",
  /*  191 */ "dbPrefix",
  /*  192 */ "ids",
  /*  193 */ "cpxName",
  /*  194 */ "ifexists",
  /*  195 */ "alter_db_optr",
  /*  196 */ "ifnotexists",
  /*  197 */ "db_optr",
  /*  198 */ "keep",
  /*  199 */ "tagitemlist",
  /*  200 */ "tables",
  /*  201 */ "cache",
  /*  202 */ "replica",
  /*  203 */ "days",
  /*  204 */ "rows",
  /*  205 */ "ablocks",
  /*  206 */ "tblocks",
  /*  207 */ "ctime",
  /*  208 */ "clog",
  /*  209 */ "comp",
  /*  210 */ "prec",
  /*  211 */ "tagitem",
  /*  212 */ "typename",
  /*  213 */ "signed",
  /*  214 */ "create_table_args",
  /*  215 */ "columnlist",
  /*  216 */ "select",
  /*  217 */ "column",
  /*  218 */ "selcollist",
  /*  219 */ "from",
  /*  220 */ "where_opt",
  /*  221 */ "interval_opt",
  /*  222 */ "fill_opt",
  /*  223 */ "sliding_opt",
  /*  224 */ "groupby_opt",
  /*  225 */ "orderby_opt",
  /*  226 */ "having_opt",
  /*  227 */ "slimit_opt",
  /*  228 */ "limit_opt",
  /*  229 */ "sclp",
  /*  230 */ "expr",
  /*  231 */ "as",
  /*  232 */ "tmvar",
  /*  233 */ "sortlist",
  /*  234 */ "sortitem",
  /*  235 */ "item",
  /*  236 */ "sortorder",
  /*  237 */ "grouplist",
  /*  238 */ "exprlist",
  /*  239 */ "expritem",
  /*  240 */ "insert_value_list",
  /*  241 */ "itemlist",
};
#endif /* defined(YYCOVERAGE) || !defined(NDEBUG) */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= cmd",
 /*   1 */ "cmd ::= SHOW DATABASES",
 /*   2 */ "cmd ::= SHOW MNODES",
 /*   3 */ "cmd ::= SHOW DNODES",
 /*   4 */ "cmd ::= SHOW USERS",
 /*   5 */ "cmd ::= SHOW MODULES",
 /*   6 */ "cmd ::= SHOW QUERIES",
 /*   7 */ "cmd ::= SHOW CONNECTIONS",
 /*   8 */ "cmd ::= SHOW STREAMS",
 /*   9 */ "cmd ::= SHOW CONFIGS",
 /*  10 */ "cmd ::= SHOW SCORES",
 /*  11 */ "cmd ::= SHOW GRANTS",
 /*  12 */ "dbPrefix ::=",
 /*  13 */ "dbPrefix ::= ids DOT",
 /*  14 */ "cpxName ::=",
 /*  15 */ "cpxName ::= DOT ids",
 /*  16 */ "cmd ::= SHOW dbPrefix TABLES",
 /*  17 */ "cmd ::= SHOW dbPrefix TABLES LIKE ids",
 /*  18 */ "cmd ::= SHOW dbPrefix STABLES",
 /*  19 */ "cmd ::= SHOW dbPrefix STABLES LIKE ids",
 /*  20 */ "cmd ::= SHOW dbPrefix VGROUPS",
 /*  21 */ "cmd ::= DROP TABLE ifexists ids cpxName",
 /*  22 */ "cmd ::= DROP DATABASE ifexists ids",
 /*  23 */ "cmd ::= DROP USER ids",
 /*  24 */ "cmd ::= USE ids",
 /*  25 */ "cmd ::= DESCRIBE ids cpxName",
 /*  26 */ "cmd ::= ALTER USER ids PASS ids",
 /*  27 */ "cmd ::= ALTER USER ids PRIVILEGE ids",
 /*  28 */ "cmd ::= ALTER DNODE IP ids",
 /*  29 */ "cmd ::= ALTER DNODE IP ids ids",
 /*  30 */ "cmd ::= ALTER LOCAL ids",
 /*  31 */ "cmd ::= ALTER DATABASE ids alter_db_optr",
 /*  32 */ "ids ::= ID",
 /*  33 */ "ids ::= STRING",
 /*  34 */ "ifexists ::= IF EXISTS",
 /*  35 */ "ifexists ::=",
 /*  36 */ "ifnotexists ::= IF NOT EXISTS",
 /*  37 */ "ifnotexists ::=",
 /*  38 */ "cmd ::= CREATE DATABASE ifnotexists ids db_optr",
 /*  39 */ "cmd ::= CREATE USER ids PASS ids",
 /*  40 */ "keep ::= KEEP tagitemlist",
 /*  41 */ "tables ::= TABLES INTEGER",
 /*  42 */ "cache ::= CACHE INTEGER",
 /*  43 */ "replica ::= REPLICA INTEGER",
 /*  44 */ "days ::= DAYS INTEGER",
 /*  45 */ "rows ::= ROWS INTEGER",
 /*  46 */ "ablocks ::= ABLOCKS ID",
 /*  47 */ "tblocks ::= TBLOCKS INTEGER",
 /*  48 */ "ctime ::= CTIME INTEGER",
 /*  49 */ "clog ::= CLOG INTEGER",
 /*  50 */ "comp ::= COMP INTEGER",
 /*  51 */ "prec ::= PRECISION STRING",
 /*  52 */ "db_optr ::=",
 /*  53 */ "db_optr ::= db_optr tables",
 /*  54 */ "db_optr ::= db_optr cache",
 /*  55 */ "db_optr ::= db_optr replica",
 /*  56 */ "db_optr ::= db_optr days",
 /*  57 */ "db_optr ::= db_optr rows",
 /*  58 */ "db_optr ::= db_optr ablocks",
 /*  59 */ "db_optr ::= db_optr tblocks",
 /*  60 */ "db_optr ::= db_optr ctime",
 /*  61 */ "db_optr ::= db_optr clog",
 /*  62 */ "db_optr ::= db_optr comp",
 /*  63 */ "db_optr ::= db_optr prec",
 /*  64 */ "db_optr ::= db_optr keep",
 /*  65 */ "alter_db_optr ::= REPLICA tagitem",
 /*  66 */ "typename ::= ids",
 /*  67 */ "typename ::= ids LP signed RP",
 /*  68 */ "signed ::= INTEGER",
 /*  69 */ "signed ::= PLUS INTEGER",
 /*  70 */ "signed ::= MINUS INTEGER",
 /*  71 */ "cmd ::= CREATE TABLE ifnotexists ids cpxName create_table_args",
 /*  72 */ "create_table_args ::= LP columnlist RP",
 /*  73 */ "create_table_args ::= LP columnlist RP TAGS LP columnlist RP",
 /*  74 */ "create_table_args ::= USING ids cpxName TAGS LP tagitemlist RP",
 /*  75 */ "create_table_args ::= AS select",
 /*  76 */ "columnlist ::= columnlist COMMA column",
 /*  77 */ "columnlist ::= column",
 /*  78 */ "column ::= ids typename",
 /*  79 */ "tagitemlist ::= tagitemlist COMMA tagitem",
 /*  80 */ "tagitemlist ::= tagitem",
 /*  81 */ "tagitem ::= INTEGER",
 /*  82 */ "tagitem ::= FLOAT",
 /*  83 */ "tagitem ::= STRING",
 /*  84 */ "tagitem ::= BOOL",
 /*  85 */ "tagitem ::= NULL",
 /*  86 */ "tagitem ::= MINUS INTEGER",
 /*  87 */ "tagitem ::= MINUS FLOAT",
 /*  88 */ "cmd ::= select",
 /*  89 */ "select ::= SELECT selcollist from where_opt interval_opt fill_opt sliding_opt groupby_opt orderby_opt having_opt slimit_opt limit_opt",
 /*  90 */ "sclp ::= selcollist COMMA",
 /*  91 */ "sclp ::=",
 /*  92 */ "selcollist ::= sclp expr as",
 /*  93 */ "selcollist ::= sclp STAR",
 /*  94 */ "as ::= AS ids",
 /*  95 */ "as ::= ids",
 /*  96 */ "as ::=",
 /*  97 */ "from ::= FROM ids cpxName",
 /*  98 */ "tmvar ::= VARIABLE",
 /*  99 */ "interval_opt ::= INTERVAL LP tmvar RP",
 /* 100 */ "interval_opt ::=",
 /* 101 */ "fill_opt ::=",
 /* 102 */ "fill_opt ::= FILL LP ID COMMA tagitemlist RP",
 /* 103 */ "fill_opt ::= FILL LP ID RP",
 /* 104 */ "sliding_opt ::= SLIDING LP tmvar RP",
 /* 105 */ "sliding_opt ::=",
 /* 106 */ "orderby_opt ::=",
 /* 107 */ "orderby_opt ::= ORDER BY sortlist",
 /* 108 */ "sortlist ::= sortlist COMMA item sortorder",
 /* 109 */ "sortlist ::= item sortorder",
 /* 110 */ "item ::= ids cpxName",
 /* 111 */ "sortorder ::= ASC",
 /* 112 */ "sortorder ::= DESC",
 /* 113 */ "sortorder ::=",
 /* 114 */ "groupby_opt ::=",
 /* 115 */ "groupby_opt ::= GROUP BY grouplist",
 /* 116 */ "grouplist ::= grouplist COMMA item",
 /* 117 */ "grouplist ::= item",
 /* 118 */ "having_opt ::=",
 /* 119 */ "having_opt ::= HAVING expr",
 /* 120 */ "limit_opt ::=",
 /* 121 */ "limit_opt ::= LIMIT signed",
 /* 122 */ "limit_opt ::= LIMIT signed OFFSET signed",
 /* 123 */ "limit_opt ::= LIMIT signed COMMA signed",
 /* 124 */ "slimit_opt ::=",
 /* 125 */ "slimit_opt ::= SLIMIT signed",
 /* 126 */ "slimit_opt ::= SLIMIT signed SOFFSET signed",
 /* 127 */ "slimit_opt ::= SLIMIT signed COMMA signed",
 /* 128 */ "where_opt ::=",
 /* 129 */ "where_opt ::= WHERE expr",
 /* 130 */ "expr ::= LP expr RP",
 /* 131 */ "expr ::= ID",
 /* 132 */ "expr ::= ID DOT ID",
 /* 133 */ "expr ::= ID DOT STAR",
 /* 134 */ "expr ::= INTEGER",
 /* 135 */ "expr ::= MINUS INTEGER",
 /* 136 */ "expr ::= PLUS INTEGER",
 /* 137 */ "expr ::= FLOAT",
 /* 138 */ "expr ::= MINUS FLOAT",
 /* 139 */ "expr ::= PLUS FLOAT",
 /* 140 */ "expr ::= STRING",
 /* 141 */ "expr ::= NOW",
 /* 142 */ "expr ::= VARIABLE",
 /* 143 */ "expr ::= BOOL",
 /* 144 */ "expr ::= ID LP exprlist RP",
 /* 145 */ "expr ::= ID LP STAR RP",
 /* 146 */ "expr ::= expr AND expr",
 /* 147 */ "expr ::= expr OR expr",
 /* 148 */ "expr ::= expr LT expr",
 /* 149 */ "expr ::= expr GT expr",
 /* 150 */ "expr ::= expr LE expr",
 /* 151 */ "expr ::= expr GE expr",
 /* 152 */ "expr ::= expr NE expr",
 /* 153 */ "expr ::= expr EQ expr",
 /* 154 */ "expr ::= expr PLUS expr",
 /* 155 */ "expr ::= expr MINUS expr",
 /* 156 */ "expr ::= expr STAR expr",
 /* 157 */ "expr ::= expr SLASH expr",
 /* 158 */ "expr ::= expr REM expr",
 /* 159 */ "expr ::= expr LIKE expr",
 /* 160 */ "expr ::= expr IN LP exprlist RP",
 /* 161 */ "exprlist ::= exprlist COMMA expritem",
 /* 162 */ "exprlist ::= expritem",
 /* 163 */ "expritem ::= expr",
 /* 164 */ "expritem ::=",
 /* 165 */ "cmd ::= INSERT INTO cpxName insert_value_list",
 /* 166 */ "insert_value_list ::= VALUES LP itemlist RP",
 /* 167 */ "insert_value_list ::= insert_value_list VALUES LP itemlist RP",
 /* 168 */ "itemlist ::= itemlist COMMA expr",
 /* 169 */ "itemlist ::= expr",
 /* 170 */ "cmd ::= RESET QUERY CACHE",
 /* 171 */ "cmd ::= ALTER TABLE ids cpxName ADD COLUMN columnlist",
 /* 172 */ "cmd ::= ALTER TABLE ids cpxName DROP COLUMN ids",
 /* 173 */ "cmd ::= ALTER TABLE ids cpxName ADD TAG columnlist",
 /* 174 */ "cmd ::= ALTER TABLE ids cpxName DROP TAG ids",
 /* 175 */ "cmd ::= ALTER TABLE ids cpxName CHANGE TAG ids ids",
 /* 176 */ "cmd ::= ALTER TABLE ids cpxName SET TAG ids EQ tagitem",
 /* 177 */ "cmd ::= KILL CONNECTION IP COLON INTEGER",
 /* 178 */ "cmd ::= KILL STREAM IP COLON INTEGER COLON INTEGER",
 /* 179 */ "cmd ::= KILL QUERY IP COLON INTEGER COLON INTEGER",
 /* 180 */ "cmd ::= CREATE GATE ids STRING",
 /* 181 */ "cmd ::= QUERY GATE ids",
 /* 182 */ "cmd ::= UPDATE GATE ids STRING",
 /* 183 */ "cmd ::= DELETE GATE ids",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.  Return the number
** of errors.  Return 0 on success.
*/
static int yyGrowStack(yyParser *p){
  int newSize;
  int idx;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  idx = p->yytos ? (int)(p->yytos - p->yystack) : 0;
  if( p->yystack==&p->yystk0 ){
    pNew = malloc(newSize*sizeof(pNew[0]));
    if( pNew ) pNew[0] = p->yystk0;
  }else{
    pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  }
  if( pNew ){
    p->yystack = pNew;
    p->yytos = &p->yystack[idx];
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows from %d to %d entries.\n",
              yyTracePrompt, p->yystksz, newSize);
    }
#endif
    p->yystksz = newSize;
  }
  return pNew==0; 
}
#endif

/* Datatype of the argument to the memory allocated passed as the
** second argument to ParseAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* Initialize a new parser that has already been allocated.
*/
void ParseInit(void *yypRawParser ParseCTX_PDECL){
  yyParser *yypParser = (yyParser*)yypRawParser;
  ParseCTX_STORE
#ifdef YYTRACKMAXSTACKDEPTH
  yypParser->yyhwm = 0;
#endif
#if YYSTACKDEPTH<=0
  yypParser->yytos = NULL;
  yypParser->yystack = NULL;
  yypParser->yystksz = 0;
  if( yyGrowStack(yypParser) ){
    yypParser->yystack = &yypParser->yystk0;
    yypParser->yystksz = 1;
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  yypParser->yytos = yypParser->yystack;
  yypParser->yystack[0].stateno = 0;
  yypParser->yystack[0].major = 0;
#if YYSTACKDEPTH>0
  yypParser->yystackEnd = &yypParser->yystack[YYSTACKDEPTH-1];
#endif
}

#ifndef Parse_ENGINEALWAYSONSTACK
/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(YYMALLOCARGTYPE) ParseCTX_PDECL){
  yyParser *yypParser;
  yypParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( yypParser ){
    ParseCTX_STORE
    ParseInit(yypParser ParseCTX_PARAM);
  }
  return (void*)yypParser;
}
#endif /* Parse_ENGINEALWAYSONSTACK */


/* The following function deletes the "minor type" or semantic value
** associated with a symbol.  The symbol can be either a terminal
** or nonterminal. "yymajor" is the symbol code, and "yypminor" is
** a pointer to the value to be deleted.  The code used to do the 
** deletions is derived from the %destructor and/or %token_destructor
** directives of the input grammar.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH
  ParseCTX_FETCH
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
    case 198: /* keep */
    case 199: /* tagitemlist */
    case 222: /* fill_opt */
    case 224: /* groupby_opt */
    case 225: /* orderby_opt */
    case 233: /* sortlist */
    case 237: /* grouplist */
{
#line 154 "sql.y"
tVariantListDestroy((yypminor->yy264));
#line 1268 "sql.c"
}
      break;
    case 216: /* select */
{
#line 282 "sql.y"
destroyQuerySql((yypminor->yy216));
#line 1275 "sql.c"
}
      break;
    case 218: /* selcollist */
    case 229: /* sclp */
    case 238: /* exprlist */
    case 241: /* itemlist */
{
#line 291 "sql.y"
tSQLExprListDestroy((yypminor->yy390));
#line 1285 "sql.c"
}
      break;
    case 220: /* where_opt */
    case 226: /* having_opt */
    case 230: /* expr */
    case 239: /* expritem */
{
#line 422 "sql.y"
tSQLExprDestroy((yypminor->yy222));
#line 1295 "sql.c"
}
      break;
    case 234: /* sortitem */
{
#line 355 "sql.y"
tVariantDestroy(&(yypminor->yy406));
#line 1302 "sql.c"
}
      break;
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
*/
static void yy_pop_parser_stack(yyParser *pParser){
  yyStackEntry *yytos;
  assert( pParser->yytos!=0 );
  assert( pParser->yytos > pParser->yystack );
  yytos = pParser->yytos--;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yy_destructor(pParser, yytos->major, &yytos->minor);
}

/*
** Clear all secondary memory allocations from the parser
*/
void ParseFinalize(void *p){
  yyParser *pParser = (yyParser*)p;
  while( pParser->yytos>pParser->yystack ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  if( pParser->yystack!=&pParser->yystk0 ) free(pParser->yystack);
#endif
}

#ifndef Parse_ENGINEALWAYSONSTACK
/* 
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
#ifndef YYPARSEFREENEVERNULL
  if( p==0 ) return;
#endif
  ParseFinalize(p);
  (*freeProc)(p);
}
#endif /* Parse_ENGINEALWAYSONSTACK */

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyhwm;
}
#endif

/* This array of booleans keeps track of the parser statement
** coverage.  The element yycoverage[X][Y] is set when the parser
** is in state X and has a lookahead token Y.  In a well-tested
** systems, every element of this matrix should end up being set.
*/
#if defined(YYCOVERAGE)
static unsigned char yycoverage[YYNSTATE][YYNTOKEN];
#endif

/*
** Write into out a description of every state/lookahead combination that
**
**   (1)  has not been used by the parser, and
**   (2)  is not a syntax error.
**
** Return the number of missed state/lookahead combinations.
*/
#if defined(YYCOVERAGE)
int ParseCoverage(FILE *out){
  int stateno, iLookAhead, i;
  int nMissed = 0;
  for(stateno=0; stateno<YYNSTATE; stateno++){
    i = yy_shift_ofst[stateno];
    for(iLookAhead=0; iLookAhead<YYNTOKEN; iLookAhead++){
      if( yy_lookahead[i+iLookAhead]!=iLookAhead ) continue;
      if( yycoverage[stateno][iLookAhead]==0 ) nMissed++;
      if( out ){
        fprintf(out,"State %d lookahead %s %s\n", stateno,
                yyTokenName[iLookAhead],
                yycoverage[stateno][iLookAhead] ? "ok" : "missed");
      }
    }
  }
  return nMissed;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
*/
static YYACTIONTYPE yy_find_shift_action(
  YYCODETYPE iLookAhead,    /* The look-ahead token */
  YYACTIONTYPE stateno      /* Current state number */
){
  int i;

  if( stateno>YY_MAX_SHIFT ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
#if defined(YYCOVERAGE)
  yycoverage[stateno][iLookAhead] = 1;
#endif
  do{
    i = yy_shift_ofst[stateno];
    assert( i>=0 );
    assert( i<=YY_ACTTAB_COUNT );
    assert( i+YYNTOKEN<=(int)YY_NLOOKAHEAD );
    assert( iLookAhead!=YYNOCODE );
    assert( iLookAhead < YYNTOKEN );
    i += iLookAhead;
    assert( i<(int)YY_NLOOKAHEAD );
    if( yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      assert( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0]) );
      iFallback = yyFallback[iLookAhead];
      if( iFallback!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        assert( yyFallback[iFallback]==0 ); /* Fallback loop must terminate */
        iLookAhead = iFallback;
        continue;
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        assert( j<(int)(sizeof(yy_lookahead)/sizeof(yy_lookahead[0])) );
        if( yy_lookahead[j]==YYWILDCARD && iLookAhead>0 ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead],
               yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
      return yy_default[stateno];
    }else{
      assert( i>=0 && i<sizeof(yy_action)/sizeof(yy_action[0]) );
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static YYACTIONTYPE yy_find_reduce_action(
  YYACTIONTYPE stateno,     /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser){
   ParseARG_FETCH
   ParseCTX_FETCH
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
/******** Begin %stack_overflow code ******************************************/
/******** End %stack_overflow code ********************************************/
   ParseARG_STORE /* Suppress warning about unused %extra_argument var */
   ParseCTX_STORE
}

/*
** Print tracing information for a SHIFT action
*/
#ifndef NDEBUG
static void yyTraceShift(yyParser *yypParser, int yyNewState, const char *zTag){
  if( yyTraceFILE ){
    if( yyNewState<YYNSTATE ){
      fprintf(yyTraceFILE,"%s%s '%s', go to state %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState);
    }else{
      fprintf(yyTraceFILE,"%s%s '%s', pending reduce %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState - YY_MIN_REDUCE);
    }
  }
}
#else
# define yyTraceShift(X,Y,Z)
#endif

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  YYACTIONTYPE yyNewState,      /* The new state to shift in */
  YYCODETYPE yyMajor,           /* The major token to shift in */
  ParseTOKENTYPE yyMinor        /* The minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yytos++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
    yypParser->yyhwm++;
    assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack) );
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yytos>yypParser->yystackEnd ){
    yypParser->yytos--;
    yyStackOverflow(yypParser);
    return;
  }
#else
  if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz] ){
    if( yyGrowStack(yypParser) ){
      yypParser->yytos--;
      yyStackOverflow(yypParser);
      return;
    }
  }
#endif
  if( yyNewState > YY_MAX_SHIFT ){
    yyNewState += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
  }
  yytos = yypParser->yytos;
  yytos->stateno = yyNewState;
  yytos->major = yyMajor;
  yytos->minor.yy0 = yyMinor;
  yyTraceShift(yypParser, yyNewState, "Shift");
}

/* For rule J, yyRuleInfoLhs[J] contains the symbol on the left-hand side
** of that rule */
static const YYCODETYPE yyRuleInfoLhs[] = {
   189,  /* (0) program ::= cmd */
   190,  /* (1) cmd ::= SHOW DATABASES */
   190,  /* (2) cmd ::= SHOW MNODES */
   190,  /* (3) cmd ::= SHOW DNODES */
   190,  /* (4) cmd ::= SHOW USERS */
   190,  /* (5) cmd ::= SHOW MODULES */
   190,  /* (6) cmd ::= SHOW QUERIES */
   190,  /* (7) cmd ::= SHOW CONNECTIONS */
   190,  /* (8) cmd ::= SHOW STREAMS */
   190,  /* (9) cmd ::= SHOW CONFIGS */
   190,  /* (10) cmd ::= SHOW SCORES */
   190,  /* (11) cmd ::= SHOW GRANTS */
   191,  /* (12) dbPrefix ::= */
   191,  /* (13) dbPrefix ::= ids DOT */
   193,  /* (14) cpxName ::= */
   193,  /* (15) cpxName ::= DOT ids */
   190,  /* (16) cmd ::= SHOW dbPrefix TABLES */
   190,  /* (17) cmd ::= SHOW dbPrefix TABLES LIKE ids */
   190,  /* (18) cmd ::= SHOW dbPrefix STABLES */
   190,  /* (19) cmd ::= SHOW dbPrefix STABLES LIKE ids */
   190,  /* (20) cmd ::= SHOW dbPrefix VGROUPS */
   190,  /* (21) cmd ::= DROP TABLE ifexists ids cpxName */
   190,  /* (22) cmd ::= DROP DATABASE ifexists ids */
   190,  /* (23) cmd ::= DROP USER ids */
   190,  /* (24) cmd ::= USE ids */
   190,  /* (25) cmd ::= DESCRIBE ids cpxName */
   190,  /* (26) cmd ::= ALTER USER ids PASS ids */
   190,  /* (27) cmd ::= ALTER USER ids PRIVILEGE ids */
   190,  /* (28) cmd ::= ALTER DNODE IP ids */
   190,  /* (29) cmd ::= ALTER DNODE IP ids ids */
   190,  /* (30) cmd ::= ALTER LOCAL ids */
   190,  /* (31) cmd ::= ALTER DATABASE ids alter_db_optr */
   192,  /* (32) ids ::= ID */
   192,  /* (33) ids ::= STRING */
   194,  /* (34) ifexists ::= IF EXISTS */
   194,  /* (35) ifexists ::= */
   196,  /* (36) ifnotexists ::= IF NOT EXISTS */
   196,  /* (37) ifnotexists ::= */
   190,  /* (38) cmd ::= CREATE DATABASE ifnotexists ids db_optr */
   190,  /* (39) cmd ::= CREATE USER ids PASS ids */
   198,  /* (40) keep ::= KEEP tagitemlist */
   200,  /* (41) tables ::= TABLES INTEGER */
   201,  /* (42) cache ::= CACHE INTEGER */
   202,  /* (43) replica ::= REPLICA INTEGER */
   203,  /* (44) days ::= DAYS INTEGER */
   204,  /* (45) rows ::= ROWS INTEGER */
   205,  /* (46) ablocks ::= ABLOCKS ID */
   206,  /* (47) tblocks ::= TBLOCKS INTEGER */
   207,  /* (48) ctime ::= CTIME INTEGER */
   208,  /* (49) clog ::= CLOG INTEGER */
   209,  /* (50) comp ::= COMP INTEGER */
   210,  /* (51) prec ::= PRECISION STRING */
   197,  /* (52) db_optr ::= */
   197,  /* (53) db_optr ::= db_optr tables */
   197,  /* (54) db_optr ::= db_optr cache */
   197,  /* (55) db_optr ::= db_optr replica */
   197,  /* (56) db_optr ::= db_optr days */
   197,  /* (57) db_optr ::= db_optr rows */
   197,  /* (58) db_optr ::= db_optr ablocks */
   197,  /* (59) db_optr ::= db_optr tblocks */
   197,  /* (60) db_optr ::= db_optr ctime */
   197,  /* (61) db_optr ::= db_optr clog */
   197,  /* (62) db_optr ::= db_optr comp */
   197,  /* (63) db_optr ::= db_optr prec */
   197,  /* (64) db_optr ::= db_optr keep */
   195,  /* (65) alter_db_optr ::= REPLICA tagitem */
   212,  /* (66) typename ::= ids */
   212,  /* (67) typename ::= ids LP signed RP */
   213,  /* (68) signed ::= INTEGER */
   213,  /* (69) signed ::= PLUS INTEGER */
   213,  /* (70) signed ::= MINUS INTEGER */
   190,  /* (71) cmd ::= CREATE TABLE ifnotexists ids cpxName create_table_args */
   214,  /* (72) create_table_args ::= LP columnlist RP */
   214,  /* (73) create_table_args ::= LP columnlist RP TAGS LP columnlist RP */
   214,  /* (74) create_table_args ::= USING ids cpxName TAGS LP tagitemlist RP */
   214,  /* (75) create_table_args ::= AS select */
   215,  /* (76) columnlist ::= columnlist COMMA column */
   215,  /* (77) columnlist ::= column */
   217,  /* (78) column ::= ids typename */
   199,  /* (79) tagitemlist ::= tagitemlist COMMA tagitem */
   199,  /* (80) tagitemlist ::= tagitem */
   211,  /* (81) tagitem ::= INTEGER */
   211,  /* (82) tagitem ::= FLOAT */
   211,  /* (83) tagitem ::= STRING */
   211,  /* (84) tagitem ::= BOOL */
   211,  /* (85) tagitem ::= NULL */
   211,  /* (86) tagitem ::= MINUS INTEGER */
   211,  /* (87) tagitem ::= MINUS FLOAT */
   190,  /* (88) cmd ::= select */
   216,  /* (89) select ::= SELECT selcollist from where_opt interval_opt fill_opt sliding_opt groupby_opt orderby_opt having_opt slimit_opt limit_opt */
   229,  /* (90) sclp ::= selcollist COMMA */
   229,  /* (91) sclp ::= */
   218,  /* (92) selcollist ::= sclp expr as */
   218,  /* (93) selcollist ::= sclp STAR */
   231,  /* (94) as ::= AS ids */
   231,  /* (95) as ::= ids */
   231,  /* (96) as ::= */
   219,  /* (97) from ::= FROM ids cpxName */
   232,  /* (98) tmvar ::= VARIABLE */
   221,  /* (99) interval_opt ::= INTERVAL LP tmvar RP */
   221,  /* (100) interval_opt ::= */
   222,  /* (101) fill_opt ::= */
   222,  /* (102) fill_opt ::= FILL LP ID COMMA tagitemlist RP */
   222,  /* (103) fill_opt ::= FILL LP ID RP */
   223,  /* (104) sliding_opt ::= SLIDING LP tmvar RP */
   223,  /* (105) sliding_opt ::= */
   225,  /* (106) orderby_opt ::= */
   225,  /* (107) orderby_opt ::= ORDER BY sortlist */
   233,  /* (108) sortlist ::= sortlist COMMA item sortorder */
   233,  /* (109) sortlist ::= item sortorder */
   235,  /* (110) item ::= ids cpxName */
   236,  /* (111) sortorder ::= ASC */
   236,  /* (112) sortorder ::= DESC */
   236,  /* (113) sortorder ::= */
   224,  /* (114) groupby_opt ::= */
   224,  /* (115) groupby_opt ::= GROUP BY grouplist */
   237,  /* (116) grouplist ::= grouplist COMMA item */
   237,  /* (117) grouplist ::= item */
   226,  /* (118) having_opt ::= */
   226,  /* (119) having_opt ::= HAVING expr */
   228,  /* (120) limit_opt ::= */
   228,  /* (121) limit_opt ::= LIMIT signed */
   228,  /* (122) limit_opt ::= LIMIT signed OFFSET signed */
   228,  /* (123) limit_opt ::= LIMIT signed COMMA signed */
   227,  /* (124) slimit_opt ::= */
   227,  /* (125) slimit_opt ::= SLIMIT signed */
   227,  /* (126) slimit_opt ::= SLIMIT signed SOFFSET signed */
   227,  /* (127) slimit_opt ::= SLIMIT signed COMMA signed */
   220,  /* (128) where_opt ::= */
   220,  /* (129) where_opt ::= WHERE expr */
   230,  /* (130) expr ::= LP expr RP */
   230,  /* (131) expr ::= ID */
   230,  /* (132) expr ::= ID DOT ID */
   230,  /* (133) expr ::= ID DOT STAR */
   230,  /* (134) expr ::= INTEGER */
   230,  /* (135) expr ::= MINUS INTEGER */
   230,  /* (136) expr ::= PLUS INTEGER */
   230,  /* (137) expr ::= FLOAT */
   230,  /* (138) expr ::= MINUS FLOAT */
   230,  /* (139) expr ::= PLUS FLOAT */
   230,  /* (140) expr ::= STRING */
   230,  /* (141) expr ::= NOW */
   230,  /* (142) expr ::= VARIABLE */
   230,  /* (143) expr ::= BOOL */
   230,  /* (144) expr ::= ID LP exprlist RP */
   230,  /* (145) expr ::= ID LP STAR RP */
   230,  /* (146) expr ::= expr AND expr */
   230,  /* (147) expr ::= expr OR expr */
   230,  /* (148) expr ::= expr LT expr */
   230,  /* (149) expr ::= expr GT expr */
   230,  /* (150) expr ::= expr LE expr */
   230,  /* (151) expr ::= expr GE expr */
   230,  /* (152) expr ::= expr NE expr */
   230,  /* (153) expr ::= expr EQ expr */
   230,  /* (154) expr ::= expr PLUS expr */
   230,  /* (155) expr ::= expr MINUS expr */
   230,  /* (156) expr ::= expr STAR expr */
   230,  /* (157) expr ::= expr SLASH expr */
   230,  /* (158) expr ::= expr REM expr */
   230,  /* (159) expr ::= expr LIKE expr */
   230,  /* (160) expr ::= expr IN LP exprlist RP */
   238,  /* (161) exprlist ::= exprlist COMMA expritem */
   238,  /* (162) exprlist ::= expritem */
   239,  /* (163) expritem ::= expr */
   239,  /* (164) expritem ::= */
   190,  /* (165) cmd ::= INSERT INTO cpxName insert_value_list */
   240,  /* (166) insert_value_list ::= VALUES LP itemlist RP */
   240,  /* (167) insert_value_list ::= insert_value_list VALUES LP itemlist RP */
   241,  /* (168) itemlist ::= itemlist COMMA expr */
   241,  /* (169) itemlist ::= expr */
   190,  /* (170) cmd ::= RESET QUERY CACHE */
   190,  /* (171) cmd ::= ALTER TABLE ids cpxName ADD COLUMN columnlist */
   190,  /* (172) cmd ::= ALTER TABLE ids cpxName DROP COLUMN ids */
   190,  /* (173) cmd ::= ALTER TABLE ids cpxName ADD TAG columnlist */
   190,  /* (174) cmd ::= ALTER TABLE ids cpxName DROP TAG ids */
   190,  /* (175) cmd ::= ALTER TABLE ids cpxName CHANGE TAG ids ids */
   190,  /* (176) cmd ::= ALTER TABLE ids cpxName SET TAG ids EQ tagitem */
   190,  /* (177) cmd ::= KILL CONNECTION IP COLON INTEGER */
   190,  /* (178) cmd ::= KILL STREAM IP COLON INTEGER COLON INTEGER */
   190,  /* (179) cmd ::= KILL QUERY IP COLON INTEGER COLON INTEGER */
   190,  /* (180) cmd ::= CREATE GATE ids STRING */
   190,  /* (181) cmd ::= QUERY GATE ids */
   190,  /* (182) cmd ::= UPDATE GATE ids STRING */
   190,  /* (183) cmd ::= DELETE GATE ids */
};

/* For rule J, yyRuleInfoNRhs[J] contains the negative of the number
** of symbols on the right-hand side of that rule. */
static const signed char yyRuleInfoNRhs[] = {
   -1,  /* (0) program ::= cmd */
   -2,  /* (1) cmd ::= SHOW DATABASES */
   -2,  /* (2) cmd ::= SHOW MNODES */
   -2,  /* (3) cmd ::= SHOW DNODES */
   -2,  /* (4) cmd ::= SHOW USERS */
   -2,  /* (5) cmd ::= SHOW MODULES */
   -2,  /* (6) cmd ::= SHOW QUERIES */
   -2,  /* (7) cmd ::= SHOW CONNECTIONS */
   -2,  /* (8) cmd ::= SHOW STREAMS */
   -2,  /* (9) cmd ::= SHOW CONFIGS */
   -2,  /* (10) cmd ::= SHOW SCORES */
   -2,  /* (11) cmd ::= SHOW GRANTS */
    0,  /* (12) dbPrefix ::= */
   -2,  /* (13) dbPrefix ::= ids DOT */
    0,  /* (14) cpxName ::= */
   -2,  /* (15) cpxName ::= DOT ids */
   -3,  /* (16) cmd ::= SHOW dbPrefix TABLES */
   -5,  /* (17) cmd ::= SHOW dbPrefix TABLES LIKE ids */
   -3,  /* (18) cmd ::= SHOW dbPrefix STABLES */
   -5,  /* (19) cmd ::= SHOW dbPrefix STABLES LIKE ids */
   -3,  /* (20) cmd ::= SHOW dbPrefix VGROUPS */
   -5,  /* (21) cmd ::= DROP TABLE ifexists ids cpxName */
   -4,  /* (22) cmd ::= DROP DATABASE ifexists ids */
   -3,  /* (23) cmd ::= DROP USER ids */
   -2,  /* (24) cmd ::= USE ids */
   -3,  /* (25) cmd ::= DESCRIBE ids cpxName */
   -5,  /* (26) cmd ::= ALTER USER ids PASS ids */
   -5,  /* (27) cmd ::= ALTER USER ids PRIVILEGE ids */
   -4,  /* (28) cmd ::= ALTER DNODE IP ids */
   -5,  /* (29) cmd ::= ALTER DNODE IP ids ids */
   -3,  /* (30) cmd ::= ALTER LOCAL ids */
   -4,  /* (31) cmd ::= ALTER DATABASE ids alter_db_optr */
   -1,  /* (32) ids ::= ID */
   -1,  /* (33) ids ::= STRING */
   -2,  /* (34) ifexists ::= IF EXISTS */
    0,  /* (35) ifexists ::= */
   -3,  /* (36) ifnotexists ::= IF NOT EXISTS */
    0,  /* (37) ifnotexists ::= */
   -5,  /* (38) cmd ::= CREATE DATABASE ifnotexists ids db_optr */
   -5,  /* (39) cmd ::= CREATE USER ids PASS ids */
   -2,  /* (40) keep ::= KEEP tagitemlist */
   -2,  /* (41) tables ::= TABLES INTEGER */
   -2,  /* (42) cache ::= CACHE INTEGER */
   -2,  /* (43) replica ::= REPLICA INTEGER */
   -2,  /* (44) days ::= DAYS INTEGER */
   -2,  /* (45) rows ::= ROWS INTEGER */
   -2,  /* (46) ablocks ::= ABLOCKS ID */
   -2,  /* (47) tblocks ::= TBLOCKS INTEGER */
   -2,  /* (48) ctime ::= CTIME INTEGER */
   -2,  /* (49) clog ::= CLOG INTEGER */
   -2,  /* (50) comp ::= COMP INTEGER */
   -2,  /* (51) prec ::= PRECISION STRING */
    0,  /* (52) db_optr ::= */
   -2,  /* (53) db_optr ::= db_optr tables */
   -2,  /* (54) db_optr ::= db_optr cache */
   -2,  /* (55) db_optr ::= db_optr replica */
   -2,  /* (56) db_optr ::= db_optr days */
   -2,  /* (57) db_optr ::= db_optr rows */
   -2,  /* (58) db_optr ::= db_optr ablocks */
   -2,  /* (59) db_optr ::= db_optr tblocks */
   -2,  /* (60) db_optr ::= db_optr ctime */
   -2,  /* (61) db_optr ::= db_optr clog */
   -2,  /* (62) db_optr ::= db_optr comp */
   -2,  /* (63) db_optr ::= db_optr prec */
   -2,  /* (64) db_optr ::= db_optr keep */
   -2,  /* (65) alter_db_optr ::= REPLICA tagitem */
   -1,  /* (66) typename ::= ids */
   -4,  /* (67) typename ::= ids LP signed RP */
   -1,  /* (68) signed ::= INTEGER */
   -2,  /* (69) signed ::= PLUS INTEGER */
   -2,  /* (70) signed ::= MINUS INTEGER */
   -6,  /* (71) cmd ::= CREATE TABLE ifnotexists ids cpxName create_table_args */
   -3,  /* (72) create_table_args ::= LP columnlist RP */
   -7,  /* (73) create_table_args ::= LP columnlist RP TAGS LP columnlist RP */
   -7,  /* (74) create_table_args ::= USING ids cpxName TAGS LP tagitemlist RP */
   -2,  /* (75) create_table_args ::= AS select */
   -3,  /* (76) columnlist ::= columnlist COMMA column */
   -1,  /* (77) columnlist ::= column */
   -2,  /* (78) column ::= ids typename */
   -3,  /* (79) tagitemlist ::= tagitemlist COMMA tagitem */
   -1,  /* (80) tagitemlist ::= tagitem */
   -1,  /* (81) tagitem ::= INTEGER */
   -1,  /* (82) tagitem ::= FLOAT */
   -1,  /* (83) tagitem ::= STRING */
   -1,  /* (84) tagitem ::= BOOL */
   -1,  /* (85) tagitem ::= NULL */
   -2,  /* (86) tagitem ::= MINUS INTEGER */
   -2,  /* (87) tagitem ::= MINUS FLOAT */
   -1,  /* (88) cmd ::= select */
  -12,  /* (89) select ::= SELECT selcollist from where_opt interval_opt fill_opt sliding_opt groupby_opt orderby_opt having_opt slimit_opt limit_opt */
   -2,  /* (90) sclp ::= selcollist COMMA */
    0,  /* (91) sclp ::= */
   -3,  /* (92) selcollist ::= sclp expr as */
   -2,  /* (93) selcollist ::= sclp STAR */
   -2,  /* (94) as ::= AS ids */
   -1,  /* (95) as ::= ids */
    0,  /* (96) as ::= */
   -3,  /* (97) from ::= FROM ids cpxName */
   -1,  /* (98) tmvar ::= VARIABLE */
   -4,  /* (99) interval_opt ::= INTERVAL LP tmvar RP */
    0,  /* (100) interval_opt ::= */
    0,  /* (101) fill_opt ::= */
   -6,  /* (102) fill_opt ::= FILL LP ID COMMA tagitemlist RP */
   -4,  /* (103) fill_opt ::= FILL LP ID RP */
   -4,  /* (104) sliding_opt ::= SLIDING LP tmvar RP */
    0,  /* (105) sliding_opt ::= */
    0,  /* (106) orderby_opt ::= */
   -3,  /* (107) orderby_opt ::= ORDER BY sortlist */
   -4,  /* (108) sortlist ::= sortlist COMMA item sortorder */
   -2,  /* (109) sortlist ::= item sortorder */
   -2,  /* (110) item ::= ids cpxName */
   -1,  /* (111) sortorder ::= ASC */
   -1,  /* (112) sortorder ::= DESC */
    0,  /* (113) sortorder ::= */
    0,  /* (114) groupby_opt ::= */
   -3,  /* (115) groupby_opt ::= GROUP BY grouplist */
   -3,  /* (116) grouplist ::= grouplist COMMA item */
   -1,  /* (117) grouplist ::= item */
    0,  /* (118) having_opt ::= */
   -2,  /* (119) having_opt ::= HAVING expr */
    0,  /* (120) limit_opt ::= */
   -2,  /* (121) limit_opt ::= LIMIT signed */
   -4,  /* (122) limit_opt ::= LIMIT signed OFFSET signed */
   -4,  /* (123) limit_opt ::= LIMIT signed COMMA signed */
    0,  /* (124) slimit_opt ::= */
   -2,  /* (125) slimit_opt ::= SLIMIT signed */
   -4,  /* (126) slimit_opt ::= SLIMIT signed SOFFSET signed */
   -4,  /* (127) slimit_opt ::= SLIMIT signed COMMA signed */
    0,  /* (128) where_opt ::= */
   -2,  /* (129) where_opt ::= WHERE expr */
   -3,  /* (130) expr ::= LP expr RP */
   -1,  /* (131) expr ::= ID */
   -3,  /* (132) expr ::= ID DOT ID */
   -3,  /* (133) expr ::= ID DOT STAR */
   -1,  /* (134) expr ::= INTEGER */
   -2,  /* (135) expr ::= MINUS INTEGER */
   -2,  /* (136) expr ::= PLUS INTEGER */
   -1,  /* (137) expr ::= FLOAT */
   -2,  /* (138) expr ::= MINUS FLOAT */
   -2,  /* (139) expr ::= PLUS FLOAT */
   -1,  /* (140) expr ::= STRING */
   -1,  /* (141) expr ::= NOW */
   -1,  /* (142) expr ::= VARIABLE */
   -1,  /* (143) expr ::= BOOL */
   -4,  /* (144) expr ::= ID LP exprlist RP */
   -4,  /* (145) expr ::= ID LP STAR RP */
   -3,  /* (146) expr ::= expr AND expr */
   -3,  /* (147) expr ::= expr OR expr */
   -3,  /* (148) expr ::= expr LT expr */
   -3,  /* (149) expr ::= expr GT expr */
   -3,  /* (150) expr ::= expr LE expr */
   -3,  /* (151) expr ::= expr GE expr */
   -3,  /* (152) expr ::= expr NE expr */
   -3,  /* (153) expr ::= expr EQ expr */
   -3,  /* (154) expr ::= expr PLUS expr */
   -3,  /* (155) expr ::= expr MINUS expr */
   -3,  /* (156) expr ::= expr STAR expr */
   -3,  /* (157) expr ::= expr SLASH expr */
   -3,  /* (158) expr ::= expr REM expr */
   -3,  /* (159) expr ::= expr LIKE expr */
   -5,  /* (160) expr ::= expr IN LP exprlist RP */
   -3,  /* (161) exprlist ::= exprlist COMMA expritem */
   -1,  /* (162) exprlist ::= expritem */
   -1,  /* (163) expritem ::= expr */
    0,  /* (164) expritem ::= */
   -4,  /* (165) cmd ::= INSERT INTO cpxName insert_value_list */
   -4,  /* (166) insert_value_list ::= VALUES LP itemlist RP */
   -5,  /* (167) insert_value_list ::= insert_value_list VALUES LP itemlist RP */
   -3,  /* (168) itemlist ::= itemlist COMMA expr */
   -1,  /* (169) itemlist ::= expr */
   -3,  /* (170) cmd ::= RESET QUERY CACHE */
   -7,  /* (171) cmd ::= ALTER TABLE ids cpxName ADD COLUMN columnlist */
   -7,  /* (172) cmd ::= ALTER TABLE ids cpxName DROP COLUMN ids */
   -7,  /* (173) cmd ::= ALTER TABLE ids cpxName ADD TAG columnlist */
   -7,  /* (174) cmd ::= ALTER TABLE ids cpxName DROP TAG ids */
   -8,  /* (175) cmd ::= ALTER TABLE ids cpxName CHANGE TAG ids ids */
   -9,  /* (176) cmd ::= ALTER TABLE ids cpxName SET TAG ids EQ tagitem */
   -5,  /* (177) cmd ::= KILL CONNECTION IP COLON INTEGER */
   -7,  /* (178) cmd ::= KILL STREAM IP COLON INTEGER COLON INTEGER */
   -7,  /* (179) cmd ::= KILL QUERY IP COLON INTEGER COLON INTEGER */
   -4,  /* (180) cmd ::= CREATE GATE ids STRING */
   -3,  /* (181) cmd ::= QUERY GATE ids */
   -4,  /* (182) cmd ::= UPDATE GATE ids STRING */
   -3,  /* (183) cmd ::= DELETE GATE ids */
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
**
** The yyLookahead and yyLookaheadToken parameters provide reduce actions
** access to the lookahead token (if any).  The yyLookahead will be YYNOCODE
** if the lookahead token has already been consumed.  As this procedure is
** only called from one place, optimizing compilers will in-line it, which
** means that the extra parameters have no performance impact.
*/
static YYACTIONTYPE yy_reduce(
  yyParser *yypParser,         /* The parser */
  unsigned int yyruleno,       /* Number of the rule by which to reduce */
  int yyLookahead,             /* Lookahead token, or YYNOCODE if none */
  ParseTOKENTYPE yyLookaheadToken  /* Value of the lookahead token */
  ParseCTX_PDECL                   /* %extra_context */
){
  int yygoto;                     /* The next state */
  YYACTIONTYPE yyact;             /* The next action */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH
  (void)yyLookahead;
  (void)yyLookaheadToken;
  yymsp = yypParser->yytos;
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfoNRhs[yyruleno];
    if( yysize ){
      fprintf(yyTraceFILE, "%sReduce %d [%s], go to state %d.\n",
        yyTracePrompt,
        yyruleno, yyRuleName[yyruleno], yymsp[yysize].stateno);
    }else{
      fprintf(yyTraceFILE, "%sReduce %d [%s].\n",
        yyTracePrompt, yyruleno, yyRuleName[yyruleno]);
    }
  }
#endif /* NDEBUG */

  /* Check that the stack is large enough to grow by a single entry
  ** if the RHS of the rule is empty.  This ensures that there is room
  ** enough on the stack to push the LHS value */
  if( yyRuleInfoNRhs[yyruleno]==0 ){
#ifdef YYTRACKMAXSTACKDEPTH
    if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
      yypParser->yyhwm++;
      assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack));
    }
#endif
#if YYSTACKDEPTH>0 
    if( yypParser->yytos>=yypParser->yystackEnd ){
      yyStackOverflow(yypParser);
      /* The call to yyStackOverflow() above pops the stack until it is
      ** empty, causing the main parser loop to exit.  So the return value
      ** is never used and does not matter. */
      return 0;
    }
#else
    if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz-1] ){
      if( yyGrowStack(yypParser) ){
        yyStackOverflow(yypParser);
        /* The call to yyStackOverflow() above pops the stack until it is
        ** empty, causing the main parser loop to exit.  So the return value
        ** is never used and does not matter. */
        return 0;
      }
      yymsp = yypParser->yytos;
    }
#endif
  }

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
/********** Begin reduce actions **********************************************/
        YYMINORTYPE yylhsminor;
      case 0: /* program ::= cmd */
      case 52: /* db_optr ::= */ yytestcase(yyruleno==52);
#line 60 "sql.y"
{}
#line 2054 "sql.c"
        break;
      case 1: /* cmd ::= SHOW DATABASES */
#line 63 "sql.y"
{ setDCLSQLElems(pInfo, SHOW_DATABASES, 0);}
#line 2059 "sql.c"
        break;
      case 2: /* cmd ::= SHOW MNODES */
#line 64 "sql.y"
{ setDCLSQLElems(pInfo, SHOW_MNODES, 0);}
#line 2064 "sql.c"
        break;
      case 3: /* cmd ::= SHOW DNODES */
#line 65 "sql.y"
{ setDCLSQLElems(pInfo, SHOW_DNODES, 0);}
#line 2069 "sql.c"
        break;
      case 4: /* cmd ::= SHOW USERS */
#line 66 "sql.y"
{ setDCLSQLElems(pInfo, SHOW_USERS, 0);}
#line 2074 "sql.c"
        break;
      case 5: /* cmd ::= SHOW MODULES */
#line 68 "sql.y"
{ setDCLSQLElems(pInfo, SHOW_MODULES, 0);  }
#line 2079 "sql.c"
        break;
      case 6: /* cmd ::= SHOW QUERIES */
#line 69 "sql.y"
{ setDCLSQLElems(pInfo, SHOW_QUERIES, 0);  }
#line 2084 "sql.c"
        break;
      case 7: /* cmd ::= SHOW CONNECTIONS */
#line 70 "sql.y"
{ setDCLSQLElems(pInfo, SHOW_CONNECTIONS, 0);}
#line 2089 "sql.c"
        break;
      case 8: /* cmd ::= SHOW STREAMS */
#line 71 "sql.y"
{ setDCLSQLElems(pInfo, SHOW_STREAMS, 0);  }
#line 2094 "sql.c"
        break;
      case 9: /* cmd ::= SHOW CONFIGS */
#line 72 "sql.y"
{ setDCLSQLElems(pInfo, SHOW_CONFIGS, 0);  }
#line 2099 "sql.c"
        break;
      case 10: /* cmd ::= SHOW SCORES */
#line 73 "sql.y"
{ setDCLSQLElems(pInfo, SHOW_SCORES, 0);   }
#line 2104 "sql.c"
        break;
      case 11: /* cmd ::= SHOW GRANTS */
#line 74 "sql.y"
{ setDCLSQLElems(pInfo, SHOW_GRANTS, 0);   }
#line 2109 "sql.c"
        break;
      case 12: /* dbPrefix ::= */
      case 35: /* ifexists ::= */ yytestcase(yyruleno==35);
      case 37: /* ifnotexists ::= */ yytestcase(yyruleno==37);
#line 77 "sql.y"
{yymsp[1].minor.yy0.n = 0;}
#line 2116 "sql.c"
        break;
      case 13: /* dbPrefix ::= ids DOT */
#line 78 "sql.y"
{yylhsminor.yy0 = yymsp[-1].minor.yy0;  }
#line 2121 "sql.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 14: /* cpxName ::= */
#line 81 "sql.y"
{yymsp[1].minor.yy0.n = 0;  }
#line 2127 "sql.c"
        break;
      case 15: /* cpxName ::= DOT ids */
#line 82 "sql.y"
{yymsp[-1].minor.yy0 = yymsp[0].minor.yy0; yymsp[-1].minor.yy0.n += 1;    }
#line 2132 "sql.c"
        break;
      case 16: /* cmd ::= SHOW dbPrefix TABLES */
#line 84 "sql.y"
{
    setDCLSQLElems(pInfo, SHOW_TABLES, 1, &yymsp[-1].minor.yy0);
}
#line 2139 "sql.c"
        break;
      case 17: /* cmd ::= SHOW dbPrefix TABLES LIKE ids */
#line 88 "sql.y"
{
    setDCLSQLElems(pInfo, SHOW_TABLES, 2, &yymsp[-3].minor.yy0, &yymsp[0].minor.yy0);
}
#line 2146 "sql.c"
        break;
      case 18: /* cmd ::= SHOW dbPrefix STABLES */
#line 92 "sql.y"
{
    setDCLSQLElems(pInfo, SHOW_STABLES, 1, &yymsp[-1].minor.yy0);
}
#line 2153 "sql.c"
        break;
      case 19: /* cmd ::= SHOW dbPrefix STABLES LIKE ids */
#line 96 "sql.y"
{
    SSQLToken token;
    setDBName(&token, &yymsp[-3].minor.yy0);
    setDCLSQLElems(pInfo, SHOW_STABLES, 2, &token, &yymsp[0].minor.yy0);
}
#line 2162 "sql.c"
        break;
      case 20: /* cmd ::= SHOW dbPrefix VGROUPS */
#line 102 "sql.y"
{
    SSQLToken token;
    setDBName(&token, &yymsp[-1].minor.yy0);
    setDCLSQLElems(pInfo, SHOW_VGROUPS, 1, &token);
}
#line 2171 "sql.c"
        break;
      case 21: /* cmd ::= DROP TABLE ifexists ids cpxName */
#line 109 "sql.y"
{
    yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
    setDCLSQLElems(pInfo, DROP_TABLE, 2, &yymsp[-1].minor.yy0, &yymsp[-2].minor.yy0);
}
#line 2179 "sql.c"
        break;
      case 22: /* cmd ::= DROP DATABASE ifexists ids */
#line 114 "sql.y"
{ setDCLSQLElems(pInfo, DROP_DATABASE, 2, &yymsp[0].minor.yy0, &yymsp[-1].minor.yy0); }
#line 2184 "sql.c"
        break;
      case 23: /* cmd ::= DROP USER ids */
#line 115 "sql.y"
{ setDCLSQLElems(pInfo, DROP_USER, 1, &yymsp[0].minor.yy0);     }
#line 2189 "sql.c"
        break;
      case 24: /* cmd ::= USE ids */
#line 118 "sql.y"
{ setDCLSQLElems(pInfo, USE_DATABASE, 1, &yymsp[0].minor.yy0);}
#line 2194 "sql.c"
        break;
      case 25: /* cmd ::= DESCRIBE ids cpxName */
#line 121 "sql.y"
{
    yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
    setDCLSQLElems(pInfo, DESCRIBE_TABLE, 1, &yymsp[-1].minor.yy0);
}
#line 2202 "sql.c"
        break;
      case 26: /* cmd ::= ALTER USER ids PASS ids */
#line 127 "sql.y"
{ setDCLSQLElems(pInfo, ALTER_USER_PASSWD, 2, &yymsp[-2].minor.yy0, &yymsp[0].minor.yy0);    }
#line 2207 "sql.c"
        break;
      case 27: /* cmd ::= ALTER USER ids PRIVILEGE ids */
#line 128 "sql.y"
{ setDCLSQLElems(pInfo, ALTER_USER_PRIVILEGES, 2, &yymsp[-2].minor.yy0, &yymsp[0].minor.yy0);}
#line 2212 "sql.c"
        break;
      case 28: /* cmd ::= ALTER DNODE IP ids */
#line 129 "sql.y"
{ setDCLSQLElems(pInfo, ALTER_DNODE, 2, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0);          }
#line 2217 "sql.c"
        break;
      case 29: /* cmd ::= ALTER DNODE IP ids ids */
#line 130 "sql.y"
{ setDCLSQLElems(pInfo, ALTER_DNODE, 3, &yymsp[-2].minor.yy0, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0);      }
#line 2222 "sql.c"
        break;
      case 30: /* cmd ::= ALTER LOCAL ids */
#line 131 "sql.y"
{ setDCLSQLElems(pInfo, ALTER_LOCAL, 1, &yymsp[0].minor.yy0);              }
#line 2227 "sql.c"
        break;
      case 31: /* cmd ::= ALTER DATABASE ids alter_db_optr */
#line 132 "sql.y"
{ SSQLToken t = {0};  setCreateDBSQL(pInfo, ALTER_DATABASE, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy82, &t);}
#line 2232 "sql.c"
        break;
      case 32: /* ids ::= ID */
      case 33: /* ids ::= STRING */ yytestcase(yyruleno==33);
#line 138 "sql.y"
{yylhsminor.yy0 = yymsp[0].minor.yy0; }
#line 2238 "sql.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 34: /* ifexists ::= IF EXISTS */
#line 142 "sql.y"
{yymsp[-1].minor.yy0.n = 1;}
#line 2244 "sql.c"
        break;
      case 36: /* ifnotexists ::= IF NOT EXISTS */
#line 146 "sql.y"
{yymsp[-2].minor.yy0.n = 1;}
#line 2249 "sql.c"
        break;
      case 38: /* cmd ::= CREATE DATABASE ifnotexists ids db_optr */
#line 150 "sql.y"
{ setCreateDBSQL(pInfo, CREATE_DATABASE, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy82, &yymsp[-2].minor.yy0);}
#line 2254 "sql.c"
        break;
      case 39: /* cmd ::= CREATE USER ids PASS ids */
#line 151 "sql.y"
{ setDCLSQLElems(pInfo, CREATE_USER, 2, &yymsp[-2].minor.yy0, &yymsp[0].minor.yy0);}
#line 2259 "sql.c"
        break;
      case 40: /* keep ::= KEEP tagitemlist */
#line 155 "sql.y"
{ yymsp[-1].minor.yy264 = yymsp[0].minor.yy264; }
#line 2264 "sql.c"
        break;
      case 41: /* tables ::= TABLES INTEGER */
      case 42: /* cache ::= CACHE INTEGER */ yytestcase(yyruleno==42);
      case 43: /* replica ::= REPLICA INTEGER */ yytestcase(yyruleno==43);
      case 44: /* days ::= DAYS INTEGER */ yytestcase(yyruleno==44);
      case 45: /* rows ::= ROWS INTEGER */ yytestcase(yyruleno==45);
      case 46: /* ablocks ::= ABLOCKS ID */ yytestcase(yyruleno==46);
      case 47: /* tblocks ::= TBLOCKS INTEGER */ yytestcase(yyruleno==47);
      case 48: /* ctime ::= CTIME INTEGER */ yytestcase(yyruleno==48);
      case 49: /* clog ::= CLOG INTEGER */ yytestcase(yyruleno==49);
      case 50: /* comp ::= COMP INTEGER */ yytestcase(yyruleno==50);
      case 51: /* prec ::= PRECISION STRING */ yytestcase(yyruleno==51);
#line 157 "sql.y"
{ yymsp[-1].minor.yy0 = yymsp[0].minor.yy0; }
#line 2279 "sql.c"
        break;
      case 53: /* db_optr ::= db_optr tables */
#line 172 "sql.y"
{ yylhsminor.yy82 = yymsp[-1].minor.yy82; yylhsminor.yy82.tablesPerVnode = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 2284 "sql.c"
  yymsp[-1].minor.yy82 = yylhsminor.yy82;
        break;
      case 54: /* db_optr ::= db_optr cache */
#line 173 "sql.y"
{ yylhsminor.yy82 = yymsp[-1].minor.yy82; yylhsminor.yy82.cacheBlockSize = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 2290 "sql.c"
  yymsp[-1].minor.yy82 = yylhsminor.yy82;
        break;
      case 55: /* db_optr ::= db_optr replica */
#line 174 "sql.y"
{ yylhsminor.yy82 = yymsp[-1].minor.yy82; yylhsminor.yy82.replica = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 2296 "sql.c"
  yymsp[-1].minor.yy82 = yylhsminor.yy82;
        break;
      case 56: /* db_optr ::= db_optr days */
#line 175 "sql.y"
{ yylhsminor.yy82 = yymsp[-1].minor.yy82; yylhsminor.yy82.daysPerFile = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 2302 "sql.c"
  yymsp[-1].minor.yy82 = yylhsminor.yy82;
        break;
      case 57: /* db_optr ::= db_optr rows */
#line 176 "sql.y"
{ yylhsminor.yy82 = yymsp[-1].minor.yy82; yylhsminor.yy82.rowPerFileBlock = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 2308 "sql.c"
  yymsp[-1].minor.yy82 = yylhsminor.yy82;
        break;
      case 58: /* db_optr ::= db_optr ablocks */
#line 177 "sql.y"
{ yylhsminor.yy82 = yymsp[-1].minor.yy82; yylhsminor.yy82.numOfAvgCacheBlocks = strtod(yymsp[0].minor.yy0.z, NULL); }
#line 2314 "sql.c"
  yymsp[-1].minor.yy82 = yylhsminor.yy82;
        break;
      case 59: /* db_optr ::= db_optr tblocks */
#line 178 "sql.y"
{ yylhsminor.yy82 = yymsp[-1].minor.yy82; yylhsminor.yy82.numOfBlocksPerTable = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 2320 "sql.c"
  yymsp[-1].minor.yy82 = yylhsminor.yy82;
        break;
      case 60: /* db_optr ::= db_optr ctime */
#line 179 "sql.y"
{ yylhsminor.yy82 = yymsp[-1].minor.yy82; yylhsminor.yy82.commitTime = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 2326 "sql.c"
  yymsp[-1].minor.yy82 = yylhsminor.yy82;
        break;
      case 61: /* db_optr ::= db_optr clog */
#line 180 "sql.y"
{ yylhsminor.yy82 = yymsp[-1].minor.yy82; yylhsminor.yy82.commitLog = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 2332 "sql.c"
  yymsp[-1].minor.yy82 = yylhsminor.yy82;
        break;
      case 62: /* db_optr ::= db_optr comp */
#line 181 "sql.y"
{ yylhsminor.yy82 = yymsp[-1].minor.yy82; yylhsminor.yy82.compressionLevel = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 2338 "sql.c"
  yymsp[-1].minor.yy82 = yylhsminor.yy82;
        break;
      case 63: /* db_optr ::= db_optr prec */
#line 182 "sql.y"
{ yylhsminor.yy82 = yymsp[-1].minor.yy82; yylhsminor.yy82.precision = yymsp[0].minor.yy0; }
#line 2344 "sql.c"
  yymsp[-1].minor.yy82 = yylhsminor.yy82;
        break;
      case 64: /* db_optr ::= db_optr keep */
#line 183 "sql.y"
{ yylhsminor.yy82 = yymsp[-1].minor.yy82; yylhsminor.yy82.keep = yymsp[0].minor.yy264; }
#line 2350 "sql.c"
  yymsp[-1].minor.yy82 = yylhsminor.yy82;
        break;
      case 65: /* alter_db_optr ::= REPLICA tagitem */
#line 186 "sql.y"
{
    yymsp[-1].minor.yy82.replica = yymsp[0].minor.yy406.i64Key;
}
#line 2358 "sql.c"
        break;
      case 66: /* typename ::= ids */
#line 191 "sql.y"
{ tSQLSetColumnType (&yylhsminor.yy339, &yymsp[0].minor.yy0); }
#line 2363 "sql.c"
  yymsp[0].minor.yy339 = yylhsminor.yy339;
        break;
      case 67: /* typename ::= ids LP signed RP */
#line 194 "sql.y"
{
    yymsp[-3].minor.yy0.type = -yymsp[-1].minor.yy85;          // negative value of name length
    tSQLSetColumnType(&yylhsminor.yy339, &yymsp[-3].minor.yy0);
}
#line 2372 "sql.c"
  yymsp[-3].minor.yy339 = yylhsminor.yy339;
        break;
      case 68: /* signed ::= INTEGER */
#line 200 "sql.y"
{ yylhsminor.yy85 = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 2378 "sql.c"
  yymsp[0].minor.yy85 = yylhsminor.yy85;
        break;
      case 69: /* signed ::= PLUS INTEGER */
#line 201 "sql.y"
{ yymsp[-1].minor.yy85 = strtol(yymsp[0].minor.yy0.z, NULL, 10); }
#line 2384 "sql.c"
        break;
      case 70: /* signed ::= MINUS INTEGER */
#line 202 "sql.y"
{ yymsp[-1].minor.yy85 = -strtol(yymsp[0].minor.yy0.z, NULL, 10);}
#line 2389 "sql.c"
        break;
      case 71: /* cmd ::= CREATE TABLE ifnotexists ids cpxName create_table_args */
#line 205 "sql.y"
{
    yymsp[-2].minor.yy0.n += yymsp[-1].minor.yy0.n;
    setCreatedMeterName(pInfo, &yymsp[-2].minor.yy0, &yymsp[-3].minor.yy0);
}
#line 2397 "sql.c"
        break;
      case 72: /* create_table_args ::= LP columnlist RP */
#line 211 "sql.y"
{
    yymsp[-2].minor.yy450 = tSetCreateSQLElems(yymsp[-1].minor.yy155, NULL, NULL, NULL, NULL, TSQL_CREATE_NORMAL_METER);
    setSQLInfo(pInfo, yymsp[-2].minor.yy450, NULL, TSQL_CREATE_NORMAL_METER);
}
#line 2405 "sql.c"
        break;
      case 73: /* create_table_args ::= LP columnlist RP TAGS LP columnlist RP */
#line 217 "sql.y"
{
    yymsp[-6].minor.yy450 = tSetCreateSQLElems(yymsp[-5].minor.yy155, yymsp[-1].minor.yy155, NULL, NULL, NULL, TSQL_CREATE_NORMAL_METRIC);
    setSQLInfo(pInfo, yymsp[-6].minor.yy450, NULL, TSQL_CREATE_NORMAL_METRIC);
}
#line 2413 "sql.c"
        break;
      case 74: /* create_table_args ::= USING ids cpxName TAGS LP tagitemlist RP */
#line 224 "sql.y"
{
    yymsp[-5].minor.yy0.n += yymsp[-4].minor.yy0.n;
    yymsp[-6].minor.yy450 = tSetCreateSQLElems(NULL, NULL, &yymsp[-5].minor.yy0, yymsp[-1].minor.yy264, NULL, TSQL_CREATE_METER_FROM_METRIC);
    setSQLInfo(pInfo, yymsp[-6].minor.yy450, NULL, TSQL_CREATE_METER_FROM_METRIC);
}
#line 2422 "sql.c"
        break;
      case 75: /* create_table_args ::= AS select */
#line 232 "sql.y"
{
    yymsp[-1].minor.yy450 = tSetCreateSQLElems(NULL, NULL, NULL, NULL, yymsp[0].minor.yy216, TSQL_CREATE_STREAM);
    setSQLInfo(pInfo, yymsp[-1].minor.yy450, NULL, TSQL_CREATE_STREAM);
}
#line 2430 "sql.c"
        break;
      case 76: /* columnlist ::= columnlist COMMA column */
#line 239 "sql.y"
{yylhsminor.yy155 = tFieldListAppend(yymsp[-2].minor.yy155, &yymsp[0].minor.yy339);   }
#line 2435 "sql.c"
  yymsp[-2].minor.yy155 = yylhsminor.yy155;
        break;
      case 77: /* columnlist ::= column */
#line 240 "sql.y"
{yylhsminor.yy155 = tFieldListAppend(NULL, &yymsp[0].minor.yy339);}
#line 2441 "sql.c"
  yymsp[0].minor.yy155 = yylhsminor.yy155;
        break;
      case 78: /* column ::= ids typename */
#line 244 "sql.y"
{
    tSQLSetColumnInfo(&yylhsminor.yy339, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy339);
}
#line 2449 "sql.c"
  yymsp[-1].minor.yy339 = yylhsminor.yy339;
        break;
      case 79: /* tagitemlist ::= tagitemlist COMMA tagitem */
#line 252 "sql.y"
{ yylhsminor.yy264 = tVariantListAppend(yymsp[-2].minor.yy264, &yymsp[0].minor.yy406, -1);    }
#line 2455 "sql.c"
  yymsp[-2].minor.yy264 = yylhsminor.yy264;
        break;
      case 80: /* tagitemlist ::= tagitem */
#line 253 "sql.y"
{ yylhsminor.yy264 = tVariantListAppend(NULL, &yymsp[0].minor.yy406, -1); }
#line 2461 "sql.c"
  yymsp[0].minor.yy264 = yylhsminor.yy264;
        break;
      case 81: /* tagitem ::= INTEGER */
      case 82: /* tagitem ::= FLOAT */ yytestcase(yyruleno==82);
      case 83: /* tagitem ::= STRING */ yytestcase(yyruleno==83);
      case 84: /* tagitem ::= BOOL */ yytestcase(yyruleno==84);
#line 255 "sql.y"
{toTSDBType(yymsp[0].minor.yy0.type); tVariantCreate(&yylhsminor.yy406, &yymsp[0].minor.yy0); }
#line 2470 "sql.c"
  yymsp[0].minor.yy406 = yylhsminor.yy406;
        break;
      case 85: /* tagitem ::= NULL */
#line 259 "sql.y"
{ yymsp[0].minor.yy0.type = TK_STRING; toTSDBType(yymsp[0].minor.yy0.type); tVariantCreate(&yylhsminor.yy406, &yymsp[0].minor.yy0); }
#line 2476 "sql.c"
  yymsp[0].minor.yy406 = yylhsminor.yy406;
        break;
      case 86: /* tagitem ::= MINUS INTEGER */
      case 87: /* tagitem ::= MINUS FLOAT */ yytestcase(yyruleno==87);
#line 261 "sql.y"
{
    yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;
    yymsp[-1].minor.yy0.type = yymsp[0].minor.yy0.type;
    toTSDBType(yymsp[-1].minor.yy0.type);
    tVariantCreate(&yylhsminor.yy406, &yymsp[-1].minor.yy0);
}
#line 2488 "sql.c"
  yymsp[-1].minor.yy406 = yylhsminor.yy406;
        break;
      case 88: /* cmd ::= select */
#line 277 "sql.y"
{
    setSQLInfo(pInfo, yymsp[0].minor.yy216, NULL, TSQL_QUERY_METER);
}
#line 2496 "sql.c"
        break;
      case 89: /* select ::= SELECT selcollist from where_opt interval_opt fill_opt sliding_opt groupby_opt orderby_opt having_opt slimit_opt limit_opt */
#line 283 "sql.y"
{
  yylhsminor.yy216 = tSetQuerySQLElems(&yymsp[-11].minor.yy0, yymsp[-10].minor.yy390, &yymsp[-9].minor.yy0, yymsp[-8].minor.yy222, yymsp[-4].minor.yy264, yymsp[-3].minor.yy264, &yymsp[-7].minor.yy0, &yymsp[-5].minor.yy0, yymsp[-6].minor.yy264, &yymsp[0].minor.yy350, &yymsp[-1].minor.yy350);
}
#line 2503 "sql.c"
  yymsp[-11].minor.yy216 = yylhsminor.yy216;
        break;
      case 90: /* sclp ::= selcollist COMMA */
#line 295 "sql.y"
{yylhsminor.yy390 = yymsp[-1].minor.yy390;}
#line 2509 "sql.c"
  yymsp[-1].minor.yy390 = yylhsminor.yy390;
        break;
      case 91: /* sclp ::= */
#line 296 "sql.y"
{yymsp[1].minor.yy390 = 0;}
#line 2515 "sql.c"
        break;
      case 92: /* selcollist ::= sclp expr as */
#line 297 "sql.y"
{
   yylhsminor.yy390 = tSQLExprListAppend(yymsp[-2].minor.yy390, yymsp[-1].minor.yy222, yymsp[0].minor.yy0.n?&yymsp[0].minor.yy0:0);
}
#line 2522 "sql.c"
  yymsp[-2].minor.yy390 = yylhsminor.yy390;
        break;
      case 93: /* selcollist ::= sclp STAR */
#line 301 "sql.y"
{
   tSQLExpr *pNode = tSQLExprIdValueCreate(NULL, TK_ALL);
   yylhsminor.yy390 = tSQLExprListAppend(yymsp[-1].minor.yy390, pNode, 0);
}
#line 2531 "sql.c"
  yymsp[-1].minor.yy390 = yylhsminor.yy390;
        break;
      case 94: /* as ::= AS ids */
#line 310 "sql.y"
{ yymsp[-1].minor.yy0 = yymsp[0].minor.yy0;    }
#line 2537 "sql.c"
        break;
      case 95: /* as ::= ids */
#line 311 "sql.y"
{ yylhsminor.yy0 = yymsp[0].minor.yy0;    }
#line 2542 "sql.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 96: /* as ::= */
#line 312 "sql.y"
{ yymsp[1].minor.yy0.n = 0;  }
#line 2548 "sql.c"
        break;
      case 97: /* from ::= FROM ids cpxName */
#line 317 "sql.y"
{yymsp[-2].minor.yy0 = yymsp[-1].minor.yy0; yymsp[-2].minor.yy0.n += yymsp[0].minor.yy0.n;}
#line 2553 "sql.c"
        break;
      case 98: /* tmvar ::= VARIABLE */
#line 321 "sql.y"
{yylhsminor.yy0 = yymsp[0].minor.yy0;}
#line 2558 "sql.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 99: /* interval_opt ::= INTERVAL LP tmvar RP */
      case 104: /* sliding_opt ::= SLIDING LP tmvar RP */ yytestcase(yyruleno==104);
#line 324 "sql.y"
{yymsp[-3].minor.yy0 = yymsp[-1].minor.yy0;     }
#line 2565 "sql.c"
        break;
      case 100: /* interval_opt ::= */
      case 105: /* sliding_opt ::= */ yytestcase(yyruleno==105);
#line 325 "sql.y"
{yymsp[1].minor.yy0.n = 0;   }
#line 2571 "sql.c"
        break;
      case 101: /* fill_opt ::= */
#line 329 "sql.y"
{yymsp[1].minor.yy264 = 0;     }
#line 2576 "sql.c"
        break;
      case 102: /* fill_opt ::= FILL LP ID COMMA tagitemlist RP */
#line 330 "sql.y"
{
    tVariant A = {0};
    toTSDBType(yymsp[-3].minor.yy0.type);
    tVariantCreate(&A, &yymsp[-3].minor.yy0);

    tVariantListInsert(yymsp[-1].minor.yy264, &A, -1, 0);
    yymsp[-5].minor.yy264 = yymsp[-1].minor.yy264;
}
#line 2588 "sql.c"
        break;
      case 103: /* fill_opt ::= FILL LP ID RP */
#line 339 "sql.y"
{
    toTSDBType(yymsp[-1].minor.yy0.type);
    yymsp[-3].minor.yy264 = tVariantListAppendToken(NULL, &yymsp[-1].minor.yy0, -1);
}
#line 2596 "sql.c"
        break;
      case 106: /* orderby_opt ::= */
      case 114: /* groupby_opt ::= */ yytestcase(yyruleno==114);
#line 357 "sql.y"
{yymsp[1].minor.yy264 = 0;}
#line 2602 "sql.c"
        break;
      case 107: /* orderby_opt ::= ORDER BY sortlist */
      case 115: /* groupby_opt ::= GROUP BY grouplist */ yytestcase(yyruleno==115);
#line 358 "sql.y"
{yymsp[-2].minor.yy264 = yymsp[0].minor.yy264;}
#line 2608 "sql.c"
        break;
      case 108: /* sortlist ::= sortlist COMMA item sortorder */
#line 360 "sql.y"
{
    yylhsminor.yy264 = tVariantListAppend(yymsp[-3].minor.yy264, &yymsp[-1].minor.yy406, yymsp[0].minor.yy328);
}
#line 2615 "sql.c"
  yymsp[-3].minor.yy264 = yylhsminor.yy264;
        break;
      case 109: /* sortlist ::= item sortorder */
#line 364 "sql.y"
{
  yylhsminor.yy264 = tVariantListAppend(NULL, &yymsp[-1].minor.yy406, yymsp[0].minor.yy328);
}
#line 2623 "sql.c"
  yymsp[-1].minor.yy264 = yylhsminor.yy264;
        break;
      case 110: /* item ::= ids cpxName */
#line 369 "sql.y"
{
  toTSDBType(yymsp[-1].minor.yy0.type);
  yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n;

  tVariantCreate(&yylhsminor.yy406, &yymsp[-1].minor.yy0);
}
#line 2634 "sql.c"
  yymsp[-1].minor.yy406 = yylhsminor.yy406;
        break;
      case 111: /* sortorder ::= ASC */
#line 377 "sql.y"
{yymsp[0].minor.yy328 = TSQL_SO_ASC; }
#line 2640 "sql.c"
        break;
      case 112: /* sortorder ::= DESC */
#line 378 "sql.y"
{yymsp[0].minor.yy328 = TSQL_SO_DESC;}
#line 2645 "sql.c"
        break;
      case 113: /* sortorder ::= */
#line 379 "sql.y"
{yymsp[1].minor.yy328 = TSQL_SO_ASC;}
#line 2650 "sql.c"
        break;
      case 116: /* grouplist ::= grouplist COMMA item */
#line 390 "sql.y"
{
  yylhsminor.yy264 = tVariantListAppend(yymsp[-2].minor.yy264, &yymsp[0].minor.yy406, -1);
}
#line 2657 "sql.c"
  yymsp[-2].minor.yy264 = yylhsminor.yy264;
        break;
      case 117: /* grouplist ::= item */
#line 394 "sql.y"
{
  yylhsminor.yy264 = tVariantListAppend(NULL, &yymsp[0].minor.yy406, -1);
}
#line 2665 "sql.c"
  yymsp[0].minor.yy264 = yylhsminor.yy264;
        break;
      case 118: /* having_opt ::= */
      case 128: /* where_opt ::= */ yytestcase(yyruleno==128);
      case 164: /* expritem ::= */ yytestcase(yyruleno==164);
#line 401 "sql.y"
{yymsp[1].minor.yy222 = 0;}
#line 2673 "sql.c"
        break;
      case 119: /* having_opt ::= HAVING expr */
      case 129: /* where_opt ::= WHERE expr */ yytestcase(yyruleno==129);
#line 402 "sql.y"
{yymsp[-1].minor.yy222 = yymsp[0].minor.yy222;}
#line 2679 "sql.c"
        break;
      case 120: /* limit_opt ::= */
      case 124: /* slimit_opt ::= */ yytestcase(yyruleno==124);
#line 406 "sql.y"
{yymsp[1].minor.yy350.limit = -1; yymsp[1].minor.yy350.offset = 0;}
#line 2685 "sql.c"
        break;
      case 121: /* limit_opt ::= LIMIT signed */
      case 125: /* slimit_opt ::= SLIMIT signed */ yytestcase(yyruleno==125);
#line 407 "sql.y"
{yymsp[-1].minor.yy350.limit = yymsp[0].minor.yy85;  yymsp[-1].minor.yy350.offset = 0;}
#line 2691 "sql.c"
        break;
      case 122: /* limit_opt ::= LIMIT signed OFFSET signed */
      case 123: /* limit_opt ::= LIMIT signed COMMA signed */ yytestcase(yyruleno==123);
      case 126: /* slimit_opt ::= SLIMIT signed SOFFSET signed */ yytestcase(yyruleno==126);
      case 127: /* slimit_opt ::= SLIMIT signed COMMA signed */ yytestcase(yyruleno==127);
#line 409 "sql.y"
{yymsp[-3].minor.yy350.limit = yymsp[-2].minor.yy85;  yymsp[-3].minor.yy350.offset = yymsp[0].minor.yy85;}
#line 2699 "sql.c"
        break;
      case 130: /* expr ::= LP expr RP */
#line 432 "sql.y"
{yymsp[-2].minor.yy222 = yymsp[-1].minor.yy222; }
#line 2704 "sql.c"
        break;
      case 131: /* expr ::= ID */
#line 434 "sql.y"
{yylhsminor.yy222 = tSQLExprIdValueCreate(&yymsp[0].minor.yy0, TK_ID);}
#line 2709 "sql.c"
  yymsp[0].minor.yy222 = yylhsminor.yy222;
        break;
      case 132: /* expr ::= ID DOT ID */
#line 435 "sql.y"
{yymsp[-2].minor.yy0.n += (1+yymsp[0].minor.yy0.n); yylhsminor.yy222 = tSQLExprIdValueCreate(&yymsp[-2].minor.yy0, TK_ID);}
#line 2715 "sql.c"
  yymsp[-2].minor.yy222 = yylhsminor.yy222;
        break;
      case 133: /* expr ::= ID DOT STAR */
#line 436 "sql.y"
{yymsp[-2].minor.yy0.n += (1+yymsp[0].minor.yy0.n); yylhsminor.yy222 = tSQLExprIdValueCreate(&yymsp[-2].minor.yy0, TK_ALL);}
#line 2721 "sql.c"
  yymsp[-2].minor.yy222 = yylhsminor.yy222;
        break;
      case 134: /* expr ::= INTEGER */
#line 438 "sql.y"
{yylhsminor.yy222 = tSQLExprIdValueCreate(&yymsp[0].minor.yy0, TK_INTEGER);}
#line 2727 "sql.c"
  yymsp[0].minor.yy222 = yylhsminor.yy222;
        break;
      case 135: /* expr ::= MINUS INTEGER */
      case 136: /* expr ::= PLUS INTEGER */ yytestcase(yyruleno==136);
#line 439 "sql.y"
{yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n; yymsp[-1].minor.yy0.type = TK_INTEGER; yylhsminor.yy222 = tSQLExprIdValueCreate(&yymsp[-1].minor.yy0, TK_INTEGER);}
#line 2734 "sql.c"
  yymsp[-1].minor.yy222 = yylhsminor.yy222;
        break;
      case 137: /* expr ::= FLOAT */
#line 441 "sql.y"
{yylhsminor.yy222 = tSQLExprIdValueCreate(&yymsp[0].minor.yy0, TK_FLOAT);}
#line 2740 "sql.c"
  yymsp[0].minor.yy222 = yylhsminor.yy222;
        break;
      case 138: /* expr ::= MINUS FLOAT */
      case 139: /* expr ::= PLUS FLOAT */ yytestcase(yyruleno==139);
#line 442 "sql.y"
{yymsp[-1].minor.yy0.n += yymsp[0].minor.yy0.n; yymsp[-1].minor.yy0.type = TK_FLOAT; yylhsminor.yy222 = tSQLExprIdValueCreate(&yymsp[-1].minor.yy0, TK_FLOAT);}
#line 2747 "sql.c"
  yymsp[-1].minor.yy222 = yylhsminor.yy222;
        break;
      case 140: /* expr ::= STRING */
#line 444 "sql.y"
{yylhsminor.yy222 = tSQLExprIdValueCreate(&yymsp[0].minor.yy0, TK_STRING);}
#line 2753 "sql.c"
  yymsp[0].minor.yy222 = yylhsminor.yy222;
        break;
      case 141: /* expr ::= NOW */
#line 445 "sql.y"
{yylhsminor.yy222 = tSQLExprIdValueCreate(&yymsp[0].minor.yy0, TK_NOW); }
#line 2759 "sql.c"
  yymsp[0].minor.yy222 = yylhsminor.yy222;
        break;
      case 142: /* expr ::= VARIABLE */
#line 446 "sql.y"
{yylhsminor.yy222 = tSQLExprIdValueCreate(&yymsp[0].minor.yy0, TK_VARIABLE);}
#line 2765 "sql.c"
  yymsp[0].minor.yy222 = yylhsminor.yy222;
        break;
      case 143: /* expr ::= BOOL */
#line 447 "sql.y"
{yylhsminor.yy222 = tSQLExprIdValueCreate(&yymsp[0].minor.yy0, TK_BOOL);}
#line 2771 "sql.c"
  yymsp[0].minor.yy222 = yylhsminor.yy222;
        break;
      case 144: /* expr ::= ID LP exprlist RP */
#line 449 "sql.y"
{
  yylhsminor.yy222 = tSQLExprCreateFunction(yymsp[-1].minor.yy390, &yymsp[-3].minor.yy0, &yymsp[0].minor.yy0, yymsp[-3].minor.yy0.type);
}
#line 2779 "sql.c"
  yymsp[-3].minor.yy222 = yylhsminor.yy222;
        break;
      case 145: /* expr ::= ID LP STAR RP */
#line 454 "sql.y"
{
  yylhsminor.yy222 = tSQLExprCreateFunction(NULL, &yymsp[-3].minor.yy0, &yymsp[0].minor.yy0, yymsp[-3].minor.yy0.type);
}
#line 2787 "sql.c"
  yymsp[-3].minor.yy222 = yylhsminor.yy222;
        break;
      case 146: /* expr ::= expr AND expr */
#line 459 "sql.y"
{yylhsminor.yy222 = tSQLExprCreate(yymsp[-2].minor.yy222, yymsp[0].minor.yy222, TK_AND);}
#line 2793 "sql.c"
  yymsp[-2].minor.yy222 = yylhsminor.yy222;
        break;
      case 147: /* expr ::= expr OR expr */
#line 460 "sql.y"
{yylhsminor.yy222 = tSQLExprCreate(yymsp[-2].minor.yy222, yymsp[0].minor.yy222, TK_OR); }
#line 2799 "sql.c"
  yymsp[-2].minor.yy222 = yylhsminor.yy222;
        break;
      case 148: /* expr ::= expr LT expr */
#line 463 "sql.y"
{yylhsminor.yy222 = tSQLExprCreate(yymsp[-2].minor.yy222, yymsp[0].minor.yy222, TK_LT);}
#line 2805 "sql.c"
  yymsp[-2].minor.yy222 = yylhsminor.yy222;
        break;
      case 149: /* expr ::= expr GT expr */
#line 464 "sql.y"
{yylhsminor.yy222 = tSQLExprCreate(yymsp[-2].minor.yy222, yymsp[0].minor.yy222, TK_GT);}
#line 2811 "sql.c"
  yymsp[-2].minor.yy222 = yylhsminor.yy222;
        break;
      case 150: /* expr ::= expr LE expr */
#line 465 "sql.y"
{yylhsminor.yy222 = tSQLExprCreate(yymsp[-2].minor.yy222, yymsp[0].minor.yy222, TK_LE);}
#line 2817 "sql.c"
  yymsp[-2].minor.yy222 = yylhsminor.yy222;
        break;
      case 151: /* expr ::= expr GE expr */
#line 466 "sql.y"
{yylhsminor.yy222 = tSQLExprCreate(yymsp[-2].minor.yy222, yymsp[0].minor.yy222, TK_GE);}
#line 2823 "sql.c"
  yymsp[-2].minor.yy222 = yylhsminor.yy222;
        break;
      case 152: /* expr ::= expr NE expr */
#line 467 "sql.y"
{yylhsminor.yy222 = tSQLExprCreate(yymsp[-2].minor.yy222, yymsp[0].minor.yy222, TK_NE);}
#line 2829 "sql.c"
  yymsp[-2].minor.yy222 = yylhsminor.yy222;
        break;
      case 153: /* expr ::= expr EQ expr */
#line 468 "sql.y"
{yylhsminor.yy222 = tSQLExprCreate(yymsp[-2].minor.yy222, yymsp[0].minor.yy222, TK_EQ);}
#line 2835 "sql.c"
  yymsp[-2].minor.yy222 = yylhsminor.yy222;
        break;
      case 154: /* expr ::= expr PLUS expr */
#line 471 "sql.y"
{yylhsminor.yy222 = tSQLExprCreate(yymsp[-2].minor.yy222, yymsp[0].minor.yy222, TK_PLUS);  }
#line 2841 "sql.c"
  yymsp[-2].minor.yy222 = yylhsminor.yy222;
        break;
      case 155: /* expr ::= expr MINUS expr */
#line 472 "sql.y"
{yylhsminor.yy222 = tSQLExprCreate(yymsp[-2].minor.yy222, yymsp[0].minor.yy222, TK_MINUS); }
#line 2847 "sql.c"
  yymsp[-2].minor.yy222 = yylhsminor.yy222;
        break;
      case 156: /* expr ::= expr STAR expr */
#line 473 "sql.y"
{yylhsminor.yy222 = tSQLExprCreate(yymsp[-2].minor.yy222, yymsp[0].minor.yy222, TK_STAR);  }
#line 2853 "sql.c"
  yymsp[-2].minor.yy222 = yylhsminor.yy222;
        break;
      case 157: /* expr ::= expr SLASH expr */
#line 474 "sql.y"
{yylhsminor.yy222 = tSQLExprCreate(yymsp[-2].minor.yy222, yymsp[0].minor.yy222, TK_DIVIDE);}
#line 2859 "sql.c"
  yymsp[-2].minor.yy222 = yylhsminor.yy222;
        break;
      case 158: /* expr ::= expr REM expr */
#line 475 "sql.y"
{yylhsminor.yy222 = tSQLExprCreate(yymsp[-2].minor.yy222, yymsp[0].minor.yy222, TK_REM);   }
#line 2865 "sql.c"
  yymsp[-2].minor.yy222 = yylhsminor.yy222;
        break;
      case 159: /* expr ::= expr LIKE expr */
#line 478 "sql.y"
{yylhsminor.yy222 = tSQLExprCreate(yymsp[-2].minor.yy222, yymsp[0].minor.yy222, TK_LIKE);  }
#line 2871 "sql.c"
  yymsp[-2].minor.yy222 = yylhsminor.yy222;
        break;
      case 160: /* expr ::= expr IN LP exprlist RP */
#line 481 "sql.y"
{yylhsminor.yy222 = tSQLExprCreate(yymsp[-4].minor.yy222, (tSQLExpr*)yymsp[-1].minor.yy390, TK_IN); }
#line 2877 "sql.c"
  yymsp[-4].minor.yy222 = yylhsminor.yy222;
        break;
      case 161: /* exprlist ::= exprlist COMMA expritem */
      case 168: /* itemlist ::= itemlist COMMA expr */ yytestcase(yyruleno==168);
#line 489 "sql.y"
{yylhsminor.yy390 = tSQLExprListAppend(yymsp[-2].minor.yy390,yymsp[0].minor.yy222,0);}
#line 2884 "sql.c"
  yymsp[-2].minor.yy390 = yylhsminor.yy390;
        break;
      case 162: /* exprlist ::= expritem */
      case 169: /* itemlist ::= expr */ yytestcase(yyruleno==169);
#line 490 "sql.y"
{yylhsminor.yy390 = tSQLExprListAppend(0,yymsp[0].minor.yy222,0);}
#line 2891 "sql.c"
  yymsp[0].minor.yy390 = yylhsminor.yy390;
        break;
      case 163: /* expritem ::= expr */
#line 491 "sql.y"
{yylhsminor.yy222 = yymsp[0].minor.yy222;}
#line 2897 "sql.c"
  yymsp[0].minor.yy222 = yylhsminor.yy222;
        break;
      case 165: /* cmd ::= INSERT INTO cpxName insert_value_list */
#line 496 "sql.y"
{
    tSetInsertSQLElems(pInfo, &yymsp[-1].minor.yy0, yymsp[0].minor.yy402);
}
#line 2905 "sql.c"
        break;
      case 166: /* insert_value_list ::= VALUES LP itemlist RP */
#line 501 "sql.y"
{yymsp[-3].minor.yy402 = tSQLListListAppend(NULL, yymsp[-1].minor.yy390);}
#line 2910 "sql.c"
        break;
      case 167: /* insert_value_list ::= insert_value_list VALUES LP itemlist RP */
#line 503 "sql.y"
{yylhsminor.yy402 = tSQLListListAppend(yymsp[-4].minor.yy402, yymsp[-1].minor.yy390);}
#line 2915 "sql.c"
  yymsp[-4].minor.yy402 = yylhsminor.yy402;
        break;
      case 170: /* cmd ::= RESET QUERY CACHE */
#line 515 "sql.y"
{ setDCLSQLElems(pInfo, RESET_QUERY_CACHE, 0);}
#line 2921 "sql.c"
        break;
      case 171: /* cmd ::= ALTER TABLE ids cpxName ADD COLUMN columnlist */
#line 518 "sql.y"
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableSQL* pAlterTable = tAlterTableSQLElems(&yymsp[-4].minor.yy0, yymsp[0].minor.yy155, NULL, ALTER_TABLE_ADD_COLUMN);
    setSQLInfo(pInfo, pAlterTable, NULL, ALTER_TABLE_ADD_COLUMN);
}
#line 2930 "sql.c"
        break;
      case 172: /* cmd ::= ALTER TABLE ids cpxName DROP COLUMN ids */
#line 524 "sql.y"
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;

    toTSDBType(yymsp[0].minor.yy0.type);
    tVariantList* K = tVariantListAppendToken(NULL, &yymsp[0].minor.yy0, -1);

    SAlterTableSQL* pAlterTable = tAlterTableSQLElems(&yymsp[-4].minor.yy0, NULL, K, ALTER_TABLE_DROP_COLUMN);
    setSQLInfo(pInfo, pAlterTable, NULL, ALTER_TABLE_DROP_COLUMN);
}
#line 2943 "sql.c"
        break;
      case 173: /* cmd ::= ALTER TABLE ids cpxName ADD TAG columnlist */
#line 535 "sql.y"
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;
    SAlterTableSQL* pAlterTable = tAlterTableSQLElems(&yymsp[-4].minor.yy0, yymsp[0].minor.yy155, NULL, ALTER_TABLE_TAGS_ADD);
    setSQLInfo(pInfo, pAlterTable, NULL, ALTER_TABLE_TAGS_ADD);
}
#line 2952 "sql.c"
        break;
      case 174: /* cmd ::= ALTER TABLE ids cpxName DROP TAG ids */
#line 540 "sql.y"
{
    yymsp[-4].minor.yy0.n += yymsp[-3].minor.yy0.n;

    toTSDBType(yymsp[0].minor.yy0.type);
    tVariantList* A = tVariantListAppendToken(NULL, &yymsp[0].minor.yy0, -1);

    SAlterTableSQL* pAlterTable = tAlterTableSQLElems(&yymsp[-4].minor.yy0, NULL, A, ALTER_TABLE_TAGS_DROP);
    setSQLInfo(pInfo, pAlterTable, NULL, ALTER_TABLE_TAGS_DROP);
}
#line 2965 "sql.c"
        break;
      case 175: /* cmd ::= ALTER TABLE ids cpxName CHANGE TAG ids ids */
#line 550 "sql.y"
{
    yymsp[-5].minor.yy0.n += yymsp[-4].minor.yy0.n;

    toTSDBType(yymsp[-1].minor.yy0.type);
    tVariantList* A = tVariantListAppendToken(NULL, &yymsp[-1].minor.yy0, -1);

    toTSDBType(yymsp[0].minor.yy0.type);
    A = tVariantListAppendToken(A, &yymsp[0].minor.yy0, -1);

    SAlterTableSQL* pAlterTable = tAlterTableSQLElems(&yymsp[-5].minor.yy0, NULL, A, ALTER_TABLE_TAGS_CHG);
    setSQLInfo(pInfo, pAlterTable, NULL, ALTER_TABLE_TAGS_CHG);
}
#line 2981 "sql.c"
        break;
      case 176: /* cmd ::= ALTER TABLE ids cpxName SET TAG ids EQ tagitem */
#line 563 "sql.y"
{
    yymsp[-6].minor.yy0.n += yymsp[-5].minor.yy0.n;

    toTSDBType(yymsp[-2].minor.yy0.type);
    tVariantList* A = tVariantListAppendToken(NULL, &yymsp[-2].minor.yy0, -1);
    A = tVariantListAppend(A, &yymsp[0].minor.yy406, -1);

    SAlterTableSQL* pAlterTable = tAlterTableSQLElems(&yymsp[-6].minor.yy0, NULL, A, ALTER_TABLE_TAGS_SET);
    setSQLInfo(pInfo, pAlterTable, NULL, ALTER_TABLE_TAGS_SET);
}
#line 2995 "sql.c"
        break;
      case 177: /* cmd ::= KILL CONNECTION IP COLON INTEGER */
#line 575 "sql.y"
{yymsp[-2].minor.yy0.n += (yymsp[-1].minor.yy0.n + yymsp[0].minor.yy0.n); setDCLSQLElems(pInfo, KILL_CONNECTION, 1, &yymsp[-2].minor.yy0);}
#line 3000 "sql.c"
        break;
      case 178: /* cmd ::= KILL STREAM IP COLON INTEGER COLON INTEGER */
#line 576 "sql.y"
{yymsp[-4].minor.yy0.n += (yymsp[-3].minor.yy0.n + yymsp[-2].minor.yy0.n + yymsp[-1].minor.yy0.n + yymsp[0].minor.yy0.n); setDCLSQLElems(pInfo, KILL_STREAM, 1, &yymsp[-4].minor.yy0);}
#line 3005 "sql.c"
        break;
      case 179: /* cmd ::= KILL QUERY IP COLON INTEGER COLON INTEGER */
#line 577 "sql.y"
{yymsp[-4].minor.yy0.n += (yymsp[-3].minor.yy0.n + yymsp[-2].minor.yy0.n + yymsp[-1].minor.yy0.n + yymsp[0].minor.yy0.n); setDCLSQLElems(pInfo, KILL_QUERY, 1, &yymsp[-4].minor.yy0);}
#line 3010 "sql.c"
        break;
      case 180: /* cmd ::= CREATE GATE ids STRING */
#line 580 "sql.y"
{setDCLSQLElems(pInfo, CREATE_GATE, 2, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0);}
#line 3015 "sql.c"
        break;
      case 181: /* cmd ::= QUERY GATE ids */
#line 581 "sql.y"
{setDCLSQLElems(pInfo, QUERY_GATE, 1, &yymsp[0].minor.yy0);}
#line 3020 "sql.c"
        break;
      case 182: /* cmd ::= UPDATE GATE ids STRING */
#line 582 "sql.y"
{setDCLSQLElems(pInfo, UPDATE_GATE, 2, &yymsp[-1].minor.yy0, &yymsp[0].minor.yy0);}
#line 3025 "sql.c"
        break;
      case 183: /* cmd ::= DELETE GATE ids */
#line 583 "sql.y"
{setDCLSQLElems(pInfo, DELETE_GATE, 1, &yymsp[0].minor.yy0);}
#line 3030 "sql.c"
        break;
      default:
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno<sizeof(yyRuleInfoLhs)/sizeof(yyRuleInfoLhs[0]) );
  yygoto = yyRuleInfoLhs[yyruleno];
  yysize = yyRuleInfoNRhs[yyruleno];
  yyact = yy_find_reduce_action(yymsp[yysize].stateno,(YYCODETYPE)yygoto);

  /* There are no SHIFTREDUCE actions on nonterminals because the table
  ** generator has simplified them to pure REDUCE actions. */
  assert( !(yyact>YY_MAX_SHIFT && yyact<=YY_MAX_SHIFTREDUCE) );

  /* It is not possible for a REDUCE to be followed by an error */
  assert( yyact!=YY_ERROR_ACTION );

  yymsp += yysize+1;
  yypParser->yytos = yymsp;
  yymsp->stateno = (YYACTIONTYPE)yyact;
  yymsp->major = (YYCODETYPE)yygoto;
  yyTraceShift(yypParser, yyact, "... then shift");
  return yyact;
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH
  ParseCTX_FETCH
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/
/************ End %parse_failure code *****************************************/
  ParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ParseCTX_STORE
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  ParseTOKENTYPE yyminor         /* The minor type of the error token */
){
  ParseARG_FETCH
  ParseCTX_FETCH
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/
#line 34 "sql.y"

  pInfo->validSql = false;
  int32_t outputBufLen = tListLen(pInfo->pzErrMsg);
  int32_t len = 0;

  if(TOKEN.z) {
    char msg[] = "syntax error near \"%s\"";
    int32_t sqlLen = strlen(&TOKEN.z[0]);

    if (sqlLen + sizeof(msg)/sizeof(msg[0]) + 1 > outputBufLen) {
        char tmpstr[128] = {0};
        memcpy(tmpstr, &TOKEN.z[0], sizeof(tmpstr)/sizeof(tmpstr[0]) - 1);
        len = sprintf(pInfo->pzErrMsg, msg, tmpstr);
    } else {
        len = sprintf(pInfo->pzErrMsg, msg, &TOKEN.z[0]);
    }

  } else {
    len = sprintf(pInfo->pzErrMsg, "Incomplete SQL statement");
  }

  assert(len <= outputBufLen);
#line 3115 "sql.c"
/************ End %syntax_error code ******************************************/
  ParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ParseCTX_STORE
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH
  ParseCTX_FETCH
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  assert( yypParser->yytos==yypParser->yystack );
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
/*********** Begin %parse_accept code *****************************************/
#line 58 "sql.y"
#line 3142 "sql.c"
/*********** End %parse_accept code *******************************************/
  ParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ParseCTX_STORE
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  YYACTIONTYPE yyact;   /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser = (yyParser*)yyp;  /* The parser */
  ParseCTX_FETCH
  ParseARG_STORE

  assert( yypParser->yytos!=0 );
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
#endif

  yyact = yypParser->yytos->stateno;
#ifndef NDEBUG
  if( yyTraceFILE ){
    if( yyact < YY_MIN_REDUCE ){
      fprintf(yyTraceFILE,"%sInput '%s' in state %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact);
    }else{
      fprintf(yyTraceFILE,"%sInput '%s' with pending reduce %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact-YY_MIN_REDUCE);
    }
  }
#endif

  do{
    assert( yyact==yypParser->yytos->stateno );
    yyact = yy_find_shift_action((YYCODETYPE)yymajor,yyact);
    if( yyact >= YY_MIN_REDUCE ){
      yyact = yy_reduce(yypParser,yyact-YY_MIN_REDUCE,yymajor,
                        yyminor ParseCTX_PARAM);
    }else if( yyact <= YY_MAX_SHIFTREDUCE ){
      yy_shift(yypParser,yyact,(YYCODETYPE)yymajor,yyminor);
#ifndef YYNOERRORRECOVERY
      yypParser->yyerrcnt--;
#endif
      break;
    }else if( yyact==YY_ACCEPT_ACTION ){
      yypParser->yytos--;
      yy_accept(yypParser);
      return;
    }else{
      assert( yyact == YY_ERROR_ACTION );
      yyminorunion.yy0 = yyminor;
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminor);
      }
      yymx = yypParser->yytos->major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
        yymajor = YYNOCODE;
      }else{
        while( yypParser->yytos >= yypParser->yystack
            && (yyact = yy_find_reduce_action(
                        yypParser->yytos->stateno,
                        YYERRORSYMBOL)) > YY_MAX_SHIFTREDUCE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yytos < yypParser->yystack || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
          yypParser->yyerrcnt = -1;
#endif
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          yy_shift(yypParser,yyact,YYERRORSYMBOL,yyminor);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
      if( yymajor==YYNOCODE ) break;
      yyact = yypParser->yytos->stateno;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor, yyminor);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      break;
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor, yyminor);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
        yypParser->yyerrcnt = -1;
#endif
      }
      break;
#endif
    }
  }while( yypParser->yytos>yypParser->yystack );
#ifndef NDEBUG
  if( yyTraceFILE ){
    yyStackEntry *i;
    char cDiv = '[';
    fprintf(yyTraceFILE,"%sReturn. Stack=",yyTracePrompt);
    for(i=&yypParser->yystack[1]; i<=yypParser->yytos; i++){
      fprintf(yyTraceFILE,"%c%s", cDiv, yyTokenName[i->major]);
      cDiv = ' ';
    }
    fprintf(yyTraceFILE,"]\n");
  }
#endif
  return;
}

/*
** Return the fallback token corresponding to canonical token iToken, or
** 0 if iToken has no fallback.
*/
int ParseFallback(int iToken){
#ifdef YYFALLBACK
  assert( iToken<(int)(sizeof(yyFallback)/sizeof(yyFallback[0])) );
  return yyFallback[iToken];
#else
  (void)iToken;
  return 0;
#endif
}
