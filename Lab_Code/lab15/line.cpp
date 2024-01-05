#include "line.h"
#include <cmath>
#include <iostream>

Line::Line(Point xp1, Point xp2) : p1(xp1), p2(xp2)
{
    distance = sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
}

Line::Line(Line &q) : p1(q.p1.getX(), q.p1.getY()), p2(q.p2.getX(), q.p2.getY()) {
    std::cout << "copy constructor called" << std::endl;
    distance = q.distance;
}


double Line::getDistance() const
{
    return distance;
}

