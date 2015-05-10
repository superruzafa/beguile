#include <stdlib.h>
#include <beguile.h>

void run_feature(char *tag)
{
    printf("Enabled tag: %s\n\n", tag == NULL ? "None" : tag);
    FeatureRunnerHeader
    tag("important")
    Feature ("Important feature")
        Scenario ("Normal scenario") EndScenario
    EndFeature

    Feature ("1st Normal feature")
        Scenario ("Normal scenario") EndScenario
    EndFeature

    Feature ("2nd Normal feature")
        tag("important")
        Scenario ("Important scenario") EndScenario
        Scenario ("Normal scenario") EndScenario
    EndFeature

    puts("");
}

int main(int argc, char **argv)
{
    beguile_disable_tag();
    run_feature(NULL);

    beguile_enable_tag("important");
    run_feature("important");

    beguile_enable_tag("another");
    run_feature("another");

    return EXIT_SUCCESS;
}
