

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netinet/ip.h>
#include<unistd.h>
#include<ctype.h>



int is_armstrong(int num) {
    int sum = 0, temp = num, digits = 0;
    while (temp) {
        digits++;
        temp /= 10;
    }
    temp = num;
    while (temp) {
        int digit = temp % 10;
        int power = 1;
        for (int i = 0; i < digits; i++)
            power *= digit;
        sum += power;
        temp /= 10;
    }
    return sum == num;
}


int main()
{
	int server_socket = socket(AF_INET, SOCK_STREAM,0);
	if (server_socket == -1)
	{	
	printf("socket not conected \n");
		exit(0);
	}
	printf("socket is %d\n", server_socket);
	
	struct sockaddr_in server, client;
	server.sin_port = 5000;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int b = bind (server_socket, (struct sockaddr *)&server, sizeof(server));
	if (b == -1)
		printf("bind failed \n");
	else
		printf("bind success");
	
	listen (server_socket, 5);
	
	int count =0;
	while (1)
	{
		socklen_t client_len = sizeof(client);
		int client_fd = accept(server_socket, (struct sockaddr*)&client, &client_len);
		if (client_fd == -1)
			printf("accept failed \n");
		else
		{
			count++;
        		printf("Client %d connected from %s\n", count, inet_ntoa(client.sin_addr));
			
			int start, end;
            read(client_fd, &start, sizeof(start));
            read(client_fd, &end, sizeof(end));

            for (int i = start; i <= end; i++) {
                if (is_armstrong(i)) {
                    write(client_fd, &i, sizeof(i));
                }
            }

            int done = -1;
            write(client_fd, &done, sizeof(done));

            close(client_fd);

			
		}
	}
	close(server_socket);
	return 0;	
}
