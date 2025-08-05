/*Wap to accept a number and extract number of bytes */

#include <stdio.h>
#include <stdlib.h>


int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    size_t bytes = sizeof(num);

    printf("The number %d occupies %zu byte(s).\n", num, bytes);

    return 0;
}