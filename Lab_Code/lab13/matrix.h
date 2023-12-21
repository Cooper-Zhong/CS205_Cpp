#pragma once
#include <memory>
#include <iostream>

class Matrix {
private:
    int rows;
    int cols;
    std::unique_ptr<float[]> data;

public:
    Matrix(int rows, int cols); // constructor
    Matrix(const Matrix& other); // copy constructor
    ~Matrix(); // destructor
    float& operator()(int row, int col); // accessor
    Matrix operator+(const Matrix& other) const; // addition
    Matrix& operator=(const Matrix& other); // assignment operator

    
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

};
