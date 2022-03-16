#ifndef _CORE_H
#define _CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h> 

#define MIN_PORT 0
#define DEFAULT_MAX_PORT 1000
#define MAX_PORT 65535

typedef struct {
    char* ip;
    int min_port;
    int max_default_port;
    int max_port;
} Target;

void help_menu();
int match(const char *string, const char *pattern);
int port_scanner(Target *target, int default_ports);

#endif