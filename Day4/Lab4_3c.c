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
	int server_socket3 = socket(AF_INET, SOCK_STREAM,0);
	if(server_socket3 ==	-1)
	{
		printf("socket no created");
		exit(0);
	}
	else
		printf("socket is %d\n", server_socket3);
	
	struct sockaddr_in server, client;
	server.sin_port = 5000;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int c = connect(server_socket3, (struct sockaddr *)&server, sizeof(server));
	if (c == -1)
		printf("connect failed");
	else
		printf("connect success\n");
		
		
	char buff[1024];
	
	printf("enter a string: \n");
	scanf("%s", buff);
	
	send(server_socket3, buff, strlen(buff), 0);
	
	char result[1024];
    recv(server_socket3, result, sizeof(result), 0);
    printf("Modified string from server: %s\n", result);
	
	

    close(server_socket3);
    return 0;

		
		
		
		
		
		
}
