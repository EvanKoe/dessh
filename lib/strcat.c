#include "../include/lib.h"

char *scat(char *str1, char *str2)
{
    if (str1 == NULL || str2 == NULL) {
        return (NULL);
    }
    char *dest = malloc(slen(str1) + slen(str2) + 2);

    int i = 0;
    for (i = 0; str1[i] != 0; ++i) {
        dest[i] = str1[i];
    }
    dest[i++] = '/';
    for (int j = 0; str2[j] != 0; ++i, ++j) {
        dest[i] = str2[j];
    }
    dest[i] = '\0';
    return (dest);
}
