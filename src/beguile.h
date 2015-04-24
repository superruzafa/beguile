#ifndef __BEGUILE_H__
#define __BEGUILE_H__

#include <stdlib.h>
#include <stdio.h>
#define BEGUILE_NAME "Beguile"
#define BEGUILE_VERSION "0.1.0"
#define BEGUILE_AUTHOR "Alfonso Ruzafa"
#define BEGUILE_EMAIL  "superruzafa@gmail.com"
#define BEGUILE_BRAND "Beguile, a BDD framework for C"

#define BEGUILE_PRINT(...)  printf(__VA_ARGS__)

#define BEGUILE_EOL BEGUILE_PRINT("\n")

#define BEGUILE_INDENT_1    BEGUILE_PRINT("    ")
#define BEGUILE_INDENT_2    BEGUILE_PRINT("        ")
#define BEGUILE_INDENT_3    BEGUILE_PRINT("            ")

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

#endif // __BEGUILE_H__
