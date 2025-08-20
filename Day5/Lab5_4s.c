/*
	Make a chat program in TCP
*/



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
	if (server_socket == -1)
	{	
	printf("socket not conected \n");
		exit(0);
	}
	printf("socket is %d\n", server_socket);
	
	struct sockaddr_in server, client;
	server.sin_port = 5000;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int b = bind (server_socket, (struct sockaddr *)&server, sizeof(server));
	if (b == -1)
		printf("bind failed \n");
	else
		printf("bind success");
	
	listen (server_socket, 5);
	
	int count =0;
	while (1)
	{
		socklen_t client_len = sizeof(client);
		int client_fd = accept(server_socket, (struct sockaddr*)&client, &client_len);
		if (client_fd == -1)
			printf("accept failed \n");
		else
		{
			count++;
        		printf("Client %d connected from %s\n", count, inet_ntoa(client.sin_addr));
			

		char ch;
		while (1) {
			int n = read(client_fd, &ch, 1);
			if (n <= 0 || ch == '\0') break;

			if (islower(ch)) ch = toupper(ch);
			else if (isupper(ch)) ch = tolower(ch);

			write(client_fd, &ch, 1);
			}
		}
	}
	close(server_socket);
	return 0;	
}
