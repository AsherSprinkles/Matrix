#include "Matrix.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include <cmath>

Matrix::Matrix(int rows, int cols)
{
    showSteps = false;
    this->rows = rows;
    this->cols = cols;
    matrix = new double*[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new double[cols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(const Matrix &m)
{
    showSteps = false;
    this->rows = m.rows;
    this->cols = m.cols;
    matrix = new double*[m.rows];
    for (int i = 0; i < m.rows; i++)
    {
        matrix[i] = new double[m.cols];
    }

    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.cols; j++)
        {
            matrix[i][j] = m.matrix[i][j];
        }
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++)
    {
        delete matrix[i];
    }
    delete matrix;
}

int Matrix::NumRows() const {return rows;}
int Matrix::NumCols() const {return cols;}

void Matrix::ShowSteps(bool ss)
{
    showSteps = ss;
}

static int most_digits(Matrix m)
{
    double max = std::numeric_limits<double>().lowest();
    for (int i = 0; i < m.NumRows(); i++)
    {
        for (int j = 0; j < m.NumCols(); j++)
        {
            if (m[i][j] > max) max = m[i][j];
        }
    }
    
    return ceil(log10(max));
}

void Matrix::print()
{
    int w = most_digits(*this);
    for (int i = 0; i < rows; i++)
    {
        std::cout << "[";
        for (int j = 0; j < cols; j++)
        {
            std::cout << std::setw(w) << matrix[i][j] << " ";
        }
        std::cout << "]" << std::endl;
    }
}

Row Matrix::operator [](int r)
{
    return matrix[r];
}

void Matrix::AddRows(int r1, int r2)
{
    Row R1 = matrix[r1];
    Row R2 = matrix[r2];
    for (int i = 0; i < cols; i++)
    {
        R1[i] = R1[i] + R2[i];
    }
}

void Matrix::MultRow(double s, int r)
{
    Row R = matrix[r];
    for (int i = 0; i < cols; i++)
    {
        R[i] = R[i] * s;
    }
}

void Matrix::AddRows(int r1, int r2, double s)
{
    Row R1 = matrix[r1];
    Row R2 = matrix[r2];
    for (int i = 0; i < cols; i++)
    {
        R1[i] = R1[i] + (R2[i] * s);
    }
}

void Matrix::RowSwap(int r1, int r2)
{
    Row temp = matrix[r1];
    matrix[r2] = matrix[r1];
    matrix[r1] = temp;
}


Matrix Matrix::transpose()
{
    Matrix T(cols, rows);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            T[j][i] = matrix[i][j];
        }
    }
    return T;
}

bool isREF(Matrix m)
{
    // TODO
    int rows = m.NumRows();
    int cols = m.NumCols();
    // Base cases
    if (rows == 0 || cols == 0) return true;
    if (rows == 1) return true;
    
    // 1.) All nonzero rows are above any all zero rows.
    int lowestNonzeroRow = rows;
    int highestZeroRow = -1;
    for (int i = rows-1; i > 0; i--)
    {
        for (int j = 0; j < cols; j++)
        {
            if (m[i][j] != 0) 
            {
                lowestNonzeroRow = i;
                break;
            }
        }
        if (lowestNonzeroRow != rows) break;
    }

    // 2.) Each leading (nonzero) entry of a row is in 
    //  a column to the right of the leading (nonzero)
    //  entry of the row above it.

    // 3.) All entries in a column below a leading entry are zeros.
}

bool isRREF(Matrix m)
{

}

Matrix Matrix::REF()
{
    if (isREF(*this)) return *this;
}

Matrix Matrix::RREF()
{
    if (isRREF(*this)) return *this;
}

double Matrix::determinant()
{
    if (rows != cols)
    {
        std::cerr << "Invalid matrix size for determinant\n";
        exit(0);
    }
}

Matrix Matrix::inverse()
{

}

// Addition
Matrix operator +(Matrix m1, Matrix m2)
{
    if (m1.cols != m2.cols || m1.rows != m2.rows)
    {
        std::cerr << "Invalid matrix sizes for operator: +\n";
        exit(0);
    }
    Matrix m(m1.rows, m1.cols);
    for (int i = 0; i < m1.rows; i++)
    {
        for (int j = 0; j < m1.cols; j++) 
        {
            m[i][j] = m1[i][j] + m2[i][j];
        }
    }
    return m;
}

// Subtraction
Matrix operator -(Matrix m1, Matrix m2)
{
    if (m1.cols != m2.cols || m1.rows != m2.rows)
    {
        std::cerr << "Invalid matrix sizes for operator: -\n";
        exit(0);
    }
    Matrix m(m1.rows, m1.cols);
    for (int i = 0; i < m1.rows; i++)
    {
        for (int j = 0; j < m1.cols; j++) 
        {
            m[i][j] = m1[i][j] - m2[i][j];
        }
    }
    return m;
}

double m_helper(Matrix m1, Matrix m2, int m1r, int m2c)
{
    double t = 0;
    for (int i = 0; i < m1.NumCols(); i++) 
    {
        t += m1[m1r][i] * m2[i][m2c];
    }
    return t;
}

// Multiplication
Matrix operator *(Matrix m1, Matrix m2)
{
    if (m1.cols != m2.rows)
    {
        std::cerr << "Invalid matrix sizes for operator: *\n";
        exit(0);
    }
    Matrix m(m1.rows, m2.cols);
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.cols; j++)
        {
            m.matrix[i][j] = m_helper(m1, m2, i, j);
        }
    }
    return m;
}

Matrix operator *(int s, Matrix m)
{
    Matrix m1 = m;
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.cols; j++)
        {
            m1.matrix[i][j] = s*m1.matrix[i][j];
        }
    }
    return m1;
}

Matrix operator *(Matrix m, int s)
{
    Matrix m1 = m;
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.cols; j++)
        {
            m1.matrix[i][j] = s*m1.matrix[i][j];
        }
    }
    return m1;
}

Matrix operator *(double s, Matrix m)
{
    Matrix m1 = m;
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.cols; j++)
        {
            m1.matrix[i][j] = s*m1.matrix[i][j];
        }
    }
    return m1;
}

Matrix operator *(Matrix m, double s)
{
    Matrix m1 = m;
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.cols; j++)
        {
            m1.matrix[i][j] = s*m1.matrix[i][j];
        }
    }
    return m1;
}

// NOT operator, used for matrix inversion
// Matrix operator ~(Matrix m);

Matrix operator /(Matrix m, int s)
{
    return m * pow(s, -1);
}

Matrix operator /(Matrix m, double s)
{
    return m * pow(s, -1);
}


Matrix Identity(int size)
{
    Matrix I(size, size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j) I[i][j] = 1;
            else I[i][j] = 0;
        }
    }
    return I;
}

Matrix Zero(int size)
{
    Matrix Z(size, size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            Z[i][j] = 0;
        }
    }
    return Z;
}

Matrix Zero(int rows, int cols)
{
    Matrix Z(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Z[i][j] = 0;
        }
    }
    return Z;
}