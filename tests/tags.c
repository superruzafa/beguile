#include <check.h>
#include <beguile.h>

#define CREATE_TEST(user_tags, feature_tags, scenario_tags, expected_feature_execs, expected_scenario_execs) \
    START_TEST(user_##user_tags##__feature_##feature_tags##__scenario_##scenario_tags) \
    {                                                                          \
        beguile_set_tags(user_tags);                                           \
        FeatureRunnerHeader                                                    \
                                                                               \
        tags(feature_tags)                                                     \
        Feature ("")                                                           \
            tags(scenario_tags)                                                \
            /* tagged scenario inside a tagged feature */                      \
            Scenario ("")                                                      \
            EndScenario                                                        \
            /* untagged scenario inside a tagged feature */                    \
            Scenario ("")                                                      \
            EndScenario                                                        \
        EndFeature                                                             \
                                                                               \
        /* this feature is not tagged */                                       \
        Feature ("")                                                           \
            tags(scenario_tags)                                                \
            /* tagged scenario inside an untagged feature */                   \
            Scenario ("")                                                      \
            EndScenario                                                        \
            /* untagged scenario inside an untagged feature */                 \
            Scenario ("")                                                      \
            EndScenario                                                        \
        EndFeature                                                             \
                                                                               \
        ck_assert_int_eq(beguile_stats.feature_total, expected_feature_execs); \
        ck_assert_int_eq(beguile_stats.scenario_total, expected_scenario_execs); \
    }                                                                          \
    END_TEST

#define untagged NULL
#define foo      "foo"
#define foobar   "foo", "bar"
#define bar      "bar"

CREATE_TEST(untagged, untagged, untagged, 2, 4)
CREATE_TEST(foo,      untagged, untagged, 0, 0)

CREATE_TEST(untagged, untagged, foo,      2, 4)
CREATE_TEST(untagged, foo,      untagged, 2, 4)
CREATE_TEST(untagged, foo,      foo,      2, 4)
CREATE_TEST(foo,      untagged, foo,      0, 0)
CREATE_TEST(foo,      foo,      untagged, 1, 0)
CREATE_TEST(foo,      foo,      foo,      1, 1)

CREATE_TEST(untagged, untagged, foobar,   2, 4)
CREATE_TEST(untagged, foobar,   untagged, 2, 4)
CREATE_TEST(untagged, foobar,   foobar,   2, 4)
CREATE_TEST(foo,      untagged, foobar,   0, 0)
CREATE_TEST(foo,      foobar,   untagged, 1, 0)
CREATE_TEST(foo,      foobar,   foobar,   1, 1)

CREATE_TEST(untagged, untagged, bar,      2, 4)
CREATE_TEST(untagged, bar,      untagged, 2, 4)
CREATE_TEST(untagged, bar,      bar,      2, 4)
CREATE_TEST(foo,      untagged, bar,      0, 0)
CREATE_TEST(foo,      bar,      untagged, 0, 0)
CREATE_TEST(foo,      bar,      bar,      0, 0)

int main(int argc, char **argv)
{
    beguile_disable_output();

    Suite *suite = suite_create("Tags");
    TCase *tcase = tcase_create("Tags");
    suite_add_tcase(suite, tcase);

#define ADD_TEST(user_tags, feature_tags, scenario_tags) \
    tcase_add_test(tcase, user_##user_tags##__feature_##feature_tags##__scenario_##scenario_tags)

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
