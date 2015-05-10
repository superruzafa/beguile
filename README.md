Beguile, a BDD framework for C
==============================

[![Build Status](https://travis-ci.org/superruzafa/beguile.svg)](https://travis-ci.org/superruzafa/beguile)

Beguile is, in essence, a collection of C macros to write simple, concise and beautiful BDD features. Its key points are:

* Sandboxed scenarios
* Backgrounds support
* Reusable, non-redundant step actions
* Hooks
* Tags for run a subset of features
* Command line interface
* Human-readable output, multiple languges other than english
* No library needed, just `#include <beguile.h>`

Download the last [Beguile](https://raw.githubusercontent.com/superruzafa/beguile/master/release/beguile.h) stable version.

```c
#include "beguile.h"

FeatureRunner

Stack *stack;

Feature ("A stack")
    In_order_to ("write once and use it in multiple projects")
    As_a ("C developer")
    I_want_to ("create a stack ADT library")

    Background
        Given (a_stack())
    EndBackground

    Scenario ("An empty stack")
        Then (the_stack_size() should_be(0))
    EndScenario

    Scenario ("Push an element")
        Given (int item = 42)
        When (I_push(item))
        Then (the_stack_size() should_be(1))
        And (the_stack_top() should_be(42))
    EndScenario

EndFeatureRunner
```

