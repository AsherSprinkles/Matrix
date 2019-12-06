#include "Matrix.hpp"
#include <iostream>


int main(void)
{
    int row = 4, col = 6;
    Matrix m(row, col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            m[i][j] = i*col+j;
        }
    }
    std::cout << "\n";
    (m*m).print();
    
    return 0;
}