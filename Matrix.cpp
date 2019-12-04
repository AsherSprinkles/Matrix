#include "Matrix.hpp"

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

void Matrix::SetElement(int row, int col, double x)
{
    matrix[row][col] = x;
}
double Matrix::GetElement(int row, int col) const {return matrix[row][col];}
int Matrix::GetRows() const {return rows;}
int Matrix::GetCols() const {return cols;}

    Matrix Identity(Matrix m);
    Matrix Identity(int size);

void Matrix::ShowSteps(bool ss)
{
    showSteps = ss;
}

void Matrix::print()
{
    for (int i = 0; i < rows; i++)
    {
        std::cout << "[";
        for (int j = 0; j < cols; j++)
        {
            std::cout << std::setw(4) << matrix[i][j];
        }
        std::cout << " ]" << std::endl;
    }
}

Matrix Matrix::transpose()
{
    Matrix T(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            T.SetElement(j, i, matrix[i][j]);
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
            m.SetElement(i, j, m1.GetElement(i,j) + m2.GetElement(i,j));
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
            m.SetElement(i, j, m1.GetElement(i,j) - m2.GetElement(i,j));
        }
    }
    return m;
}

double m_helper(const Matrix &m1, const Matrix &m2, int m1r, int m2c)
{
    double t = 0;
    for (int i = 0; i < m1.GetCols(); i++) 
    {
        t += m1.GetElement(m1r, i) * m2.GetElement(i, m2c);
    }
    return t;
}

// Multiplication
Matrix operator *(Matrix m1, Matrix m2)
{
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
