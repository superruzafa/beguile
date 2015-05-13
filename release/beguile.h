/* Beguile 0.2.1-dev, a BDD framework for C
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Alfonso Ruzafa
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

typedef void (* BeguileHook)(BeguileHookType type, int is_child);

typedef struct {
    int             output_enabled;
    int             fork_enabled;
    int             pretty_print_enabled;
    BeguileHook     hook;
    char          **user_tags;
} BeguileGlobalVars;

BeguileGlobalVars beguile_global_vars = {1, 1, 0, NULL, NULL};

#define BEGUILE_NAME "Beguile"
#define BEGUILE_VERSION "0.2.1-dev"
#define BEGUILE_AUTHOR "Alfonso Ruzafa"
#define BEGUILE_EMAIL  "superruzafa@gmail.com"
#define BEGUILE_BRAND "Beguile, a BDD framework for C"
#define BEGUILE_URL "https://github.com/superruzafa/beguile.git"

#define BEGUILE_PRINT(...) (beguile_global_vars.output_enabled ? printf(__VA_ARGS__) : 0)
#define BEGUILE_FLUSH() (beguile_global_vars.output_enabled ? fflush(stdout) : 0)

#define beguile_enable_pretty_print() beguile_global_vars.pretty_print_enabled = 1
#define beguile_disable_pretty_print() beguile_global_vars.pretty_print_enabled = 0

void beguile_pretty_print(char *string)
{
    char *str = string;
    if (beguile_global_vars.pretty_print_enabled) {
        while (*str != '\0') {
            if (*str == ' ' || *str == '_' || *str == '(' || *str == ')') {
                while (*str != '\0' && (*str == ' ' || *str == '_' || *str == '(' || *str == ')')) ++str;
                if (*str != '\0') BEGUILE_PRINT(" ");
            } else {
                BEGUILE_PRINT("%c", *str);
                ++str;
            }
        }
    } else {
        BEGUILE_PRINT("%s", string);
    }
}

#define beguile_enable_output() beguile_global_vars.output_enabled = 1
#define beguile_disable_output() beguile_global_vars.output_enabled = 0

#define BEGUILE_EOL() BEGUILE_PRINT("\n")

#define BEGUILE_CONCAT(a, b) a ## b

#define BEGUILE_INDENT_1()  BEGUILE_PRINT("  ")
#define BEGUILE_INDENT_2()  BEGUILE_PRINT("    ")
#define BEGUILE_INDENT_3()  BEGUILE_PRINT("      ")

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

#define BEGUILE_SIGNALS SIGABRT, SIGFPE, SIGSEGV

void beguile_signal_handler(int signal)
{
    BEGUILE_PRINT(" " BEGUILE_STYLE_FAILURE("%s") "\n", strsignal(signal));
    _exit(EXIT_FAILURE);
}

#define BEGUILE_REGISTER_SIGNAL_HANDLER()                                                                               \
    do {                                                                                                              \
        struct sigaction beguile_sigaction;                                                                           \
        sigemptyset(&beguile_sigaction.sa_mask);                                                                      \
        beguile_sigaction.sa_handler = beguile_signal_handler;                                                        \
        int beguile_signals[] = { BEGUILE_SIGNALS, 0 }, beguile_i;                                                    \
        for (beguile_i = 0; beguile_signals[beguile_i] != 0; ++beguile_i) {                                           \
            if (sigaction(beguile_signals[beguile_i], &beguile_sigaction, NULL) < 0) {                                \
                BEGUILE_PRINT(BEGUILE_STYLE_FAILURE("Cannot set signal error handler for signal %d") "\n", beguile_signals[beguile_i]); \
                exit(EXIT_FAILURE);                                                                                   \
            }                                                                                                         \
        }                                                                                                             \
    } while(0)

typedef struct {
    int need_eol;
    int feature_has_failed;
    int scenario_has_failed;
    int background_enabled;
    int background_printed;
    int outside_background;
} BeguileInternalFlags;

typedef struct {
    int            written_bytes;
    void          *background_section;
    jmp_buf        jmp_buf;
    pid_t          pid;
    int            pipe[2];
    int            tags_index;
    char         **tags[2];
} BeguileInternalVars;

#define beguile_enable_hook(function) beguile_global_vars.hook = function
#define beguile_disable_hook() beguile_global_vars.hook = NULL

#define beguile_enable_fork() beguile_global_vars.fork_enabled = 1
#define beguile_disable_fork() beguile_global_vars.fork_enabled = 0

#define BEGUILE_TRIGGER_HOOK(type, is_child)                                   \
    if (beguile_global_vars.hook != NULL) beguile_global_vars.hook(type, is_child)

#define FeatureRunnerHeader \
    BeguileStats beguile_stats = {0, 0, 0, 0, 0, 0, 0};                        \
    volatile BeguileInternalFlags beguile_internal_flags = {0, 0, 0, 0, 0, 0}; \
    BeguileInternalVars beguile_internal_vars;                                 \
    beguile_internal_vars.tags_index = 0;                                      \
    beguile_internal_vars.tags[0] = NULL;                                      \
    beguile_internal_vars.tags[1] = NULL;                                      \
    BEGUILE_REGISTER_SIGNAL_HANDLER();

#define BEGUILE_SUMMARY_COMPONENT(component, total, failed)                    \
    BEGUILE_PRINT(component " (", total);                                      \
    if (failed == 0) {                                                         \
        BEGUILE_PRINT(BEGUILE_STYLE_SUCCESS(BEGUILE_MSG_SUMMARY_ALL_PASSED));  \
    } else {                                                                   \
        BEGUILE_PRINT(BEGUILE_STYLE_FAILURE(BEGUILE_MSG_SUMMARY_FAILED), failed); \
    }                                                                          \
    BEGUILE_PRINT(")\n");

#define FeatureRunnerSummary                                                   \
    BEGUILE_EOL();                                                             \
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
        FeatureRunnerHeader                                                    \
        beguile_parse_options(argc, argv);

#define EndFeatureRunner                                                       \
        FeatureRunnerFooter                                                    \
    }

#define BEGUILE_FEATURE(feature_keyword, feature_name)                         \
    do {                                                                       \
        if (beguile_internal_flags.need_eol) {                             \
            BEGUILE_EOL();                                                 \
            beguile_internal_flags.need_eol = 0;                           \
        }                                                                  \
        beguile_internal_flags.need_eol = 1;                               \
        BEGUILE_PRINT(BEGUILE_STYLE_FEATURE(feature_keyword ":") " " feature_name); \
        BEGUILE_FLUSH();                                                   \
        BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_BEFORE_FEATURE, 0);                  \
        ++beguile_stats.feature_total;                                         \
        beguile_internal_vars.tags_index = 1;                                  \
        beguile_internal_flags.feature_has_failed = 0;                         \
        beguile_internal_flags.background_printed = 0;                         \
        beguile_internal_vars.background_section = NULL;                       \

#define BEGUILE_ENDFEATURE                                                     \
        if (beguile_internal_flags.feature_has_failed) ++beguile_stats.feature_failed;  \
        BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_AFTER_FEATURE, 0);                   \
        beguile_internal_vars.tags_index = 0;                                  \
        beguile_internal_vars.tags[0] = NULL;                                  \
    } while (0);

#define BEGUILE_FEATURE_INTRO(intro_keyword, text)                             \
    if (beguile_internal_flags.need_eol) {                                     \
        BEGUILE_EOL();                                                         \
        beguile_internal_flags.need_eol = 0;                                   \
    }                                                                          \
    BEGUILE_INDENT_1();                                                        \
    BEGUILE_PRINT(intro_keyword " " text "\n");

#define BEGUILE_MESSAGE_PARENT(message)                                        \
    (beguile_global_vars.fork_enabled ? beguile_internal_vars.written_bytes = write(beguile_internal_vars.pipe[1], message, sizeof(char)) : 0)

#define BEGUILE_BACKGROUND(background_keyword)                                 \
    BEGUILE_REAL_BACKGROUND(background_keyword, __LINE__)

#define BEGUILE_REAL_BACKGROUND(background_keyword, line)                      \
    beguile_internal_flags.background_enabled = 0;                             \
    BEGUILE_CONCAT(beguile_background_, line):;                                \
    beguile_internal_vars.background_section = && BEGUILE_CONCAT(beguile_background_, line); \
    if (beguile_internal_flags.background_enabled) {                           \
        BEGUILE_MESSAGE_PARENT("b");                                           \
        BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_BEFORE_BACKGROUND, beguile_global_vars.fork_enabled); \
        if (!beguile_internal_flags.background_printed) {                      \
            BEGUILE_EOL();                                                     \
            BEGUILE_INDENT_1();                                                \
            BEGUILE_PRINT(BEGUILE_STYLE_BACKGROUND(background_keyword ":") "\n"); \
        }

#define BEGUILE_ENDBACKGROUND                                                  \
        BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_AFTER_BACKGROUND, beguile_global_vars.fork_enabled); \
        BEGUILE_MESSAGE_PARENT("B");                                           \
        longjmp(beguile_internal_vars.jmp_buf, 1);                             \
    }                                                                          \
    beguile_internal_flags.background_enabled = 1;

#define BEGUILE_SCENARIO(scenario_keyword, scenario_name)                      \
    do {                                                                       \
        BEGUILE_CHECK_SCENARIO_TAGS();                                         \
        ++beguile_stats.scenario_total;                                        \
        beguile_internal_flags.scenario_has_failed = 0;                        \
        if (beguile_global_vars.fork_enabled) {                                \
            if (pipe(beguile_internal_vars.pipe) != 0) {                       \
                beguile_internal_flags.scenario_has_failed = 1;                \
                BEGUILE_EOL();                                                 \
                BEGUILE_INDENT_1();                                            \
                BEGUILE_PRINT(BEGUILE_STYLE_SCENARIO(scenario_keyword ":") " " \
                    scenario_name " "                                          \
                    BEGUILE_STYLE_FAILURE(BEGUILE_MSG_COULD_NOT_PIPE) "\n");   \
                    break;                                                     \
            }                                                                  \
            beguile_internal_vars.pid = fork();                                \
            if (beguile_internal_vars.pid < 0) {                               \
                close(beguile_internal_vars.pipe[0]);                          \
                close(beguile_internal_vars.pipe[1]);                          \
                beguile_internal_flags.scenario_has_failed = 1;                \
                BEGUILE_EOL();                                                 \
                BEGUILE_INDENT_1();                                            \
                BEGUILE_PRINT(BEGUILE_STYLE_SCENARIO(scenario_keyword ":") " " \
                    scenario_name " "                                          \
                    BEGUILE_STYLE_FAILURE(BEGUILE_MSG_COULD_NOT_FORK) "\n");   \
                    break;                                                     \
            } else if (beguile_internal_vars.pid > 0) {                        \
                char beguile_message;                                          \
                close(beguile_internal_vars.pipe[1]);                          \
                while (read(beguile_internal_vars.pipe[0], &beguile_message, sizeof(char))) { \
                    switch (beguile_message) {                                 \
                        case 'T':                                              \
                            ++beguile_stats.step_total;                        \
                            beguile_internal_flags.need_eol = 1;               \
                            break;                                             \
                        case 'G': ++beguile_stats.signal_total; break;         \
                        case 'g': --beguile_stats.signal_total; break;         \
                        case 'F': ++beguile_stats.step_failed; break;          \
                        case 'f': --beguile_stats.step_failed; break;          \
                        case 'c': BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_BEFORE_SCENARIO, 0); break; \
                        case 'b': BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_BEFORE_BACKGROUND, 0); break; \
                        case 'B': BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_AFTER_BACKGROUND, 0); break; \
                        case 's': BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_BEFORE_STEP, 0); break; \
                        case 'S': BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_AFTER_STEP, 0); break; \
                    }                                                          \
                }                                                              \
                int beguile_status;                                            \
                waitpid(beguile_internal_vars.pid, &beguile_status, 0);        \
                beguile_internal_flags.background_printed = 1;                 \
                beguile_internal_flags.scenario_has_failed = beguile_status != EXIT_SUCCESS; \
            }                                                                  \
        }                                                                      \
        if (!beguile_global_vars.fork_enabled || beguile_internal_vars.pid == 0) { \
            if (beguile_global_vars.fork_enabled) close(beguile_internal_vars.pipe[0]); \
            if (beguile_internal_vars.background_section != NULL && !setjmp(beguile_internal_vars.jmp_buf)) \
                goto *beguile_internal_vars.background_section;                \
            BEGUILE_MESSAGE_PARENT("c");                                       \
            BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_BEFORE_SCENARIO, beguile_global_vars.fork_enabled); \
            beguile_internal_flags.outside_background = 1;                     \
            BEGUILE_EOL();                                                     \
            BEGUILE_INDENT_1();                                                \
            BEGUILE_PRINT(BEGUILE_STYLE_SCENARIO(scenario_keyword ":") " "     \
                scenario_name "\n");

#define BEGUILE_ENDSCENARIO                                                    \
            beguile_internal_flags.outside_background = 0;                     \
            if (beguile_global_vars.fork_enabled) {                            \
                BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_AFTER_SCENARIO, 1);          \
                _exit(beguile_internal_flags.scenario_has_failed ? EXIT_FAILURE : EXIT_SUCCESS); \
            }                                                                  \
        }                                                                      \
        if (beguile_internal_flags.scenario_has_failed) {                      \
            ++beguile_stats.scenario_failed;                                   \
            beguile_internal_flags.feature_has_failed = 1;                     \
        }                                                                      \
        BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_AFTER_SCENARIO, 0);                  \
    } while(0);                                                                \

#define BEGUILE_STEP(step_keyword, sentence, statement)                        \
    BEGUILE_MESSAGE_PARENT("s");                                               \
    BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_BEFORE_STEP, beguile_global_vars.fork_enabled);                         \
    BEGUILE_MESSAGE_PARENT("T");                                               \
    if (!beguile_internal_flags.background_printed || beguile_internal_flags.outside_background) { \
        BEGUILE_INDENT_2();                                                    \
        BEGUILE_PRINT(BEGUILE_STYLE_STEP(step_keyword) " ");                   \
        beguile_pretty_print(sentence);                                        \
        BEGUILE_FLUSH();                                                       \
    }                                                                          \
    BEGUILE_MESSAGE_PARENT("G");                                               \
    BEGUILE_MESSAGE_PARENT("F");                                               \
    statement;                                                                 \
    BEGUILE_MESSAGE_PARENT("g");                                               \
    BEGUILE_MESSAGE_PARENT("f");                                               \
    if (!beguile_internal_flags.background_printed || beguile_internal_flags.outside_background) BEGUILE_EOL(); \
    BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_AFTER_STEP, beguile_global_vars.fork_enabled); \
    BEGUILE_MESSAGE_PARENT("S");

#define BEGUILE_ASSERT_OK() BEGUILE_PRINT(" " BEGUILE_STYLE_SUCCESS(BEGUILE_MSG_OK))
#define BEGUILE_ASSERT_FAIL() (BEGUILE_PRINT(" " BEGUILE_STYLE_FAILURE(BEGUILE_MSG_FAIL)), \
    beguile_internal_flags.scenario_has_failed = 1,                            \
    BEGUILE_MESSAGE_PARENT("F"))

#define BEGUILE_ASSERT_SHOULD_BE_EQUAL_TO(x)              == x    ? BEGUILE_ASSERT_OK() : BEGUILE_ASSERT_FAIL()
#define BEGUILE_ASSERT_SHOULD_NOT_BE_EQUAL_TO(x)          != x    ? BEGUILE_ASSERT_OK() : BEGUILE_ASSERT_FAIL()
#define BEGUILE_ASSERT_SHOULD_BE_LESS_THAN(x)              < x    ? BEGUILE_ASSERT_OK() : BEGUILE_ASSERT_FAIL()
#define BEGUILE_ASSERT_SHOULD_BE_LESS_OR_EQUAL_THAN(x)    <= x    ? BEGUILE_ASSERT_OK() : BEGUILE_ASSERT_FAIL()
#define BEGUILE_ASSERT_SHOULD_BE_GREATER_OR_EQUAL_THAN(x) >= x    ? BEGUILE_ASSERT_OK() : BEGUILE_ASSERT_FAIL()
#define BEGUILE_ASSERT_SHOULD_BE_GREATER_THAN(x)           > x    ? BEGUILE_ASSERT_OK() : BEGUILE_ASSERT_FAIL()
#define BEGUILE_ASSERT_SHOULD_BE_NULL                     == NULL ? BEGUILE_ASSERT_OK() : BEGUILE_ASSERT_FAIL()
#define BEGUILE_ASSERT_SHOULD_NOT_BE_NULL                 != NULL ? BEGUILE_ASSERT_OK() : BEGUILE_ASSERT_FAIL()

#include <getopt.h>

#define BEGUILE_HELP(argc, argv)                                               \
    printf("%s - %s %s\n", argv[0], BEGUILE_NAME, BEGUILE_VERSION);            \
    printf("Usage: %s [OPTION]... [TAGS]...\n", argv[0]);                      \
    puts("  -h, --help                 show this help");                       \
    puts("  -s, --silent               do not print features");                \
    puts("  -f, --no-fork              do not fork process");                  \
    puts("  -p, --pretty-print         pretty-print the output");

#define BEGUILE_PARSE_TAGS(argc, argv)                                         \
    char beguile_tags_buffer[2048];                                            \
    char *beguile_tags_argv[16];                                               \
    char *beguile_tags_ptr = beguile_tags_buffer;                              \
    int beguile_i = 0;                                                         \
    memset(beguile_tags_buffer, 0, sizeof(char) * 2048);                       \
    memset(beguile_tags_argv, 0, sizeof(char) * 16);                           \
    while (optind < argc && beguile_i < 16) {                                  \
        strcpy(beguile_tags_ptr, argv[optind]);                                \
        beguile_tags_argv[beguile_i] = beguile_tags_ptr;                       \
        beguile_tags_ptr += strlen(argv[optind]) + 1;                          \
        ++beguile_i;                                                           \
        ++optind;                                                              \
        beguile_global_vars.user_tags = beguile_tags_argv;                     \
    }

#define beguile_parse_options(argc, argv)                                      \
    do {                                                                       \
        int beguile_option;                                                    \
        int beguile_option_index = 0;                                          \
        struct option beguile_options[] = {                                    \
            {"help",         no_argument, 0, 'h'},                             \
            {"silent",       no_argument, 0, 's'},                             \
            {"no-fork",      no_argument, 0, 'f'},                             \
            {"pretty-print", no_argument, 0, 'p'},                             \
            {0,              0,           0, 0}                                \
        };                                                                     \
        beguile_option = getopt_long(argc, argv, "hsfp", beguile_options, &beguile_option_index); \
        while (beguile_option != -1) {                                         \
            switch (beguile_option) {                                          \
                case 's': beguile_global_vars.output_enabled = 0; break;       \
                case 'f': beguile_global_vars.fork_enabled = 0; break;         \
                case 'p': beguile_global_vars.pretty_print_enabled = 1; break; \
                case 'h': BEGUILE_HELP(argc, argv); exit(-1); break;           \
            }                                                                  \
            beguile_option = getopt_long(argc, argv, "hsfp", beguile_options, &beguile_option_index); \
        }                                                                      \
        BEGUILE_PARSE_TAGS(argc, argv);                                        \
    } while (0);

#define BEGUILE_REAL_TAG(line, ...)                                           \
    do {                                                                       \
        static char * BEGUILE_CONCAT(beguile_tags_, line) [] = {__VA_ARGS__, NULL}; \
        beguile_internal_vars.tags[beguile_internal_vars.tags_index] = BEGUILE_CONCAT(beguile_tags_, line); \
    } while (0);

#define tag(...) BEGUILE_REAL_TAG(__LINE__, __VA_ARGS__)

#define BEGUILE_REAL_ENABLE_TAG(line, ...)                                       \
    do {                                                                       \
        static char * BEGUILE_CONCAT(beguile_set_tags_, line) [] = {__VA_ARGS__, NULL}; \
        beguile_global_vars.user_tags = BEGUILE_CONCAT(beguile_set_tags_, line); \
    } while (0)

#define beguile_enable_tag(...) BEGUILE_REAL_ENABLE_TAG(__LINE__, __VA_ARGS__)
#define beguile_disable_tag() beguile_global_vars.user_tags = NULL

int beguile_tags_match_user_tags(char **tags)
{
    char **tag;
    char **user_tag = beguile_global_vars.user_tags;
    int user_tag_found;

    while (user_tag != NULL && *user_tag != NULL) {
        user_tag_found = 0;
        for (tag = tags; tag != NULL && *tag != NULL; ++tag) {
            if (strcmp(*user_tag, *tag) == 0) {
                user_tag_found = 1;
                break;
            }
        }
        if (!user_tag_found) return 0;
        ++user_tag;
    }
    return 1;
}

#define BEGUILE_CHECK_SCENARIO_TAGS()                                          \
    if (beguile_global_vars.user_tags != NULL) {                               \
        if (beguile_internal_vars.tags[1] != NULL) {                           \
            if (!beguile_tags_match_user_tags(beguile_internal_vars.tags[1])) { \
                beguile_internal_vars.tags[1] = NULL;                          \
                break;                                                         \
            } else {                                                           \
                beguile_internal_vars.tags[1] = NULL;                          \
            }                                                                  \
        } else if (beguile_internal_vars.tags[0] != NULL) {                    \
            if (!beguile_tags_match_user_tags(beguile_internal_vars.tags[0])) { \
                break;                                                         \
            }                                                                  \
        } else {                                                               \
            break;                                                             \
        }                                                                      \
    }

#ifndef BEGUILE_LANG_ES

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

#ifdef BEGUILE_LANG_ES

#define Caracteristica(feature_name)            BEGUILE_FEATURE("Característica", feature_name)
#define FinCaracteristica                       BEGUILE_ENDFEATURE

#define Como(role)                              BEGUILE_FEATURE_INTRO("Como", role)
#define Quiero(feature)                         BEGUILE_FEATURE_INTRO("Quiero", feature)
#define Para_poder(benefit)                     BEGUILE_FEATURE_INTRO("Para poder", benefit)

#define Antecedentes                            BEGUILE_BACKGROUND("Antecedentes")
#define FinAntecedentes                         BEGUILE_ENDBACKGROUND

#define Escenario(scenario_name)                BEGUILE_SCENARIO("Escenario", scenario_name)
#define FinEscenario                            BEGUILE_ENDSCENARIO

#define Dado(...)                               BEGUILE_STEP("Dado",     #__VA_ARGS__, __VA_ARGS__)
#define Dada(...)                               BEGUILE_STEP("Dada",     #__VA_ARGS__, __VA_ARGS__)
#define Dados(...)                              BEGUILE_STEP("Dados",    #__VA_ARGS__, __VA_ARGS__)
#define Dadas(...)                              BEGUILE_STEP("Dadas",    #__VA_ARGS__, __VA_ARGS__)
#define Cuando(...)                             BEGUILE_STEP("Cuando",   #__VA_ARGS__, __VA_ARGS__)
#define Entonces(...)                           BEGUILE_STEP("Entonces", #__VA_ARGS__, __VA_ARGS__)
#define Y(...)                                  BEGUILE_STEP("Y",        #__VA_ARGS__, __VA_ARGS__)
#define Pero(...)                               BEGUILE_STEP("Pero",     #__VA_ARGS__, __VA_ARGS__)

#define deberia_ser_igual_a(x)                  BEGUILE_ASSERT_SHOULD_BE_EQUAL_TO(x)
#define deberia_ser(x)                          BEGUILE_ASSERT_SHOULD_BE_EQUAL_TO(x)
#define no_deberia_ser_igual_a(x)               BEGUILE_ASSERT_SHOULD_NOT_BE_EQUAL_TO(x)
#define no_deberia_ser(x)                       BEGUILE_ASSERT_SHOULD_NOT_BE_EQUAL_TO(x)
#define deberia_ser_menor_que(x)                BEGUILE_ASSERT_SHOULD_BE_LESS_THAN(x)
#define deberia_ser_menor_o_igual_a(x)          BEGUILE_ASSERT_SHOULD_BE_LESS_OR_EQUAL_THAN(x)
#define deberia_ser_mayor_que(x)                BEGUILE_ASSERT_SHOULD_BE_GREATER_THAN(x)
#define deberia_ser_mayor_o_igual_a(x)          BEGUILE_ASSERT_SHOULD_BE_GREATER_OR_EQUAL_THAN(x)
#define deberia_ser_nulo                        BEGUILE_ASSERT_SHOULD_BE_NULL
#define no_deberia_ser_nulo                     BEGUILE_ASSERT_SHOULD_NOT_BE_NULL

#define BEGUILE_MSG_OK                          "BIEN"
#define BEGUILE_MSG_FAIL                        "FALLO"

#define BEGUILE_MSG_SUMMARY_FEATURES            "%d características"
#define BEGUILE_MSG_SUMMARY_SCENARIOS           "%d escenarios"
#define BEGUILE_MSG_SUMMARY_STEPS               "%d pasos"
#define BEGUILE_MSG_SUMMARY_ALL_PASSED          "todos pasaron"
#define BEGUILE_MSG_SUMMARY_FAILED              "%d fallaron"

#define BEGUILE_MSG_COULD_NOT_PIPE              "No se pudo crear la tubería del escenario"
#define BEGUILE_MSG_COULD_NOT_FORK              "No se pudo bifurcar el subproceso del escenario"

#endif

#endif // __BEGUILE_H__
