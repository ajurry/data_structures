#include "gtest/gtest.h"
#include "stack.hpp"

using namespace libcontainers;

class STACK : public::testing::Test {
    public:
    size_t custom_stack_size = 20;
};

TEST_F(STACK, test_size) {
    stack<int> no_size;
    stack<std::string> sized(custom_stack_size);

    EXPECT_EQ(no_size.size(), 0);
    EXPECT_EQ(sized.size(), 0);
    
    EXPECT_EQ(no_size.array_size(), default_stack_size);
    EXPECT_EQ(sized.array_size(), custom_stack_size);
}

TEST_F (STACK, test_resize) {
    stack<int> sized (3);

    sized.push(1);
    sized.push(2);
    sized.push(3);
    EXPECT_EQ(sized.size(), 3);
    EXPECT_EQ(sized.array_size(), 3);

    sized.push(4);
    EXPECT_EQ(sized.size(), 4);
    EXPECT_EQ(sized.array_size(), 6);
}

TEST_F(STACK, test_push_pop_and_peek) {
    stack<int> sized(3);

    sized.push(1);
    sized.push(2);
    EXPECT_EQ(sized.size(), 2);
    EXPECT_EQ(sized.pop(), 2);
    EXPECT_EQ(sized.pop(), 1);

    sized.push(1);
    sized.push(2);
    sized.push(3);
    sized.push(4);
    EXPECT_EQ(sized.size(), 4);

    EXPECT_EQ(sized.pop(), 4);
    EXPECT_EQ(sized.pop(), 3);
    EXPECT_EQ(sized.pop(), 2);
    EXPECT_EQ(sized.pop(), 1);

    sized.push(1);
    sized.push(2);
    EXPECT_EQ(sized.size(), 2);
    EXPECT_EQ(sized.peek(), 2);

    EXPECT_EQ(sized.size(), 2);
    EXPECT_EQ(sized.pop(), 2);

    EXPECT_EQ(sized.size(), 1);
    EXPECT_EQ(sized.peek(), 1);

    EXPECT_EQ(sized.size(), 1);
    EXPECT_EQ(sized.pop(), 1);
}

TEST_F(STACK, test_copy) {

    stack<int> sized(3);
    sized.push(1);
    sized.push(2);

    stack<int> copy_assigned_sized = sized;
    stack<int> copy_constructed_sized(sized);

    do 
    {
        EXPECT_EQ(sized.peek(), copy_assigned_sized.peek());
        EXPECT_EQ(sized.peek(), copy_constructed_sized.peek());
        copy_assigned_sized.pop();
        copy_constructed_sized.pop();
        sized.pop();
    }
    while(sized.size() != 0);
}

TEST_F(STACK, test_move) {

    stack<int> sized(3);
    sized.push(1);
    sized.push(2);

    stack<int> move_assigned_sized = std::move(sized);
    EXPECT_EQ(sized.size(), 0);

    sized.push(1);
    sized.push(2);
    stack<int> move_constructed_sized(std::move(sized));
    EXPECT_EQ(sized.size(), 0);

    sized.push(1);
    sized.push(2);

    do 
    {
        EXPECT_EQ(sized.peek(), move_assigned_sized.peek());
        EXPECT_EQ(sized.peek(), move_constructed_sized.peek());
        move_assigned_sized.pop();
        move_constructed_sized.pop();
        sized.pop();
    }
    while(sized.size() != 0);
}