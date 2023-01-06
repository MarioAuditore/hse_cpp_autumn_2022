#include "serializer.hpp"
#include <gtest/gtest.h>


class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};


TEST(TestUtils, test_logic)
{
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(&stream);
    Error result = serializer.save(x);

    Data y { 0, false, 0 };

    Deserializer deserializer(&stream);
    const Error err = deserializer.load(y);

    ASSERT_EQ(x.a, y.a);
    ASSERT_EQ(x.b, y.b);
    ASSERT_EQ(x.c, y.c);
    ASSERT_EQ(result, Error::NoError);
    ASSERT_EQ(err, Error::NoError);
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}