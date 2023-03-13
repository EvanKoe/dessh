#include "../include/main.h"

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