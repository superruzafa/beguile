#include <beguile.h>

int i = 0;
FeatureRunner

Feature ("Backgrounds")

    Background
        Given(i = 10)
    EndBackground

    Scenario ("First background execution")
        Then (i should_be(10))
    EndScenario

    Scenario ("Second background execution")
        When (i += 5)
        Then (i should_be(15))
    EndScenario

EndFeature

EndFeatureRunner
