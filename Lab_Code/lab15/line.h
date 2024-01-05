#pragma once
#include "point.h"

class Line
{
private:
    Point p1, p2;
    double distance;

public:
    Line(Point xp1, Point xp2);
    Line(Line &q);
    double getDistance() const;
};