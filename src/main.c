#include "../include/main.h"

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
    char *command = malloc(sizeof(char) * 512);

    while (d->isOpened) {
        command = readline(d->prompt->_str);
        cout(command);
        cout("\n");
        if (strcmp(command, "exit") == 0) {
            d->isOpened = 0;
        }
    }
    cout("pute\n");
    free(command);
    return (0);
}

int main(const int ac, const char **av, const char **env)
{
    Data *d = shell_setup(ac, av, env);
    mainloop(d);
    clean(d);
    return (0);
}
