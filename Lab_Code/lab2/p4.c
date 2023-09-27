#include <stdio.h>
int main()
{
    printf("please input a character:\n");
    char a;
    scanf("%c", &a);
    printf("please input an integer:\n");
    int b;
    scanf("%d", &b);
    printf("please input a float:\n");
    float c;
    scanf("%f", &c);
    printf("the variables you entered were:\n");
    printf("a=%c\nb=%d\nc=%f\n", a, b, c);
}