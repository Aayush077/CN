 #include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netinet/ip.h>
#include<unistd.h>
#include<ctype.h>



int main()
{
	int server_socket = socket(AF_INET, SOCK_STREAM,0);
	if(server_socket ==	-1)
	{
		printf("socket no created");
		exit(0);
	}
	else
		printf("socket is %d\n", server_socket);
	
	struct sockaddr_in server, client;
	server.sin_port = 5000;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int bi = bind(server_socket, (struct sockaddr*)&server,sizeof(server));
	if(bi == -1)
		printf("bind failed");
	else
		printf("bind success");
	
	listen(server_socket, 5);
	
	socklen_t client_len = sizeof(client);
	int new_fd    = accept(server_socket, (struct sockaddr*)&client, &client_len);
	if(new_fd == -1)
		printf("accept failed");
	else
		printf("connected with client %d\n",new_fd);
	
	// A single buffer to receive both strings at once
	char buffer[2048];
	recv(new_fd, buffer, sizeof(buffer), 0);

	// Pointers to locate the two strings inside the buffer
	char* buff1 = buffer;
	char* buff2 = buffer + strlen(buff1) + 1;

	printf("Received string 1: %s\n", buff1);
	printf("Received string 2: %s\n", buff2);

    char result[1024];
    int cmp = strcmp(buff1, buff2);
    if (cmp == 0)
        strcpy(result, "equal");
    else if (cmp > 0)
        strcpy(result, "greater");
    else
        strcpy(result, "smaller");

    send(new_fd, result, strlen(result) + 1, 0);


    close(new_fd);
    close(server_socket);
    return 0;

	
		
		
}
