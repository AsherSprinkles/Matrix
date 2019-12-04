#include "Matrix.hpp"

int main(void)
{
    int row = 4, col = 4;
    Matrix m(row, col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            m.SetElement(i,j,(i*row) + j);
        }
    }
    Matrix p = m.transpose();

    m.print();
    std::cout << "\n";
    p.print();
    std::cout << "\n";
    (5*p).print();
    std::cout << "\n";
    (p*5).print();
    return 0;
}