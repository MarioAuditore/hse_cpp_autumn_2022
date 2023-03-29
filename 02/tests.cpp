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

    std::string out = parser.Parse(line);


    ASSERT_EQ(out, " a b");
}

// Тест успешно пройдёт.
TEST(TestUtils, test_digit_token)
{
    TokenParser parser;

    std::string line = "10\n2";

    std::string out = parser.Parse(line);

    
    ASSERT_EQ(out, " 10 2");

}

// Тест успешно пройдёт.
TEST(TestUtils, test_complex_token)
{
    TokenParser parser;

    std::string line = "bruh 1234 fatjoe4\ncringe\tbillClinton";

    std::string out = parser.Parse(line);

    ASSERT_EQ(out, " bruh 1234 fatjoe4 cringe billClinton");
}



TEST(TestUtils, test_callback_start)
{
    TokenParser parser;

    std::string line = "238";
    auto add_word = [](std::string x){return x + " callback";};

    parser.SetStartCallback(add_word);
    std::string out = parser.Parse(line);

    ASSERT_EQ(out, " 238 callback");
}


TEST(TestUtils, ultimate_test)
{
    TokenParser parser;
    auto letter_callback = [](std::string s){return s + "_letter_callback";};
    auto digit_callback = [](uint64_t x){return x*10;};

    parser.SetLetterTokenCallback(letter_callback);


    std::string spaces = "    ";
    std::string empty = "";

    auto spaces_output = parser.Parse(spaces);
    ASSERT_EQ(spaces_output, spaces);

    auto empty_output = parser.Parse(empty);
    ASSERT_EQ(empty_output, "");

    parser.SetDigitTokenCallback(digit_callback);
    std::string one_char_tokens_letter = "a";
    auto one_char_tokens_letter_output = parser.Parse(one_char_tokens_letter);
    ASSERT_EQ(one_char_tokens_letter_output, " a_letter_callback");

    std::string one_char_tokens_digit = "2";
    auto one_char_tokens_digit_output = parser.Parse(one_char_tokens_digit);
    ASSERT_EQ(one_char_tokens_digit_output, " 20");

    std::string multimodal_tokens = "42str str42 2str4 s24tr";
    auto multimodal_tokens_output = parser.Parse(multimodal_tokens);
    ASSERT_EQ(multimodal_tokens_output, " 42str_letter_callback str42_letter_callback 2str4_letter_callback s24tr_letter_callback");

    auto digit_callback_ = [](uint64_t x){return x - 5;};
    parser.SetDigitTokenCallback(digit_callback_);

    std::string not_long = "18446744073709551615"; // 2**64 - 1
    auto not_long_output = parser.Parse(not_long);
    ASSERT_EQ(not_long_output, " 18446744073709551610");

    std::string too_long = "18446744073709551616"; // 2**64
    auto too_long_output = parser.Parse(too_long);
    ASSERT_EQ(too_long_output, " 18446744073709551616_letter_callback");

    std::string very_long = "36893488147419103232"; // 2**65
    auto very_long_output = parser.Parse(very_long);
    ASSERT_EQ(very_long_output, " 36893488147419103232_letter_callback");
}


TEST(TestUtils, all_nullptr)
{
    TokenParser parser;
    std::string out = parser.Parse("abc efg");
    ASSERT_EQ(out, " abc efg");
}





int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
