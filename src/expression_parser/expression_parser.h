#pragma once

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define STACK_SIZE 50

typedef char Variable;
typedef double Number;
typedef double(*Function)(double);
typedef double(*Operator)(double, double);

typedef enum NodeType {
    VARIABLE, NUMBER, FUNCTION, OPERATOR
} NodeType;

typedef union Data {
    Variable variable;
    Number number;
    Function function;
    Operator operator;
} Data;

typedef struct Node {
    NodeType type;
    Data data;
    struct Node *left, *right;
} Node;

typedef struct NodeStack {
    Node* data[STACK_SIZE];
    int top;
} NodeStack;

Node* create_variable(Variable variable);
Node* create_number(Number number);
Node* create_function(Function function);
Node* create_operator(Operator operator);

Node* expression_parse(char* expression);
double expression_evaluate(Node* head, double x);
void expression_free(Node* head);

void stack_push(NodeStack* stack, Node* node);
Node* stack_pop(NodeStack* stack);

double _add(double a, double b);
double _sub(double a, double b);
double _mul(double a, double b);
double _div(double a, double b);
double _cot(double x);