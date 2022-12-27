#include "bigint.hpp"
#include <gtest/gtest.h>


class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};


TEST(TestUtils, test_logic)
{
    BigInt a = BigInt("12"), b = BigInt("9");

    ASSERT_EQ((a != b), true);
    ASSERT_EQ((a > b), true);
}


TEST(TestUtils, test_sum)
{
    BigInt a = BigInt("12"), b = BigInt("9"), c = BigInt("21");
    BigInt sum = a + b;
    ASSERT_EQ((sum == c), true);
}

TEST(TestUtils, test_sub)
{
    BigInt a = BigInt("12"), b = BigInt("0");
    BigInt subtract = a - a;
    ASSERT_EQ((subtract == b), true);
}

TEST(TestUtils, test_move)
{
    BigInt a = BigInt("12");
    BigInt b = a;
    BigInt c;
    c = std::move(a);
    ASSERT_EQ((c == b), true);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}