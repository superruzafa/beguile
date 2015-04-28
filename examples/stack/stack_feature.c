#include <beguile.h>
#include "stack_context.c"

FeatureRunner

beguile_enable_hook(stack_hook);

Feature ("A stack")
    In_order_to ("write once and use it in multiple projects")
    As_a ("C developer")
    I_want_to ("create a stack ADT library")

    Scenario ("An empty stack")
        Given (a_stack())
        Then (the_stack_size() should_be(0))
    EndScenario

    Scenario ("Push an element")
        Given (a_stack())
        When (I_push(42))
        Then (the_stack_size() should_be(1))
        And (the_stack_top() should_be(42))
    EndScenario

    Scenario ("[Deliberate error] Pop and element from an empty stack")
        Given (a_stack())
        When (I_pop()) // Pop from an empty stack would cause a SIGSEGV signal
        Then (the_stack_size() should_be(0))
    EndScenario

    Scenario ("Push and pop an element")
        Given (a_stack())
        When (I_push(42))
        And (I_pop())
        Then (the_stack_size() should_be(0))
    EndScenario

EndFeature

Feature ("Reverse polish notation")
    As_a ("C math developer")
    I_want_to ("use an stack")
    So_that ("I can do reverse polish notation calculations")

    Background
        Given (a_stack())
    EndBackground

    Scenario ("Add two numbers")
        When (I_push(5))
        And (I_push(10))
        And (I_push_the_operator('+'))
        And (I_evaluate_the_stack())
        Then (the_result() should_be(15))
        And (the_stack_size() should_be(0));
    EndScenario

    Scenario ("[Deliberate error] Divide by 0")
        When (I_push(0))
        And (I_push(1))
        And (I_push_the_operator('/'))
        And (I_evaluate_the_stack())
        Then (the_result() should_be(0))   // Divide by 0 would cause a SIGFPE signal
        And (the_stack_size() should_be(0))
    EndScenario

EndFeature

EndFeatureRunner

