#include "ExpressionParser.h"
#include "Token.h"
#include "DataStructures.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

//suppoerted functions
static inline double _sin(double x) { return sin(x); }
static inline double _cos(double x) { return cos(x); }
static inline double _tg(double x) { return tan(x); }
static inline double _ctg(double x) { return 1.0 / tan(x); }
static inline double _ln(double x) { return log(x); }
static inline double _exp(double x) { return exp(x); }
static inline double _abs(double x) { return fabs(x); }

//function data
typedef struct FunctionData {
    char name[10];
    double(*function)(double);
} FunctionData;
static FunctionData functions[FN_COUNT] = {
    { "sin", _sin },
    { "cos", _cos },
    { "tg",  _tg },
    { "ctg", _ctg },
    { "ln",  _ln },
    { "exp", _exp },
    { "abs", _abs }
};

//supported operators
static inline double _add(double a, double b) { return a + b; }
static inline double _sub(double a, double b) { return a - b; }
static inline double _mul(double a, double b) { return a * b; }
static inline double _div(double a, double b) { return a / b; }
static inline double _pow(double a, double b) { return pow(a, b); }

//operator data
typedef struct OperatorData {
    char sign;
    int precedence;
    bool right_associative;
    double(*function)(double, double);
} OperatorData;
static OperatorData operators[OP_COUNT] = {
    { '+', 1, false, _add },
    { '-', 1, false, _sub },
    { '*', 2, false, _mul },
    { '/', 2, false, _div },
    { '^', 3, true,  _pow }
};

// hidden functions
static bool expression_tokenize(Token* tokens[TOKEN_ARRAY_SIZE], size_t* n, const char* expression);
static Token* expression_infix_to_postfix_to_tree(Token* tokens[TOKEN_ARRAY_SIZE], size_t n);

//API functions
Token* expression_parse(const char* expression)
{
    Token* tokens[TOKEN_ARRAY_SIZE]; size_t n;
    if (!expression_tokenize(tokens, &n, expression))
        return NULL;
    
    Token* root = expression_infix_to_postfix_to_tree(tokens, n);
    if (!root)
        return NULL;

    return root;
}
double expression_evaluate(Token* root, double x)
{
    if (root == NULL)
        return 0.0;

    if (root->type == TT_VARIABLE)
        return x;
    else if (root->type == TT_CONSTANT)
        return root->data.constant;
    else if (root->type == TT_OPERATOR)
        return operators[root->data.operator].function(expression_evaluate(root->left, x), expression_evaluate(root->right, x));
    else
        return functions[root->data.function].function(expression_evaluate(root->left, x));
}
void expression_free(Token* root)
{
    if (root != NULL)
    {
        free(root->left);
        free(root->right);
        free(root);
    }    
}
void expression_print(Token* root)
{
    if (root == NULL)
        return;

    switch (root->type)
    {
        case TT_CONSTANT:
            printf("%g ", root->data.constant);
            break;
        case TT_VARIABLE:
            printf("%c ", root->data.variable);
            break;
        case TT_OPERATOR:
            expression_print(root->left);
            printf("%c ", operators[root->data.operator].sign);
            expression_print(root->right);
            break;
        case TT_FUNCTION:
            printf("%s ", functions[root->data.function].name);
            expression_print(root->left);
            break;    
        default:
            break;
    }
}

static bool expression_tokenize(Token* tokens[TOKEN_ARRAY_SIZE], size_t* n, const char* expression)
{
    *n = 0; char c; size_t i = 0;
    while ((c = expression[i++]) != '\0')
    {
        if (c == ' ') continue;
        if (isalpha(c)) // function or variable
        {
            char buffer[10];
            size_t j = 0;
            do
            {
                buffer[j++] = c;
                c = expression[i++];
            } while (isalpha(c));
            buffer[j] = '\0'; i--;
            
            // check if it's a function, operator or variable
            if (j == 1) // variable or operator
            {
                Token* token = create_operator(buffer[0]);
                if (token != NULL) // operator
                    tokens[(*n)++] = token;
                else // variable
                    tokens[(*n)++] = create_variable(buffer[0]);
            }
            else // function
            {
                Token* token = create_function(buffer);
                if (token != NULL)
                    tokens[(*n)++] = token;
                else
                    return false;
            }
        }
        else if (isdigit(c)) // constant
        {
            char buffer[10];
            size_t j = 0;
            do
            {
                buffer[j++] = c;
                c = expression[i++];
                if (c == ',') c = '.'; // comma can also be used as decimal point
            } while (isdigit(c) || c == '.');
            buffer[j] = '\0'; i--;
            tokens[(*n)++] = create_constant(atof(buffer));
        }
        else // operator or parenthesis
        {
            if (c == '(' || c == ')') // parenthesis
                tokens[(*n)++] = create_operator(c);
            else
            {
                Token* token = create_operator(c);
                if (token != NULL)
                    tokens[(*n)++] = token;
                else
                    return false;
            }
        }
    }
    return true;
}
static Token* expression_infix_to_postfix_to_tree(Token* tokens[TOKEN_ARRAY_SIZE], size_t n)
{
    // infix to postfix (shunting yard algorithm)
    TokenStack stack = stack_create();
    TokenQueue output = queue_create();
    for (size_t i = 0; i < n; i++)
    {
        Token* token = tokens[i];
        if (token->type == TT_CONSTANT || token->type == TT_VARIABLE)
            queue_enqueue(&output, token);
        else if (token->type == TT_FUNCTION)
            stack_push(&stack, token);
        else if (token->type == TT_OPERATOR)
        {
            if (token->data.operator == OP_LEFT_PARENTHESIS) // left parenthesis
                stack_push(&stack, token);
            else if (token->data.operator == OP_RIGHT_PARENTHESIS) // right parenthesis
            {
                Token* top;
                while ((top = stack_top(&stack))->type != TT_OPERATOR || top->data.operator != OP_LEFT_PARENTHESIS)
                {
                    assert(!stack_is_empty(&stack));
                    queue_enqueue(&output, stack_pop(&stack));
                }
                assert(stack_top(&stack)->type == TT_OPERATOR && stack_top(&stack)->data.operator == OP_LEFT_PARENTHESIS);
                token_destroy(stack_pop(&stack));
                if (!stack_is_empty(&stack) && stack_top(&stack)->type == TT_FUNCTION)
                    queue_enqueue(&output, stack_pop(&stack));
                token_destroy(token);
            }
            else // operator
            {
                Token* top;
                while (!stack_is_empty(&stack) && (top = stack_top(&stack))->type == TT_OPERATOR && 
                        top->data.operator != OP_LEFT_PARENTHESIS &&
                        (operators[top->data.operator].precedence > operators[token->data.operator].precedence ||
                        (operators[top->data.operator].precedence == operators[token->data.operator].precedence && !operators[token->data.operator].right_associative)))

                { 
                    queue_enqueue(&output, stack_pop(&stack));
                }
                stack_push(&stack, token);
            }
        }
    }
    while (!stack_is_empty(&stack))
    {
        assert(stack_top(&stack)->type != TT_OPERATOR || stack_top(&stack)->data.operator != OP_LEFT_PARENTHESIS);
        queue_enqueue(&output, stack_pop(&stack));
    }

    // create expression tree
    TokenStack treeStack = stack_create();
    Token* token;
    while (!queue_is_empty(&output))
    {
        token = queue_dequeue(&output);
        if (token->type == TT_CONSTANT || token->type == TT_VARIABLE)
            stack_push(&treeStack, token);
        else if (token->type == TT_OPERATOR)
        {
            if (token->data.operator == OP_LEFT_PARENTHESIS || token->data.operator == OP_RIGHT_PARENTHESIS)
                return NULL;
            else
            {
                token->right = stack_pop(&treeStack);
                token->left = stack_pop(&treeStack);
                stack_push(&treeStack, token);
            }
        }
        else if (token->type == TT_FUNCTION)
        {
            token->left = stack_pop(&treeStack);
            stack_push(&treeStack, token);
        }
        else
            return NULL;
    }
    return stack_pop(&treeStack);
}