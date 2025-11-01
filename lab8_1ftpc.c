#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        printf("socket not created\n");
        exit(0);
    }
    else
        printf("socket is %d\n", client_socket);

    struct sockaddr_in server;
    server.sin_port = htons(5000);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int c = connect(client_socket, (struct sockaddr*)&server, sizeof(server));
    if (c == -1)
    {
        printf("connection failed\n");
        exit(0);
    }
    else
        printf("connected to server\n");

    char buffer[1024];
    int bytes;
    while ((bytes = recv(client_socket, buffer, sizeof(buffer)-1, 0)) > 0)
    {
        buffer[bytes] = '\0';
        printf("%s", buffer);
    }

    close(client_socket);
    return 0;
}
