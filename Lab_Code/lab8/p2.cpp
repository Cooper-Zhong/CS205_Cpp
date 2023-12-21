#include "match.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int main()
{
    printf("Please input a string: ");
    char s[50];
    cin.getline(s, 50);
    printf("Please input a character: ");
    char c;
    cin >> c;
    const char *res = match(s, c);
    if (!res)
    {
        printf("Not found");
    }
    else
    {
        std::cout << res;
    }

    return 0;
}