Beguile,  BDD framework for C
==============================

Beguile is, in essence, a collection of C macros to write simple, concise and beautiful BDD features. Its key points are:

* Sandboxed scenarios
* Backgrounds support
* Reusable, non-redundant step actions
* Hooks
* Human-readable output
* No library needed, just `#include <beguile.h>`

## How does it look like?

```c
Feature ("A list in C")
  In_order_to ("")
  As_a ("C developer")
  I_want_to ("implement a list in C")
  
  Scenario ("Pushing an element")
    Given (an_empty_list())
    When (I_push(42))
    Then (the_stack_top() should_be(42))
    And (the_stack_size() should_be(1))
  EndScenario
EndFeature
```

## Writing features

A feature is the description of a requirement that want to be achieved and its behavior.

It's defined by the `Feature(...)` and `EndFeature` pair of macros.
The optional narrative part of the feature could be defined with the macros `In_order_that(...)`, `So_that(...)`, `As_a(...)`, `I_want_to(...)`, etc...

```c
Feature ("Descriptive title of a requirement")
    In_order_to ("benefit achieved")
    As_a ("the person that wants the feature")
    I_want_to ("feature requested")
    
    // Scenarios...
EndFeature
```

### Scenarios

A scenario is an example of one of the feature's expected behaviors.

To define a scenario you must use the `Scenario(...)` and `EndScenario` pair of macros.
Each scenario consists in an ordered sequence of steps that describe such behavior.

```c
Feature (...)
    Scenario ("Descriptive title of an expected behavior")
        // Steps needed to reproduce and check a behavior
    EndScenario
```

### Backgrounds

A background is a way to describe an initial state common to all of the scenarios in the feature. Like scenarios, backgrounds can contain steps that will be executed before every scenario in the feature.

You can define a background with the `Background` and `EndBackground` pair of tags.
The background section is optional and a feature should contain only one.
If a feature has a background then it must be defined before any scenario.

```c
Feature (...)
    Background
        // Steps for describe an initial state to all scenarios
    EndBackground
```

### Steps (given, when, then)

The steps are actions that are allow to describe an state, perform actions and check a behavior.

To define an step you should use one of the following macros:
* `Given(...)` should be used to describe an initial state.
* `When(...)` should be used to do actions according an expected behavior.
* `Then(...)` should be used to check that the outcome you were expected happened. It's usually used along with asserts.

You can use also the `And(...)` and `But(...)` step macros to improve the readability of the scenario.

Internally, Beguile makes no distinction between all those keywords but, for sake of readability, you shouldn't. Functionality is the same but semantically they mean different things.

The part that goes inside a step must be real evaluable C code.

```c
Feature (...)
    Scenario (...)
        Given (int x = 5)
        And (int y = 3)
        When (int z = x * y)
        Then (z should_be_equal_to(15))
    ScenarioEnd
```

### Asserts

Asserts allow to verify whether the behavior is the expected or not. Ideally they should be used along with a `Then(...)`.

Beguile comes with a predefined set of asserts:

| Assert                                  | What it checks                      |
|-----------------------------------------|-------------------------------------|
| `should_be_equal_to(x)`                 | value == x                          |
| `should_be(x)`                          | Alias for `should_be_equal_to(x)`   |
| `should_not_be_equal_to(x)`             | value != x                          |
| `should_not_be(x)`                      | Alias for `shouldnt_be_equal_to(x)` |
| `should_be_greater_than(x)`             | value > x                           |
| `should_be_greater_or_equal_than(x)`    | value >= x                          |
| `should_be_less_than(x)`                | value < x                           |
| `should_be_less_or_equal_than(x)`       | value <= x                          |
| `should_be_null`                        | value == NULL                       |
| `shouldnt_be_null`                      | value != NULL                       |

## Running features

### Standalone way

In this way you define your features inside the `FeatureRunner` and `EndFeatureRunner` pair of macros and that's all. If you compile this file you'll have a fully functional executable file.

```c
#include <beguile.h>
FeatureRunner
    // features
EndFeatureRunner
```

### Non-standalone way

In this way you can use features in functions. In order to do that your features must be wrapped everytime by the `FeatureRunnerHeader` and `FeatureRunnerFooter` pair of macros.

```c
#include <beguile.h>

int run_feature()
{
    FeatureRunnerHeader
        // features...
    FeatureRunnerFooter     // returns EXIT_SUCCESS or EXIT_FAILURE
}

int main(int argc, char **argv)
{
    return run_other_feature();
}
```

## Hooks

Beguile allows you to hooking into the test process. You can specify the function that will be called using the `beguile_set_hook(...)` function. A hook function is expected to have the signture `void you_hook_name(BeguileHookType type)`. Everytime an event is triggered this function will be called with one of these self-explanatory values:

* `BEGUILE_HOOK_BEFORE_FEATURE`
* `BEGUILE_HOOK_AFTER_FEATURE`
* `BEGUILE_HOOK_BEFORE_BACKGROUND`
* `BEGUILE_HOOK_AFTER_BACKGROUND`
* `BEGUILE_HOOK_BEFORE_SCENARIO`
* `BEGUILE_HOOK_AFTER_SCENARIO`
* `BEGUILE_HOOK_BEFORE_STEP`
* `BEGUILE_HOOK_AFTER_STEP`


```c
void my_hook_function(BeguileHookType type)
{
    // ...
}


FeatureRunner
beguile_set_hook(my_hook_function);

// features

EndFeatureRunner











