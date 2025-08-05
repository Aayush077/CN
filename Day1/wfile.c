/*WAP to enter data through keyboard and write into file*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[100];
    char data[256];

    printf("Enter the filename to write to: ");
    scanf("%s", filename);

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    printf("Enter data : ");
    scanf(" %c", data);
    fgets(data, sizeof(data), stdin);
    fprintf(file, "%s", data);
    fclose(file);
    printf("Data written to %s successfully.\n", filename);
    return 0;
}
