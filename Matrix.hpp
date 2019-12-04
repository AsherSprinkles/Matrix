#pragma once
#include <iostream>
#include <iomanip>

class Matrix
{
private:
    double **matrix;
    int rows, cols;
    bool showSteps;

    double *AddRows(int r1, int r2);
    double *RowMult(double s, int r1);
    double *RowSub(int r1, int r2);
public:
    // Constructors / Destructors
    Matrix(int rows, int cols);
    Matrix(const Matrix &obj);
    ~Matrix();

    // Set / Get
    void SetElement(int row, int col, double x);
    double GetElement(int row, int col) const;
    int GetRows() const;
    int GetCols() const;

    // Utility
    Matrix Identity(const Matrix &m) const;
    Matrix Identity(int size);
    void ShowSteps(bool);
    void print();

    // Math Operations
    Matrix transpose();
    double determinant();
    friend Matrix operator +(Matrix m1, Matrix m2);
    friend Matrix operator -(Matrix m1, Matrix m2);
    friend Matrix operator *(Matrix m1, Matrix m2);
    friend Matrix operator *(int s, Matrix m);
    friend Matrix operator *(Matrix m, int s);
    friend Matrix operator *(double s, Matrix m);
    friend Matrix operator *(Matrix m, double s);
};

// Addition
Matrix operator +(Matrix m1, Matrix m2);

// Subtraction
Matrix operator -(Matrix m1, Matrix m2);

// Multiplication
Matrix operator *(Matrix m1, Matrix m2);
Matrix operator *(int s, Matrix m);
Matrix operator *(Matrix m, int s);
Matrix operator *(double s, Matrix m);
Matrix operator *(Matrix m, double s);

// NOT operator, used for matrix inversion
Matrix operator ~(Matrix m);