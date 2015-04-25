#include <beguile.h>
#include "stack_context.c"

void hook(hook_type) {
    switch (hook_type) {
        case BEGUILE_HOOK_AFTER_SCENARIO:
            stack = stack_free(stack);
            break;
    }
}

FeatureRunner

BEGUILE_SET_HOOK(hook);

Feature ("An stack")
    As_a ("C programmer")
    I_want_to ("create a basic stack library")
    In_order_to ("other programs could take profit of it")

    Background
        Given (an_empty_stack)
    EndBackground

    Scenario ("Push an element")
        When (I_push_the_element(42))
        Then (the_stack_size should_be(1))
        And (the_stack_top should_be(42))
    EndScenario

    Scenario ("Push and pop")
        When (I_push_any_element)
        And (I_pop)
        Then (the_stack_should_be_empty)
    EndScenario

    Scenario ("Pop the stack")
        When (I_pop)
        Then (the_stack_should_be_empty)
    EndScenario

EndFeature

EndFeatureRunner
