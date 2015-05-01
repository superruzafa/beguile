#ifndef __BEGUILE_H__
#define __BEGUILE_H__

#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

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

typedef void (* BeguileHook)(BeguileHookType type, int is_child);

typedef struct {
    int             output_enabled;
    int             fork_enabled;
    BeguileHook     hook;
    char          **user_tags;
} BeguileGlobalVars;

BeguileGlobalVars beguile_global_vars = {1, 1, NULL};

