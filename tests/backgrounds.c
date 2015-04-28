#include <check.h>
#include <beguile.h>

START_TEST(background_should_not_be_executed_if_there_are_no_scenarios)
{
    volatile int i = 10;
    FeatureRunnerHeader
    Feature ("")
        Background
            Given (i = 10)
            Then (i should_be(20))
        EndBackground
    EndFeature

    ck_assert_int_eq(beguile_stats.feature_total, 1);
    ck_assert_int_eq(beguile_stats.feature_failed, 0);
    ck_assert_int_eq(beguile_stats.scenario_total, 0);
    ck_assert_int_eq(beguile_stats.step_total, 0);
}
END_TEST

START_TEST(test_background_should_be_executed_if_there_is_at_least_one_scenario)
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

    ck_assert_int_eq(beguile_stats.feature_total, 1);
    ck_assert_int_eq(beguile_stats.feature_failed, 0);
    ck_assert_int_eq(beguile_stats.scenario_total, 1);
    ck_assert_int_eq(beguile_stats.scenario_failed, 0);
    ck_assert_int_eq(beguile_stats.step_total, 2);
    ck_assert_int_eq(beguile_stats.step_failed, 0);
}
END_TEST

START_TEST(test_background_should_be_executed_if_there_is_at_least_one_scenario_fail_case)
{
    volatile int i = -1;
    FeatureRunnerHeader
    Feature ("")
        Background
            Given (i = 10)
        EndBackground
        Scenario ("")
            Then (i should_be_equal_to(30))
        EndScenario
    EndFeature

    ck_assert_int_eq(beguile_stats.feature_total, 1);
    ck_assert_int_eq(beguile_stats.feature_failed, 1);
    ck_assert_int_eq(beguile_stats.scenario_total, 1);
    ck_assert_int_eq(beguile_stats.scenario_failed, 1);
    ck_assert_int_eq(beguile_stats.step_total, 2);
    ck_assert_int_eq(beguile_stats.step_failed, 1);
}
END_TEST

START_TEST(test_background_should_be_executed_once_for_each_scenario)
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

    ck_assert_int_eq(beguile_stats.feature_total, 1);
    ck_assert_int_eq(beguile_stats.feature_failed, 0);
    ck_assert_int_eq(beguile_stats.scenario_total, 2);
    ck_assert_int_eq(beguile_stats.scenario_failed, 0);
    ck_assert_int_eq(beguile_stats.step_total, 6);
    ck_assert_int_eq(beguile_stats.step_failed, 0);
}
END_TEST

START_TEST(test_backgrounds_not_work_with_non_volatile_variables)
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

    ck_assert_int_eq(beguile_stats.feature_total, 1);
    ck_assert_int_eq(beguile_stats.feature_failed, 1);
    ck_assert_int_eq(beguile_stats.scenario_total, 1);
    ck_assert_int_eq(beguile_stats.scenario_failed, 1);
    ck_assert_int_eq(beguile_stats.step_total, 2);
    ck_assert_int_eq(beguile_stats.step_failed, 1);
}
END_TEST

int i = 5;
void set_i(int value) { i = value; }

START_TEST(test_backgrounds_should_work_for_non_volatile_global_variables_and_functions)
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

    ck_assert_int_eq(beguile_stats.feature_total, 1);
    ck_assert_int_eq(beguile_stats.feature_failed, 0);
    ck_assert_int_eq(beguile_stats.scenario_total, 1);
    ck_assert_int_eq(beguile_stats.scenario_failed, 0);
    ck_assert_int_eq(beguile_stats.step_total, 2);
    ck_assert_int_eq(beguile_stats.step_failed, 0);
}
END_TEST

int main(int argc, char **argv)
{
    beguile_disable_output();

    Suite *suite = suite_create("Backgrounds");
    TCase *tcase = tcase_create("Backgrounds");
    suite_add_tcase(suite, tcase);

    tcase_add_test(tcase, background_should_not_be_executed_if_there_are_no_scenarios);

    tcase_add_test(tcase, test_background_should_be_executed_if_there_is_at_least_one_scenario);
    tcase_add_test(tcase, test_background_should_be_executed_if_there_is_at_least_one_scenario_fail_case);

    tcase_add_test(tcase, test_background_should_be_executed_once_for_each_scenario);
    tcase_add_test(tcase, test_backgrounds_not_work_with_non_volatile_variables);
    tcase_add_test(tcase, test_backgrounds_should_work_for_non_volatile_global_variables_and_functions);

    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_VERBOSE);
    int test_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (test_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
