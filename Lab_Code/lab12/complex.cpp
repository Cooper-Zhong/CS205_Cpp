#include <iostream>
#include "complex.h"
using namespace std;

Complex::Complex(const Complex &rhs)
{
    real = rhs.real;
    imag = rhs.imag;
    cout << "Copy constructor called" << endl;
}

// add
Complex Complex::operator+(const Complex &rhs) const // c1 + c2
{
    return Complex(real + rhs.real, imag + rhs.imag);
}

Complex Complex::operator+(double rhs) const // c + 1.0
{
    return Complex(real + rhs, imag);
}

// friend function
Complex operator+(double lhs, const Complex &rhs) // 1.0 + c
{
    return rhs + lhs;
}

// subtract
Complex Complex::operator-(const Complex &rhs) const // c1 - c2
{
    return Complex(real - rhs.real, imag - rhs.imag);
}

Complex Complex::operator-(double rhs) const // c - 1.0
{
    return Complex(real - rhs, imag);
}

// friend function, not a member function
Complex operator-(double lhs, const Complex &rhs) // 1.0 - c
{
    return Complex(lhs - rhs.real, -rhs.imag);
}

// multiply
Complex Complex::operator*(const Complex &rhs) const // c1 * c2
{
    return Complex(real * rhs.real - imag * rhs.imag, real * rhs.imag + imag * rhs.real);
}

Complex Complex::operator*(double rhs) const // c * 1.0
{
    return Complex(real * rhs, imag * rhs);
}

Complex operator*(double lhs, const Complex &rhs) // 1.0 * c
{
    return rhs * lhs;
}

// ~
Complex Complex::operator~() const // conjugate
{
    return Complex(real, -imag);
}

// ==
bool Complex::operator==(const Complex &rhs) const
{
    return (real == rhs.real && imag == rhs.imag);
}
    
// !=
bool Complex::operator!=(const Complex &rhs) const
{
    return !(*this == rhs);
}

// friend function
ostream &operator<<(ostream &os, const Complex &rhs)
{
    if (rhs.imag < 0)
    {
        os << rhs.real << " - " << -rhs.imag << "i";
        return os;
    }
    else
    {
        os << rhs.real << " + " << rhs.imag << "i";
        return os;
    }
}

istream &operator>>(istream &is, Complex &rhs)
{
    cout << "Enter real part: ";
    is >> rhs.real;
    cout << "Enter imaginary part: ";
    is >> rhs.imag;
    return is;
}