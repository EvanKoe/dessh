#include "../include/main.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void set_default_values(Data *d)
{
    char *a = malloc(1024);
    realpath(getcwd(NULL, 1024), a);

    d->pwd = malloc(slen(a) + 1);
    d->prompt = malloc(slen(a) + 3);
    d->start_path = malloc(slen(a) + 1);
    d->pwd = strcpy(d->pwd, a);
    d->prompt = strcpy(d->prompt, a);
    d->prompt = strcat(d->prompt, "> ");
    d->start_path = strcpy(d->start_path, a);
    d->isOpened = 1;
    free(a);
}

int analyze_config_file(cstr *c, Data *d)
{
    // not available at the moment
    return (0);
}

int parse_file(const char **av, Data *d)
{
    if (av == NULL || access(av[0], R_OK)) {
        return cerr("Warning: couldn't read config file. Using default settings\n");
    }
    int fd = open(av[0], O_RDONLY);
    char *buf = malloc(sizeof(char) * 256);
    int len = lseek(fd, 0, SEEK_END);
    if (len == SYSTEM_ERROR) {
        return cerr("Warning: couldn't read config file. Using default settings\n");
    }
    read(fd, buf, len);
    cstr *content = Cstr(buf);
    analyze_config_file(content, d);
    free(buf);
    return (0);
}

int copy_env(const char **env, Data *d)
{
    if (env == NULL) {
        d->env = NULL;
        return cerr("Warning: env is empty\n");
    }
    size_t i = 0;
    size_t size = 0;
    for (; env[size] != NULL; ++size);
    d->env = malloc(sizeof(char *) * (size + 1));

    for (; env[i] != NULL; ++i) {
        d->env[i] = strdup(env[i]);
    }
    d->env[i] = NULL;
    return (0);
}

Data *shell_setup(const int ac, const char **av, const char **env)
{
    static Data d;

    copy_env(env, &d);
    if (ac == 1 || parse_file(av, &d)) {
        set_default_values(&d);
    }
    return (&d);
}
