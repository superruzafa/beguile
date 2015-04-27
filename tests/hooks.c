#include <beguile.h>
#include <stdarg.h>

struct HookLogger {
    BeguileHookType hook_type[10];
    int index;
} hook_logger;

void track_hook(BeguileHookType type)
{
    hook_logger.hook_type[hook_logger.index++] = type;
}

#define assert_triggered_hooks(...) real_assert_triggered_hooks(1, ##__VA_ARGS__, -1)

int real_assert_triggered_hooks(int anchor, ...)
{
    int i = 0;
    BeguileHookType hook_type;
    va_list list;
    va_start(list, anchor);
    hook_type = va_arg(list, BeguileHookType);
    while (hook_type != -1 && i < hook_logger.index) {
        if (hook_logger.hook_type[i] != hook_type) return EXIT_FAILURE;
        ++i;
        hook_type = va_arg(list, BeguileHookType);
    }
    va_end(list);
    return (i == hook_logger.index) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int test_empty()
{
    FeatureRunnerHeader
    beguile_set_hook(track_hook);
    return assert_triggered_hooks();
}

int test_feature()
{
    FeatureRunnerHeader
    beguile_set_hook(track_hook);
    Feature("")
    EndFeature

    return assert_triggered_hooks(BEGUILE_HOOK_BEFORE_FEATURE, BEGUILE_HOOK_AFTER_FEATURE);
}

int test_feature_scenario()
{
    FeatureRunnerHeader
    beguile_set_hook(track_hook);
    Feature("")
        Scenario("")
        EndScenario
    EndFeature

    return assert_triggered_hooks(
        BEGUILE_HOOK_BEFORE_FEATURE,
        BEGUILE_HOOK_BEFORE_SCENARIO,
        BEGUILE_HOOK_AFTER_SCENARIO,
        BEGUILE_HOOK_AFTER_FEATURE
    );
}

int test_feature_background()
{
    FeatureRunnerHeader
    beguile_set_hook(track_hook);
    Feature("")
        Background
        EndBackground
    EndFeature

    return assert_triggered_hooks(
        BEGUILE_HOOK_BEFORE_FEATURE,
        BEGUILE_HOOK_AFTER_FEATURE
    );
}

int test_feature_background_scenario()
{
    FeatureRunnerHeader
    beguile_set_hook(track_hook);
    Feature("")
        Background
        EndBackground
        Scenario("")
        EndScenario
    EndFeature

    return assert_triggered_hooks(
        BEGUILE_HOOK_BEFORE_FEATURE,
        BEGUILE_HOOK_BEFORE_BACKGROUND,
        BEGUILE_HOOK_AFTER_BACKGROUND,
        BEGUILE_HOOK_BEFORE_SCENARIO,
        BEGUILE_HOOK_AFTER_SCENARIO,
        BEGUILE_HOOK_AFTER_FEATURE
    );
}

int test_feature_background_scenario_scenario()
{
    FeatureRunnerHeader
    beguile_set_hook(track_hook);
    Feature("")
        Background
        EndBackground
        Scenario("")
        EndScenario
        Scenario("")
        EndScenario
    EndFeature

    return assert_triggered_hooks(
        BEGUILE_HOOK_BEFORE_FEATURE,
        BEGUILE_HOOK_BEFORE_BACKGROUND,
        BEGUILE_HOOK_AFTER_BACKGROUND,
        BEGUILE_HOOK_BEFORE_SCENARIO,
        BEGUILE_HOOK_AFTER_SCENARIO,
        BEGUILE_HOOK_BEFORE_BACKGROUND,
        BEGUILE_HOOK_AFTER_BACKGROUND,
        BEGUILE_HOOK_BEFORE_SCENARIO,
        BEGUILE_HOOK_AFTER_SCENARIO,
        BEGUILE_HOOK_AFTER_FEATURE
    );
}

#define FEATURE_SHOULD_SUCCEED(function) \
    hook_logger.index = 0; \
    printf("Running %s... ", #function); \
    if (function() == EXIT_SUCCESS) { \
        puts("OK"); \
    } else { \
        puts("FAIL"); \
        result = EXIT_FAILURE; \
    }

int main(int argc, char **argv)
{
    int result = EXIT_SUCCESS;
    FEATURE_SHOULD_SUCCEED(test_empty);
    FEATURE_SHOULD_SUCCEED(test_feature);
    FEATURE_SHOULD_SUCCEED(test_feature_scenario);
    FEATURE_SHOULD_SUCCEED(test_feature_background);
    FEATURE_SHOULD_SUCCEED(test_feature_background_scenario);
    FEATURE_SHOULD_SUCCEED(test_feature_background_scenario_scenario);
    return result;
}
