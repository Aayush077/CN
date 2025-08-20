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
		
		
	int start, end;
    printf("Enter start of range: ");
    scanf("%d", &start);
    printf("Enter end of range: ");
    scanf("%d", &end);

    write(server_socket1, &start, sizeof(start));
    write(server_socket1, &end, sizeof(end));

    int num;
    printf("Armstrong numbers:\n");
    while (1) {
        read(server_socket1, &num, sizeof(num));
        if (num == -1) break;
        printf("%d ", num);
    }
    printf("\n");


		
    	close(server_socket1);
    	return 0;
	
	
}
