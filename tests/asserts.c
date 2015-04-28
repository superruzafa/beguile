#include <check.h>
#include <beguile.h>

#define TEST(name, value, expected, should_fail)                      \
    START_TEST(name)                                                  \
    {                                                                 \
        FeatureRunnerHeader                                           \
            Feature ("")                                              \
                Scenario ("")                                         \
                    Then (value expected)                             \
                EndScenario                                           \
            EndFeature                                                \
                                                                      \
        ck_assert_int_eq(beguile_stats.feature_total, 1);             \
        ck_assert_int_eq(beguile_stats.feature_failed, should_fail);  \
        ck_assert_int_eq(beguile_stats.scenario_total, 1);            \
        ck_assert_int_eq(beguile_stats.scenario_failed, should_fail); \
        ck_assert_int_eq(beguile_stats.step_total, 1);                \
        ck_assert_int_eq(beguile_stats.step_failed, should_fail);     \
    }                                                                 \
    END_TEST

#define CREATE_TEST(name, success_value, expected, fail_value) \
    TEST(test_ ## name, success_value, expected, 0) \
    TEST(test_ ## name ## _fail , fail_value, expected, 1)

CREATE_TEST(should_be,                       1,         should_be(1),                               2)
CREATE_TEST(should_not_be,                   1,         should_not_be(2),                           2)
CREATE_TEST(should_be_equal_to,              1,         should_be_equal_to(1),                      2)
CREATE_TEST(should_not_be_equal_to,          1,         should_not_be_equal_to(2),                  2)
CREATE_TEST(should_be_less_than,             5,         should_be_less_than(10),                   20)
CREATE_TEST(should_be_less_or_equal_than,    5,         should_be_less_or_equal_than(5),           10)
CREATE_TEST(should_be_greater_than,          9,         should_be_greater_than(5),                  3)
CREATE_TEST(should_be_greater_or_equal_than, 5,         should_be_greater_or_equal_than(5),         3)
CREATE_TEST(should_be_null_,                 NULL,      should_be_null,                     (void *)1)
CREATE_TEST(should_not_be_null_,             (void *)1, should_not_be_null,                      NULL)

int main(int argc, char **argv)
{
    beguile_disable_output();

    Suite *suite = suite_create("Asserts");
    TCase *tcase = tcase_create("Asserts");
    suite_add_tcase(suite, tcase);

#define ADD_TEST(name) \
    tcase_add_test(tcase, test_ ## name); \
    tcase_add_test(tcase, test_ ## name ## _fail);

    ADD_TEST(should_be);
    ADD_TEST(should_not_be);
    ADD_TEST(should_be_equal_to);
    ADD_TEST(should_not_be_equal_to);
    ADD_TEST(should_be_less_than);
    ADD_TEST(should_be_less_or_equal_than);
    ADD_TEST(should_be_greater_than);
    ADD_TEST(should_be_greater_or_equal_than);
    ADD_TEST(should_be_null_);
    ADD_TEST(should_not_be_null_);

    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_VERBOSE);
    int test_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (test_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
