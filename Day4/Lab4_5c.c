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
	int server_socket5 = socket(AF_INET, SOCK_STREAM,0);
	if(server_socket5 ==	-1)
	{
		printf("socket no created");
		exit(0);
	}
	else
		printf("socket is %d\n", server_socket5);
	
	struct sockaddr_in server, client;
	server.sin_port = 5000;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int c = connect(server_socket5, (struct sockaddr *)&server, sizeof(server));
	if (c == -1)
		printf("connect failed");
	else
		printf("connect success\n");
		
		
	char buff1[1024];
	char buff2[1024];
	
	printf("enter a string1: \n");
	scanf("%s", buff1);
	
	
	printf("enter a string2: \n");
	scanf("%s", buff2);
	
	send(server_socket5, buff1, strlen(buff1) + 1, 0);
	send(server_socket5, buff2, strlen(buff2) + 1, 0);

	
	char result[1024];
    recv(server_socket5, result, sizeof(result), 0);
    printf("Comparison: %s\n", result);


	
	
    close(server_socket5);
    return 0;

		
		
		
		
		
		
}
