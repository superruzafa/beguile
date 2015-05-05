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

