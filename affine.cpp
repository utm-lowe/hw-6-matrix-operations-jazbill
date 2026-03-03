/**
 * @file affine.cpp
 * @author Bob Lowe
 * @brief Perform affine transformations on 2D points.
 * @version 0.1
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "matrix.h"
#include <iostream>
#include <cmath>

using namespace std;

// Transformation Matrix Creation Functions

/**
 * @brief Create a 3x3 identity matrix.
 *
 * @return Matrix
 */
Matrix transIdent();

/**
 * @brief Rotate about an angle in degrees
 *
 * @param angle
 * @return Matrix
 */
Matrix transRotate(double angle);

/**
 * @brief Scale by factors sx and sy
 *
 * @param sx
 * @param sy
 * @return Matrix
 */
Matrix transScale(double sx, double sy);

/**
 * @brief Translate by tx and ty
 *
 * @param tx
 * @param ty
 * @return Matrix
 */
Matrix translate(double tx, double ty);

/**
 * @brief Prompt the user for transformations, return the resultant matrix.
 *
 * @return Matrix
 */
Matrix transformMenu();

/**
 * @brief Get the 3 element column vector affine point from the user.
 *
 * @return Matrix
 */
Matrix getPoint();

int main()
{
    Matrix transform = transformMenu();

    // Display the transformation matrix
    cout << "Transformation Matrix: " << endl;
    cout << transform << endl;
    cout << endl;

    // transform points
    while (cin) {
        Matrix point = getPoint();

        // Transform the point (single line)
        if (cin) point = transform * point;

        // If we have a new point, display it.
        if (cin) {
            cout << "Transformed Point: ("
                 << point.at(0,0) << ", " << point.at(1,0) << ")" << endl;
        }
    }

    return 0;
}

// build an identity matrix
Matrix transIdent()
{
    Matrix I(3, 3);
    I.at(0,0) = 1; I.at(0,1) = 0; I.at(0,2) = 0;
    I.at(1,0) = 0; I.at(1,1) = 1; I.at(1,2) = 0;
    I.at(2,0) = 0; I.at(2,1) = 0; I.at(2,2) = 1;
    return I;
}

// build a rotation matrix (angle is in degrees)
Matrix transRotate(double angle)
{
    double rad = angle * M_PI / 180.0;
    double c = cos(rad);
    double s = sin(rad);

    Matrix R(3, 3);
    R.at(0,0) = c;   R.at(0,1) = -s;  R.at(0,2) = 0;
    R.at(1,0) = s;   R.at(1,1) =  c;  R.at(1,2) = 0;
    R.at(2,0) = 0;   R.at(2,1) =  0;  R.at(2,2) = 1;
    return R;
}

// build a scaling matrix
Matrix transScale(double sx, double sy)
{
    Matrix S(3, 3);
    S.at(0,0) = sx;  S.at(0,1) = 0;   S.at(0,2) = 0;
    S.at(1,0) = 0;   S.at(1,1) = sy;  S.at(1,2) = 0;
    S.at(2,0) = 0;   S.at(2,1) = 0;   S.at(2,2) = 1;
    return S;
}

// build a translation matrix
Matrix translate(double tx, double ty)
{
    // Column-vector convention:  [x y 1]^T  ->  T * point
    // Matrix form:
    //  1 0 tx
    //  0 1 ty
    //  0 0 1
    Matrix T(3, 3);
    T.at(0,0) = 1;  T.at(0,1) = 0;  T.at(0,2) = tx;
    T.at(1,0) = 0;  T.at(1,1) = 1;  T.at(1,2) = ty;
    T.at(2,0) = 0;  T.at(2,1) = 0;  T.at(2,2) = 1;
    return T;
}

// do the transformation menu
Matrix transformMenu()
{
    Matrix result = transIdent();
    double x, y, angle;
    char choice;

    do {
        // get the choice
        cout << "(T)ranslate, (R)otate, (S)cale, or (D)one? ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice)
        {
            case 'T':
                cout << "Enter the x and y translation: ";
                cin >> x >> y;
                result = translate(x, y) * result;
                break;

            case 'R':
                cout << "Enter the angle of rotation (degrees): ";
                cin >> angle;
                result = transRotate(angle) * result;
                break;

            case 'S':
                cout << "Enter the x and y scaling factors: ";
                cin >> x >> y;
                result = transScale(x, y) * result;
                break;

            case 'D':
                // done
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

    } while (choice != 'D');

    return result;
}

// get the point from the user
Matrix getPoint()
{
    double x, y;
    cout << "\nEnter x and y: ";
    cin >> x >> y;

    Matrix p(3, 1);
    p.at(0,0) = x;
    p.at(1,0) = y;
    p.at(2,0) = 1;

    return p;
}