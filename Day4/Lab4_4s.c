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



int count_vowels(const char *str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        char ch = tolower(str[i]);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
            count++;
    }
    return count;
}


int main()
{
	int server_socket = socket(AF_INET, SOCK_STREAM,0);
	if(server_socket ==	-1)
	{
		printf("socket no created");
		exit(0);
	}
	else
		printf("socket is %d\n", server_socket);
	
	struct sockaddr_in server, client;
	server.sin_port = 5000;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int bi = bind(server_socket, (struct sockaddr*)&server,sizeof(server));
	if(bi == -1)
		printf("bind failed");
	else
		printf("bind success");
	
	listen(server_socket, 5);
	
	socklen_t client_len = sizeof(client);
	int new_fd    = accept(server_socket, (struct sockaddr*)&client, &client_len);
	if(new_fd == -1)
		printf("accept failed");
	else
		printf("connected with client %d\n",new_fd);
	
	char buffer[1024];
    recv(new_fd, buffer, sizeof(buffer), 0);

    int vowel_count = count_vowels(buffer);
    char result[32];
    sprintf(result, "%d", vowel_count);

    send(new_fd, result, strlen(result) + 1, 0);



	
	close(new_fd);	
    close(server_socket);
    return 0;

	
		
		
}
