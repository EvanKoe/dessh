#include "../include/lib.h"
#include <stdarg.h>

void free_word_array(char **array)
{
    if (array == NULL) {
        return;
    }
    for (int i = 0; array[i] != NULL; ++i) {
        free(array[i]);
    }
    free(array);
    return;
}

void free_em_all(int n, ...)
{
    va_list list;
    void *ptr = NULL;

    va_start(list, n);
    for (int i = 0; i < n; ++i) {
        ptr = va_arg(list, void *);
        if (ptr != NULL) {
            free(ptr);
        }
    }
    va_end(list);
    return;
}
