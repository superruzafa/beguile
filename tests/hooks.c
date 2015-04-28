#include <check.h>
#include <beguile.h>
#include <stdarg.h>

struct HookMessage {
    BeguileHookType type;
    int is_child;
};

struct HookLog {
    struct HookMessage message[20];
    int index;
} hook_log;

void setup()
{
    hook_log.index = 0;
}

void hook_logger(BeguileHookType type, int is_child)
{
//    printf("(%d, %d) -> ", type, is_child); fflush(stdout);
    hook_log.message[hook_log.index].type = type;
    hook_log.message[hook_log.index].is_child = is_child;
    ++hook_log.index;
}

int real_assert_triggered_hooks(int anchor, ...)
{
    int i = 0;
    struct HookMessage message;
    va_list list;

    va_start(list, anchor);
    message.type = va_arg(list, BeguileHookType);
    message.is_child = va_arg(list, int);
    while (message.type != -1 && i < hook_log.index) {
        ck_assert_int_eq(hook_log.message[i].type, message.type);
        ck_assert_int_eq(hook_log.message[i].is_child, message.is_child);
        ++i;
        message.type = va_arg(list, BeguileHookType);
        message.is_child = va_arg(list, int);
    }
    va_end(list);
    ck_assert_int_eq(i, hook_log.index);
}

#define assert_triggered_hooks(...) real_assert_triggered_hooks(1, ##__VA_ARGS__, -1)

START_TEST(test_empty_feature_no_fork)
{
    beguile_disable_fork();

    FeatureRunnerHeader

    assert_triggered_hooks();
}
END_TEST

START_TEST(test_empty_feature_fork)
{
    beguile_enable_fork();

    FeatureRunnerHeader

    assert_triggered_hooks();
}
END_TEST

START_TEST(test_feature_no_fork)
{
    beguile_disable_fork();

    FeatureRunnerHeader
    Feature("")
    EndFeature

    assert_triggered_hooks(
        BEGUILE_HOOK_BEFORE_FEATURE, 0,
        BEGUILE_HOOK_AFTER_FEATURE, 0
    );
}
END_TEST

START_TEST(test_feature_fork)
{
    beguile_enable_fork();

    FeatureRunnerHeader
    Feature("")
    EndFeature

    assert_triggered_hooks(
        BEGUILE_HOOK_BEFORE_FEATURE, 0,
        BEGUILE_HOOK_AFTER_FEATURE, 0
    );
}
END_TEST

START_TEST(test_feature_scenario_no_fork)
{
    beguile_disable_fork();

    FeatureRunnerHeader
    Feature("")
        Scenario("")
        EndScenario
    EndFeature

    assert_triggered_hooks(
        BEGUILE_HOOK_BEFORE_FEATURE, 0,
        BEGUILE_HOOK_BEFORE_SCENARIO, 0,
        BEGUILE_HOOK_AFTER_SCENARIO, 0,
        BEGUILE_HOOK_AFTER_FEATURE, 0
    );
}
END_TEST

START_TEST(test_feature_scenario_fork)
{
    beguile_enable_fork();

    FeatureRunnerHeader
    Feature("")
        Scenario("")
        EndScenario
    EndFeature

    assert_triggered_hooks(
        BEGUILE_HOOK_BEFORE_FEATURE, 0,
        BEGUILE_HOOK_BEFORE_SCENARIO, 0,
//        BEGUILE_HOOK_BEFORE_SCENARIO, 1,
//        BEGUILE_HOOK_AFTER_SCENARIO, 1,
        BEGUILE_HOOK_AFTER_SCENARIO, 0,
        BEGUILE_HOOK_AFTER_FEATURE, 0
    );
}
END_TEST

START_TEST(test_feature_background_no_fork)
{
    beguile_disable_fork();

    FeatureRunnerHeader
    Feature("")
        Background
        EndBackground
    EndFeature

    assert_triggered_hooks(
        BEGUILE_HOOK_BEFORE_FEATURE, 0,
        BEGUILE_HOOK_AFTER_FEATURE, 0
    );
}
END_TEST

START_TEST(test_feature_background_fork)
{
    beguile_enable_fork();

    FeatureRunnerHeader
    Feature("")
        Background
        EndBackground
    EndFeature

    assert_triggered_hooks(
        BEGUILE_HOOK_BEFORE_FEATURE, 0,
        BEGUILE_HOOK_AFTER_FEATURE, 0
    );
}
END_TEST

START_TEST(test_feature_background_scenario_no_fork)
{
    beguile_disable_fork();

    FeatureRunnerHeader
    Feature("")
        Background
        EndBackground
        Scenario("")
        EndScenario
    EndFeature

    assert_triggered_hooks(
        BEGUILE_HOOK_BEFORE_FEATURE, 0,
        BEGUILE_HOOK_BEFORE_BACKGROUND, 0,
        BEGUILE_HOOK_AFTER_BACKGROUND, 0,
        BEGUILE_HOOK_BEFORE_SCENARIO, 0,
        BEGUILE_HOOK_AFTER_SCENARIO, 0,
        BEGUILE_HOOK_AFTER_FEATURE, 0
    );
}
END_TEST

START_TEST(test_feature_background_scenario_fork)
{
    beguile_enable_fork();

    FeatureRunnerHeader
    Feature("")
        Background
        EndBackground
        Scenario("")
        EndScenario
    EndFeature

    assert_triggered_hooks(
        BEGUILE_HOOK_BEFORE_FEATURE, 0,
        BEGUILE_HOOK_BEFORE_BACKGROUND, 0,
//        BEGUILE_HOOK_BEFORE_BACKGROUND, 1,
//        BEGUILE_HOOK_AFTER_BACKGROUND, 1,
        BEGUILE_HOOK_AFTER_BACKGROUND, 0,
        BEGUILE_HOOK_BEFORE_SCENARIO, 0,
//        BEGUILE_HOOK_BEFORE_SCENARIO, 1,
//        BEGUILE_HOOK_AFTER_SCENARIO, 1,
        BEGUILE_HOOK_AFTER_SCENARIO, 0,
        BEGUILE_HOOK_AFTER_FEATURE, 0
    );
}
END_TEST

START_TEST(test_feature_background_scenario_scenario_no_fork)
{
    beguile_disable_fork();

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
        BEGUILE_HOOK_BEFORE_FEATURE, 0,
        BEGUILE_HOOK_BEFORE_BACKGROUND, 0,
        BEGUILE_HOOK_AFTER_BACKGROUND, 0,
        BEGUILE_HOOK_BEFORE_SCENARIO, 0,
        BEGUILE_HOOK_AFTER_SCENARIO, 0,
        BEGUILE_HOOK_BEFORE_BACKGROUND, 0,
        BEGUILE_HOOK_AFTER_BACKGROUND, 0,
        BEGUILE_HOOK_BEFORE_SCENARIO, 0,
        BEGUILE_HOOK_AFTER_SCENARIO, 0,
        BEGUILE_HOOK_AFTER_FEATURE, 0
    );
}
END_TEST

START_TEST(test_feature_background_scenario_scenario_fork)
{
    beguile_enable_fork();

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
        BEGUILE_HOOK_BEFORE_FEATURE, 0,
        BEGUILE_HOOK_BEFORE_BACKGROUND, 0,
//        BEGUILE_HOOK_BEFORE_BACKGROUND, 1,
//        BEGUILE_HOOK_AFTER_BACKGROUND, 1,
        BEGUILE_HOOK_AFTER_BACKGROUND, 0,
        BEGUILE_HOOK_BEFORE_SCENARIO, 0,
//        BEGUILE_HOOK_BEFORE_SCENARIO, 1,
//        BEGUILE_HOOK_AFTER_SCENARIO, 1,
        BEGUILE_HOOK_AFTER_SCENARIO, 0,
        BEGUILE_HOOK_BEFORE_BACKGROUND, 0,
//        BEGUILE_HOOK_BEFORE_BACKGROUND, 1,
//        BEGUILE_HOOK_AFTER_BACKGROUND, 1,
        BEGUILE_HOOK_AFTER_BACKGROUND, 0,
        BEGUILE_HOOK_BEFORE_SCENARIO, 0,
//        BEGUILE_HOOK_BEFORE_SCENARIO, 1,
//        BEGUILE_HOOK_AFTER_SCENARIO, 1,
        BEGUILE_HOOK_AFTER_SCENARIO, 0,
        BEGUILE_HOOK_AFTER_FEATURE, 0
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
    tcase_add_test(tcase, test_empty_feature_no_fork);
    tcase_add_test(tcase, test_empty_feature_fork);
    tcase_add_test(tcase, test_feature_no_fork);
    tcase_add_test(tcase, test_feature_fork);
    tcase_add_test(tcase, test_feature_scenario_no_fork);
    tcase_add_test(tcase, test_feature_scenario_fork);
    tcase_add_test(tcase, test_feature_background_no_fork);
    tcase_add_test(tcase, test_feature_background_fork);
    tcase_add_test(tcase, test_feature_background_scenario_no_fork);
    tcase_add_test(tcase, test_feature_background_scenario_fork);
    tcase_add_test(tcase, test_feature_background_scenario_scenario_no_fork);
    tcase_add_test(tcase, test_feature_background_scenario_scenario_fork);

    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_VERBOSE);
    int test_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (test_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
