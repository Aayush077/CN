#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netinet/ip.h>
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
    server.sin_port = 5000;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int c = connect(client_socket, (struct sockaddr*)&server, sizeof(server));
    if (c == -1)
    {
        printf("connect failed\n");
        exit(0);
    }
    else
        printf("connect success\n");

    char buffer[100];

    while (1)
    {
        // write message
        printf("Client: ");
        int n = read(0, buffer, sizeof(buffer) - 1);
        if (n <= 0) break;
        buffer[n] = '\0';
        write(client_socket, buffer, strlen(buffer));

        // read reply
        int bytes = read(client_socket, buffer, sizeof(buffer) - 1);
        if (bytes <= 0)
        {
            printf("server disconnected\n");
            break;
        }
        buffer[bytes] = '\0';
        printf("Server: %s", buffer);
    }

    close(client_socket);
    return 0;
}

