#include "allocator.hpp"
#include <gtest/gtest.h>


class TestFoo : public ::testing::Test
{
protected:
    void SetUp() {}
    void TearDown() {}
};

// Тест успешно пройдёт.
TEST(TestUtils, test_size_data)
{
    allocator::Allocator myalloc = allocator::Allocator();
    
    myalloc.makeAllocator(10);
    std::size_t true_size = 10;
    ASSERT_EQ( myalloc.max_memory, true_size );

    char* mem_1 = myalloc.alloc(5);
    std::size_t true_used_memory = 5;
    ASSERT_EQ( myalloc.used_memory, true_used_memory );
    ASSERT_NE( mem_1, nullptr );

}

// Тест успешно пройдёт.
TEST(TestUtils, test_nullptr)
{
    allocator::Allocator myalloc = allocator::Allocator();
    myalloc.makeAllocator(5);

    char* mem_1 = myalloc.alloc(9);

    ASSERT_EQ( mem_1, nullptr );
}


TEST(TestUtils, test_reset)
{
    allocator::Allocator myalloc = allocator::Allocator();
    myalloc.makeAllocator(15);

    char* mem_1 = myalloc.alloc(10);
    std::size_t true_used_memory = 10;
    ASSERT_EQ( myalloc.used_memory, true_used_memory );
    ASSERT_NE( mem_1, nullptr );

    myalloc.reset();
    true_used_memory = 0;
    ASSERT_EQ(myalloc.used_memory, true_used_memory);
}


TEST(TestUtils, test_overfill)
{
    allocator::Allocator myalloc = allocator::Allocator();
    myalloc.makeAllocator(15);

    char* mem_1 = myalloc.alloc(10);
    std::size_t true_used_memory = 10;
    ASSERT_EQ( myalloc.used_memory, true_used_memory );
    ASSERT_NE( mem_1, nullptr );

    char* mem_2 = myalloc.alloc(10);
    ASSERT_EQ( myalloc.used_memory, true_used_memory );
    ASSERT_EQ( mem_2, nullptr );
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}