#include "stack.h"

static Stack *stack;
static int last_result;

void stack_hook(BeguileHookType type, int is_child)
{
    if (type == BEGUILE_HOOK_AFTER_SCENARIO && is_child) {
        stack = stack_free(stack);
    }
}

void a_stack()
{
    stack = stack_new();
}

int the_stack_size()
{
    return stack_size(stack);
}

void I_push(int element)
{
    stack = stack_push(stack, element);
}

void I_push_the_operator(char oper)
{
    stack = stack_push(stack, (char)oper);
}

void I_pop()
{
    stack = stack_pop(stack);
}

StackElement the_stack_top()
{
    return stack_top(stack);
}

void I_evaluate_the_stack()
{
    StackElement oper = (int)stack_top(stack);
    stack = stack_pop(stack);
    StackElement op1 = stack_top(stack);
    stack = stack_pop(stack);
    StackElement op2 = stack_top(stack);
    stack = stack_pop(stack);

    switch ((char) oper) {
        case '+':
            last_result = op1 + op2;
            break;
        case '/':
            last_result = op1 / op2;
            break;
        default:
            last_result = 0;
            break;
    }
}

int the_result()
{
    return last_result;
}
