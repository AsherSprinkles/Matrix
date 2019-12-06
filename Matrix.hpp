#pragma once
typedef double* Row;

class Matrix
{
private:
    double **matrix;
    int rows, cols;
    bool showSteps;
public:
    // Constructors / Destructors
    Matrix(int rows, int cols);
    Matrix(const Matrix &obj);
    ~Matrix();

    // Set / Get
    int NumRows() const;
    int NumCols() const;
    Row operator [](int r);

    // Utility
    void ShowSteps(bool);
    void print();

    // Row Operations
    void AddRows(int R1, int R2);
    void AddRows(int R1, int R2, double s); //  R1 = R2 * s
    void MultRow(double s, int R); // R = R * s
    void RowSwap(int R1, int R2); // R1 <=> R2

    // Math Operations
    Matrix transpose();
    Matrix REF();
    Matrix RREF();
    double determinant();
    Matrix inverse();

    // Operator overloads
    friend Matrix operator +(Matrix m1, Matrix m2);
    friend Matrix operator -(Matrix m1, Matrix m2);
    friend Matrix operator *(Matrix m1, Matrix m2);
    friend Matrix operator *(int s, Matrix m);
    friend Matrix operator *(Matrix m, int s);
    friend Matrix operator *(double s, Matrix m);
    friend Matrix operator *(Matrix m, double s);
};

////---- OPERATOR OVERLOADS ----////
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

// Division
Matrix operator /(Matrix m, int s);
Matrix operator /(Matrix m, double s);

// NOT operator, used for matrix inversion
Matrix operator ~(Matrix m);

////---- UTILITY FUNCTIONS ----////
Matrix Identity(int size);
Matrix Zero(int size);
Matrix Zero(int rows, int cols);