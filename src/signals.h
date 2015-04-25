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

