/**
 * @file matrix_test.cpp
 * @brief A basic test of the matrix class.
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include "matrix.h"

using namespace std;
int main()
{
    Matrix a{3,3};
    Matrix b{3,3};

    // Test out the input
    cout << "Enter a 3x3 matrix (A)\n" << flush;
    cin >> a;
    cout << "Enter a 3x3 matrix (B)\n" << flush;
    cin >> b;

    // Test out the output
    cout << "Matrix A\n";
    cout << a << "\n";

    cout << "Matrix B\n";
    cout << b << "\n";

    // Test out matrix arithmetic
    cout << "A + B\n" << a+b << "\n";
    cout << "A - B\n" << a-b << "\n";
    cout << "A * B\n" << a*b << "\n";

    // Test out scalar multiplication
    cout << "2*A\n" << 2*a << "\n";
    cout << "A*2\n" << a*2;
}