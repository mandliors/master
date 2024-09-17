#ifndef TOKEN_H
#define TOKEN_H

typedef struct Token Token;

typedef char Variable;
typedef double Constant;
typedef enum Function { FN_NONE = -1, FN_SIN, FN_COS, FN_TG, FN_CTG, FN_LN, FN_EXP, FN_ABS, FN_COUNT } Function;
typedef enum Operator { OP_NONE = -1, OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_POW, OP_LEFT_PARENTHESIS, OP_RIGHT_PARENTHESIS, OP_COUNT = OP_LEFT_PARENTHESIS } Operator;

typedef enum TokenType {
    TT_NONE = -1, TT_VARIABLE, TT_CONSTANT, TT_FUNCTION, TT_OPERATOR, TT_COUNT
} TokenType;

typedef union TokenData {
    Variable variable;
    Constant constant;
    Function function;
    Operator operator;
} TokenData;

typedef struct Token {
    TokenType type;
    TokenData data;
    struct Token* left, *right;
} Token;

Token* create_variable(char variable);
Token* create_constant(double constant);
Token* create_function(const char* function);
Token* create_operator(char operator);
void token_destroy(Token* token);

#endif