#include "point.h"

Point::Point(double newX, double newY) : x(newX), y(newY)
{
}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

