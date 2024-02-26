#include "ExpressionParser.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//supported operators
static inline double _add(double a, double b) { return a + b; }
static inline double _sub(double a, double b) { return a - b; }
static inline double _mul(double a, double b) { return a * b; }
static inline double _div(double a, double b) { return a / b; }
static inline double _pow(double a, double b) { return pow(a, b); }

//supported functions
static inline double _sin(double x) { return sin(x); }
static inline double _cos(double x) { return cos(x); }
static inline double _tan(double x) { return tan(x); }
static inline double _cot(double x) { return 1.0 / tan(x); }
static inline double _ln(double x) { return log(x); }
static inline double _exp(double x) { return exp(x); }
static inline double _abs(double x) { return fabs(x); }

//helper functions
static Token* create_variable(char variable);
static Token* create_constant(double constant);
static Token* create_function(const char* function);
static Token* create_operator(char operator);

//stack functions
static void stack_push(TokenStack* stack, Token* node);
static Token* stack_pop(TokenStack* stack);

//API functions
Token* expression_tokenize(const char* expression)
{

}
Token* expression_infix_to_postfix(Token* infix)
{
    TokenStack stack; stack.top = -1;
    Token* token = infix;
    while (token != NULL)
    {
        if (strcmp(token, "x") == 0) //variable
        {
            Token* node = create_variable('x');
            stack_push(&stack, node);
        }
        else if ((c = strpbrk("+-*/^", token)) != NULL) //operator
        {
            Token* node = create_operator(*c);
            node->data.operator.right = stack_pop(&stack);
            node->data.operator.left = stack_pop(&stack);
            stack_push(&stack, node);
        }
        else if(strcmp(token, "sin") == 0) //function
        {
            Token* node = create_function(_sin);
            Token* left = stack_pop(&stack);
            node->left = left;
            stack_push(&stack, node);
        }
        else if(strcmp(token, "cos") == 0)
        {
            Token* node = create_function(_cos);
            Token* left = stack_pop(&stack);
            node->left = left;
            stack_push(&stack, node);
        }
        else if(strcmp(token, "tg") == 0 || strcmp(token, "tan") == 0)
        {
            Token* node = create_function(_tan);
            Token* left = stack_pop(&stack);
            node->left = left;
            stack_push(&stack, node);
        }
        else if(strcmp(token, "ctg") == 0 || strcmp(token, "cot") == 0)
        {
            Token* node = create_function(_cot);
            Token* left = stack_pop(&stack);
            node->left = left;
            stack_push(&stack, node);
        }
        else if(strcmp(token, "ln") == 0 || strcmp(token, "log") == 0)
        {
            Token* node = create_function(_ln);
            Token* left = stack_pop(&stack);
            node->left = left;
            stack_push(&stack, node);
        }
        else if(strcmp(token, "exp") == 0)
        {
            Token* node = create_function(_exp);
            Token* left = stack_pop(&stack);
            node->left = left;
            stack_push(&stack, node);
        }
        else if (strcmp(token, "abs") == 0)
        {
            Token* node = create_function(_abs);
            Token* left = stack_pop(&stack);
            node->left = left;
            stack_push(&stack, node);
        }
        else //constant
        {
            Token* node = create_constant(atoi(token));
            stack_push(&stack, node);
        }
        token = strtok(NULL, " ");
    }
    return stack.data[0];
}

double expression_evaluate(Token* head, double x)
{
    if (head == NULL)
        return 0.0;

    if (head->type == VARIABLE)
        return x;
    else if (head->type == CONSTANT)
        return head->data.constant;
    else if (head->type == OPERATOR)
        return head->data.operator.operator(expression_evaluate(head->data.operator.left, x), expression_evaluate(head->data.operator.right, x));
    else
        return head->data.function.function(x);
}
void expression_free(Token* head)
{
    if (head != NULL)
    {
        switch (head->type)
        {
            case VARIABLE:
            case CONSTANT:
                break;
            case FUNCTION:
                expression_free(head->data.function.param);
                break;
            case OPERATOR:
                expression_free(head->data.operator.left);
                expression_free(head->data.operator.right);
                break;
        }
        free(head);
    }    
}

static Token* create_variable(char variable)
{
    Token* node = (Token*)malloc(sizeof(Token));
    node->type = VARIABLE;
    node->data.variable = variable;
    return node;
}
static Token* create_constant(double constant)
{
    Token* node = (Token*)malloc(sizeof(Token));
    node->type = CONSTANT;
    node->data.constant = constant;
    return node;
}
static Token* create_function(const char* function)
{
    Function func = { NULL, NULL };
    if (strcmp(function, "sin") == 0) func.function = _sin;
    else if (strcmp(function, "cos") == 0) func.function = _cos;
    else if (strcmp(function, "tan") == 0 || strcmp(function, "tg") == 0) func.function = _tan;
    else if (strcmp(function, "cot") == 0 || strcmp(function, "ctg") == 0) func.function = _cot;
    else if (strcmp(function, "ln") == 0 || strcmp(function, "log") == 0) func.function = _ln;
    else if (strcmp(function, "exp") == 0) func.function = _exp;
    else if (strcmp(function, "abs") == 0) func.function = _abs;
    else return NULL;

    Token* node = (Token*)malloc(sizeof(Token));
    node->type = FUNCTION;
    node->data.function = func;
    return node;
}
static Token* create_operator(char operator)
{
    Operator op = { NULL, NULL, NULL };
    switch (operator)
    {
        case '+': op.operator = _add; break;
        case '-': op.operator = _sub; break;
        case '*': op.operator = _mul; break;
        case '/': op.operator = _div; break;
        case '^': op.operator = _pow; break;
        default: return NULL;
    }

    Token* node = (Token*)malloc(sizeof(Token));
    node->type = OPERATOR;
    node->data.operator = op;
    return node;
}

static void stack_push(TokenStack* stack, Token* node)
{
    if (stack->top == STACK_SIZE - 1) exit(1);
    stack->data[++stack->top] = node;
}
static Token* stack_pop(TokenStack* stack)
{
    if (stack->top < 0) exit(1);
    return stack->data[stack->top--];
}