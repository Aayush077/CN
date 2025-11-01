#include <sys/time.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

#define STDIN 0

int main() {
    char ch;
    fd_set readfd;

    FD_ZERO(&readfd);
    FD_SET(STDIN, &readfd);  


    struct timeval t1;
    t1.tv_sec = 5;
    t1.tv_usec = 50000;


    int ret = select(STDIN + 1, &readfd, NULL, NULL, &t1);
    if (ret == -1) {
        perror("Select Error");
    } else if (ret == 0) {
        printf("No key is pressed or timeout occurred\n");
    } else if (FD_ISSET(STDIN, &readfd)) { 
        scanf("%c", &ch);
        printf("Return is: %c\n", ch);
    }

    return 0;
}
