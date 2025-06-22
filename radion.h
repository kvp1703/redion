/* Radion.h */

#ifndef RADION
#define RADION

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdarg.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define HOST    "127.0.0.1"
#define PORT    "8000"

typedef unsigned int int32;
typedef unsigned short int int16;
typedef unsigned char int8;

typedef struct s_client {
    int s;
    char ip[16]; // "xxx.xxx.xxx.\0"
    int16 port;
} client_t;

void zero (int8 *, int16);
void mainloop(int);
int init_server(int16);
int main(int, char**);

#endif
