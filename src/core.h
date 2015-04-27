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

typedef struct {
    int need_eol;
    int feature_has_failed;
    int scenario_has_failed;
    int background_enabled;
    int background_printed;
    int outside_background;
} BeguileFlags;

typedef void (* BeguileHook)(BeguileHookType type);

typedef struct {
    int            written_bytes;
    void          *background_section;
    jmp_buf        jmp_buf;
    pid_t          pid;
    int            pipe[2];
    BeguileHook    hook;
} BeguileVars;

void beguile_pretty_print(char *string)
{
    char *str = string;
    while (*str != '\0') {
        if (*str == ' ' || *str == '_' || *str == '(' || *str == ')') {
            while (*str != '\0' && (*str == ' ' || *str == '_' || *str == '(' || *str == ')')) ++str;
            if (*str != '\0') BEGUILE_PRINT(" ");
        } else {
            BEGUILE_PRINT("%c", *str);
            ++str;
        }
    }
}

#define beguile_set_hook(function)                                             \
    beguile_vars.hook = function

#define BEGUILE_TRIGGER_HOOK(type)                                             \
    if (beguile_vars.hook != NULL) beguile_vars.hook(type)

#define FeatureRunnerHeader \
    BeguileStats beguile_stats = {0, 0, 0, 0, 0, 0, 0};                        \
    BeguileFlags beguile_flags = {0, 0, 0, 0, 0, 0};                           \
    BeguileVars beguile_vars;                                                  \
    beguile_set_hook(NULL);                                                    \
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
        beguile_flags.feature_has_failed = 0;                                  \
        beguile_flags.background_printed = 0;                                  \
        beguile_vars.background_section = NULL;                                \
        if (beguile_flags.need_eol) {                                          \
            BEGUILE_EOL;                                                       \
            beguile_flags.need_eol = 0;                                        \
        }                                                                      \
        beguile_flags.need_eol = 1;                                            \
        BEGUILE_PRINT(BEGUILE_STYLE_FEATURE(feature_keyword ":") " " feature_name); \
        BEGUILE_FLUSH;

#define BEGUILE_ENDFEATURE                                                     \
        if (beguile_flags.feature_has_failed) ++beguile_stats.feature_failed;  \
        BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_AFTER_FEATURE);                      \
    } while(0);

#define BEGUILE_FEATURE_INTRO(intro_keyword, text)                             \
    if (beguile_flags.need_eol) {                                              \
        BEGUILE_EOL;                                                           \
        beguile_flags.need_eol = 0;                                            \
    }                                                                          \
    BEGUILE_INDENT_1;                                                          \
    BEGUILE_PRINT(intro_keyword " " text "\n");

#define BEGUILE_MESSAGE_PARENT(message)                                        \
    beguile_vars.written_bytes = write(beguile_vars.pipe[1], message, sizeof(char))

#define BEGUILE_BACKGROUND(background_keyword)                                 \
    BEGUILE_REAL_BACKGROUND(background_keyword, __LINE__)

#define BEGUILE_REAL_BACKGROUND(background_keyword, line)                      \
    beguile_flags.background_enabled = 0;                                      \
    BEGUILE_CONCAT(beguile_background_, line):;                                \
    beguile_vars.background_section = && BEGUILE_CONCAT(beguile_background_, line); \
    if (beguile_flags.background_enabled) {                                    \
        BEGUILE_MESSAGE_PARENT("b");                                           \
        if (!beguile_flags.background_printed) {                               \
            BEGUILE_EOL;                                                       \
            BEGUILE_INDENT_1;                                                  \
            BEGUILE_PRINT(BEGUILE_STYLE_BACKGROUND(background_keyword ":") "\n"); \
        }

#define BEGUILE_ENDBACKGROUND                                                  \
        BEGUILE_MESSAGE_PARENT("B");                                           \
        longjmp(beguile_vars.jmp_buf, 1);                                      \
    }                                                                          \
    beguile_flags.background_enabled = 1;

#define BEGUILE_SCENARIO(scenario_keyword, scenario_name)                      \
    do {                                                                       \
        ++beguile_stats.scenario_total;                                        \
        beguile_flags.scenario_has_failed = 0;                                 \
        if (pipe(beguile_vars.pipe) != 0) {                                    \
            beguile_flags.scenario_has_failed = 1;                             \
            BEGUILE_EOL;                                                       \
            BEGUILE_INDENT_1;                                                  \
            BEGUILE_PRINT(BEGUILE_STYLE_SCENARIO(scenario_keyword ":") " "     \
                scenario_name " "                                              \
                BEGUILE_STYLE_FAILURE(BEGUILE_MSG_COULD_NOT_PIPE) "\n");       \
                break;                                                         \
        };                                                                     \
        beguile_vars.pid = fork();                                             \
        if (beguile_vars.pid < 0) {                                            \
            beguile_flags.scenario_has_failed = 1;                             \
            BEGUILE_EOL;                                                       \
            BEGUILE_INDENT_1;                                                  \
            BEGUILE_PRINT(BEGUILE_STYLE_SCENARIO(scenario_keyword ":") " "     \
                scenario_name " "                                              \
                BEGUILE_STYLE_FAILURE(BEGUILE_MSG_COULD_NOT_FORK) "\n");       \
        } else if (beguile_vars.pid > 0) {                                     \
            char beguile_message;                                              \
            close(beguile_vars.pipe[1]);                                       \
            while (read(beguile_vars.pipe[0], &beguile_message, sizeof(char))) { \
                switch (beguile_message) {                                     \
                    case 'T':                                                  \
                        ++beguile_stats.step_total;                            \
                        beguile_flags.need_eol = 1;                            \
                        break;                                                 \
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
            waitpid(beguile_vars.pid, &beguile_status, 0);                     \
            beguile_flags.background_printed = 1;                              \
            beguile_flags.scenario_has_failed = beguile_status != EXIT_SUCCESS; \
        } else {                                                               \
            close(beguile_vars.pipe[0]);                                       \
            if (beguile_vars.background_section != NULL                        \
                && !setjmp(beguile_vars.jmp_buf)) {                            \
                goto *beguile_vars.background_section;                         \
            }                                                                  \
            BEGUILE_MESSAGE_PARENT("c");                                       \
            beguile_flags.outside_background = 1;                              \
            BEGUILE_EOL;                                                       \
            BEGUILE_INDENT_1;                                                  \
            BEGUILE_PRINT(BEGUILE_STYLE_SCENARIO(scenario_keyword ":") " "     \
                scenario_name "\n");

#define BEGUILE_ENDSCENARIO                                                    \
            beguile_flags.outside_background = 0;                              \
            _exit(beguile_flags.scenario_has_failed ? EXIT_FAILURE : EXIT_SUCCESS); \
        }                                                                      \
        if (beguile_flags.scenario_has_failed) {                               \
            ++beguile_stats.scenario_failed;                                   \
            beguile_flags.feature_has_failed = 1;                              \
        }                                                                      \
        BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_AFTER_SCENARIO);                     \
    } while(0);

#define BEGUILE_STEP(step_keyword, sentence, statement)                        \
    BEGUILE_MESSAGE_PARENT("s");                                               \
    BEGUILE_MESSAGE_PARENT("T");                                               \
    if (!beguile_flags.background_printed || beguile_flags.outside_background) { \
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
    if (!beguile_flags.background_printed || beguile_flags.outside_background) BEGUILE_EOL; \
    BEGUILE_MESSAGE_PARENT("S");                                               \

#define BEGUILE_ASSERT_OK BEGUILE_PRINT(" " BEGUILE_STYLE_SUCCESS(BEGUILE_MSG_OK))
#define BEGUILE_ASSERT_FAIL (BEGUILE_PRINT(" " BEGUILE_STYLE_FAILURE(BEGUILE_MSG_FAIL)), \
    beguile_flags.scenario_has_failed = 1,                                     \
    BEGUILE_MESSAGE_PARENT("F"))

#define BEGUILE_ASSERT_SHOULD_BE_EQUAL_TO(x)              == x    ? BEGUILE_ASSERT_OK : BEGUILE_ASSERT_FAIL
#define BEGUILE_ASSERT_SHOULD_NOT_BE_EQUAL_TO(x)          != x    ? BEGUILE_ASSERT_OK : BEGUILE_ASSERT_FAIL
#define BEGUILE_ASSERT_SHOULD_BE_LESS_THAN(x)              < x    ? BEGUILE_ASSERT_OK : BEGUILE_ASSERT_FAIL
#define BEGUILE_ASSERT_SHOULD_BE_LESS_OR_EQUAL_THAN(x)    <= x    ? BEGUILE_ASSERT_OK : BEGUILE_ASSERT_FAIL
#define BEGUILE_ASSERT_SHOULD_BE_GREATER_OR_EQUAL_THAN(x) >= x    ? BEGUILE_ASSERT_OK : BEGUILE_ASSERT_FAIL
#define BEGUILE_ASSERT_SHOULD_BE_GREATER_THAN(x)           > x    ? BEGUILE_ASSERT_OK : BEGUILE_ASSERT_FAIL
#define BEGUILE_ASSERT_SHOULD_BE_NULL                     == NULL ? BEGUILE_ASSERT_OK : BEGUILE_ASSERT_FAIL
#define BEGUILE_ASSERT_SHOULD_NOT_BE_NULL                 != NULL ? BEGUILE_ASSERT_OK : BEGUILE_ASSERT_FAIL
