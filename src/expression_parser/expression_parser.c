#include "expression_parser.h"

Node* create_variable(Variable variable)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = VARIABLE;
    node->data.variable = variable;
    node->left = node->right = NULL;
    return node;
}
Node* create_number(Number number)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = NUMBER;
    node->data.number = number;
    node->left = node->right = NULL;
    return node;
}
Node* create_function(Function function)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = FUNCTION;
    node->data.function = function;
    node->left = node->right = NULL;
    return node;
}
Node* create_operator(Operator operator)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = OPERATOR;
    node->data.operator = operator;
    node->left = node->right = NULL;
    return node;
}

Node* expression_parse(char* expression)
{
    NodeStack stack; stack.top = -1;
    char* token = strtok(expression, " ");
    char* c;
    while (token != NULL)
    {
        if (strcmp(token, "x") == 0) //variable
        {
            Node* node = create_variable('x');
            stack_push(&stack, node);
        }
        else if ((c = strpbrk("+-*/^", token)) != NULL) //operator
        {
            Node* node;
            switch(*c)
            {
                case '+': node = create_operator(_add); break;
                case '-': node = create_operator(_sub); break;
                case '*': node = create_operator(_mul); break;
                case '/': node = create_operator(_div); break;
                case '^': node = create_operator(pow); break;
                default: exit(1);
            }
            Node* right = stack_pop(&stack);
            Node* left = stack_pop(&stack);
            node->left = left;
            node->right = right;
            stack_push(&stack, node);
        }
        else if(strcmp(token, "sin") == 0) //function
        {
            Node* node = create_function(sin);
            Node* left = stack_pop(&stack);
            node->left = left;
            stack_push(&stack, node);
        }
        else if(strcmp(token, "cos") == 0)
        {
            Node* node = create_function(cos);
            Node* left = stack_pop(&stack);
            node->left = left;
            stack_push(&stack, node);
        }
        else if(strcmp(token, "tg") == 0)
        {
            Node* node = create_function(tan);
            Node* left = stack_pop(&stack);
            node->left = left;
            stack_push(&stack, node);
        }
        else if(strcmp(token, "ctg") == 0)
        {
            Node* node = create_function(_cot);
            Node* left = stack_pop(&stack);
            node->left = left;
            stack_push(&stack, node);
        }
        else if(strcmp(token, "ln") == 0)
        {
            Node* node = create_function(log);
            Node* left = stack_pop(&stack);
            node->left = left;
            stack_push(&stack, node);
        }
        else if(strcmp(token, "exp") == 0)
        {
            Node* node = create_function(exp);
            Node* left = stack_pop(&stack);
            node->left = left;
            stack_push(&stack, node);
        }
        else //number
        {
            Node* node = create_number(atoi(token));
            stack_push(&stack, node);
        }
        token = strtok(NULL, " ");
    }
    return stack.data[0];
}
double expression_evaluate(Node* head, double x)
{
    if (head == NULL)
        return 0.0;

    if (head->type == VARIABLE)
        return x;
    else if (head->type == NUMBER)
        return head->data.number;
    else if (head->type == OPERATOR)
        return head->data.operator(expression_evaluate(head->left, x), expression_evaluate(head->right, x));
    else
        return head->data.function(x);
}
void expression_free(Node* head)
{
    if (head != NULL)
    {
        expression_free(head->left);
        expression_free(head->right);
        free(head);
    }    
}

void stack_push(NodeStack* stack, Node* node)
{
    if (stack->top == STACK_SIZE - 1) exit(1);
    stack->data[++stack->top] = node;
}
Node* stack_pop(NodeStack* stack)
{
    if (stack->top < 0) exit(1);
    return stack->data[stack->top--];
}

double _add(double a, double b) { return a + b; }
double _sub(double a, double b) { return a - b; }
double _mul(double a, double b) { return a * b; }
double _div(double a, double b) { return a / b; }
double _cot(double x) { return 1.0 / tan(x); };