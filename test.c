#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"
#include "Server.c"

#define PORT 8080;
void launch(struct Server server)
{
    char buffer[30000];
    int address_len = sizeof(server.address);
    const char *hello =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: 48\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<html><body><h1>Hello, World!</h1></body></html>";
    int new_soc;

    while (1)
    {
        printf("=====WAITING FOR CONNECTION=====\n");
        new_soc = accept(server.socket, (struct sockaddr *)&server.address, (socklen_t *)&address_len);
        read(new_soc, buffer, sizeof(buffer));
        printf("response is : %s\n", hello);
        write(new_soc, hello, strlen(hello));
        close(new_soc);
    }
}

int main()
{
    struct Server server = constructor(AF_INET, 0, INADDR_ANY, SOCK_STREAM, 10, 6969, launch);
    server.launch(server);
    return 0;
}