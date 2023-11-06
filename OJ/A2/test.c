#include <stdio.h>
#include <stdlib.h>


void printx(void *value, int width)
{
    if (value == NULL || width <= 0)
        return;
    unsigned char *data = (unsigned char *)value;
    printf("0x");
    unsigned char highest = data[width - 1];

    for (size_t i = 0; i < width; i++)
    {
        if (data[i] < 0x10)
            printf("0");
        printf("%x", data[i]);
    }
    printf("\n");
}

int main() {
    unsigned char * data = (unsigned char *)malloc(sizeof(unsigned char) * 3);
    data[0] = 0x10;
    data[1] = 0x00;
    data[2] = 0x0f;
    
    printx(data, 2); // Output: 0x05140f

    unsigned char singleByte[] = {0x00};
    printx(singleByte, 1); // Output: 0x00

    return 0;
}
