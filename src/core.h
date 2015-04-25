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

