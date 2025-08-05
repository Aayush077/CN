#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

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
		
	struct sockaddr_in server;
	server.sin_port = htons(5000); // Use htons for port
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	int c = connect(server_socket, (struct sockaddr*)&server, sizeof(server)); //connect(socket name, server, size of server)
	
	if (c == -1)
        printf("connect failed");
    else
        printf("Connected successful\n");
        
    char buff[1024];
    printf("Enter a string: \n");
    scanf("%s", buff);
    
    send(server_socket, buff, strlen(buff), 0);
    
    // Clear buffer before receiving
    memset(buff, 0, sizeof(buff));
    
    recv(server_socket, buff, 1024, 0);
    printf("Server sent: %s\n", buff);
        
    close(server_socket);
    return 0;
}
