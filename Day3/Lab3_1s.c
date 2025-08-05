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
	server.sin_addr.s_addr=inet_addr("127.0.0.1"); // Listen on any available IP address

	int b = bind(server_socket, (struct sockaddr*)&server, sizeof(server));   // bind(socket, server, size of server)
	printf("%d\n", b);
	if (b == -1)
        printf("Bind failed");
    else
        printf("Bind successful\n");
            listen(server_socket, 5); 
            
    
    socklen_t client_len = sizeof(client);
    int client_socket = accept(server_socket, (struct sockaddr*)&client, &client_len);
   
       if (client_socket== -1)
        printf("Accept failed");
    else
        printf("Client connected with socket %d\n", client_socket);
    
    int x, y, res;

    // Use client_socket to receive data
    recv(client_socket, &x, sizeof(int), 0);
    recv(client_socket, &y, sizeof(int), 0);
    
    res = x + y;
    
    // Use client_socket to send data back
    send(client_socket, &res, sizeof(int), 0);       
    printf("Sent sum back to client.\n");
        
    close(client_socket);    
    close(server_socket);
    return 0;
}
