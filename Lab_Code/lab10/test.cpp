// test.cpp
#include <iostream>
#include "functions.h"

int main() {
    int a = 10, b = 5;
    
    std::cout << "Addition: " << addition(a, b) << std::endl;
    std::cout << "Subtraction: " << subtraction(a, b) << std::endl;
    std::cout << "Multiplication: " << multiplication(a, b) << std::endl;
    
    float result = division(a, b);
    if (result == -1) {
        std::cout << "Error: Division by zero" << std::endl;
    } else {
        std::cout << "Division: " << result << std::endl;
    }
    
    return 0;
}
