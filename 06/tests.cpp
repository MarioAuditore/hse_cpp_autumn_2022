#include "formater.hpp"
#include <gtest/gtest.h>


class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};


TEST(TestUtils, test_result)
{
    auto text = format("{1}+{1} = {0}", 2, "one");
    ASSERT_EQ(text, "one+one = 2");
}

TEST(TestUtils, test_more_args)
{
    auto text = format("{0} = {1}", "pi", 3.14159);
    ASSERT_EQ(text, "pi = 3.14159");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}