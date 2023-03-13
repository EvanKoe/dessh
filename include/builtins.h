#pragma once

#include "main.h"

#define HOMEPATH "/home/ekoehler/\0"

typedef struct {
    const char *cmd;
    int (*callback)(Data *, char **);
} builtsins_t;

#define BUILTINS_NB 5

int change_directory(Data *d, char **cmd);
int display_env(Data *d, char **cmd);
int set_env(Data *d, char **cmd);
int unset_env(Data *d, char **cmd);
int print_working_dir(Data *d, char **cmd);

static const builtsins_t builtins[] = {
    { "cd", &change_directory },
    { "env", &display_env },
    { "setenv", &set_env },
    { "unsetenv", &unset_env },
    { "pwd", &print_working_dir },
    { NULL, NULL }
};
