#include "Rectangle.h"
#include <iostream>

int Rectangle::countOfObject = 0; // must be defined outside the class

Rectangle::Rectangle() : width(1), height(1)
{
    countOfObject++;
}

Rectangle::Rectangle(double w, double h) : width(w), height(h)
{ // initializer list
    countOfObject++;
}

double Rectangle::getWidth() const
{
    return width;
}

void Rectangle::setWidth(double w)
{
    width = w;
}

double Rectangle::getHeight() const
{
    return height;
}

void Rectangle::setHeight(double h)
{
    height = h;
}

double Rectangle::getArea() const
{
    return width * height;
}

double Rectangle::getPerimeter() const
{
    return 2 * (width + height);
}

void Rectangle::display() const
{
    std::cout << "----- Rectangle -----" << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Area: " << getArea() << std::endl;
    std::cout << "Perimeter: " << getPerimeter() << std::endl;
}

int Rectangle::getCount()
{
    return countOfObject;
}
