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
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("socket not created");
        exit(1);
    }

    struct sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(server_socket, (struct sockaddr*)&server, sizeof(server)) == -1)
    {
        perror("bind failed");
        exit(1);
    }

    listen(server_socket, 5);
    printf("Server listening on port 5000...\n");

    socklen_t client_len = sizeof(client);
    int client_fd = accept(server_socket, (struct sockaddr*)&client, &client_len);
    if (client_fd == -1)
    {
        perror("accept failed");
        exit(1);
    }
    printf("Client connected from %s\n", inet_ntoa(client.sin_addr));

    char filename[100];
    recv(client_fd, filename, sizeof(filename), 0);
    printf("Client requested file: %s\n", filename);

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        char *msg = "File not found!";
        send(client_fd, msg, strlen(msg), 0);
        close(client_fd);
        close(server_socket);
        return 0;
    }

    char buffer[1024];
    int n;
    while ((n = fread(buffer, 1, sizeof(buffer), fp)) > 0)
    {
        send(client_fd, buffer, n, 0);
    }

    printf("File sent successfully.\n");

    fclose(fp);
    close(client_fd);
    close(server_socket);
    return 0;
}

