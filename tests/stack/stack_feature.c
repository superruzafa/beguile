#include <beguile.h>
#include "stack_context.c"

FeatureRunner

Feature ("An stack")
    As_a ("C programmer")
    I_want_to ("create a basic stack library")
    In_order_to ("other programs could take profit of it")

    Background
        Given (an_empty_stack)
    EndBackground

    Scenario ("Insert an element")
        When (I_push_the_element(42))
        Then (the_stack_size should_be(1))
        And (the_stack_top should_be(42))
    EndScenario

    Scenario ("Push and pop")
        When (I_push_any_element)
        And (I_pop)
        Then (the_stack_should_be_empty)
    EndScenario

EndFeature


EndFeatureRunner
