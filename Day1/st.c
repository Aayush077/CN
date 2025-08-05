/*Wap to create structure student having data members roll, name, 5 subject mark then display the total mark, average mark of student using pointer*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int roll;
    char name[50];
    int marks[5];
};

void cal(struct student *s, int *total, float *avg) {
    *total = 0;
    for (int i = 0; i < 5; i++) {
        *total = *total + s->marks[i];
    }
    *avg = *total / 5;
}

int main() {
    struct student s;
    int total;
    float avg;

    printf("Enter roll number: ");
    scanf("%d", &s.roll);
    printf("Enter name: ");
    scanf(" %[^\n]", s.name); 
    printf("Enter marks for 5 subjects:\n");
    for (int i = 0; i < 5; i++) {
        printf("Sub %d: ", i + 1);
        scanf("%d", &s.marks[i]);
    }

    cal(&s, &total, &avg);

    printf("\nTotal Marks: %d\n", total);
    printf("Average Marks: %.2f\n", avg);

    return 0;
}
