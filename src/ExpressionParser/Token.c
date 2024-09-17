#include "Token.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Token* create_variable(char variable)
{
    Token* node = (Token*)malloc(sizeof(Token));
    node->type = TT_VARIABLE;
    node->data.variable = variable;
    return node;
}
Token* create_constant(double constant)
{
    Token* node = (Token*)malloc(sizeof(Token));
    node->type = TT_CONSTANT;
    node->data.constant = constant;
    return node;
}
Token* create_function(const char* function)
{
    Function func = FN_NONE;
    if (strcmp(function, "sin") == 0) func = FN_SIN;
    else if (strcmp(function, "cos") == 0) func = FN_COS;
    else if (strcmp(function, "tg") == 0 || strcmp(function, "tan") == 0) func = FN_TG;
    else if (strcmp(function, "ctg") == 0 || strcmp(function, "cot") == 0) func = FN_CTG;
    else if (strcmp(function, "ln") == 0 || strcmp(function, "log") == 0) func = FN_LN;
    else if (strcmp(function, "exp") == 0) func = FN_EXP;
    else if (strcmp(function, "abs") == 0) func = FN_ABS;
    else return NULL;

    Token* node = (Token*)malloc(sizeof(Token));
    node->type = TT_FUNCTION;
    node->data.function = func;
    return node;
}
Token* create_operator(char operator)
{
    Operator op = OP_NONE;
    switch (operator)
    {
        case '+': op = OP_ADD; break;
        case '-': op = OP_SUB; break;
        case '*': op = OP_MUL; break;
        case '/': op = OP_DIV; break;
        case '^': op = OP_POW; break;
        case '(': op = OP_LEFT_PARENTHESIS; break;
        case ')': op = OP_RIGHT_PARENTHESIS; break;
        default: return NULL;
    }

    Token* node = (Token*)malloc(sizeof(Token));
    node->type = TT_OPERATOR;
    node->data.operator = op;
    return node;
}
void token_destroy(Token* token)
{
    free(token);
}