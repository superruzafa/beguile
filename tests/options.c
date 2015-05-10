#include <check.h>
#include <beguile.h>

START_TEST(test_help_option)
{
    char *argv[] = {"options", "-h"};
    beguile_parse_options(2, argv);
}
END_TEST

START_TEST(test_help_long_option)
{
    char *argv[] = {"options", "--help"};
    beguile_parse_options(2, argv);
}
END_TEST

START_TEST(test_silent_option)
{
    char *argv[] = {"options", "-s"};
    beguile_global_vars.output_enabled = -1;
    beguile_parse_options(2, argv);
    ck_assert_int_eq(beguile_global_vars.output_enabled, 0);
}
END_TEST

START_TEST(test_silent_long_option)
{
    char *argv[] = {"options", "--silent"};
    beguile_global_vars.output_enabled = -1;
    beguile_parse_options(2, argv);
    ck_assert_int_eq(beguile_global_vars.output_enabled, 0);
}
END_TEST

START_TEST(test_no_fork_option)
{
    char *argv[] = {"options", "-f"};
    beguile_global_vars.fork_enabled = -1;
    beguile_parse_options(2, argv);
    ck_assert_int_eq(beguile_global_vars.fork_enabled, 0);
}
END_TEST

START_TEST(test_no_fork_long_option)
{
    char *argv[] = {"options", "--no-fork"};
    beguile_global_vars.fork_enabled = -1;
    beguile_parse_options(2, argv);
    ck_assert_int_eq(beguile_global_vars.fork_enabled, 0);
}
END_TEST

START_TEST(test_no_tags)
{
    char *argv[] = {"options"};
    beguile_global_vars.user_tags = NULL;
    beguile_parse_options(1, argv);
    ck_assert(beguile_global_vars.user_tags == NULL);
}
END_TEST

START_TEST(test_tags)
{
    char *argv[] = {"options", "foo", "bar"};
    beguile_global_vars.user_tags = NULL;
    beguile_parse_options(3, argv);
    ck_assert_str_eq(beguile_global_vars.user_tags[0], "foo");
    ck_assert_str_eq(beguile_global_vars.user_tags[1], "bar");
    ck_assert_int_eq(beguile_global_vars.user_tags[2], 0);
}
END_TEST

int main(int argc, char **argv)
{
    beguile_disable_output();

    Suite *suite = suite_create("Options");
    TCase *tcase = tcase_create("Options");
    suite_add_tcase(suite, tcase);

    tcase_add_exit_test(tcase, test_help_option, -1);
    tcase_add_exit_test(tcase, test_help_long_option, -1);
    tcase_add_test(tcase, test_silent_option);
    tcase_add_test(tcase, test_silent_long_option);
    tcase_add_test(tcase, test_no_fork_option);
    tcase_add_test(tcase, test_no_fork_long_option);
    tcase_add_test(tcase, test_no_tags);
    tcase_add_test(tcase, test_tags);

    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_VERBOSE);
    int test_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (test_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
