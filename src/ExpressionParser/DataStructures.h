#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "Token.h"

#include <stdbool.h>

#define TOKEN_STACK_SIZE 50
#define TOKEN_QUEUE_SIZE 50

// stack
typedef struct TokenStack {
    Token* data[TOKEN_STACK_SIZE];
    unsigned top;
} TokenStack;

TokenStack stack_create();
void stack_push(TokenStack* stack, Token* token);
Token* stack_pop(TokenStack* stack);
Token* stack_top(TokenStack* stack);
bool stack_is_empty(TokenStack* stack);
bool stack_is_full(TokenStack* stack);

// queue
typedef struct TokenQueue {
    Token* data[TOKEN_QUEUE_SIZE];
    int front, rear, size;
} TokenQueue;

TokenQueue queue_create();
void queue_enqueue(TokenQueue* queue, Token* node);
Token* queue_dequeue(TokenQueue* queue);
Token* queue_front(TokenQueue* queue);
Token* queue_rear(TokenQueue* queue);
bool queue_is_empty(TokenQueue* queue);
bool queue_is_full(TokenQueue* queue);

#endif