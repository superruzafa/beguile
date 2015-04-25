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
#define BEGUILE_FLUSH fflush(stdout);

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
} BeguileHookType;

typedef struct {
    unsigned int feature_total;
    unsigned int feature_failed;
    unsigned int scenario_total;
    unsigned int scenario_failed;
    unsigned int step_total;
    unsigned int step_failed;
    unsigned int signal_total;
} BeguileStats;

typedef void (* beguile_hook)(BeguileHookType type);
beguile_hook beguile_hook_function = NULL;

void beguile_pretty_print(char *string)
{
    char *str = string;
    while (*str != '\0') {
        if (*str == '_' || *str == '(' || *str == ')') {
            while (*str != '\0' && (*str == '_' || *str == '(' || *str == ')')) ++str;
            if (*str != '\0') BEGUILE_PRINT(" ");
        } else {
            BEGUILE_PRINT("%c", *str);
            ++str;
        }
    }
}

#define BEGUILE_SET_HOOK(function)                                             \
    beguile_hook_function = function;

#define BEGUILE_TRIGGER_HOOK(type)                                             \
    if (beguile_hook_function != NULL) beguile_hook_function(type)

#define FeatureRunnerHeader \
    BeguileStats beguile_stats = {0, 0, 0, 0, 0, 0, 0};                        \
    int beguile_intro_is_first = 1;                                            \
    int beguile_feature_has_failed;                                            \
    int beguile_scenario_has_failed;                                           \
    int beguile_written_bytes;                                                 \
    void *beguile_background_section;                                          \
    int beguile_background_enabled;                                            \
    int beguile_background_printed;                                            \
    int beguile_outside_background;                                            \
    jmp_buf beguile_jmp_buf;                                                   \
    pid_t beguile_pid;                                                         \
    int beguile_pipe[2];                                                       \
    BEGUILE_REGISTER_SIGNAL_HANDLER

#define BEGUILE_SUMMARY_COMPONENT(component, total, failed)                    \
    BEGUILE_PRINT(component " (", total);                                      \
    if (failed == 0) {                                                         \
        BEGUILE_PRINT(BEGUILE_STYLE_SUCCESS(BEGUILE_MSG_SUMMARY_ALL_PASSED));  \
    } else {                                                                   \
        BEGUILE_PRINT(BEGUILE_STYLE_FAILURE(BEGUILE_MSG_SUMMARY_FAILED), failed); \
    }                                                                          \
    BEGUILE_PRINT(")\n");

#define FeatureRunnerSummary                                                   \
    BEGUILE_EOL;                                                               \
    BEGUILE_SUMMARY_COMPONENT(BEGUILE_MSG_SUMMARY_FEATURES,                    \
        beguile_stats.feature_total, beguile_stats.feature_failed);            \
    BEGUILE_SUMMARY_COMPONENT(BEGUILE_MSG_SUMMARY_SCENARIOS,                   \
        beguile_stats.scenario_total, beguile_stats.scenario_failed);          \
    BEGUILE_SUMMARY_COMPONENT(BEGUILE_MSG_SUMMARY_STEPS,                       \
        beguile_stats.step_total, beguile_stats.step_failed);

#define FeatureRunnerFooter                                                    \
    FeatureRunnerSummary                                                       \
    return beguile_stats.feature_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;

#define FeatureRunner                                                          \
    int main(int argc, char **argv)                                            \
    {                                                                          \
        FeatureRunnerHeader

#define EndFeatureRunner                                                       \
        FeatureRunnerFooter                                                    \
    }

#define BEGUILE_FEATURE(feature_keyword, feature_name)                         \
    do {                                                                       \
        BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_BEFORE_FEATURE);                     \
        ++beguile_stats.feature_total;                                         \
        beguile_feature_has_failed = 0;                                        \
        beguile_background_printed = 0;                                        \
        beguile_background_section = NULL;                                     \
        BEGUILE_PRINT(BEGUILE_STYLE_FEATURE(feature_keyword ":") " " feature_name); \
        BEGUILE_FLUSH;

#define BEGUILE_ENDFEATURE                                                     \
        if (beguile_feature_has_failed) ++beguile_stats.feature_failed;        \
        BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_AFTER_FEATURE);                      \
    } while(0);

#define BEGUILE_FEATURE_INTRO(intro_keyword, text)                             \
    if (beguile_intro_is_first) {                                              \
        BEGUILE_EOL;                                                           \
        beguile_intro_is_first = 0;                                            \
    }                                                                          \
    BEGUILE_INDENT_1;                                                          \
    BEGUILE_PRINT(intro_keyword " " text "\n");

#define BEGUILE_MESSAGE_PARENT(message)                                        \
    beguile_written_bytes = write(beguile_pipe[1], message, sizeof(char))

#define BEGUILE_BACKGROUND(background_keyword)                                 \
    BEGUILE_REAL_BACKGROUND(background_keyword, __LINE__)

#define BEGUILE_REAL_BACKGROUND(background_keyword, line)                      \
    beguile_background_enabled = 0;                                            \
    BEGUILE_CONCAT(beguile_background_, line):;                                \
    beguile_background_section = && BEGUILE_CONCAT(beguile_background_, line); \
    if (beguile_background_enabled) {                                          \
        BEGUILE_MESSAGE_PARENT("b");                                           \
        if (!beguile_background_printed) {                                     \
            BEGUILE_EOL;                                                       \
            BEGUILE_INDENT_1;                                                  \
            BEGUILE_PRINT(BEGUILE_STYLE_BACKGROUND(background_keyword ":") "\n"); \
        }

#define BEGUILE_ENDBACKGROUND                                                  \
        BEGUILE_MESSAGE_PARENT("B");                                           \
        longjmp(beguile_jmp_buf, 1);                                           \
    }                                                                          \
    beguile_background_enabled = 1;

#define BEGUILE_SCENARIO(scenario_keyword, scenario_name)                      \
    do {                                                                       \
        ++beguile_stats.scenario_total;                                        \
        beguile_scenario_has_failed = 0;                                       \
        if (pipe(beguile_pipe) != 0) {                                         \
            beguile_scenario_has_failed = 1;                                   \
            BEGUILE_EOL;                                                       \
            BEGUILE_INDENT_1;                                                  \
            BEGUILE_PRINT(BEGUILE_STYLE_SCENARIO(scenario_keyword ":") " "     \
                scenario_name " "                                              \
                BEGUILE_STYLE_FAILURE(BEGUILE_MSG_COULD_NOT_PIPE) "\n");       \
                break;                                                         \
        };                                                                     \
        beguile_pid = fork();                                                  \
        if (beguile_pid < 0) {                                                 \
            beguile_scenario_has_failed = 1;                                   \
            BEGUILE_EOL;                                                       \
            BEGUILE_INDENT_1;                                                  \
            BEGUILE_PRINT(BEGUILE_STYLE_SCENARIO(scenario_keyword ":") " "     \
                scenario_name " "                                              \
                BEGUILE_STYLE_FAILURE(BEGUILE_MSG_COULD_NOT_FORK) "\n");       \
        } else if (beguile_pid > 0) {                                          \
            char beguile_message;                                              \
            close(beguile_pipe[1]);                                            \
            while (read(beguile_pipe[0], &beguile_message, sizeof(char))) {    \
                switch (beguile_message) {                                     \
                    case 'T': ++beguile_stats.step_total; break;               \
                    case 'G': ++beguile_stats.signal_total; break;             \
                    case 'g': --beguile_stats.signal_total; break;             \
                    case 'F': ++beguile_stats.step_failed; break;              \
                    case 'f': --beguile_stats.step_failed; break;              \
                    case 'c': BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_BEFORE_SCENARIO); break; \
                    case 'b': BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_BEFORE_BACKGROUND); break; \
                    case 'B': BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_AFTER_BACKGROUND); break; \
                    case 's': BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_BEFORE_STEP); break; \
                    case 'S': BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_AFTER_STEP); break; \
                }                                                              \
            }                                                                  \
            int beguile_status;                                                \
            waitpid(beguile_pid, &beguile_status, 0);                          \
            beguile_background_printed = 1;                                    \
            beguile_scenario_has_failed = beguile_status != EXIT_SUCCESS;      \
        } else {                                                               \
            close(beguile_pipe[0]);                                            \
            if (beguile_background_section != NULL                             \
                && !setjmp(beguile_jmp_buf)) {                                 \
                goto *beguile_background_section;                              \
            }                                                                  \
            BEGUILE_MESSAGE_PARENT("c");    \
            beguile_outside_background = 1;                                    \
            BEGUILE_EOL;                                                       \
            BEGUILE_INDENT_1;                                                  \
            BEGUILE_PRINT(BEGUILE_STYLE_SCENARIO(scenario_keyword ":") " "     \
                scenario_name "\n");

#define BEGUILE_ENDSCENARIO                                                    \
            beguile_outside_background = 0;                                    \
            _exit(beguile_scenario_has_failed ? EXIT_FAILURE : EXIT_SUCCESS);  \
        }                                                                      \
        if (beguile_scenario_has_failed) {                                     \
            ++beguile_stats.scenario_failed;                                   \
            beguile_feature_has_failed = 1;                                    \
        }                                                                      \
        BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_AFTER_SCENARIO);                     \
    } while(0);

#define BEGUILE_STEP(step_keyword, sentence, statement)                        \
    BEGUILE_MESSAGE_PARENT("s");                                               \
    BEGUILE_MESSAGE_PARENT("T");                                               \
    if (!beguile_background_printed || beguile_outside_background) {           \
        BEGUILE_INDENT_2;                                                      \
        BEGUILE_PRINT(BEGUILE_STYLE_STEP(step_keyword) " ");                   \
        beguile_pretty_print(sentence);                                        \
        BEGUILE_FLUSH;                                                         \
    }                                                                          \
    BEGUILE_MESSAGE_PARENT("G");                                               \
    BEGUILE_MESSAGE_PARENT("F");                                               \
    statement;                                                                 \
    BEGUILE_MESSAGE_PARENT("g");                                               \
    BEGUILE_MESSAGE_PARENT("f");                                               \
    if (!beguile_background_printed || beguile_outside_background) BEGUILE_EOL; \
    BEGUILE_MESSAGE_PARENT("S");                                               \

#define BEGUILE_ASSERT_OK BEGUILE_PRINT(" " BEGUILE_STYLE_SUCCESS(BEGUILE_MSG_OK))
#define BEGUILE_ASSERT_FAIL (BEGUILE_PRINT(" " BEGUILE_STYLE_FAILURE(BEGUILE_MSG_FAIL)), \
    beguile_scenario_has_failed = 1,                                           \
    BEGUILE_MESSAGE_PARENT("F"))

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
#define should_be_null(x)                       BEGUILE_ASSERT_SHOULD_NOT_BE_EQUAL_TO(x)
#define should_not_be_null(x)                   BEGUILE_ASSERT_SHOULD_NOT_BE_EQUAL_TO(x)

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

#define BEGUILE_SIGNALS SIGABRT, SIGFPE, SIGSEGV

void beguild_signal_handler(int signal)
{
    BEGUILE_PRINT(" " BEGUILE_STYLE_FAILURE("%s") "\n", strsignal(signal));
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
