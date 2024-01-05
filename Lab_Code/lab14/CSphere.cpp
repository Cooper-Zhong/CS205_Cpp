#include "CSphere.h"
#include <iostream>
#include <iomanip>

CSphere::CSphere(double r) : radius(r) {}

double CSphere::GetArea() {
    return 4 * 3.14 * radius * radius;
}

double CSphere::GetVolume() {
    return (4.0 / 3.0) * 3.14 * radius * radius * radius;
}

void CSphere::Show() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Sphere Details:" << std::endl;
    std::cout << "Radius: " << radius << std::endl;
    std::cout << "Surface Area: " << GetArea() << ", Volume: " << GetVolume() << std::endl;
}
