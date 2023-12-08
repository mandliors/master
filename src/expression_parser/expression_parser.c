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

Node* parse(char* expression)
{
    NodeStack stack; stack.top = -1;
    char* token = strtok(expression, " ");
    char* c;
    while (token != NULL)
    {
        if (strcmp(token, "x") == 0) //variable
        {
            Node* node = create_variable('x');
            push(&stack, node);
        }
        else if ((c = strpbrk("+-*/^", token)) != NULL) //operator
        {
            Node* node;
            switch(*c)
            {
                case '+': node = create_operator(add); break;
                case '-': node = create_operator(subtract); break;
                case '*': node = create_operator(multiply); break;
                case '/': node = create_operator(divide); break;
                case '^': node = create_operator(pow); break;
                default: exit(1);
            }
            Node* right = pop(&stack);
            Node* left = pop(&stack);
            node->left = left;
            node->right = right;
            push(&stack, node);
        }
        else if(strcmp(token, "sin") == 0) //function
        {
            Node* node = create_function(sin);
            Node* left = pop(&stack);
            node->left = left;
            push(&stack, node);
        }
        else if(strcmp(token, "cos") == 0)
        {
            Node* node = create_function(cos);
            Node* left = pop(&stack);
            node->left = left;
            push(&stack, node);
        }
        else if(strcmp(token, "tg") == 0)
        {
            Node* node = create_function(tan);
            Node* left = pop(&stack);
            node->left = left;
            push(&stack, node);
        }
        else if(strcmp(token, "ctg") == 0)
        {
            Node* node = create_function(cot);
            Node* left = pop(&stack);
            node->left = left;
            push(&stack, node);
        }
        else if(strcmp(token, "ln") == 0)
        {
            Node* node = create_function(log);
            Node* left = pop(&stack);
            node->left = left;
            push(&stack, node);
        }
        else if(strcmp(token, "exp") == 0)
        {
            Node* node = create_function(exp);
            Node* left = pop(&stack);
            node->left = left;
            push(&stack, node);
        }
        else //number
        {
            Node* node = create_number(atoi(token));
            push(&stack, node);
        }
        token = strtok(NULL, " ");
    }
    return stack.data[0];
}
double evaluate(Node* head, double x)
{
    if (head == NULL)
        return 0.0;

    if (head->type == VARIABLE)
        return x;
    else if (head->type == NUMBER)
        return head->data.number;
    else if (head->type == OPERATOR)
        return head->data.operator(evaluate(head->left, x), evaluate(head->right, x));
    else
        return head->data.function(x);
}

void push(NodeStack* stack, Node* node)
{
    if (stack->top == STACK_SIZE - 1) exit(1);
    stack->data[++stack->top] = node;
}
Node* pop(NodeStack* stack)
{
    if (stack->top < 0) exit(1);
    return stack->data[stack->top--];
}

double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) { return a / b; }
double cot(double x) { return 1.0 / tan(x); };