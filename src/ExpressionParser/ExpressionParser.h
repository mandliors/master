#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include "Token.h"

#define TOKEN_ARRAY_SIZE 100

Token* expression_parse(const char* expression);
double expression_evaluate(Token* head, double x);
void expression_free(Token* head);
void expression_print(Token* head);

#endif