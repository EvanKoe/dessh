#pragma once

#include "../include/lib.h"
#include "../include/cstr.h"

#include <stdio.h>

int str_is_del(char c, char *del)
{
    for (int i = 0; del[i] != '\0'; i++) {
        if (c == del[i])
            return (1);
    }
    return (0);
}

int sud(char *str, char *delim)
{
    int i = 0;
    for (; str[i] != '\0' && !str_is_del(str[i], delim); i++);
    return (i);
}

int nb_line(char *str, char *del)
{
    int nb = 1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str_is_del(str[i], del) && !str_is_del(str[i + 1], del))
            nb++;
    }
    return (nb);
}

char **my_str_to_word_array(char *str, char *del)
{
    int nb_row = nb_line(str, del);
    int pos = 0;
    char **array = malloc(sizeof(char *) * (nb_row + 1));
    for (int i = 0; i < nb_row; i++) {
        for (; str[pos] != '\0' && str_is_del(str[pos], del); pos++);
        array[i] = malloc(sizeof(char) * (sud(str + pos, del) + 1));
        for (int j = 0; str[pos] != '\0' && j != sud(str + pos, del); j++)
            array[i][j] = str[pos + j];
        array[i][sud(str + pos, del)] = '\0';
        pos += sud(str + pos, del);
        for (; str_is_del(str[pos], del); ++pos);
    }
    array[nb_row] = NULL;
    return (array);
}

char **copy_array(char **dest, char **src)
{
    if (src == NULL) {
        return (NULL);
    }
    if (dest != NULL) {
        free_word_array(dest);
    }
    int i = 0;
    for (; src[i] != NULL; ++i);
    dest = malloc(sizeof(char *) * i + 1);
    for (int j = 0; src[j] != NULL; ++j) {
        dest[j] = malloc(slen(src[j]) + 1);
        dest[j] = strcpy(dest[j], src[j]);
    }
    dest[i] = NULL;
    return (dest);
}
