#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
private:
    double width;
    double height;
    static int countOfObject;

public:
    Rectangle(); // No-arg constructor
    Rectangle(double w, double h); // Constructor with specified width and height

    // Getters and setters
    double getWidth() const;
    void setWidth(double w);
    double getHeight() const;
    void setHeight(double h);

    double getArea() const;
    double getPerimeter() const;
    void display() const;

    static int getCount();
};

#endif // RECTANGLE_H
