#if !defined BEGUILE_OPTION_LANG || BEGUILE_OPTION_LANG == en

#define Feature(feature_name)                   BEGUILE_FEATURE("Feature", feature_name)
#define EndFeature                              BEGUILE_ENDFEATURE
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
#define should_be_null(x)                       BEGUILE_ASSERT_SHOULD_NOT_BE_EQUAL_TO(x)
#define should_not_be_null(x)                   BEGUILE_ASSERT_SHOULD_NOT_BE_EQUAL_TO(x)

#define BEGUILE_OK                              "OK"
#define BEGUILE_FAIL                            "FAIL"

#endif

