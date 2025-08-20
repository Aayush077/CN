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
	
	int b = bind(server_socket, (struct sockaddr*)&server,sizeof(server));
	if(b == -1)
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
		
	int x;
	char buff[1024];
	recv(new_fd,&x,sizeof(int), 0);
	
	if(x % 2== 0)
			strcpy(buff,"EVEN NO");
	else
		strcpy(buff,"ODD NO");
	
	send(new_fd,buff,sizeof(buff),0);
	
	close(new_fd);
	close(server_socket);
	return 0;
}
