#define FeatureRunner                                                          \
    int main(int argc, char **argv)                                            \
    {

#define EndFeatureRunner                                                       \
        return EXIT_SUCCESS;                                                   \
    }

#define BEGUILE_FEATURE(feature_keyword, feature_name)                         \
    BEGUILE_PRINT(feature_keyword ": " feature_name "\n");

#define BEGUILE_ENDFEATURE

#define BEGUILE_SCENARIO(scenario_keyword, scenario_name)                      \
    {                                                                          \
        BEGUILE_INDENT_1;                                                      \
        BEGUILE_PRINT(scenario_keyword ": " scenario_name "\n");
#define BEGUILE_ENDSCENARIO                                                    \
    }

#define BEGUILE_STEP(step_keyword, sentence, statement)                        \
    BEGUILE_INDENT_2;                                                          \
    BEGUILE_PRINT(step_keyword " " sentence);                                  \
    statement;                                                                 \
    BEGUILE_EOL;

#define BEGUILE_ASSERT_OK BEGUILE_PRINT(" " BEGUILE_OK)
#define BEGUILE_ASSERT_FAIL BEGUILE_PRINT(" " BEGUILE_OK)

#define BEGUILE_ASSERT_SHOULD_BE_EQUAL_TO(x)              == x    ? BEGUILE_ASSERT_OK : BEGUILE_ASSERT_FAIL
#define BEGUILE_ASSERT_SHOULD_NOT_BE_EQUAL_TO(x)          != x    ? BEGUILE_ASSERT_OK : BEGUILE_ASSERT_FAIL
#define BEGUILE_ASSERT_SHOULD_BE_LESS_THAN(x)              < x    ? BEGUILE_ASSERT_OK : BEGUILE_ASSERT_FAIL
#define BEGUILE_ASSERT_SHOULD_BE_LESS_OR_EQUAL_THAN(x)    <= x    ? BEGUILE_ASSERT_OK : BEGUILE_ASSERT_FAIL
#define BEGUILE_ASSERT_SHOULD_BE_GREATER_OR_EQUAL_THAN(x) >= x    ? BEGUILE_ASSERT_OK : BEGUILE_ASSERT_FAIL
#define BEGUILE_ASSERT_SHOULD_BE_GREATER_THAN(x)           > x    ? BEGUILE_ASSERT_OK : BEGUILE_ASSERT_FAIL
#define BEGUILE_ASSERT_SHOULD_BE_NULL                     == NULL ? BEGUILE_ASSERT_OK : BEGUILE_ASSERT_FAIL
#define BEGUILE_ASSERT_SHOULD_NOT_BE_NULL                 != NULL ? BEGUILE_ASSERT_OK : BEGUILE_ASSERT_FAIL

