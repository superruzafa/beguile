#ifndef __BEGUILE_H__
#define __BEGUILE_H__

#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define BEGUILE_NAME "Beguile"
#define BEGUILE_VERSION "0.1.0"
#define BEGUILE_AUTHOR "Alfonso Ruzafa"
#define BEGUILE_EMAIL  "superruzafa@gmail.com"
#define BEGUILE_BRAND "Beguile, a BDD framework for C"

#define BEGUILE_PRINT(...)  printf(__VA_ARGS__)

#define BEGUILE_EOL BEGUILE_PRINT("\n")

#define BEGUILE_CONCAT(a, b) a ## b

#define BEGUILE_INDENT_1    BEGUILE_PRINT("  ")
#define BEGUILE_INDENT_2    BEGUILE_PRINT("    ")
#define BEGUILE_INDENT_3    BEGUILE_PRINT("      ")

#define BEGUILE_STYLE_RESET                 "\x1b[0m"
#define BEGUILE_STYLE_BOLD                  "\x1b[1m"
#define BEGUILE_STYLE_ITALIC                "\x1b[3m"
#define BEGUILE_STYLE_UNDERLINE             "\x1b[4m"
#define BEGUILE_STYLE_BLINK                 "\x1b[5m"
#define BEGUILE_STYLE_STRIKETHROUGH         "\x1b[9m"
#define BEGUILE_STYLE_FOREGROUND_BLACK      "\x1b[30m"
#define BEGUILE_STYLE_FOREGROUND_RED        "\x1b[31m"
#define BEGUILE_STYLE_FOREGROUND_GREEN      "\x1b[32m"
#define BEGUILE_STYLE_FOREGROUND_YELLOW     "\x1b[33m"
#define BEGUILE_STYLE_FOREGROUND_BLUE       "\x1b[34m"
#define BEGUILE_STYLE_FOREGROUND_MAGENTA    "\x1b[35m"
#define BEGUILE_STYLE_FOREGROUND_CYAN       "\x1b[36m"
#define BEGUILE_STYLE_FOREGROUND_WHITE      "\x1b[37m"
#define BEGUILE_STYLE_FOREGROUND_DEFAULT    "\x1b[38m"
#define BEGUILE_STYLE_BACKGROUND_BLACK      "\x1b[40m"
#define BEGUILE_STYLE_BACKGROUND_RED        "\x1b[41m"
#define BEGUILE_STYLE_BACKGROUND_GREEN      "\x1b[42m"
#define BEGUILE_STYLE_BACKGROUND_YELLOW     "\x1b[43m"
#define BEGUILE_STYLE_BACKGROUND_BLUE       "\x1b[44m"
#define BEGUILE_STYLE_BACKGROUND_MAGENTA    "\x1b[45m"
#define BEGUILE_STYLE_BACKGROUND_CYAN       "\x1b[46m"
#define BEGUILE_STYLE_BACKGROUND_WHITE      "\x1b[47m"
#define BEGUILE_STYLE_BACKGROUND_DEFAULT    "\x1b[49m"

#define BEGUILE_STYLE_KEYWORD(keyword)                  BEGUILE_STYLE_BOLD keyword BEGUILE_STYLE_RESET
#define BEGUILE_STYLE_FEATURE(feature_keyword)          BEGUILE_STYLE_KEYWORD(feature_keyword)
#define BEGUILE_STYLE_BACKGROUND(background_keyword)    BEGUILE_STYLE_KEYWORD(background_keyword)
#define BEGUILE_STYLE_SCENARIO(scenario_keyword)        BEGUILE_STYLE_KEYWORD(scenario_keyword)
#define BEGUILE_STYLE_STEP(step_keyword)                BEGUILE_STYLE_FOREGROUND_YELLOW step_keyword BEGUILE_STYLE_RESET

#define BEGUILE_STYLE_SUCCESS(message)                  BEGUILE_STYLE_FOREGROUND_GREEN message BEGUILE_STYLE_RESET
#define BEGUILE_STYLE_FAILURE(message)                  BEGUILE_STYLE_FOREGROUND_RED message BEGUILE_STYLE_RESET

typedef enum {
    BEGUILE_HOOK_BEFORE_FEATURE,
    BEGUILE_HOOK_AFTER_FEATURE,
    BEGUILE_HOOK_BEFORE_BACKGROUND,
    BEGUILE_HOOK_AFTER_BACKGROUND,
    BEGUILE_HOOK_BEFORE_SCENARIO,
    BEGUILE_HOOK_AFTER_SCENARIO,
    BEGUILE_HOOK_BEFORE_STEP,
    BEGUILE_HOOK_AFTER_STEP,
}
BeguileHookType;

typedef void (* beguile_hook)(BeguileHookType type);
beguile_hook beguile_hook_function = NULL;

#define BEGUILE_SET_HOOK(function)                                             \
    beguile_hook_function = function;

#define FeatureRunnerHeader \
    unsigned int beguile_stats_total_feature = 0;                              \
    unsigned int beguile_stats_failed_feature = 0;                             \
    unsigned int beguile_stats_total_scenario = 0;                             \
    unsigned int beguile_stats_failed_scenario = 0;                            \
    int beguile_feature_has_failed;                                            \
    int beguile_scenario_has_failed;                                           \
    void *beguile_background_section;                                          \
    int beguile_background_enabled;                                            \
    int beguile_background_printed;                                            \
    int beguile_outside_background;                                            \
    jmp_buf beguile_jmp_buf;                                                   \
    pid_t beguile_pid;                                                         \
    BEGUILE_REGISTER_SIGNAL_HANDLER

#define FeatureRunnerFooter                                                    \
    return beguile_stats_failed_feature == 0 ? EXIT_SUCCESS : EXIT_FAILURE;

#define FeatureRunner                                                          \
    int main(int argc, char **argv)                                            \
    {                                                                          \
        FeatureRunnerHeader

#define EndFeatureRunner                                                       \
        FeatureRunnerFooter                                                    \
    }

#define BEGUILE_FEATURE(feature_keyword, feature_name)                         \
    {                                                                          \
        if (beguile_hook_function != NULL)                                     \
            beguile_hook_function(BEGUILE_HOOK_BEFORE_FEATURE);                \
        beguile_feature_has_failed = 0;                                        \
        beguile_background_printed = 0;                                        \
        beguile_background_section = NULL;                                     \
        BEGUILE_PRINT(BEGUILE_STYLE_FEATURE(feature_keyword ":") " " feature_name "\n");

#define BEGUILE_ENDFEATURE                                                     \
        if (beguile_feature_has_failed) ++beguile_stats_failed_feature;        \
        if (beguile_hook_function != NULL)                                     \
            beguile_hook_function(BEGUILE_HOOK_AFTER_FEATURE);                 \
    }

#define BEGUILE_FEATURE_INTRO(intro_keyword, text)                             \
    BEGUILE_INDENT_1;                                                          \
    BEGUILE_PRINT(intro_keyword " " text "\n");

#define BEGUILE_BACKGROUND(background_keyword)                                 \
    BEGUILE_REAL_BACKGROUND(background_keyword, __LINE__)

#define BEGUILE_REAL_BACKGROUND(background_keyword, line)                      \
    beguile_background_enabled = 0;                                            \
    BEGUILE_CONCAT(beguile_background_, line):;                                \
    beguile_background_section = && BEGUILE_CONCAT(beguile_background_, line); \
    if (beguile_background_enabled) {                                          \
        if (beguile_hook_function != NULL)                                     \
            beguile_hook_function(BEGUILE_HOOK_BEFORE_BACKGROUND);             \
        if (!beguile_background_printed) {                                     \
            BEGUILE_INDENT_1;                                                  \
            BEGUILE_PRINT(BEGUILE_STYLE_BACKGROUND(background_keyword ":") "\n"); \
        }

#define BEGUILE_ENDBACKGROUND                                                  \
        if (beguile_hook_function != NULL)                                     \
            beguile_hook_function(BEGUILE_HOOK_AFTER_BACKGROUND);              \
        longjmp(beguile_jmp_buf, 1);                                           \
    }                                                                          \
    beguile_background_enabled = 1;

#define BEGUILE_SCENARIO(scenario_keyword, scenario_name)                      \
    {                                                                          \
        beguile_scenario_has_failed = 0;                                       \
        beguile_pid = fork();                                                  \
        if (beguile_pid < 0) {                                                 \
            beguile_scenario_has_failed = 1;                                   \
            BEGUILE_PRINT(BEGUILE_STYLE_FAILURE("Couldn't fork process") "\n"); \
        } else if (beguile_pid > 0) {                                          \
            int beguile_status;                                                \
            waitpid(beguile_pid, &beguile_status, 0);                          \
            beguile_background_printed = 1;                                    \
            beguile_scenario_has_failed = beguile_status != EXIT_SUCCESS;      \
        } else {                                                               \
            if (beguile_background_section != NULL                             \
                && !setjmp(beguile_jmp_buf)) {                                 \
                goto *beguile_background_section;                              \
            }                                                                  \
            if (beguile_hook_function != NULL)                                 \
                beguile_hook_function(BEGUILE_HOOK_BEFORE_SCENARIO);           \
            beguile_outside_background = 1;                                    \
            BEGUILE_INDENT_1;                                                  \
            BEGUILE_PRINT(BEGUILE_STYLE_SCENARIO(scenario_keyword ":") " " scenario_name "\n");

#define BEGUILE_ENDSCENARIO                                                    \
            beguile_outside_background = 0;                                    \
            _exit(beguile_scenario_has_failed ? EXIT_FAILURE : EXIT_SUCCESS);  \
        }                                                                      \
        if (beguile_scenario_has_failed) {                                     \
            ++beguile_stats_failed_scenario;                                   \
            beguile_feature_has_failed = 1;                                    \
        }                                                                      \
        if (beguile_hook_function != NULL)                                     \
            beguile_hook_function(BEGUILE_HOOK_AFTER_SCENARIO);                \
    }

#define BEGUILE_STEP(step_keyword, sentence, statement)                        \
    if (beguile_hook_function != NULL)                                         \
        beguile_hook_function(BEGUILE_HOOK_BEFORE_STEP);                       \
    if (!beguile_background_printed || beguile_outside_background) {           \
        BEGUILE_INDENT_2;                                                      \
        BEGUILE_PRINT(BEGUILE_STYLE_STEP(step_keyword) " " sentence);          \
    }                                                                          \
    statement;                                                                 \
    if (!beguile_background_printed || beguile_outside_background) BEGUILE_EOL;\
    if (beguile_hook_function != NULL)                                         \
        beguile_hook_function(BEGUILE_HOOK_AFTER_STEP);                        \

#define BEGUILE_ASSERT_OK BEGUILE_PRINT(" " BEGUILE_STYLE_SUCCESS(BEGUILE_OK))
#define BEGUILE_ASSERT_FAIL (BEGUILE_PRINT(" " BEGUILE_STYLE_FAILURE(BEGUILE_FAIL)), beguile_scenario_has_failed = 1)

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

#define As_a(role)                              BEGUILE_FEATURE_INTRO("As a", #role)
#define As_an(role)                             BEGUILE_FEATURE_INTRO("As an", #role)
#define I_want_to(feature)                      BEGUILE_FEATURE_INTRO("I want to", #feature)
#define I_want(feature)                         BEGUILE_FEATURE_INTRO("I want", #feature)
#define In_order_to(benefit)                    BEGUILE_FEATURE_INTRO("In order to", #benefit)
#define So_that(benefit)                        BEGUILE_FEATURE_INTRO("So that", #benefit)

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
#define should_be_null(x)                       BEGUILE_ASSERT_SHOULD_NOT_BE_EQUAL_TO(x)
#define should_not_be_null(x)                   BEGUILE_ASSERT_SHOULD_NOT_BE_EQUAL_TO(x)

#define BEGUILE_OK                              "OK"
#define BEGUILE_FAIL                            "FAIL"

#endif

#define BEGUILE_SIGNALS SIGABRT, SIGFPE, SIGSEGV

void beguild_signal_handler(int signal)
{
    BEGUILE_PRINT(" " BEGUILE_STYLE_FAILURE(BEGUILE_FAIL " %s") "\n", strsignal(signal));
    _exit(EXIT_FAILURE);
}

#define BEGUILE_REGISTER_SIGNAL_HANDLER                                                                               \
    do {                                                                                                              \
        struct sigaction beguile_sigaction;                                                                           \
        sigemptyset(&beguile_sigaction.sa_mask);                                                                      \
        beguile_sigaction.sa_handler = beguild_signal_handler;                                                        \
        int beguild_signals[] = { BEGUILE_SIGNALS, 0 }, beguile_i;                                                    \
        for (beguile_i = 0; beguild_signals[beguile_i] != 0; ++beguile_i) {                                           \
            if (sigaction(beguild_signals[beguile_i], &beguile_sigaction, NULL) < 0) {                                \
                BEGUILE_PRINT(BEGUILE_STYLE_FAILURE("Cannot set signal error handler for signal %d") "\n", beguild_signals[beguile_i]); \
                exit(EXIT_FAILURE);                                                                                   \
            }                                                                                                         \
        }                                                                                                             \
    }                                                                                                                 \
    while (0);

#endif // __BEGUILE_H__
