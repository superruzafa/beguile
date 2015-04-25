#include <stdlib.h>
#include <malloc.h>
#include "stack.h"

struct _Stack {
    StackElement    element;
    Stack          *next;
};

Stack *stack_new()
{
    return NULL;
}

Stack *stack_free(Stack *stack)
{
    Stack *node = stack;
    while (stack != NULL) {
        node = stack;
        stack = stack->next;
        free(node);
    }
    return stack;
}

Stack *stack_push(Stack *stack, StackElement element)
{
    Stack *node = (Stack *)malloc(sizeof(Stack));
    node->next = stack;
    node->element = element;
    return node;
}

StackElement stack_top(Stack *stack)
{
    return stack->element;
}

Stack *stack_pop(Stack *stack)
{
    if (stack == NULL) return stack;
    Stack *node = stack;
    stack = stack->next;
    free(node);
    return stack;
}

int stack_size(Stack *stack)
{
    int size = 0;
    while (stack != NULL) {
        ++size;
        stack = stack->next;
    }
    return size;
}
