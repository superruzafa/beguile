#ifndef __STACK_H
#define __STACK_H

#include <stdlib.h>
#include <malloc.h>

typedef struct _Stack Stack;
typedef int StackElement;

Stack *stack_new();
Stack *stack_free(Stack *stack);
Stack *stack_push(Stack *stack, StackElement element);
StackElement stack_top(Stack *stack);
Stack *stack_pop(Stack *stack);
int stack_size(Stack *stack);

#endif
