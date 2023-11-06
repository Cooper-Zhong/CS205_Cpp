#include <stdio.h>
#include <stdlib.h>

int fill_array(double arr[], int size);
void show_array(double *arr, int size);
void reverse_array(double *arr, int start, int end);

int main() {
    int size;
    printf("Enter the size of the array: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        printf("Invalid size input.\n");
        return 1;
    }

    double *arr = (double *)malloc(size * sizeof(double));

    int numEntries = fill_array(arr, size);

    printf("Array contents:\n");
    show_array(arr, numEntries);

    printf("Reversed array:\n");
    reverse_array(arr, 0, numEntries - 1);
    show_array(arr, numEntries);

    free(arr);
    return 0;
}

int fill_array(double arr[], int size) {
    int numEntries = 0;

    for (int i = 0; i < size; i++) {
        printf("Enter value #%d: ", i + 1);
        if (scanf("%lf", &arr[i]) != 1) {
            break; // Exit loop on non-numeric input
        }
        numEntries++;
    }

    return numEntries;
}

void show_array(double *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", int(*arr));
        arr++;
    }
    printf("\n");
}

void reverse_array(double *arr, int start, int end) {
    if (start >= end) {
        return; // Base case
    }

    // Swap the elements at the start and end indices
    double temp = arr[start];
    arr[start] = arr[end];
    arr[end] = temp;

    // Recursively reverse the remaining elements
    reverse_array(arr, start + 1, end - 1);
}
