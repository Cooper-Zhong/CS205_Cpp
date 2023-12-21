#include <iostream>
using namespace std;
class triangle
{
private:
    int x, y, z;
    int C;

public:
    // static int count;
    triangle(int w = 0, int h = 0, int l = 0)
    {
        x = w;
        y = h;
        z = l;
        C = x + y + z;
    }
    // triangle()
    // {
    //     count++;
    // }
    // ~triangle()
    // {
    //     count--;
    // }
};

// triangle a(1, 1, 1);
triangle b = triangle(2, 2, 2);
// triangle c{3, 3, 3};
// triangle d = {4, 4, 4, 12};
// triangle e = a;

// int triangle::count = 0;

int main()
{

    // triangle a(1, 1, 1);
// triangle b = triangle(2, 2, 2);
triangle c{3, 3, 3};
// triangle d = {4, 4, 4, 12};
// triangle e = a;


//     triangle a;
//     {
//         triangle b;
//         cout << triangle::count << endl;
//         b.~triangle();
//     }
//     a.~triangle();
//     cout << triangle::count << endl;
//     return 0;
}