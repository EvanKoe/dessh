#include "../include/lib.h"
#include <string.h>

int is_help(char *str)
{
    int a = strcmp(str, "-h") == 0;
    int b = strcmp(str, "--help") == 0;

    return (a || b);
}

int is_help_array(char **array)
{
    for (int i = 0; array != NULL && array[i] != NULL; ++i) {
        if (is_help(array[i])) {
            return (1);
        }
    }
    return (0);
}
