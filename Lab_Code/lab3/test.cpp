#include <stdio.h>
#include <iostream>
using namespace std;
union data
{
    int n;
    char ch;
    short m;
};
struct Car
{

    char brand[20];

    int year;
};
enum Colors
{
    RED = 1,
    GREEN,
    BLUE
};
int main()
{
    int arr[3] = {1, 2, 3};
    cout << BLUE;
    Car mycar = {"toytla", 2020};
    return 0;
}
