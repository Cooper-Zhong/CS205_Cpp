#include <stdio.h>
int main()
{
    char a = 127; // overflow = -128
    unsigned char b = 0xff; // +1  = all zeros = 0
    unsigned char c = 0; // -1 = all ones = 255
    a++;
    b++;
    c--;

    printf("a=%d\nb=%d\nc=%d\n", a, b, c);
    return 0;
}