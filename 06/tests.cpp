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

TEST(TestException, test_throw)
{
    EXPECT_ANY_THROW(auto text = format("}{", 2, "one"));
}

TEST(TestException, test_throw_msg)
{
    EXPECT_ANY_THROW(auto text = format("}{", 2, "one"));
    try {
        auto text = format("}{", 2, "one");
    }
    catch (const Error& e) {
        ASSERT_EQ("Invalid curly braces: closing brace before opening", e.message_);
    }
}

TEST(TestException, test_throw_nested_braces)
{
    
    EXPECT_ANY_THROW(auto text = format("{{}}", 2, "one"));
    try {
        auto text = format("{{}}", 2, "one");
    }
    catch (const Error& e) {
        ASSERT_EQ("Invalid character inside curly braces", e.message_);
    }
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}