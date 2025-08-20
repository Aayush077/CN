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
	if(server_socket1 ==	-1)
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
		
	char input[100], result[100];
	
    int n = read(0, input, sizeof(input) - 1);
    input[n] = '\0';

    int i;
    for (i = 0; input[i] != '\0'; i++) {
        write(server_socket1, &input[i], 1);
        read(server_socket1, &result[i], 1);
    }

    result[i] = '\0';
    printf("Converted string: %s\n", result);

    char end = '\0';
    write(server_socket1, &end, 1);


		
	

    	close(server_socket1);
    	return 0;
	
	
}
