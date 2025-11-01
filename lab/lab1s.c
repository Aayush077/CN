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
        printf("Socket not created\n");
        exit(0);
    }
    printf("Socket created: %d\n", server_socket);

    struct sockaddr_in server, client;
    server.sin_port = 5000;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    int b = bind(server_socket, (struct sockaddr *)&server, sizeof(server));
    if (b == -1)
    {
        printf("Bind failed\n");
        exit(0);
    }
    printf("Bind success\n");

    listen(server_socket, 5);

    int count = 0;
    int num[2];
    int res = 0;

    while (1)
    {
        socklen_t client_len = sizeof(client);
        int client_fd = accept(server_socket, (struct sockaddr*)&client, &client_len);

        if (client_fd == -1)
        {
            printf("Accept failed\n");
            exit(0);
        }

        count++;

        if (count == 1)
        {
            recv(client_fd, &num[0], sizeof(int), 0);
        }
        else if (count == 2) 
        {
            recv(client_fd, &num[1], sizeof(int), 0);

            if (num[0] > num[1])
                res = num[0];
            else
                res = num[1];
        }
        else if (count == 3)  
        {
            send(client_fd, &res, sizeof(int), 0);
       
            count = 0;
        }

        close(client_fd);
    }

    close(server_socket);
    return 0;
}

