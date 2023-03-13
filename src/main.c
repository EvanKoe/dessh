#include "../include/main.h"
#include <signal.h>
#include <unistd.h>

void clean(Data *d)
{
    for (int i = 0; d->env[i] != NULL; ++i) {
        if (d->env[i] != NULL) {
            free(d->env[i]);
        }
    }
    free(d->env);
    free(d->prompt);
    free(d->pwd);
    free(d->start_path);
}

int mainloop(Data *d)
{
    char *command = malloc(1024);

    while (d->isOpened) {
        command = readline(d->prompt);
        if (command == NULL || strcmp(command, "exit") == 0) {
            d->isOpened = 0;
            break;
        }
        analyze_cmd(command, d);
        update_prompt(d);
    }
    free(command);
    return (0);
}

void handler(int sig)
{
    switch (sig) {
        case (SIGINT): exit(0);
        case (SIGSEGV): exit(cerr("Error: segmentation fault. Program stopped.\n"));
    }
    return;
}

int main(const int ac, const char **av, const char **env)
{
    chdir(getcwd(NULL, 1024));
    signal(SIGINT, handler);
    Data *d = shell_setup(ac, av, env);
    mainloop(d);
    clean(d);
    return (0);
}
