#include <stdio.h>
#include "server.h"
#define PORT 8080;
void launch(struct Server server)
{
    char buffer[30000];
    int address_len = sizeof(server.address);
    char *hello = "";
    int new_soc = accept(server.socket, (struct sockaddr_in *)&server.address, sizeof(server.address));
    while (1)
    {
        printf("WAITING FOR CONNECTION\n");
        read(new_soc, buffer, sizeof(buffer));
        printf("response is : %s\n", hello);
        write(new_soc, buffer, strlen(hello));
        close(new_soc);
    }
}

int main()
{
    struct Server server = constructor(AF_INET, SOCK_STREAM, INADDR_ANY, 0, 10, 8080);
    server.launch(server);
    return 0;
}