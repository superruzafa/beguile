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
    BeguileInternalFlags beguile_internal_flags = {0, 0, 0, 0, 0, 0};          \
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
        beguile_internal_vars.tags_index = 1;                                  \
        BEGUILE_TRIGGER_HOOK(BEGUILE_HOOK_BEFORE_FEATURE, 0);                  \
        ++beguile_stats.feature_total;                                         \
        beguile_internal_flags.feature_has_failed = 0;                         \
        beguile_internal_flags.background_printed = 0;                         \
        beguile_internal_vars.background_section = NULL;                       \
        if (beguile_internal_flags.need_eol) {                                 \
            BEGUILE_EOL();                                                     \
            beguile_internal_flags.need_eol = 0;                               \
        }                                                                      \
        beguile_internal_flags.need_eol = 1;                                   \
        BEGUILE_PRINT(BEGUILE_STYLE_FEATURE(feature_keyword ":") " " feature_name); \
        BEGUILE_FLUSH();

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
        BEGUILE_PRETTY_PRINT(sentence);                                        \
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

