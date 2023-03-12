#include "../include/lib.h"

int slen(const char *str)
{
    int i = 0;

    for (; str[i] != 0; ++i);
    return (i);
}

int putstr(const char *str, const int fd)
{
    if (str == NULL || str[0] == 0) {
        return (84);
    }
    int a = write(fd, str, slen(str));
    return (a == -1 ? 84 : 0);
}

int cout(const char *str)
{
    return (putstr(str, 1));
}

int cerr(const char *str)
{
    return (putstr(str, 2));
}
