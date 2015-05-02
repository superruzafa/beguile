#define BEGUILE_REAL_TAGS(line, ...) \
    char * BEGUILE_CONCAT(beguile_tags_, line) [] = {__VA_ARGS__, NULL}; \
    beguile_internal_vars.last_tags = BEGUILE_CONCAT(beguile_tags_, line);

#define BEGUILE_TAGS(...) BEGUILE_REAL_TAGS(__LINE__, __VA_ARGS__)

#define tags(...) BEGUILE_TAGS(__VA_ARGS__)

#define BEGUILE_REAL_SET_TAGS(line, ...) \
    char * BEGUILE_CONCAT(beguile_set_tags_, line) [] = {__VA_ARGS__, NULL}; \
    beguile_global_vars.user_tags = BEGUILE_CONCAT(beguile_set_tags_, line)

#define beguile_set_tags(...) BEGUILE_REAL_SET_TAGS(__LINE__, __VA_ARGS__)

int beguile_last_tags_match_all_user_tags_match(char **last_tags)
{
    char **tag;
    char **user_tag = beguile_global_vars.user_tags;
    int user_tag_found;

    while (user_tag != NULL && *user_tag != NULL) {
        user_tag_found = 0;
        for (tag = last_tags; tag != NULL && *tag != NULL; ++tag) {
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

#define BEGUILE_CHECK_TAGS() \
    if (!beguile_last_tags_match_all_user_tags_match(beguile_internal_vars.last_tags)) { \
        beguile_internal_vars.last_tags = NULL;                                 \
        break;                                                                 \
    } else                                                                     \
        beguile_internal_vars.last_tags = NULL;

