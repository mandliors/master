#include "DataStructures.h"

#include <stdlib.h>
#include <assert.h>

// stack
TokenStack stack_create()
{
    TokenStack stack;
    stack.top = -1;
    return stack;
}
void stack_push(TokenStack* stack, Token* token)
{
    assert(!stack_is_full(stack)); // stack overflow
    stack->data[++stack->top] = token;
}
Token* stack_pop(TokenStack* stack)
{
    assert(!stack_is_empty(stack)); // stack underflow
    return stack->data[stack->top--];
}
Token* stack_top(TokenStack* stack)
{
    assert(!stack_is_empty(stack)); // stack underflow
    return stack->data[stack->top];

}
bool stack_is_empty(TokenStack* stack)
{
    return stack->top == -1;
}
bool stack_is_full(TokenStack* stack)
{
    return stack->top == TOKEN_STACK_SIZE - 1;
}

// queue
TokenQueue queue_create()
{
    TokenQueue queue;
    queue.front = queue.size = 0;
    queue.rear = TOKEN_QUEUE_SIZE - 1;
    queue.size = 0;
    return queue;
}
void queue_enqueue(TokenQueue* queue, Token* token)
{
    assert(!queue_is_full(queue)); // queue is full
    queue->rear = (queue->rear + 1) % TOKEN_QUEUE_SIZE;
    queue->data[queue->rear] = token;
    queue->size = queue->size + 1;
}
Token* queue_dequeue(TokenQueue* queue)
{
    assert(!queue_is_empty(queue)); // queue is empty
    Token* item = queue->data[queue->front];
    queue->front = (queue->front + 1) % TOKEN_QUEUE_SIZE;
    queue->size = queue->size - 1;
    return item;
}
Token* queue_front(TokenQueue* queue)
{
    assert(!queue_is_empty(queue)); // queue is empty
    return queue->data[queue->front];
}
Token* queue_rear(TokenQueue* queue)
{
    assert(!queue_is_empty(queue)); // queue is empty
    return queue->data[queue->rear];
}
bool queue_is_empty(TokenQueue* queue)
{
    return queue->size == 0;
}
bool queue_is_full(TokenQueue* queue)
{
    return queue->size == TOKEN_QUEUE_SIZE;
}