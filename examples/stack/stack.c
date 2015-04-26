#include <malloc.h>
#include <stdlib.h>
#include "stack.h"

struct _Stack {
    struct _Stack *next;
    StackElement element;
};

Stack *stack_new()
{
    return NULL;
}

Stack *stack_free(Stack *stack)
{
    while (stack != NULL) {
        stack = stack_pop(stack);
    }
}

unsigned int stack_size(Stack *stack)
{
    unsigned int size = 0;
    while (stack != NULL) {
        ++size;
        stack = stack->next;
    }
    return size;
}

Stack *stack_push(Stack *stack, StackElement element)
{
    Stack *node = (Stack *)malloc(sizeof(Stack));
    node->element = element;
    node->next = stack;
    return node;
}

Stack *stack_pop(Stack *stack)
{
    Stack *node = stack = stack;
    stack = stack->next;
    free(node);
    return stack;
}

StackElement stack_top(Stack *stack)
{
    return stack->element;
}
