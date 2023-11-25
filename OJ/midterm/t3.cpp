//
// Created by 志源 on 2023/11/16.
//


#include <iostream>

using namespace std;

// Function for scalar multiplication
void multiply(long a, long b);

// Function for scalar and vector multiplication
void multiply(long scaler, long *vec, int vec_size);

// Function for dot product of two vectors
void multiply(long *vec1, long *vec2, int vec_size);


//scalar
void multiply(long a, long b) {
    cout << (a * b);
}

//scalar and vector
void multiply(long scaler, long *vec, int vec_size) {
    for (int i = 0; i < vec_size; ++i) {
        cout << scaler * vec[i] << " ";
    }
}

// Function for dot product of two vectors
void multiply(long *vec1, long *vec2, int vec_size) {
    long sum = 0;
    for (int i = 0; i < vec_size; ++i) {
        sum += vec1[i] * vec2[i];
//        cout << vec1[i] * vec2[i] << " ";
    }
    cout << sum;
}


int main() {
    char typeA, typeB;
    long scalarA, scalarB;
    int sizeA, sizeB;
    long *vectorA = nullptr, *vectorB = nullptr;


    std::cin >> typeA;
    if (typeA == 'S') {
        std::cin >> scalarA;
    } else if (typeA == 'V') {
        std::cin >> sizeA;
        vectorA = new long[sizeA];
        for (int i = 0; i < sizeA; ++i) {
            std::cin >> vectorA[i];
        }
    }

    std::cin >> typeB;
    if (typeB == 'S') {
        std::cin >> scalarB;
    } else if (typeB == 'V') {
        std::cin >> sizeB;
        vectorB = new long[sizeB];
        for (int i = 0; i < sizeB; ++i) {
            std::cin >> vectorB[i];
        }
    }

    // Perform multiplication based on types of A and B
    if (typeA == 'S' && typeB == 'S') {
        multiply(scalarA, scalarB);
    } else if (typeA == 'S' && typeB == 'V') {
        multiply(scalarA, vectorB, sizeB);
    } else if (typeA == 'V' && typeB == 'S') {
        multiply(scalarB, vectorA, sizeA);
    } else if (typeA == 'V' && typeB == 'V' && sizeA == sizeB) {
        multiply(vectorA, vectorB, sizeA);
    } else {
        std::cout << "Invalid input or mismatched dimensions" << std::endl;
    }

    // Clean up dynamically allocated memory
    delete[] vectorA;
    delete[] vectorB;

    return 0;
}
