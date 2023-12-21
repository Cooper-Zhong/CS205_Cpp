// test_swap.c
#include <stdio.h>
#include "swap.h"

// Declare the swap function from the library
extern void swap(int *a, int *b);

int main()
{
    int x = 5, y = 10;

    printf("Before swap: x = %d, y = %d\n", x, y);

    // Call the swap function to swap x and y
    swap(&x, &y);

    printf("After swap: x = %d, y = %d\n", x, y);

    return 0;
}
