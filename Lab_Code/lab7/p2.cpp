#include <iostream>
using namespace std;

template <typename T>
T maxn(T arr[], int n)
{
    T max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

template <>
char *maxn<char *>(char *arr[], int n)
{
    int max = strlen(arr[0]);
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        if (strlen(arr[i]) > max)
        {
            max = strlen(arr[i]);
            index = i;
        }
    }
    return arr[index];
}

int main()
{
    int arr1[5] = {1, 2, 3, 4, 5};
    double arr2[5] = {1.1, 2.7, -3.5, -2};
    char *arr3[5] = {"Hello", "World", "C++", "Programming hahah", "Language"};
    cout << maxn(arr1, 5) << endl;
    cout << maxn(arr2, 5) << endl;
    cout << maxn(arr3, 5) << endl;
}