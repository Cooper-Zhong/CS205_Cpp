#include "Rectangle.h"
#include <iostream>s

int main() {
    Rectangle rect1; // Default rectangle
    const Rectangle rect2(4, 35.2); // Rectangle with specified width and height

    std::cout << "Rectangle 1:" << std::endl;
    rect1.display();
    std::cout << std::endl;

    std::cout << "Rectangle 2:" << std::endl;
    rect2.display();
    std::cout << std::endl;

    std::cout << "Number of rectangle objects created: " << Rectangle::getCount() << std::endl;

    return 0;
}
