#ifndef __STACK_H
#define __STACK_H

typedef int StackElement;
typedef struct _Stack Stack;

Stack *stack_new();

Stack *stack_free(Stack *stack);

unsigned int stack_size(Stack *stack);

Stack *stack_push(Stack *stack, StackElement element) __attribute__((warn_unused_result));

Stack *stack_pop(Stack *stack) __attribute__((warn_unused_result));

StackElement stack_top(Stack *stack);

#endif
