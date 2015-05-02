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

