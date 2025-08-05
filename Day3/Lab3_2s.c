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
		
	struct sockaddr_in server, client;
	server.sin_port = htons(5000); // Use htons for port
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int b = bind(server_socket, (struct sockaddr*)&server, sizeof(server)); // bind(socket, server, size of server)
	
	if (b == -1)
        printf("Bind failed");
    else
        printf("Bind successful\n");
        
    listen(server_socket, 5); //listen(socket name , amount of client);
    
    socklen_t client_len = sizeof(client);
    int a = accept(server_socket, (struct sockaddr*)&client, &client_len); 		// accept(socket name, client, sizeof(client));
    
    if (a == -1)
        printf("Accept failed");
    else
        printf("Client connected with socket %d\n", a);

    char buff[1024] = {0}; // Initialize buffer to all zeros
    recv(a, buff, 1024, 0);
    printf("Client sent: %s\n", buff);
    
   /* // --- Logic to reverse the string ---
    int i = 0;
    int j = strlen(buff) - 1;
    char temp;
    while(i < j) {
       temp = buff[i];
       buff[i] = buff[j];
       buff[j] = temp;
       i++;
       j--;
    }
    // --- End of reversal logic ---
**/
    send(a, buff, strlen(buff), 0);
    
    close(a); // Close client connection socket
    close(server_socket); // Close listening socket
    return 0;
}
