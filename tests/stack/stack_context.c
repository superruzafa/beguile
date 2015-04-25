#include <time.h>
#include <stdlib.h>
#include "stack.h"


static Stack *stack;

// Custom asserts

#define the_stack_should_not_be_empty stack_size(stack) should_not_be(0)
#define the_stack_should_be_empty stack_size(stack) should_be(0)

// Helpers

int random_integer()
{
    srand(time(NULL));
    return rand();
}

// Predicates

#define an_empty_stack                  stack = NULL
#define I_push_the_element(element)     stack = stack_push(stack, element)
#define I_push_any_element              stack = stack_push(stack, random())
#define I_pop                           stack = stack_pop(stack)
#define the_stack_size                  stack_size(stack)
#define the_stack_top                   stack_top(stack)
