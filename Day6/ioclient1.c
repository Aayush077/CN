#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>

int main(){
    int sockfd;
    struct sockaddr_in serv;
    int nums[2], max;
    socklen_t slen;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = 5000;
    serv.sin_addr.s_addr = INADDR_ANY;

    printf("Enter two numbers: ");
    scanf("%d %d", &nums[0], &nums[1]);

    slen = sizeof(serv);
    sendto(sockfd, nums, sizeof(nums), 0, (struct sockaddr*)&serv, slen);
    recvfrom(sockfd, &max, sizeof(max), 0, NULL, NULL);

    printf("Max value received: %d\n", max);

    close(sockfd);
}
