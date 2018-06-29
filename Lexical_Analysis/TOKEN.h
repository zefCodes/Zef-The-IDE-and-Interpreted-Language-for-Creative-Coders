#ifndef TOKEN_H
#define TOKEN_H

#include <string.h>
#include <deque>

using namespace std;

enum TOKENS {


    //CONSTANT

    //ILLEGAL_ID

    //OPERATORS

    //SEPARATORS

    //COLON = 102,
    //PERIOD = 103,


    //ID


    //KEYWORDS
    SEMI_COLON = 200,
    IF = 201,
    LPAREN = 202,
    RPAREN = 203,
    LBRACE = 204,
    RBRACE = 205,
    OWISE = 206,
    UNTIL = 207,
    WHILE = 208,
    FOR = 209,
    ID = 210,
    FROM = 211,
    TO = 212,
    STEP = 213,
    IN_K = 214,
    LEAVE = 215,
    RETURN = 216,
    COMMA = 217,
    SUB_ASSIGN = 218,
    PLUS_ASSIGN = 219,
    DIV_ASSIGN = 220,
    MUL_ASSIGN = 221,
    PWR_ASSIGN = 222,
    ASSIGN = 223,
    LOR = 224,
    LAND = 225,
    NOT_EQ = 226,
    IS_EQ = 227,
    LTE = 228,
    GTE = 229,
    GT = 230,
    LT = 231,
    SUBTRACT = 232,
    PLUS = 233,
    MULTIPLY = 234,
    MODULUS = 235,
    POWER = 236,
    DIVIDE = 237,
    INC = 238,
    DEC = 239,
    LNOT = 240,
    TRUE_K = 241,
    FALSE_K = 242,
    CONST_K = 243,
    QUOT_MARK = 244,
    STR_LIT = 245,
    LSQBR = 246,
    RSQBR = 247,
    LET = 248,
    EOF_TOKEN = 249,
    NULLT=250,

    //LET = 112,
    //THEN = 107,


    //JOB = 111,

    //STEP = 113,


    //IMPORT = 116,
    //DO = 117,


    //SWITCH = 121,
    //DEFAULT = 122,
    //CASE = 123,


    //BOOLEAN LITERALS



    //ILLEGAL/UNKNOWN
    UNKNOWN_ILLEGAL = 127,
    ILL_ID = 71,
    //SPECIALCHARS

    SPEC_CHAR = 129,

    //STRING LITERALS


    //EOF_TOKEN


    //FOR PARSING
    EPSILON = 500,
    DATALIST = 501,

};



enum NT {
    PROGRAM = 1,
    GLOBAL_STMTS = 2,
    GLOBAL_DECS = 3,
    STMTS = 4,
    IF_STATEMENT = 5,
    OTHERWISE = 6,
    OTHERWISE_BRANCH = 7,
    UNTIL_STATEMENT = 8,
    WHILE_STATEMENT = 9,
    FOR_STATEMENT = 10,
    FUNC_DECLARATION = 11,
    RETURNS = 12,
    STMT = 13,
    PARAMETERS = 14,
    EXTRA_PARAMETERS = 15,
    EXPR = 16,
    EXPRA = 17,
    EXPR1 = 18,
    EXPRB = 19,
    EXPR2 = 20,
    EXPRC = 21,
    EXPR3 = 22,
    EXPRD = 23,
    EXPR4 = 24,
    EXPRE = 25,
    EXPR5 = 26,
    EXPRF = 27,
    EXPR6 = 28,
    EXPRG = 29,
    EXPR7 = 30,
    EXPR8 = 31,
    OP = 32,
    EXPR9 = 33,
    FUNCORDATA = 34,
    VARIABLE_DECLARATION = 35,
};

enum ACTION {
    ACTION_ADD = 300,
    ACTION_MUL = 301,
    ACTION_ASSIGN = 302,
    ACTION_SUB = 303,
    ACTION_DIV = 304,
    ACTION_CREATE_VAR = 305,
    ACTION_PUSH_CONST = 306,
    ACTION_NEW_VAR = 307,
    ACTION_POP = 308,
    ACTION_ASSIGN_VAR = 309,
    ACTION_PRE_INC = 310,
    ACTION_PRE_DEC = 311,
    ACTION_POS = 312,
    ACTION_NEG = 313,
    ACTION_NOT = 314,
    ACTION_POST_INC = 315,
    ACTION_POST_DEC = 316,
    ACTION_LOR = 317,
    ACTION_LAND = 318,
    ACTION_NOT_EQ = 319,
    ACTION_IS_EQ = 320,
    ACTION_MOD = 321,
    ACTION_POW = 322,
    ACTION_GT = 323,
    ACTION_LT = 324,
    ACTION_GTE = 325,
    ACTION_LTE = 326,
    ACTION_SUB_ASS = 327,
  ACTION_PLUS_ASS = 328,
  ACTION_DIV_ASS = 329,
  ACTION_MUL_ASS = 330,
  ACTION_PWR_ASS = 331,


    ACTION_CHECK = 332,
    ACTION_RESUME = 333,
    ACTION_NEW_IF = 334,
    ACTION_END_IF = 335,
    ACTION_NEW_FUNC = 336,
    ACTION_END_FUNC = 337,
    ACTION_FUNC_CALL = 338,
    ACTION_RETURN = 339,
    ACTION_PUSH = 340,
    ACTION_PARAM = 341,
    ACTION_FUNC_NAME = 342,
    ACTION_INIT = 343,
    ACTION_OWISE = 344,
    ACTION_OWISE_IF = 345,
    ACTION_OWISE_BRANCH = 346,

    ACTION_CHECK_WHILE = 347,
    ACTION_JUMP_BACK = 348,
    ACTION_EVAL_WHILE = 349,
    ACTION_START_LOOP = 350,
    ACTION_END_LOOP = 351,



    FUNC_LOG = 352,
    FUNC_LOG_2 = 353,
    FUNC_DRAW_OVAL_PRIM = 354,
    FUNC_FILL_OVAL_PRIM = 355,
    FUNC_DRAW_RECT_PRIM = 356,
    FUNC_FILL_RECT_PRIM = 357,
    FUNC_SET_BACKGROUND_PRIM = 358,
    FUNC_SET_COLOR_PRIM = 359,
    FUNC_SET_LINE_WEIGHT_PRIM = 360,
    FUNC_DRAW_LINE_PRIM = 361,
    FUNC_CLEAR_SCREEN_PRIM = 362,


    ACTION_SET_CURRENT = 363,
    ACTION_PUSH_BRACK = 364,
    ACTION_PUSH_SQR_BRACK = 365,
    ACTION_COLLECT_LIST = 366,
    ACTION_INDEX = 367,


    FUNC_SIZE_PRIM = 368,
    FUNC_APPEND_PRIM = 369,
    FUNC_PREPEND_PRIM = 370,

    FUNC_SIN_PRIM = 371,
    FUNC_COS_PRIM = 372,
    FUNC_TAN_PRIM = 373,
    FUNC_ASIN_PRIM = 374,
    FUNC_ACOS_PRIM = 375,
    FUNC_ATAN_PRIM = 376,
    FUNC_LOG_PRIM = 377,
    FUNC_ROOT_PRIM = 378,
    FUNC_ABS_PRIM = 379,
    FUNC_FLOOR_PRIM =  380,
    FUNC_CEIL_PRIM = 381,
    FUNC_RAND_PRIM = 382,
    FUNC_RADIANS_PRIM = 383,
    FUNC_DEGREES_PRIM = 384,
    FUNC_TRANS_PRIM = 385,
    FUNC_SCALE_PRIM = 386,
    FUNC_ROT_PRIM = 387,

    FUNC_MOUSE_X_PRIM = 388,
    FUNC_MOUSE_Y_PRIM = 389,

    FUNC_DRAW_ARC_PRIM = 390,
    FUNC_FILL_ARC_PRIM = 391,
};

enum TOKEN_TYPE_T {
    STR_LITERAL = 133,
    CONSTANT = 134,
    BOOL_LITERAL = 135,
    IDENTIFIER = 136,
    ILLEGAL_ID = 137,
    OPERATOR = 138,
    SPECIAL_CHAR = 139,
    SEPARATOR = 140,
    STR_OPERATOR = 141,
    KEYWORD = 142,
    ILLEGAL = 143,
    EOF_T = 144,
    EOF_T2 = 145,
    DATAL = 146,
    REFL = 147,
};


struct ELEMENT {
    TOKEN_TYPE_T TYPE;
    TOKENS NAME;
    string lexeme;
    int lineNo;
    int column;
    deque<ELEMENT> list;
};

struct TOKEN {
    TOKEN_TYPE_T TYPE;
    TOKENS NAME;
    string lexeme;
    int lineNo;
    int column;
    int tokenID;
};

#endif
