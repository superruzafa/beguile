#include <getopt.h>

#define BEGUILE_HELP(argc, argv)                                               \
    printf("%s - %s %s\n", argv[0], BEGUILE_NAME, BEGUILE_VERSION);            \
    printf("Usage: %s [OPTION]... [TAGS]...\n", argv[0]);                      \
    puts("  -h, --help                 show this help");                       \
    puts("  -s, --silent               do not print features");                \
    puts("  -f, --no-fork              do not fork process");

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
            {"help",    no_argument, 0, 'h'},                                  \
            {"silent",  no_argument, 0, 's'},                                  \
            {"no-fork", no_argument, 0, 'f'},                                  \
            {0,         0,           0, 0}                                     \
        };                                                                     \
        beguile_option = getopt_long(argc, argv, "hsf", beguile_options, &beguile_option_index); \
        while (beguile_option != -1) {                                         \
            switch (beguile_option) {                                          \
                case 's': beguile_global_vars.output_enabled = 0; break;       \
                case 'f': beguile_global_vars.fork_enabled = 0; break;         \
                case 'h': BEGUILE_HELP(argc, argv); exit(-1); break;           \
            }                                                                  \
            beguile_option = getopt_long(argc, argv, "hsf", beguile_options, &beguile_option_index); \
        }                                                                      \
        BEGUILE_PARSE_TAGS(argc, argv);                                        \
    } while (0);

