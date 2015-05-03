#include <check.h>
#include <beguile.h>

#define CREATE_TEST(the_tags, feature_tags, scenario_tags, expected_trace) \
    START_TEST(user_##the_tags##__feature_##feature_tags##__scenario_##scenario_tags) \
    {                                                                          \
        char trace[] = "....";                                                 \
        if (the_tags) beguile_set_tags(the_tags);                              \
                                                                               \
        FeatureRunnerHeader                                                    \
                                                                               \
        if (feature_tags) tag(feature_tags)                                    \
        Feature ("")                                                           \
            if (scenario_tags) tag(scenario_tags)                              \
            Scenario ("")                                                      \
                trace[0] = 'A';                                                \
            EndScenario                                                        \
                                                                               \
            Scenario ("")                                                      \
                trace[1] = 'B';                                                \
            EndScenario                                                        \
        EndFeature                                                             \
                                                                               \
        Feature ("")                                                           \
            if (scenario_tags) tag(scenario_tags)                              \
            Scenario ("")                                                      \
                trace[2] = 'C';                                                \
            EndScenario                                                        \
                                                                               \
            Scenario ("")                                                      \
                trace[3] = 'D';                                                \
            EndScenario                                                        \
        EndFeature                                                             \
        ck_assert_str_eq(trace, expected_trace);                               \
    }                                                                          \
    END_TEST

#define untagged NULL
#define foo      "foo"
//#define foobar   "foo", "bar"
#define bar      "bar"

//          user tag,  feature tag, scenario tag, expectations
CREATE_TEST(untagged,  untagged,    untagged,     "ABCD")
CREATE_TEST(foo,       untagged,    untagged,     "....")

CREATE_TEST(untagged,  untagged,    foo,          "ABCD")
CREATE_TEST(untagged,  foo,         untagged,     "ABCD")
CREATE_TEST(untagged,  foo,         foo,          "ABCD")
CREATE_TEST(foo,       untagged,    foo,          "A.C.")
CREATE_TEST(foo,       foo,         untagged,     "AB..")
CREATE_TEST(foo,       foo,         foo,          "ABC.")

CREATE_TEST(untagged,  untagged,    bar,          "ABCD")
CREATE_TEST(untagged,  bar,         untagged,     "ABCD")
CREATE_TEST(untagged,  bar,         bar,          "ABCD")
CREATE_TEST(foo,       untagged,    bar,          "....")
CREATE_TEST(foo,       bar,         untagged,     "....")
CREATE_TEST(foo,       bar,         bar,          "....")

int main(int argc, char **argv)
{
    beguile_disable_output();
    beguile_disable_fork();

    Suite *suite = suite_create("Tags");
    TCase *tcase = tcase_create("Tags");
    suite_add_tcase(suite, tcase);

#define ADD_TEST(the_tags, feature_tags, scenario_tags) \
    tcase_add_test(tcase, user_##the_tags##__feature_##feature_tags##__scenario_##scenario_tags)

    ADD_TEST(untagged, untagged, untagged);
    ADD_TEST(foo,      untagged, untagged);

    ADD_TEST(untagged, untagged, foo     );
    ADD_TEST(untagged, foo,      untagged);
    ADD_TEST(untagged, foo,      foo     );
    ADD_TEST(foo,      untagged, foo     );
    ADD_TEST(foo,      foo,      untagged);
    ADD_TEST(foo,      foo,      foo     );

    ADD_TEST(untagged, untagged, bar     );
    ADD_TEST(untagged, bar,      untagged);
    ADD_TEST(untagged, bar,      bar     );
    ADD_TEST(foo,      untagged, bar     );
    ADD_TEST(foo,      bar,      untagged);
    ADD_TEST(foo,      bar,      bar     );

    SRunner *runner = srunner_create(suite);
    srunner_run_all(runner, CK_VERBOSE);
    int test_failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (test_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
