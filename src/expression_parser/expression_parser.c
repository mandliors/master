#include "expression_parser.h"

Node* create_variable(char c)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = VARIABLE;
    node->data.variable = (Variable){c};
    node->left = node->right = NULL;
    return node;
}
Node* create_number(int n)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = NUMBER;
    node->data.number = (Number){n};
    node->left = node->right = NULL;
    return node;
}
Node* create_function(const char* name, Func func)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = FUNCTION;
    Function f;
    strcpy(f.name, name);
    f.func = func;
    node->data.function = f;
    node->left = node->right = NULL;
    return node;
}
Node* create_operator(char operator)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = OPERATOR;
    node->data.operator = (Operator){operator};
    node->left = node->right = NULL;
    return node;
}

Node* parse(char* expression)
{
    NodeStack stack; stack.top = -1;
    char* token = strtok(expression, " ");
    while (token != NULL)
    {
        if (strcmp(token, "x") == 0) //variable
        {
            Node* node = create_variable('x');
            push(&stack, node);
        }
        else if (strpbrk("+-*/^", token) != NULL) //operator
        {
            Node* node = create_operator(token[0]);
            Node* right = pop(&stack);
            Node* left = pop(&stack);
            node->left = left;
            node->right = right;
            push(&stack, node);
        }
        else if(strcmp(token, "sin") == 0) //function
        {
            Node* node = create_function("sin", sin);
            Node* left = pop(&stack);
            node->left = left;
            push(&stack, node);
        }
        else if(strcmp(token, "cos") == 0)
        {
            Node* node = create_function("cos", cos);
            Node* left = pop(&stack);
            node->left = left;
            push(&stack, node);
        }
        else if(strcmp(token, "tg") == 0)
        {
            Node* node = create_function("tg", tan);
            Node* left = pop(&stack);
            node->left = left;
            push(&stack, node);
        }
        else if(strcmp(token, "ctg") == 0)
        {
            Node* node = create_function("ctg", cot);
            Node* left = pop(&stack);
            node->left = left;
            push(&stack, node);
        }
        else if(strcmp(token, "ln") == 0)
        {
            Node* node = create_function("ln", log);
            Node* left = pop(&stack);
            node->left = left;
            push(&stack, node);
        }
        else if(strcmp(token, "exp") == 0)
        {
            Node* node = create_function("exp", exp);
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
        return head->data.number.number;
    else if (head->type == OPERATOR)
    {
        switch (head->data.operator.operator)
        {
            case '+': return evaluate(head->left, x) + evaluate(head->right, x);
            case '-': return evaluate(head->left, x) - evaluate(head->right, x);
            case '*': return evaluate(head->left, x) * evaluate(head->right, x);
            case '/': return evaluate(head->left, x) / evaluate(head->right, x);
            case '^': return pow(evaluate(head->left, x), evaluate(head->right, x));        
            default: exit(1);
        }
    }
    else //FUNCTION
        return head->data.function.func(x);
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

double cot(double x) { return 1.0 / tan(x); };