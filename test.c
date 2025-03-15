#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"
#include "Server.c"

#define PORT 8080;
void launch(struct Server server)
{
    printf("3\n");

    char buffer[30000];
    int address_len = sizeof(server.address);

    const char *hello =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: 48\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<html><body><h1>Hello, World!</h1></body></html>";

    //  char *hello = "HTTP/1.1 200 OK\r\n"
    //                "Server: CustomServer/1.0\r\n"
    //                "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\r\n"
    //                "Content-Type: text/html\r\n"
    //                "Content-Length: 44\r\n"
    //                "Connection: Closed\r\n"
    //                "\r\n"
    //                "<html><body><h1>Homo Deus</h1></body></html>";

    printf("4\n");
    int new_soc;

    while (1)
    {
        printf("=====WAITING FOR CONNECTION=====\n");
        new_soc = accept(server.socket, (struct sockaddr *)&server.address, (socklen_t *)&address_len);
        read(new_soc, buffer, sizeof(buffer));
        printf("response is : %s\n", hello);
        write(new_soc, hello, strlen(hello));
        printf("5\n");

        close(new_soc);
    }
}

int main()
{
    printf("1\n");
    struct Server server = constructor(AF_INET, 0, INADDR_ANY, SOCK_STREAM, 10, 6969, launch);
    // struct Server server = constructor();

    printf("2\n");

    server.launch(server);
    return 0;
}