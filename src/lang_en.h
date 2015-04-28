#if !defined BEGUILE_OPTION_LANG || BEGUILE_OPTION_LANG == en

#define Feature(feature_name)                   BEGUILE_FEATURE("Feature", feature_name)
#define EndFeature                              BEGUILE_ENDFEATURE

#define As_a(role)                              BEGUILE_FEATURE_INTRO("As a", role)
#define As_an(role)                             BEGUILE_FEATURE_INTRO("As an", role)
#define I_want_to(feature)                      BEGUILE_FEATURE_INTRO("I want to", feature)
#define I_want(feature)                         BEGUILE_FEATURE_INTRO("I want", feature)
#define In_order_to(benefit)                    BEGUILE_FEATURE_INTRO("In order to", benefit)
#define So_that(benefit)                        BEGUILE_FEATURE_INTRO("So that", benefit)

#define Background                              BEGUILE_BACKGROUND("Background")
#define EndBackground                           BEGUILE_ENDBACKGROUND

#define Scenario(scenario_name)                 BEGUILE_SCENARIO("Scenario", scenario_name)
#define EndScenario                             BEGUILE_ENDSCENARIO

#define Given(...)                              BEGUILE_STEP("Given", #__VA_ARGS__, __VA_ARGS__)
#define When(...)                               BEGUILE_STEP("When",  #__VA_ARGS__, __VA_ARGS__)
#define Then(...)                               BEGUILE_STEP("Then",  #__VA_ARGS__, __VA_ARGS__)
#define And(...)                                BEGUILE_STEP("And",   #__VA_ARGS__, __VA_ARGS__)
#define But(...)                                BEGUILE_STEP("But",   #__VA_ARGS__, __VA_ARGS__)

#define should_be_equal_to(x)                   BEGUILE_ASSERT_SHOULD_BE_EQUAL_TO(x)
#define should_be(x)                            BEGUILE_ASSERT_SHOULD_BE_EQUAL_TO(x)
#define should_not_be_equal_to(x)               BEGUILE_ASSERT_SHOULD_NOT_BE_EQUAL_TO(x)
#define should_not_be(x)                        BEGUILE_ASSERT_SHOULD_NOT_BE_EQUAL_TO(x)
#define should_be_less_than(x)                  BEGUILE_ASSERT_SHOULD_BE_LESS_THAN(x)
#define should_be_less_or_equal_than(x)         BEGUILE_ASSERT_SHOULD_BE_LESS_OR_EQUAL_THAN(x)
#define should_be_greater_than(x)               BEGUILE_ASSERT_SHOULD_BE_GREATER_THAN(x)
#define should_be_greater_or_equal_than(x)      BEGUILE_ASSERT_SHOULD_BE_GREATER_OR_EQUAL_THAN(x)
#define should_be_null                          BEGUILE_ASSERT_SHOULD_BE_NULL
#define should_not_be_null                      BEGUILE_ASSERT_SHOULD_NOT_BE_NULL

#define BEGUILE_MSG_OK                          "OK"
#define BEGUILE_MSG_FAIL                        "FAIL"

#define BEGUILE_MSG_SUMMARY_FEATURES            "%d features"
#define BEGUILE_MSG_SUMMARY_SCENARIOS           "%d scenarios"
#define BEGUILE_MSG_SUMMARY_STEPS               "%d steps"
#define BEGUILE_MSG_SUMMARY_ALL_PASSED          "all passed"
#define BEGUILE_MSG_SUMMARY_FAILED              "%d failed"

#define BEGUILE_MSG_COULD_NOT_PIPE              "Couldn't create scenario pipe"
#define BEGUILE_MSG_COULD_NOT_FORK              "Couldn't fork scenario subprocess"

#endif

