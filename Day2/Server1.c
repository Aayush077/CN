#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (server_socket == -1)
    {
        printf("Socket creation failed\n");
        exit(0);
    }
    else
        printf("Socket is %d\n", server_socket);

    struct sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int b = bind(server_socket, (struct sockaddr*)&server, sizeof(server));

    if (b == -1)
        perror("Bind failed");
    else
        printf("Bind successful\n");

    listen(server_socket, 5);

    socklen_t client_len = sizeof(client);
    int a = accept(server_socket, (struct sockaddr*)&client, &client_len);

    if (a == -1)
        perror("Accept failed");
    else
        printf("Client connected with socket %d\n", a);

    return 0;
}
