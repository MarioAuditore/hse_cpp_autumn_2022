#include "matrix.hpp"
#include <gtest/gtest.h>


class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

// Тест успешно пройдёт.
TEST(TestUtils, test_comparison)
{
    Matrix matrix_1 = Matrix(3, 3);
    Matrix matrix_2 = Matrix(3, 3);
    
    matrix_1[0][0] = 2;
    matrix_1[1][1] = 3;
    matrix_1[2][1] = 7;

    matrix_2[0][1] = 1;
    matrix_2[1][0] = 5;
    matrix_2[2][2] = 10;

    ASSERT_EQ(matrix_1 == matrix_1, true);
    ASSERT_EQ(matrix_2 == matrix_2, true);
    ASSERT_EQ(matrix_1 != matrix_2, true);
}


// Тест успешно пройдёт.
TEST(TestUtils, test_multiply)
{
    Matrix matrix_1 = Matrix(3, 3);
    Matrix matrix_2 = Matrix(3, 3);
    
    matrix_1[0][1] = 1;
    matrix_1[1][0] = 5;
    matrix_1[2][2] = 10;

    matrix_2[0][1] = 2;
    matrix_2[1][0] = 10;
    matrix_2[2][2] = 20;

    matrix_1 *= 2;

    ASSERT_EQ(matrix_1 == matrix_2, true);
}


// Тест успешно пройдёт.
TEST(TestUtils, test_sum)
{
    Matrix matrix_1 = Matrix(3, 3);
    Matrix matrix_2 = Matrix(3, 3);
    Matrix matrix_3 = Matrix(3, 3);
    
    matrix_1[0][0] = 2;
    matrix_1[1][0] = 3;

    matrix_2[0][0] = 1;
    matrix_2[1][0] = 5; 

    matrix_3[0][0] = 3;
    matrix_3[1][0] = 8;

    Matrix matrix_sum = matrix_1 + matrix_2;

    ASSERT_EQ(matrix_sum == matrix_3, true);
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}