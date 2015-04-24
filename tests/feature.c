#include <beguile.h>

int precondition() { return 3; }
int behavior() { return 3; }
int postcondition() { return 3; }

FeatureRunner

Feature ("My feature")
    Scenario ("My scenario")
        Given (precondition())
        When (behavior())
        Then (postcondition() should_be_equal_to(3))
    EndScenario
EndFeature

EndFeatureRunner
