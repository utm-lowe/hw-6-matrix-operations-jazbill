#include "matrix.h"
#include <iomanip>
#include <iostream>

using namespace std;

Matrix::Matrix(unsigned int rows, unsigned int cols)
    : m(rows), n(cols), ar(nullptr)
{
    ar = new double*[m];
    for (unsigned int i = 0; i < m; i++) {
        ar[i] = new double[n];
        for (unsigned int j = 0; j < n; j++) ar[i][j] = 0.0;
    }
}

Matrix::~Matrix()
{
    if (ar != nullptr) {
        for (unsigned int i = 0; i < m; i++) {
            delete[] ar[i];
        }
        delete[] ar;
        ar = nullptr;
    }
}

Matrix::Matrix(const Matrix& rhs)
    : Matrix(rhs.m, rhs.n)
{
    for (unsigned int i = 0; i < m; i++)
        for (unsigned int j = 0; j < n; j++)
            ar[i][j] = rhs.ar[i][j];
}

Matrix& Matrix::operator=(const Matrix& rhs)
{
    if (this == &rhs) return *this;

    if (m != rhs.m || n != rhs.n)
    {
        // Deallocate old memory
        if (ar != nullptr) {
            for (unsigned int i = 0; i < m; i++) {
                delete[] ar[i];
            }
            delete[] ar;
        }
        
        // Allocate new memory
        m = rhs.m;
        n = rhs.n;
        ar = new double*[m];
        for (unsigned int i = 0; i < m; i++) {
            ar[i] = new double[n];
        }
    }

    for (unsigned int i = 0; i < m; i++)
        for (unsigned int j = 0; j < n; j++)
            ar[i][j] = rhs.ar[i][j];

    return *this;
}

int Matrix::getRows() const { return m; }
int Matrix::getCols() const { return n; }

double& Matrix::at(unsigned int row, unsigned int col)
{
    return ar[row][col];
}

const double& Matrix::at(unsigned int row, unsigned int col) const
{
    return ar[row][col];
}

// ---------------- Operators ----------------

Matrix operator+(const Matrix& a, const Matrix& b)
{
    Matrix out(a.getRows(), a.getCols());
    for (int r = 0; r < a.getRows(); r++)
        for (int c = 0; c < a.getCols(); c++)
            out.at(r, c) = a.at(r, c) + b.at(r, c);
    return out;
}

Matrix operator-(const Matrix& a, const Matrix& b)
{
    Matrix out(a.getRows(), a.getCols());
    for (int r = 0; r < a.getRows(); r++)
        for (int c = 0; c < a.getCols(); c++)
            out.at(r, c) = a.at(r, c) - b.at(r, c);
    return out;
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
    Matrix out(a.getRows(), b.getCols());

    for (int r = 0; r < out.getRows(); r++)
    {
        for (int c = 0; c < out.getCols(); c++)
        {
            double sum = 0.0;
            for (int k = 0; k < a.getCols(); k++)
                sum += a.at(r, k) * b.at(k, c);
            out.at(r, c) = sum;
        }
    }
    return out;
}

Matrix operator*(double s, const Matrix& m)
{
    Matrix out(m.getRows(), m.getCols());
    for (int r = 0; r < m.getRows(); r++)
        for (int c = 0; c < m.getCols(); c++)
            out.at(r, c) = s * m.at(r, c);
    return out;
}

Matrix operator*(const Matrix& m, double s)
{
    return s * m;
}

ostream& operator<<(ostream& os, const Matrix& m)
{
    for (int r = 0; r < m.getRows(); r++)
    {
        for (int c = 0; c < m.getCols(); c++)
            os << setw(10) << m.at(r, c) << " ";
        os << "\n";
    }
    os << "\n";
    return os;
}

istream& operator>>(istream& is, Matrix& m)
{
    for (int r = 0; r < m.getRows(); r++)
        for (int c = 0; c < m.getCols(); c++)
            is >> m.at(r, c);
    return is;
}