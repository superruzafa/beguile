#include <beguile.h>

BeguileStats sigsegv_feature()
{
    FeatureRunnerHeader

    Feature ("Cause a SIGSEGV")
        Scenario ("NULL dereferencing")
            Given (int *nullptr = NULL)
            When (*nullptr = 42)
            Then (*nullptr should_be(42))
        EndScenario
    EndFeature

    return beguile_stats;
}

BeguileStats sigfpe_feature()
{
    FeatureRunnerHeader

    Feature ("Cause a SIGFPE")
        Scenario ("Division by 0")
            Given (int zero = 0)
            And (int integer = 3);
            And (int result)
            When (result = integer / zero)
            Then (result should_be(0))
        EndScenario
    EndFeature

    return beguile_stats;
}

BeguileStats stats;

FeatureRunner

    Feature ("Catch signals in features")

        Scenario ("Catch SIGFPE signals")
            When (stats = sigfpe_feature())
            Then (stats.feature_total should_be(1))
            But (stats.feature_failed should_be(1))
            And (stats.scenario_total should_be(1))
            But (stats.scenario_failed should_be(1))
            And (stats.step_total should_be(4))
            But (stats.step_failed should_be(1))
            And (stats.signal_total should_be(1))
        EndScenario

        Scenario ("Catch SIGSEGV signals")
            When (stats = sigsegv_feature())
            Then (stats.feature_total should_be(1))
            But (stats.feature_failed should_be(1))
            And (stats.scenario_total should_be(1))
            But (stats.scenario_failed should_be(1))
            And (stats.step_total should_be(2))
            But (stats.step_failed should_be(1))
            And (stats.signal_total should_be(1))
        EndScenario

    EndFeature

EndFeatureRunner
