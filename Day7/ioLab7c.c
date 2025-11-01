#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int sockfd;
    struct sockaddr_in serv;
    char msg[20];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(0);
    }

    serv.sin_family = AF_INET;
    serv.sin_port = 5000;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
    {
        perror("connect");
        exit(0);
    }

    printf("Connected to server\n");

    while (1)
    {
        printf("Enter message: ");
        fgets(msg, sizeof(msg), stdin);
        send(sockfd, msg, strlen(msg), 0);
    }

    close(sockfd);
    return 0;
}

