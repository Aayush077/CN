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
	int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 		//socket(domain-(ipverse,Pv4,IPv6	-	AF_INET,AF_INET6), type-SOCK_STREAM,SOCK_DGRAM, protocol-IPPROTO_TCP, IPPROTO_UDP,0(if dont know))
	
	if(server_socket ==-1)
	{
		printf("Socket creation failed");
		exit(0);
	}
	else
		printf("Socket is %d\n",server_socket);	
		
	struct sockaddr_in server, client;
	server.sin_port=5000;
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");  //  inet_addr() converts the ip from string to original dotted format  inet_atoi() converts the ip from original dotted format to string

	int c = connect(server_socket,(struct sockaddr*)&server,sizeof(server));      //connect(socket name,  server, size of server)
	
	if (c == -1)
        printf("connet failed");
    else
        printf("Connected successful\n");
        
        
        
        
        return 0;
}
