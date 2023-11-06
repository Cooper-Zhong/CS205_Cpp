#include <iostream>

int* modifyarr (int* arr){
    *arr++ = 42;
    return arr--;
}
int main()
{
    const int num = 5;
    int arr[] = {1,2,3,4,5};
    int *ptr = arr;
    ptr = modifyarr(ptr);
    std::cout << ptr[0];
    return 0;
}