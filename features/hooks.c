#include <stdarg.h>
#include <beguile.h>

struct HookSequence {
    BeguileHookType sequence[20];
    int current;
} hook_sequence;

void hook_handler(BeguileHookType type)
{
    hook_sequence.sequence[hook_sequence.current] = type;
    ++hook_sequence.current;
}

void real_the_hook_sequence_should_be(int anchor, ...)
{
    int i = 0;
    va_list hooks;
    va_start(hooks, anchor);
    BeguileHookType type = va_arg(hooks, BeguileHookType);
    while (type != -1) {
        if (hook_sequence.sequence[i++] != type) {
            BEGUILE_PRINT(" " BEGUILE_STYLE_FAILURE(BEGUILE_MSG_FAIL) "\n");
            _exit(EXIT_FAILURE);
        }
        type = va_arg(hooks, BeguileHookType);
    }
    va_end(hooks);
    if (i != hook_sequence.current)
    {
        BEGUILE_PRINT(" " BEGUILE_STYLE_FAILURE(BEGUILE_MSG_FAIL) "\n");
        _exit(EXIT_FAILURE);
    }
    BEGUILE_PRINT(" " BEGUILE_STYLE_SUCCESS(BEGUILE_MSG_OK) "\n");
}

#define the_hook_sequence_should_be(...) \
    real_the_hook_sequence_should_be(1, ##__VA_ARGS__, -1)

void i_run_no_feature()
{
    hook_sequence.current = 0;
    FeatureRunnerHeader
    beguile_set_hook(hook_handler);
    beguile_set_hook(NULL);
}

void i_run_a_feature_with_background_but_not_scenarios()
{
    hook_sequence.current = 0;
    FeatureRunnerHeader
    beguile_set_hook(hook_handler);
        Background
        EndBackground
    Feature ("Feature with no scenarios")
    EndFeature
    beguile_set_hook(NULL);
}

void i_run_a_feature_with_no_scenarios()
{
    hook_sequence.current = 0;
    FeatureRunnerHeader
    beguile_set_hook(hook_handler);
    Feature ("Feature with no scenarios")
    EndFeature
    beguile_set_hook(NULL);
}

void i_run_a_feature_with_one_scenario()
{
    hook_sequence.current = 0;
    FeatureRunnerHeader
    beguile_set_hook(hook_handler);
    Feature ("Feature with no scenarios")
        Scenario ("Unique scenario")
        EndScenario
    EndFeature
    beguile_set_hook(NULL);
}

void i_run_a_feature_with_two_scenarios()
{
    hook_sequence.current = 0;
    FeatureRunnerHeader
    beguile_set_hook(hook_handler);
    Feature ("Feature with no scenarios")
        Scenario ("First scenario")
        EndScenario
        Scenario ("Second scenario")
        EndScenario
    EndFeature
    beguile_set_hook(NULL);
}

void i_run_a_feature_with_background_and_two_scenarios()
{
    hook_sequence.current = 0;
    FeatureRunnerHeader
    beguile_set_hook(hook_handler);
    Feature ("Feature with background and two scenarios")
        Background
        EndBackground
        Scenario ("First scenario")
        EndScenario
        Scenario ("Second scenario")
        EndScenario
    EndFeature
    beguile_set_hook(NULL);
}

void i_run_a_feature_with_a_background_which_has_steps()
{
    hook_sequence.current = 0;
    FeatureRunnerHeader
    beguile_set_hook(hook_handler);
    Feature ("Feature with a background which has steps")
        Background
            Given()
            When()
        EndBackground
    EndFeature
    beguile_set_hook(NULL);
}

void i_run_a_feature_with_background_scenarios_and_steps()
{
    hook_sequence.current = 0;
    FeatureRunnerHeader
    beguile_set_hook(hook_handler);
    Feature ("Feature with background, scenarios and steps")
        Background
            Given()
        EndBackground
        Scenario("Foo")
            Then()
        EndScenario
        Scenario("Bar")
            Then()
        EndScenario
    EndFeature
    beguile_set_hook(NULL);
}

FeatureRunner

Feature ("Hooks")

    Scenario ("A feature without... features!")
        When (i_run_no_feature())
        Then (the_hook_sequence_should_be())
    EndScenario

    Scenario ("A feature with no scenarios")
        When (i_run_a_feature_with_no_scenarios())
        Then (the_hook_sequence_should_be(
            BEGUILE_HOOK_BEFORE_FEATURE,
            BEGUILE_HOOK_AFTER_FEATURE
        ))
    EndScenario

    Scenario ("A feature with background but not scenarios")
        When (i_run_a_feature_with_background_but_not_scenarios())
        Then (the_hook_sequence_should_be(
            BEGUILE_HOOK_BEFORE_FEATURE,
            BEGUILE_HOOK_AFTER_FEATURE
        ))
    EndScenario

    Scenario ("A feature with a single scenario")
        When (i_run_a_feature_with_one_scenario())
        Then (the_hook_sequence_should_be(
            BEGUILE_HOOK_BEFORE_FEATURE,
            BEGUILE_HOOK_BEFORE_SCENARIO,
            BEGUILE_HOOK_AFTER_SCENARIO,
            BEGUILE_HOOK_AFTER_FEATURE
        ))
    EndScenario

    Scenario ("A feature with two scenarios")
        When (i_run_a_feature_with_two_scenarios())
        Then (the_hook_sequence_should_be(
            BEGUILE_HOOK_BEFORE_FEATURE,
            BEGUILE_HOOK_BEFORE_SCENARIO,
            BEGUILE_HOOK_AFTER_SCENARIO,
            BEGUILE_HOOK_BEFORE_SCENARIO,
            BEGUILE_HOOK_AFTER_SCENARIO,
            BEGUILE_HOOK_AFTER_FEATURE
        ))
    EndScenario

    Scenario ("A feature with background and two scenarios")
        When (i_run_a_feature_with_background_and_two_scenarios())
        Then (the_hook_sequence_should_be(
            BEGUILE_HOOK_BEFORE_FEATURE,
                BEGUILE_HOOK_BEFORE_BACKGROUND, BEGUILE_HOOK_AFTER_BACKGROUND,
                BEGUILE_HOOK_BEFORE_SCENARIO, BEGUILE_HOOK_AFTER_SCENARIO,
                BEGUILE_HOOK_BEFORE_BACKGROUND, BEGUILE_HOOK_AFTER_BACKGROUND,
                BEGUILE_HOOK_BEFORE_SCENARIO, BEGUILE_HOOK_AFTER_SCENARIO,
            BEGUILE_HOOK_AFTER_FEATURE
        ))
    EndScenario

   Scenario ("A feature with background, scenarios and steps")
        When (i_run_a_feature_with_background_scenarios_and_steps())
        Then (the_hook_sequence_should_be(
            BEGUILE_HOOK_BEFORE_FEATURE,
                BEGUILE_HOOK_BEFORE_BACKGROUND,
                    BEGUILE_HOOK_BEFORE_STEP, BEGUILE_HOOK_AFTER_STEP,
                BEGUILE_HOOK_AFTER_BACKGROUND,
                BEGUILE_HOOK_BEFORE_SCENARIO,
                    BEGUILE_HOOK_BEFORE_STEP, BEGUILE_HOOK_AFTER_STEP,
                BEGUILE_HOOK_AFTER_SCENARIO,
                BEGUILE_HOOK_BEFORE_BACKGROUND,
                    BEGUILE_HOOK_BEFORE_STEP, BEGUILE_HOOK_AFTER_STEP,
                BEGUILE_HOOK_AFTER_BACKGROUND,
                BEGUILE_HOOK_BEFORE_SCENARIO,
                    BEGUILE_HOOK_BEFORE_STEP, BEGUILE_HOOK_AFTER_STEP,
                BEGUILE_HOOK_AFTER_SCENARIO,
            BEGUILE_HOOK_AFTER_FEATURE
        ))
    EndScenario

EndFeature

EndFeatureRunner
