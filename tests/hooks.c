#include <check.h>
#include <beguile.h>
#include <stdarg.h>

struct HookLog {
    BeguileHookType type[10];
    int index;
} hook_log;

void setup()
{
    hook_log.index = 0;
}

void hook_logger(BeguileHookType type)
{
    hook_log.type[hook_log.index++] = type;
}

int real_assert_triggered_hooks(int anchor, ...)
{
    int i = 0;
    BeguileHookType hook_type;
    va_list list;
    va_start(list, anchor);
    hook_type = va_arg(list, BeguileHookType);
    while (hook_type != -1 && i < hook_log.index) {
        ck_assert_int_eq(hook_log.type[i], hook_type);
        ++i;
        hook_type = va_arg(list, BeguileHookType);
    }
    va_end(list);
    ck_assert_int_eq(i, hook_log.index);
}

#define assert_triggered_hooks(...) real_assert_triggered_hooks(1, ##__VA_ARGS__, -1)

START_TEST(test_empty_feature)
{
    FeatureRunnerHeader

    assert_triggered_hooks();
}
END_TEST

START_TEST(test_feature)
{
    FeatureRunnerHeader
    Feature("")
    EndFeature

    assert_triggered_hooks(BEGUILE_HOOK_BEFORE_FEATURE, BEGUILE_HOOK_AFTER_FEATURE);
}
END_TEST

START_TEST(test_feature_scenario)
{
    FeatureRunnerHeader
    Feature("")
        Scenario("")
        EndScenario
    EndFeature

    assert_triggered_hooks(
        BEGUILE_HOOK_BEFORE_FEATURE,
        BEGUILE_HOOK_BEFORE_SCENARIO,
        BEGUILE_HOOK_AFTER_SCENARIO,
        BEGUILE_HOOK_AFTER_FEATURE
    );
}
END_TEST

START_TEST(test_feature_background)
{
    FeatureRunnerHeader
    Feature("")
        Background
        EndBackground
    EndFeature

    assert_triggered_hooks(
        BEGUILE_HOOK_BEFORE_FEATURE,
        BEGUILE_HOOK_AFTER_FEATURE
    );
}                                          
END_TEST

START_TEST(test_feature_background_scenario)
{
    FeatureRunnerHeader
    Feature("")
        Background
        EndBackground
        Scenario("")
        EndScenario
    EndFeature

    assert_triggered_hooks(
        BEGUILE_HOOK_BEFORE_FEATURE,
        BEGUILE_HOOK_BEFORE_BACKGROUND,
        BEGUILE_HOOK_AFTER_BACKGROUND,
        BEGUILE_HOOK_BEFORE_SCENARIO,
        BEGUILE_HOOK_AFTER_SCENARIO,
        BEGUILE_HOOK_AFTER_FEATURE
    );
}
END_TEST

START_TEST(test_feature_background_scenario_scenario)
{
    FeatureRunnerHeader
    Feature("")
        Background
        EndBackground
        Scenario("")
        EndScenario
        Scenario("")
        EndScenario
    EndFeature

    assert_triggered_hooks(
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
END_TEST

int main(int argc, char **argv)
{
    beguile_disable_output();
    beguile_enable_hook(hook_logger);

    Suite *suite = suite_create("Hooks");
    TCase *tcase = tcase_create("Hooks");
    suite_add_tcase(suite, tcase);

    tcase_add_checked_fixture(tcase, setup, NULL);
    tcase_add_test(tcase, test_empty_feature);
    tcase_add_test(tcase, test_feature);
    tcase_add_test(tcase, test_feature_scenario);
    tcase_add_test(tcase, test_feature_background);
    tcase_add_test(tcase, test_feature_background_scenario);
    tcase_add_test(tcase, test_feature_background_scenario_scenario);

    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_VERBOSE);
    int test_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (test_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
