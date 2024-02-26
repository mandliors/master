#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#define STACK_SIZE 50

//node types
typedef char Variable;
typedef double Constant;
typedef char Parenthesis;

typedef struct Function {
    double(*function)(double);
    Token* param;
} Function;

typedef struct Operator {
    double(*operator)(double, double);
    Token* left, *right;
} Operator;

typedef enum TokenType {
    VARIABLE, CONSTANT, PARENTHESIS, FUNCTION, OPERATOR
} TokenType;


//nodes
typedef union TokenData {
    Variable variable;
    Constant constant;
    Function function;
    Operator operator;
    Parenthesis parenthesis;
} TokenData;

typedef struct Token {
    TokenType type;
    TokenData data;
} Token;

typedef struct TokenListElement {
    Token* token;
    struct TokenListElement* next;
} TokenListElement;

typedef struct TokenList {
    TokenListElement* head;
    unsigned size;
} TokenList;

typedef struct TokenStack {
    Token* data[STACK_SIZE];
    unsigned top;
} TokenStack;


//API functions
Token* expression_tokenize(const char* expression);
Token* expression_infix_to_postfix(Token* infix);
double expression_evaluate(Token* head, double x);
void expression_free(Token* head);

#endif