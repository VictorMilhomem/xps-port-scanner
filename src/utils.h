#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <regex.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int match(const char *string, const char *pattern);

#endif