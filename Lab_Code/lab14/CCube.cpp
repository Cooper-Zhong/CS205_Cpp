#include "CCube.h"
#include <iostream>
#include <iomanip>

CCube::CCube(double l, double w, double h) : length(l), width(w), height(h) {}

double CCube::GetArea() {
    return 2 * (length * width + length * height + width * height);
}

double CCube::GetVolume() {
    return length * width * height;
}

void CCube::Show() {
    std::cout << std::fixed << std::setprecision(0);
    std::cout << "Cube Details:" << std::endl;
    std::cout << "Length: " << length << ", Width: " << width << ", Height: " << height << std::endl;
    std::cout << "Surface Area: " << GetArea() << ", Volume: " << GetVolume() << std::endl;
}
