#include "matrix.h"
#include <iostream>

using namespace std;
//constructor
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols), data(new float[rows * cols]) {}

//copy constructor
Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), data(new float[rows * cols]) {
    for (int i = 0; i < rows * cols; ++i) {
        data[i] = other.data[i];
    }
}

//destructor
Matrix::~Matrix() {} // smart pointer will clean up memory

// accessor ()
float& Matrix::operator()(int row, int col) {
    return data[row * cols + col];
}

// addition +
Matrix Matrix::operator+(const Matrix& other) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; ++i) {
        result.data[i] = data[i] + other.data[i];
    }
    return result; // return by value invokes copy constructor
}

// assignment operator =
Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) { // self-assignment
        return *this;
    }
    rows = other.rows;
    cols = other.cols;
    data.reset(new float[rows * cols]); 
    for (int i = 0; i < rows * cols; ++i) {
        data[i] = other.data[i];
    }
    return *this;
}

ostream& operator<<(ostream & os, const Matrix & m) {
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            os << m.data[i * m.cols + j] << " ";
        }
        os << endl;
    }
    return os;
}