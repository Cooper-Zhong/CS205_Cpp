#include <iostream>
#ifndef COMPLEX_H
#define COMPLEX_H
class Complex
{
private:
    double real;
    double imag;

public:
    Complex() : real(1), imag(1)
    {
        // std::cout << "Default constructor called" << std::endl;
    }
    Complex(double r, double i) : real(r), imag(i)
    {
        // std::cout << "Constructor called" << std::endl;
    }

    Complex(const Complex &rhs); // copy constructor
    ~Complex()
    {
        // std::cout << "Destructor called" << std::endl;
    }
    Complex operator+(const Complex &rhs) const; // c1 + c2
    Complex operator-(const Complex &rhs) const; // c1 - c2

    Complex operator+(double rhs) const;         // c + 1.0
    Complex operator-(double rhs) const;         // c - 1.0
    Complex operator*(const Complex &rhs) const; // c1 * c2
    Complex operator*(double rhs) const;         // c * 1.0
    Complex operator~() const;                   // conjugate
    bool operator==(const Complex &rhs) const;
    bool operator!=(const Complex &rhs) const;

    void show() const;

    friend Complex operator+(double lhs, const Complex &rhs);              // 1.0 + c
    friend Complex operator-(double lhs, const Complex &rhs);              // 1.0 - c
    friend Complex operator*(double lhs, const Complex &rhs);              // 1.0 * c
    friend std::ostream &operator<<(std::ostream &os, const Complex &rhs); // cout << c
    friend std::istream &operator>>(std::istream &is, Complex &rhs);       // cin >> c
};
#endif
