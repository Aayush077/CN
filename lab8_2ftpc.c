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
        perror("socket not created");
        exit(1);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_socket, (struct sockaddr*)&server, sizeof(server)) == -1)
    {
        perror("connection failed");
        exit(1);
    }

    char filename[100];
    printf("Enter filename to download: ");
    scanf("%s", filename);

    send(client_socket, filename, sizeof(filename), 0);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        perror("file create failed");
        close(client_socket);
        exit(1);
    }

    char buffer[1024];
    int bytes;
    while ((bytes = recv(client_socket, buffer, sizeof(buffer), 0)) > 0)
    {
        fwrite(buffer, 1, bytes, fp);
    }

    printf("File downloaded successfully.\n");

    fclose(fp);
    close(client_socket);
    return 0;
}

