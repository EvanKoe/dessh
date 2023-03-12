#pragma once

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


// Prototypes
int slen(const char *);
int putstr(const char *, const int);
int cout(const char *);
int cerr(const char *);

// my_str_to_word_array
char **my_str_to_word_array(char *, char *);

// strcat
char *scat(char *, char *);
