/*Radion.c*/
#include "radion.h"

bool scontinuation;
bool ccontinuation;

void zero (int8 *buff, int16 size)
{
    int8 *p;
    int16 n;

    for (n = 0, p = buff; n < size; n++, p++) {
        *p = 0;
    }
    return;
}

void child_loop(client_t *cli)
{
    sleep(1);
    return;
}

void mainloop(int s)
{
    struct sockaddr_in cli;
    int32 len;
    int s2;
    char * ip;
    int16 port;
    client_t *client;
    pid_t pid;

    s2 = accept(s, (struct sockaddr *) &cli, (unsigned int *) &len);
    if (s2 < 0) {
        // sleep(1);
        return;
    }

    port = (int16) htons((int) cli.sin_port);
    ip = inet_ntoa(cli.sin_addr);


    printf("Connection from %s: %d\n", ip, port);

    client = (client_t *) malloc (sizeof(client_t));
    assert(client);

    zero((int8 *)client, sizeof(client_t));
    client->s = s;
    client->port = port;
    strncpy(client->ip, ip, 15);

    pid = fork();
    if (pid) {
        free(client);
        return;
    } else {
        dprintf(s2, "100 Connected to redion server\n");
        ccontinuation = true;
        while (ccontinuation){
            child_loop(client);
        }
        close(s2);
        free(client);
    }

    return;
}

int init_server(int16 port)
{
    struct sockaddr_in sock;
    int s;

    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    sock.sin_addr.s_addr = inet_addr(HOST);

    s = socket(AF_INET, SOCK_STREAM, 0);
    assert(s > 0);

    errno = 0;
    if (bind(s, (struct sockaddr*) &sock, sizeof(sock))) {
        assert_perror(errno);
    }

    errno = 0;
    if (listen(s, 20)) {
        assert_perror(errno);
    }

    printf("Server listening on %s:%d\n", HOST, port);

    scontinuation = false;

    return s;
}

int main(int argc, char *argv[])
{
    char *sport;
    int16 port;
    int s;

    if (argc < 2) {
        sport = PORT;
    } else {
        sport = argv[1];
    }

    port = (int16) atoi(sport);
    s = init_server(port);

    scontinuation = true;
    while (scontinuation) {
        mainloop(s);
    }

    printf("Shutting down...\n");
    close(s);

    return 0;
}
