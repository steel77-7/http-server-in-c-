#ifndef SERVER_H
#define SERVER_H
#include <sys/socket.h>
#include <netinet/in.h>

struct Server
{
    int domain;
    int protocol;
    unsigned long interface;
    int service;
    int backlog;
    int port;

    struct sockaddr_in address;

    int socket;
    void (*launch)(struct Server server);
};

struct Server constructor(int domain, int protocol, unsigned long interface, int service, int backlog, int port,void (*launch)(struct Server server));

#endif
