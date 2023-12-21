#include "matrix.h"
#include <iostream>

using namespace std;
int main()
{
    Matrix a(3, 4);
    Matrix b(3, 4);
    a(1, 2) = 3;

    cout << "a is\n" << a << endl;
    b(2, 3) = 4;
    cout << "b is\n" << b << endl;
    Matrix c = a + b;
    cout << "c is\n" << c << endl;
    Matrix d = a;
    cout << "before assignment" << endl;
    cout << d << endl;
    d = b;
    cout << "after assignment" << endl;
    cout << d << endl;
}