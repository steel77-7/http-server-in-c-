#include <stdlib.h>
#include "server.h" 

struct Server constructor(int domain, int protocol, unsigned long interface, int service, int backlog, int port,void (*launch)(struct Server server))
{

    struct Server server;

    server.domain = domain;
    server.protocol = protocol;
    server.interface = interface;
    server.service = service;
    server.backlog = backlog;
    server.port = port;

    server.address.sin_addr.s_addr = htonl(interface);
    server.address.sin_port = htons(port);
    server.address.sin_family = domain;

    if ((server.socket = socket(server.domain, server.service, server.protocol)) < 0)
    {
        perror("error in running the socket");
        exit(1);
    }

    if (bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address)) < 0)
    {
        perror("error in binding the socket");
        exit(1);
    }

    if (listen(server.socket, server.backlog) < 0)
    {
        perror("failed to listen");
        exit(1);
    }


    server.launch = launch;
    return server;
}
