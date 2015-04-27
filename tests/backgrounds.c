#include <beguile.h>

int test_background_should_not_be_executed_if_there_are_no_scenarios()
{
    volatile int i = 10;
    FeatureRunnerHeader
    Feature ("")
        Background
            Given (i = 10)
            Then (i should_be(20))
        EndBackground
    EndFeature
    FeatureRunnerFooter
}

int test_background_should_be_executed_if_there_is_at_least_one_scenario()
{
    volatile int i = -1;
    FeatureRunnerHeader
    Feature ("")
        Background
            Given (i = 10)
        EndBackground
        Scenario ("")
            Then (i should_be_equal_to(10))
        EndScenario
    EndFeature
    FeatureRunnerFooter
}

int test_background_should_be_executed_once_for_each_scenario()
{
    volatile int i = 5;
    FeatureRunnerHeader
    Feature ("")
        Background
            Given (i = 10)
        EndBackground
        Scenario ("")
            When (i += 20)
            Then (i should_be_equal_to(30))
        EndScenario
        Scenario ("")
            When (i -= 3)
            Then (i should_be_equal_to(7))
        EndScenario
    EndFeature
    FeatureRunnerFooter
}

int test_backgrounds_should_not_work_with_non_volatile_variables()
{
    int i = 5;
    FeatureRunnerHeader
    Feature ("")
        Background
            Given (i = 10)
        EndBackground
        Scenario ("")
            Then (i should_be_equal_to(10))
        EndScenario
    EndFeature
    FeatureRunnerFooter
}

int i = 5;
void set_i(int value) { i = value; }

int test_backgrounds_should_work_for_non_volatile_global_variables_and_functions()
{
    FeatureRunnerHeader
    Feature ("")
        Background
            Given (set_i(10))
        EndBackground
        Scenario ("")
            Then (i should_be_equal_to(10))
        EndScenario
    EndFeature
    FeatureRunnerFooter
}

#define FEATURE_SHOULD_SUCCEED(function) \
    printf("Running %s... ", #function); \
    if (function() == EXIT_SUCCESS) { \
        puts("OK"); \
    } else { \
        puts("FAIL"); \
        result = EXIT_FAILURE; \
    }

#define FEATURE_SHOULD_FAIL(function) \
    printf("Running %s... ", #function); \
    if (function() != EXIT_SUCCESS) { \
        puts("OK"); \
    } else { \
        puts("FAIL"); \
        result = EXIT_FAILURE; \
    }


int main(int argc, char **argv)
{
    int result = EXIT_SUCCESS;
    FEATURE_SHOULD_SUCCEED(test_background_should_not_be_executed_if_there_are_no_scenarios);
    FEATURE_SHOULD_SUCCEED(test_background_should_be_executed_if_there_is_at_least_one_scenario);
    FEATURE_SHOULD_SUCCEED(test_background_should_be_executed_once_for_each_scenario);
    FEATURE_SHOULD_FAIL(test_backgrounds_should_not_work_with_non_volatile_variables);
    FEATURE_SHOULD_SUCCEED(test_backgrounds_should_work_for_non_volatile_global_variables_and_functions);
    return result;
}
