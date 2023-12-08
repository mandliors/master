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

Node* parse(char* expression);
double evaluate(Node* head, double x);

void push(NodeStack* stack, Node* node);
Node* pop(NodeStack* stack);

double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
double cot(double x);