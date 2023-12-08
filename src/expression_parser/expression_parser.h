#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define STACK_SIZE 50

typedef struct Variable {
    char c;
} Variable;

typedef struct Number {
    double number;
} Number;

typedef double (*Func)(double);
typedef struct Function {
    char name[4+1];
    Func func;
} Function;

typedef struct Operator {
    char operator;
} Operator;

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

Node* create_variable(char c);
Node* create_number(int n);
Node* create_function(const char* name, Func func);
Node* create_operator(char operator);

Node* parse(char* expression);
double evaluate(Node* head, double x);

void push(NodeStack* stack, Node* node);
Node* pop(NodeStack* stack);

double cot(double x);