#include <iostream>
struct student
{
    char name[10];
    int age;
    bool graduate;
};

int main()
{
    // unsigned int num  = 0x4142;
    // char* p = (char*)(&num);
    // std::cout << *p << std::endl;
    // std::cout << *(p+1) << std::endl;

    // student s = {"John", 11, false};
    // student *p = &s;

    // std::cout << sizeof p << std::endl;
    // std::cout << sizeof(struct student) << std::endl;
    // int yuu = 100;
    // for (;;)
    //     break;
    // for (int i = 10; i >= 0; i--)
    //     ;
    // while (yuu = 100)
    // {
    //     std::cout << i + yuu << std::endl;
    // }
    int n = 0;
    for (; n == 0; ++n)
    {
        std::cout << n;
    }
    while (n = 0)
    {
        std::cout << n;
    }
    for (; n < 3; n += 2)
        ;
    switch (n)
    {
    case 1:
        std::cout << n;
    case 2:
        std::cout << n;
    case 3:
        std::cout << n;
    case 4:
        std::cout << n;
    case 5:
        std::cout << n;
    }
}