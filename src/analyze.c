#include "../include/main.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

int fork_and_launch(Data *d, char *command, char **args)
{
    int pid = fork();
    int ret = 0;

    if (pid == 0) {
        return (execve(command, args, d->env));
    } else if (pid == -1) {
        return (cerr("Error: couldn't fork program.\n"));
    } else {
        wait(&ret);
        kill(pid, SIGTERM);
        d->return_code = ret;
        if (ret != 0) {
            printf("Program exited with code %d\n", ret);
        }
        return (0);
    }
}

int execute_from_path(Data *d, char **cmd, int is_dot_slash)
{
    if (is_dot_slash) {
        // copy_array(d->args, &(cmd[1]));
        for (int i = 0; d->args[i] != NULL; ++i) {
            printf("[%s, ", d->args[i]);
        }
        cout("]\n");
        return (fork_and_launch(d, cmd[0], cmd));
    }
    int i = does_env_exist(d, "PATH");
    if (i == -1 || cmd == NULL || cmd[0] == NULL) {
        return (cerr("Error: couldn't find path variable.\n"));
    }
    char **a = my_str_to_word_array(d->env[i], "=");
    char **paths = my_str_to_word_array(a[1], ":");
    char *tmp = NULL;
    for (int i = 0; paths[i] != NULL; ++i) {
        tmp = malloc(1024);
        tmp = scat(paths[i], '/', cmd[0]);
        if (access(tmp, F_OK) != -1) {
            return (fork_and_launch(d, tmp, cmd));
        }
        free(tmp);
    }

    free_word_array(a);
    free_word_array(paths);
    return (-1);
}

int has_dot_slash(char **array)
{
    int a = strncmp(array[0], "./", 2);
    int b = array[0][0] == '/';

    if (access(array[0], F_OK) == -1) {
        return (0);
    }
    return (a || b);
}

void analyze_cmd(char *command, Data *d)
{
    if (command == NULL || command[0] == 0) {
        return;
    }
    char **a = my_str_to_word_array(command, " ");
    for (int i = 0; i < BUILTINS_NB; ++i) {
        if (strcmp(builtins[i].cmd, a[0]) == 0) {
            builtins[i].callback(d, a);
            return;
        }
    }
    execute_from_path(d, a, has_dot_slash(a));
    free_word_array(a);
    return;
}

int update_prompt(Data *d)
{
    free(d->prompt);

    d->prompt = malloc(slen(d->pwd) + 3);
    d->prompt = strcpy(d->prompt, d->pwd);
    d->prompt = strcat(d->prompt, "> ");
    return (0);
}
