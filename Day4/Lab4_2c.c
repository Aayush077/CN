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
	int client_socket = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
	if(client_socket ==	-1)
	{
		printf("socket no created");
		exit(0);
	}
	else
		printf("socket is %d\n", client_socket);
	
	struct sockaddr_in server, client;
	server.sin_port = htons(5000);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int c = connect(client_socket, (struct sockaddr *)&server, sizeof(server));
	if (c == -1)
		printf("connect failed");
	else
		printf("connect success\n");
	
	int a,b;
	
	printf("enter number 1   and 2\n");
	scanf("%d %d", &a,&b);
	
	send(client_socket, &a,sizeof(int),0);
	send(client_socket, &b,sizeof(int),0);
	
	int swapped_a, swapped_b;
    recv(client_socket, &swapped_a, sizeof(int), 0);
    recv(client_socket, &swapped_b, sizeof(int), 0);

    printf("Swapped numbers from server: a = %d, b = %d\n", swapped_a, swapped_b);

    close(client_socket);
    return 0;

		
		
		
		
		
		
}

