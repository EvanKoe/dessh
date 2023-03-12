#include "../include/main.h"
#include <stdlib.h>
#include <unistd.h>

int change_directory(Data *d, char **cmd)
{
    if (cmd[1] == NULL) {
        return (cerr("Error: please provide a path\n"));
    }
    char *a = scat(d->pwd->_str, cmd[1]);
    char *b = realpath(a, NULL);

    if (access(b, F_OK) == -1) {
        return (cerr("Error: invalid path\n"));
    }
    chdir(b);
    Cstr_destroy(d->pwd);
    d->pwd = Cstr(b);
    free(a);
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
    printf("env\n");
    return (0);
}

int unset_env(Data *d, char **cmd)
{
    printf("unsetenv\n");
    return (0);
}

int set_env(Data *d, char **cmd)
{
    printf("setenv\n");
    return (0);
}
