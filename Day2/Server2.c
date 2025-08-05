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
	
	int b = bind(server_socket, (struct sockaddr*)&server, sizeof(server));     //  bind(socket, server, size of (server)
	
	printf("%d\n", b);
	
	if (b == -1)
        printf("Bind failed");
    else
        printf("Bind successful\n");
        
        listen(server_socket,5); //listen(socket name  , amount of client);
        
        
        socklen_t client_len = sizeof(client);
        int a = accept(server_socket, (struct sockaddr*)&client, &client_len); 		// accept(socket name, client,sizeof(client);
        
        if (a == -1)
        perror("Accept failed");
    else
        printf("Client connected with socket %d\n", a);

    return 0;

}


/*
0-standard input 
1- standard output 
2-standard error
3-socket
4-accept
...
*/


/*
predefined internet structure 
accessed by struct sockaddr_in 	server; IPv4 
			     sockaddr_in6; IPv6
			     sockaddr

struct Socketaddr_in
{
	int port; 			//port - 1023 is reserved port we have to use between 1024-65000
	int domain;
	long ipaddr;
};

struct in_addr
{
long s_addr;
}sin_addr;

 
	INADDR_ANY - any IP addr.

send( accept name or socket name	,&x	, sizeof(int)	,	0); - server
receive(clinet_fd	,	&p,sizeof(int)	,	0);	-client


*/
