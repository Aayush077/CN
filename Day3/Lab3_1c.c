#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>

int main()
{
	int server_socket = socket(AF_INET, SOCK_STREAM, 0); 		//socket(domain, type, protocol)
	
	if(server_socket == -1)
	{
		printf("Socket creation failed");
		exit(0);
	}
	else
		printf("Socket is %d\n", server_socket);	
		
	struct sockaddr_in server,client;
	server.sin_port = htons(5000); // Use htons for correct byte order
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	int c = connect(server_socket, (struct sockaddr*)&server, sizeof(server)); //connect(socket name, server, size of server)
	
	if (c == -1)
        printf("connect failed");
    else
        printf("Connected successful\n");
        
    int x, y, res;
    printf("Enter two numbers: \n");
    scanf("%d %d", &x, &y);
    
    // Use server_socket to send data
    send(server_socket, &x, sizeof(int), 0);
    send(server_socket, &y, sizeof(int), 0);
    
    // Use server_socket to receive data
    recv(server_socket, &res, sizeof(int), 0);       
    printf("sum is %d\n", res);
        
    close(server_socket);
    return 0;
}
