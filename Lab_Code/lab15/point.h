#pragma once
class Point
{
private:
    double x, y;

public:
    Point(double newX, double newY);
    double getX() const;
    double getY() const;
};