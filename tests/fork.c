#include <check.h>
#include <beguile.h>

START_TEST(test_sigfpe_signal_no_fork)
{
    beguile_disable_fork();

    FeatureRunnerHeader
        Feature ("")
            Scenario ("")
                Given (int x = 0)
                When (int y = 10 / x)
                Then (y should_be(0))               // <-- effective SIGFPE
            EndScenario
        EndFeature

    exit(99);
}
END_TEST

START_TEST(test_sigfpe_signal_fork)
{
    beguile_enable_fork();

    FeatureRunnerHeader
        Feature ("")
            Scenario ("")
                Given (int x = 0)
                When (int y = 10 / x)
                Then (y should_be(0))               // <-- effective SIGFPE
            EndScenario
            Scenario ("")
                Then (1 should_be(1))
            EndScenario
        EndFeature

    ck_assert_int_eq(beguile_stats.feature_total, 1);
    ck_assert_int_eq(beguile_stats.feature_failed, 1);
    ck_assert_int_eq(beguile_stats.scenario_total, 2);
    ck_assert_int_eq(beguile_stats.scenario_failed, 1);
    ck_assert_int_eq(beguile_stats.signal_total, 1);
}
END_TEST

START_TEST(test_sigsegv_signal_no_fork)
{
    beguile_disable_fork();

    FeatureRunnerHeader
        Feature ("")
            Scenario ("")
                Given (char *string = "A")
                When (string[0] = 'a')              // <-- SIGSEGV
                Then (string['a'] should_be('a'))
            EndScenario
        EndFeature

    exit(99);
}
END_TEST

START_TEST(test_sigsegv_signal_fork)
{
    beguile_enable_fork();

    FeatureRunnerHeader
        Feature ("")
            Scenario ("")
                Given (char *string = "A")
                When (string[0] = 'a')              // <-- SIGSEGV
                Then (string['a'] should_be('a'))
            EndScenario
            Scenario ("")
                Then (1 should_be(1))
            EndScenario
        EndFeature

    ck_assert_int_eq(beguile_stats.feature_total, 1);
    ck_assert_int_eq(beguile_stats.feature_failed, 1);
    ck_assert_int_eq(beguile_stats.scenario_total, 2);
    ck_assert_int_eq(beguile_stats.scenario_failed, 1);
    ck_assert_int_eq(beguile_stats.signal_total, 1);
}
END_TEST

START_TEST(test_exit_no_fork)
{
    beguile_disable_fork();

    FeatureRunnerHeader
        Feature ("")
            Scenario ("")
                Given (exit(99))
            EndScenario
        EndFeature
}
END_TEST

START_TEST(test_exit_fork)
{
    beguile_enable_fork();

    FeatureRunnerHeader
        Feature ("")
            Scenario ("")
                Given (exit(99))
            EndScenario
            Scenario ("")
                Given (exit(EXIT_SUCCESS))
            EndScenario
            Scenario ("")
                Given (exit(97))
            EndScenario
        EndFeature

    ck_assert_int_eq(beguile_stats.feature_total, 1);
    ck_assert_int_eq(beguile_stats.feature_failed, 1);
    ck_assert_int_eq(beguile_stats.scenario_total, 3);
    ck_assert_int_eq(beguile_stats.scenario_failed, 2);
    ck_assert_int_eq(beguile_stats.signal_total, 3);
}
END_TEST

int main(int argc, char **argv)
{
    beguile_disable_output();

    Suite *suite = suite_create("Fork");
    TCase *tcase = tcase_create("Fork");
    suite_add_tcase(suite, tcase);

    tcase_add_exit_test(tcase, test_sigfpe_signal_no_fork, EXIT_FAILURE);
    tcase_add_test(tcase, test_sigfpe_signal_fork);
    tcase_add_exit_test(tcase, test_sigsegv_signal_no_fork, EXIT_FAILURE);
    tcase_add_test(tcase, test_sigsegv_signal_fork);
    tcase_add_exit_test(tcase, test_exit_no_fork, 99);
    tcase_add_test(tcase, test_exit_fork);

    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_VERBOSE);
    int test_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (test_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
