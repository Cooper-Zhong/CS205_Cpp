#include <iostream>
using namespace std;
int main()
{

    int num1 = 2147483647;
    int num2 = 1;
    char ch = 'a';
    short sh = 1;
    long lo = 1;
    long long ll = 1;

    int result = 0;

    result = num1 + num2;
    cout << "The result is " << result << endl;
    cout << sizeof(ch) << endl;
    cout << sizeof(sh) << endl;
    cout << sizeof(lo) << endl;
    cout << sizeof(ll) << endl;
    cout << (9.0f / 5) << endl;

    float a = 1234.0;
    float b = 1.0;
    float sum = a + b;
    cout << a << " + " << b << " = " << sum << endl;
    cout.setf(ios::fixed);
    cout << a << " + " << b << " = " << sum << endl;


    return 0;
}