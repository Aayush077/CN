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
    int server_socket3 = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket3 == -1)
    {
        printf("socket not created\n");
        exit(0);
    }
    else
        printf("socket is %d\n", server_socket3);

    struct sockaddr_in server, client;
    server.sin_port = 5000;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int b = bind(server_socket3, (struct sockaddr*)&server, sizeof(server));
    if (b == -1)
    {
        printf("bind failed\n");
        exit(0);
    }
    else
        printf("bind success\n");

    listen(server_socket3, 5);

    socklen_t client_len = sizeof(client);
    int client_fd = accept(server_socket3, (struct sockaddr*)&client, &client_len);
    if (client_fd == -1)
    {
        printf("accept failed\n");
        exit(0);
    }
    else
        printf("client connected from %s\n", inet_ntoa(client.sin_addr));

    char buffer[100];

    while (1)
    {
        // read from client
        int bytes = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes <= 0)
        {
            printf("client disconnected\n");
            break;
        }
        buffer[bytes] = '\0';
        printf("Client: %s", buffer);

        // write reply
        printf("Server: ");
        int n = read(0, buffer, sizeof(buffer) - 1);
        if (n <= 0) break;
        buffer[n] = '\0';
        write(client_fd, buffer, strlen(buffer));
    }

    close(client_fd);
    close(server_socket3);
    return 0;
}

