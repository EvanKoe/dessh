#include "../include/main.h"
#include <stdlib.h>
#include <unistd.h>

int change_directory(Data *d, char **cmd)
{
    char *a = malloc((cmd[1] == NULL ? slen(HOMEPATH) + 1 : slen(cmd[1])) + 1);
    a = cmd[1] == NULL ? strcpy(a, HOMEPATH) : scat(d->pwd, '/', cmd[1]);
    char *b = realpath(a, NULL);

    if (access(b, F_OK) == -1) {
        return (cerr("Error: invalid path\n"));
    }
    chdir(b);
    free_em_all(2, a, d->pwd);
    d->pwd = malloc(slen(b) + 1);
    d->pwd = strcpy(d->pwd, b);
    free(b);
    return (0);
}

int print_working_dir(Data *d, char **cmd)
{
    char *a = malloc(1024);
    a = getcwd(a, 1024);
    if (a == NULL) {
        return (cerr("Error: couldn't get current working directory\n"));
    }
    cout(a);
    cout("\n");
    free(a);
    return (0);
}

int display_env(Data *d, char **cmd)
{
    for (int i = 0; d->env != NULL && d->env[i] != NULL; ++i) {
        cout(d->env[i]);
        cout("\n");
    }
    return (0);
}

int does_env_exist(Data *d, char *cmd)
{
    for (int i = 0; d->env[i] != NULL; ++i) {
        char **a = my_str_to_word_array(d->env[i], "=");
        if (strcmp(a[0], cmd) == 0) {
            return (i);
        }
    }
    return (-1);
}

int unset_env(Data *d, char **cmd)
{
    int i = 0;

    if (cmd == NULL || cmd[1] == NULL) {
        return (cerr("Error: wrong parameters\n"));
    } else if (is_help_array(cmd)) {
        return (cout("Help:\n\tunsetenv [REGISTRY]\n"));
    } else if (!does_env_exist(d, cmd[1])) {
        return (cerr("Error: cannot find entry.\n"));
    }
    i = does_env_exist(d, cmd[1]);
    if (i == -1 || d->env[i] == NULL) {
        return (cerr("Error: cannot find entry.\n"));
    }
    for (; d->env[i + 1] != NULL; ++i) {
        d->env[i] = d->env[i + 1];
    }
    d->env[i] = NULL;
    return (0);
}

int set_env(Data *d, char **cmd)
{
    if (cmd == NULL || cmd[1] == NULL || cmd[2] == NULL) {
        return (cerr("Error: wrong parameters\n"));
    } else if (is_help_array(cmd)) {
        return (cout("Help:\n\tsetenv KEY VALUE\n"));
    }
    int i = does_env_exist(d, cmd[1]);
    size_t size = 0;
    size_t len = 0;
    for (; d->env[len] != NULL; ++len);
    char **cpy = NULL;

    if (i == -1) {
        cpy = copy_array(cpy, d->env);
        for (i = 0; d->env[i] != NULL; ++i);
        size = slen(cmd[1]) + slen(cmd[2]) + 2;
        d->env[i] = malloc(size);
        d->env[i] = strcpy(d->env[i], cmd[1]);
        d->env[i] = scat(cmd[1], '=', cmd[2]);
        d->env[i + 1] = NULL;
        d->env = copy_array(d->env, cpy);
    } else {
        free(d->env[i]);
        d->env[i] = malloc(slen(cmd[1]) + slen(cmd[2]) + 2);
        d->env[i] = scat(cmd[1], '=', cmd[2]);
    }
    return (0);
}
