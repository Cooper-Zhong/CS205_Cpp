#include <iostream> 
using namespace std;

int main()
{

    int a, b;
    double c, d;

    a = 19.99 + 21.99; // int (41.98) -> 41

    b = (int)19.99 + (int)21.99; // 19+21 = 40

    c = 23 / 8; // discard fractional part

    d = 23 / 8.0; // convert to double

    cout << "a = " << a << endl;

    cout << "b = " << b << endl;

    cout << "c = " << c << endl;

    cout << "d = " << d << endl;

    cout << "0/0= " << 0 / 0 << endl; // my mac is 1

    return 0;
}