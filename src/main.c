#include "../include/main.h"
#include <unistd.h>

void clean(Data *d)
{
    for (int i = 0; d->env[i] != NULL; ++i) {
        if (d->env[i] != NULL) {
            free(d->env[i]);
        }
    }
    free(d->env);
    Cstr_destroy(d->prompt);
    Cstr_destroy(d->pwd);
    Cstr_destroy(d->start_path);
}

int mainloop(Data *d)
{
    char *command = malloc(1024);

    while (d->isOpened) {
        command = readline(d->prompt->_str);
        if (strcmp(command, "exit") == 0) {
            d->isOpened = 0;
            break;
        }
        analyze_cmd(command, d);
    }
    free(command);
    return (0);
}

int main(const int ac, const char **av, const char **env)
{
    chdir(getcwd(NULL, 1024));
    Data *d = shell_setup(ac, av, env);
    mainloop(d);
    clean(d);
    return (0);
}
