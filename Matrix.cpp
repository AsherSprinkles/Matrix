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

int Matrix::GetRows() const {return rows;}
int Matrix::GetCols() const {return cols;}

void Matrix::ShowSteps(bool ss)
{
    showSteps = ss;
}

static int most_digits(Matrix m)
{
    double max = std::numeric_limits<double>().lowest();
    for (int i = 0; i < m.GetRows(); i++)
    {
        for (int j = 0; j < m.GetCols(); j++)
        {
            if (m[i][j] > max)
            {
                max = m[i][j];
            }
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

// Addition
Matrix operator +(Matrix m1, Matrix m2)
{
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
    for (int i = 0; i < m1.GetCols(); i++) 
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
        std::cerr << "Invalid matrix sizes";
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