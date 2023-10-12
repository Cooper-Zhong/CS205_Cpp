#include <iostream>

int main()
{
    // Dynamically allocate an array for five integers
    int *arr = new int[5]{1, 2, 3, 4, 5};

    // Print the elements of the array in reverse order using a pointer
    std::cout << "Reversed order: ";
    for (int i = 4; i >= 0; i--)
    {
        std::cout << *(arr+i) << " ";
    }
    std::cout << std::endl;

    // Deallocate the dynamically allocated array to prevent memory leaks
    delete[] arr;

    return 0;
}
