#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>

int main(){
    int sockfd, num, count;
    struct sockaddr_in serv;
    socklen_t slen;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = 5000;
    serv.sin_addr.s_addr = INADDR_ANY;

    printf("Enter a number: ");
    scanf("%d", &num);

    slen = sizeof(serv);
    sendto(sockfd, &num, sizeof(num), 0, (struct sockaddr*)&serv, slen);
    recvfrom(sockfd, &count, sizeof(count), 0, NULL, NULL);

    printf("Digit count received: %d\n", count);
    close(sockfd);
}
