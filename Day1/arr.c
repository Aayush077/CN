/*Wap to create a dynamic array and accept n number of element and display max, min and avg value*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, *arr;
    float avg = 0.0;
    int max, min;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &arr[i]);
        avg += arr[i];
        
        // Initialize max and min
        if (i == 0) {
            max = min = arr[i];
        } else {
            if (arr[i] > max) max = arr[i];
            if (arr[i] < min) min = arr[i];
        }
    }

    avg /= n;

    printf("Max value: %d\n", max);
    printf("Min value: %d\n", min);
    printf("Avg value: %.2f\n", avg);

    free(arr);
    return 0;
}