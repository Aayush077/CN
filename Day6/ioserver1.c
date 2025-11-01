#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>

int main(){
    int sockfd;
    struct sockaddr_in serv, cli;
    int nums[2], max;
    socklen_t clen;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = 5000;
    serv.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));

    clen = sizeof(cli);
    recvfrom(sockfd, nums, sizeof(nums), 0, (struct sockaddr*)&cli, &clen);
    max = (nums[0] > nums[1]) ? nums[0] : nums[1];
    sendto(sockfd, &max, sizeof(max), 0, (struct sockaddr*)&cli, clen);

    close(sockfd);
}
