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
	int server_socket1 = socket(AF_INET, SOCK_STREAM,0);
	if(server_socket1 ==-1)
	{
		printf("socket not created\n");
		exit(0);
	}
	else
		printf("socket is %d\n", server_socket1);
	
	struct sockaddr_in server, client;
	server.sin_port = 5000;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int c =connect(server_socket1, (struct sockaddr*)&server, sizeof(server));
	if (c == -1)
		printf("connect failed");
	else
		printf("connect success\n");
		
	int co;
	printf("for send press 1 and to receive press 2:");
	scanf("%d", &co);
	if(co == 1)
	{
		printf("sending");
		int num;
		printf("Enter the number: ");
		scanf ("%d", &num); 
		send (server_socket1, &num, sizeof(int),0);
	}
	if(co == 2)
	{
		int res;
		recv(server_socket1,&res,sizeof(int),0);
		printf("Max is %d", res);
	}
		
	 close(server_socket1);
   	 return 0;

	
}
