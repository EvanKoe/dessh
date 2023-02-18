#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "./lib.h"
#include "./cstr.h"

#define SYSTEM_ERROR -1
#define ERROR 84

typedef struct {
    int isOpened;
    char **env;
    cstr *prompt;
    cstr *pwd;
    cstr *start_path;
} Data;

// prototypes

// shell_setup.c
Data *shell_setup(const int, const char **, const char **);
int copy_env(const char **, Data *);
int parse_file(const char **, Data *);
int analyze_config_file(cstr *, Data *);
void set_default_values(Data *);