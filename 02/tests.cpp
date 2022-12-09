#include "token_parser.hpp"
#include <gtest/gtest.h>


class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

// Тест успешно пройдёт.
TEST(TestUtils, test_string_token)
{
    TokenParser parser;

    std::string line = "a b";

    parser.Parse(line);

    ASSERT_EQ(parser.string_tokens[0], "a");
    ASSERT_EQ(parser.string_tokens[1], "b");

}

// Тест успешно пройдёт.
TEST(TestUtils, test_digit_token)
{
    TokenParser parser;

    std::string line = "10\n2";

    parser.Parse(line);

    uint64_t digit_buf = 10;
    ASSERT_EQ(parser.digit_tokens[0], digit_buf);
    digit_buf = 2;
    ASSERT_EQ(parser.digit_tokens[1], digit_buf);

}

// Тест успешно пройдёт.
TEST(TestUtils, test_complex_token)
{
    TokenParser parser;

    std::string line = "bruh 1234 fatjoe4\ncringe\tbillClinton";

    parser.Parse(line);

    ASSERT_EQ(parser.string_tokens[0], "bruh");
    ASSERT_EQ(parser.string_tokens[1], "fatjoe4");

    uint64_t digit_buf = 1234;
    ASSERT_EQ(parser.digit_tokens[0], digit_buf);
}

TEST(TestUtils, test_extreme_token)
{
    TokenParser parser;

    std::string line = "184467440737095516150 dollars";

    parser.Parse(line);

    ASSERT_EQ(parser.string_tokens[0], "184467440737095516150");
    ASSERT_EQ(parser.string_tokens[1], "dollars");
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

