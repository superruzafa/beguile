#include <check.h>
#include <beguile.h>

START_TEST(test_verbose_option)
{
    char *argv[] = {"options", "--verbose"};
    beguile_global_vars.output_enabled = -1;
    BeguileParseOptions(2, argv);
    ck_assert_int_eq(beguile_global_vars.output_enabled, 1);
}
END_TEST

START_TEST(test_silent_option)
{
    char *argv[] = {"options", "--silent"};
    beguile_global_vars.output_enabled = -1;
    BeguileParseOptions(2, argv);
    ck_assert_int_eq(beguile_global_vars.output_enabled, 0);
}
END_TEST

int main(int argc, char **argv)
{
    beguile_disable_output();

    Suite *suite = suite_create("Options");
    TCase *tcase = tcase_create("Options");
    suite_add_tcase(suite, tcase);

    tcase_add_test(tcase, test_verbose_option);
    tcase_add_test(tcase, test_silent_option);

    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_VERBOSE);
    int test_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (test_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
