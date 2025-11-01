#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/select.h>

#define STDIN 0

int main()
{
    char msg[20];
    fd_set master_fd, copy_fd;
    struct sockaddr_in serv, client;
    socklen_t size;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        printf("socket not created\n");
        exit(0);
    }
    else
        printf("socket is %d\n", server_fd);

    serv.sin_family = AF_INET;
    serv.sin_port = 5000;
    serv.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
    {
        perror("bind failed");
        exit(0);
    }

    listen(server_fd, 5);

    int maxfd = STDIN >= server_fd ? STDIN : server_fd;
    maxfd = maxfd + 1;

    FD_ZERO(&master_fd);
    FD_SET(STDIN, &master_fd);     // monitor keyboard
    FD_SET(server_fd, &master_fd); // monitor new connections

    while (1)
    {
        copy_fd = master_fd;

        struct timeval t1;
        t1.tv_sec = 7;
        t1.tv_usec = 500000;

        int ret = select(maxfd, &copy_fd, NULL, NULL, &t1);
        if (ret == -1)
        {
            printf("select() failed\n");
            exit(0);
        }
        if (ret == 0)
        {
            printf("timeout\n");
        }
        else
        {
            // keyboard input
            if (FD_ISSET(STDIN, &copy_fd))
            {
                fgets(msg, sizeof(msg), stdin);
                printf("msg from keyboard: %s", msg);
            }

            // new client connection
            if (FD_ISSET(server_fd, &copy_fd))
            {
                size = sizeof(client);
                int new_fd = accept(server_fd, (struct sockaddr *)&client, &size);
                if (new_fd == -1)
                {
                    perror("accept failed");
                }
                else
                {
                    FD_SET(new_fd, &master_fd);
                    maxfd = (new_fd > maxfd ? new_fd : maxfd);
                    maxfd = maxfd + 1;
                    printf("new client connected\n");
                }
            }

            // check all client sockets
            for (int cfd = 0; cfd < maxfd; cfd++)
            {
                if (cfd != STDIN && cfd != server_fd && FD_ISSET(cfd, &copy_fd))
                {
                    int k = recv(cfd, msg, sizeof(msg) - 1, 0);
                    if (k <= 0)
                    {
                        close(cfd);
                        FD_CLR(cfd, &master_fd);
                        printf("client disconnected\n");
                    }
                    else
                    {
                        msg[k] = '\0';
                        printf("msg from client: %s\n", msg);
                    }
                }
            }
        }
    }
}

