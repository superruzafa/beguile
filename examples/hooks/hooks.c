#include <beguile.h>

void my_beguile_hook(BeguileHookType type, int is_child)
{
    printf("| ");
    if (is_child) {
        printf("                  | ");
    }

    switch (type) {
        case BEGUILE_HOOK_BEFORE_FEATURE:
            printf("Before Feature   ");
            break;
        case BEGUILE_HOOK_BEFORE_BACKGROUND:
            printf("Before Background");
            break;
        case BEGUILE_HOOK_AFTER_BACKGROUND:
            printf("After Background ");
            break;
        case BEGUILE_HOOK_BEFORE_SCENARIO:
            printf("Before Scenario  ");
            break;
        case BEGUILE_HOOK_AFTER_SCENARIO:
            printf("After Scenario   ");
            break;
        case BEGUILE_HOOK_BEFORE_STEP:
            printf("Before Step      ");
            break;
        case BEGUILE_HOOK_AFTER_STEP:
            printf("After Step       ");
            break;
        case BEGUILE_HOOK_AFTER_FEATURE:
            printf("After Feature    ");
            break;
    }
    if (!is_child) {
        printf(" |                  ");
    }
    puts(" |");
}

int run_feature()
{
    FeatureRunnerHeader

    Feature ("A feature")
        Background
            Given ("some precondition")
        EndBackground

        Scenario ("A scenario")
            Then ("some postcondition")
        EndScenario
        Scenario ("Other scenario")
            When ("some behavior")
            Then ("some other postcondition")
        EndScenario
    EndFeature

    FeatureRunnerFooter
}

#define PRINT_TABLE(title) \
    puts("");                                                                  \
    puts("Hook sequence (" title "):");                                        \
    puts("+-------------------+-------------------+");                         \
    puts("| Parent process    | Child process     |");                         \
    puts("+-------------------+-------------------+");                         \
    run_feature();                                                             \
    puts("+-------------------+-------------------+");


int main()
{
    run_feature();

    beguile_disable_output();
    beguile_enable_hook(my_beguile_hook);

    beguile_enable_fork();
    PRINT_TABLE("fork enabled");

    beguile_disable_fork();
    PRINT_TABLE("fork disabled");

    return EXIT_SUCCESS;
}
