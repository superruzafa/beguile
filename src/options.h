#include <getopt.h>

#define BeguileParseOptions(argc, argv)                                                             \
    do {                                                                                            \
        int beguile_option;                                                                         \
        int beguile_option_index = 0;                                                               \
        struct option beguile_options[] = {                                                         \
            {"verbose", no_argument, &beguile_global_vars.output_enabled, 1},                       \
            {"silent",  no_argument, &beguile_global_vars.output_enabled, 0},                       \
            {NULL,      0,           0,                                   0}                        \
        };                                                                                          \
        beguile_option = getopt_long(argc, argv, "vs", beguile_options, &beguile_option_index);     \
        while (beguile_option != -1) {                                                              \
            switch (beguile_option) {                                                               \
                case 0:                                                                             \
                case '?':                                                                           \
                    break;                                                                          \
                default:                                                                            \
                    break;                                                                          \
            }                                                                                       \
            beguile_option = getopt_long(argc, argv, "vs", beguile_options, &beguile_option_index); \
        }                                                                                           \
    } while (0);

