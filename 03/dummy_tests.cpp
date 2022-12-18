#include "matrix.hpp"


int main()
{
    Matrix matrix_1 = Matrix(3, 3);
    Matrix matrix_2 = Matrix(3, 3);
    
    matrix_1[0][0] = 2;
    matrix_1[1][1] = 3;
    matrix_1[2][1] = 7;

    matrix_2[0][1] = 1;
    matrix_2[1][0] = 5;
    matrix_2[2][2] = 10;


    std::cout << "Matrix 1:\n" << matrix_1 << std::endl;
    std::cout << "Matrix 2:\n" << matrix_2 << std::endl;

    matrix_1 *= 2;

    std::cout << "Matrix 1:\n" << matrix_1 << std::endl;

    bool choice = (matrix_2 == matrix_2);
    
    std::cout << "mtx_2 == mtx_2: " << choice << std::endl;
    std::cout << "mtx_1 == mtx_2: " << (matrix_1 == matrix_2) << std::endl;

    Matrix matrix_3 = matrix_1 + matrix_2;

    std::cout << "mtx_1 + mtx_2\n" << matrix_3 << std::endl;

    return 0;
}