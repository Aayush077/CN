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
	int server_socket = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
	if(server_socket ==	-1)
	{
		printf("socket not created");
		exit(0);
	}
	else
		printf("socket is %d\n", server_socket);
	
	struct sockaddr_in server, client;
	server.sin_port = htons(5000);
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


	int a, b;
    recv(new_fd, &a, sizeof(int), 0);
    recv(new_fd, &b, sizeof(int), 0);


    
    int temp = a;
    a = b;
    b = temp;

    send(new_fd, &a, sizeof(int), 0);
    send(new_fd, &b, sizeof(int), 0);
    printf("Swapped and sent back: a = %d, b = %d\n", a, b);

    close(new_fd);
    close(server_socket);
    return 0;

		
		
		
}

