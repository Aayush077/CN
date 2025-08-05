/*Wap to create structure student having data members roll, name, 2 subject mark then swap mark of 2 subject using pointer and function*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int roll;
    char name[50];
    int marks[2];
};

void swap(struct student *s, int sub1, int sub2) {
    int temp = s->marks[sub1];
    s->marks[sub1] = s->marks[sub2];
    s->marks[sub2] = temp;

    printf("Marks after swapping:");
        for (int i = 0; i < 2; i++) {
            printf("Sub %d: %d\n", i + 1, s->marks[i]);
        }
}

int main() {
    struct student s;
    int sub1, sub2;

    printf("Enter roll no: ");
    scanf("%d", &s.roll);
    printf("Enter name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter marks for 2 sub:\n");
    for (int i = 0; i < 2; i++) {
        printf("Sub %d: ", i + 1);
        scanf("%d", &s.marks[i]);
    }

        swap(&s, sub1, sub2);

    return 0;
}