#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>

int main(){
    int sockfd, num, count=0;
    struct sockaddr_in serv, cli;
    socklen_t clen;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = 5000;
    serv.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));

    clen = sizeof(cli);
    recvfrom(sockfd, &num, sizeof(num), 0, (struct sockaddr*)&cli, &clen);

    int temp = num;
    if(temp == 0) count = 1;
    else{
        while(temp != 0){
            count++;
            temp /= 10;
        }
    }

    sendto(sockfd, &count, sizeof(count), 0, (struct sockaddr*)&cli, clen);
    close(sockfd);
}
