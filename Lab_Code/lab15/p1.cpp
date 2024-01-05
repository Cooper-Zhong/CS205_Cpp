#include "line.h"
#include "point.h"
#include <iostream>
using namespace std;
int main()
{
    Point p1(8, 9);
    Point p2(1, -1);
    Line l1(p1, p2);
    cout << "line1: " << l1.getDistance() << "\n";
    Line l2(l1);
    cout << "line2: " << l2.getDistance() << "\n";

    return 0;
}