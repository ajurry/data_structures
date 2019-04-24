#include "gtest/gtest.h"
#include "queue.hpp"

using namespace libcontainers;

class QUEUE : public::testing::Test {
    public:
    size_t custom_queue_size = 20;
};

TEST_F(QUEUE, test_size) {
    queue<int> no_size;
    queue<std::string> sized(custom_queue_size);

    EXPECT_EQ(no_size.size(), 0);
    EXPECT_EQ(sized.size(), 0);
    
    EXPECT_EQ(no_size.array_size(), default_queue_size);
    EXPECT_EQ(sized.array_size(), custom_queue_size);
}

TEST_F (QUEUE, test_resize) {
    queue<int> sized (3);

    sized.enqueue(1);
    sized.enqueue(2);
    sized.enqueue(3);
    EXPECT_EQ(sized.size(), 3);
    EXPECT_EQ(sized.array_size(), 3);

    sized.enqueue(4);
    EXPECT_EQ(sized.size(), 4);
    EXPECT_EQ(sized.array_size(), 6);
}

TEST_F(QUEUE, test_enqueue_and_dequeue_and_peek) {
    queue<int> sized(3);

    sized.enqueue(1);
    sized.enqueue(2);
    EXPECT_EQ(sized.size(), 2);
    EXPECT_EQ(sized.dequeue(), 1);
    EXPECT_EQ(sized.dequeue(), 2);

    sized.enqueue(1);
    sized.enqueue(2);
    sized.enqueue(3);
    sized.enqueue(4);
    EXPECT_EQ(sized.size(), 4);

    EXPECT_EQ(sized.dequeue(), 1);
    EXPECT_EQ(sized.dequeue(), 2);
    EXPECT_EQ(sized.dequeue(), 3);
    EXPECT_EQ(sized.dequeue(), 4);

    sized.enqueue(1);
    sized.enqueue(2);
    EXPECT_EQ(sized.size(), 2);
    EXPECT_EQ(sized.peek(), 1);

    EXPECT_EQ(sized.size(), 2);
    EXPECT_EQ(sized.dequeue(), 1);

    EXPECT_EQ(sized.size(), 1);
    EXPECT_EQ(sized.peek(), 2);

    EXPECT_EQ(sized.size(), 1);
    EXPECT_EQ(sized.dequeue(), 2);
}

TEST_F(QUEUE, test_copy) {

    queue<int> sized(3);
    sized.enqueue(1);
    sized.enqueue(2);

    queue<int> copy_assigned_sized = sized;
    queue<int> copy_constructed_sized(sized);

    do 
    {
        EXPECT_EQ(sized.peek(), copy_assigned_sized.peek());
        EXPECT_EQ(sized.peek(), copy_constructed_sized.peek());
        copy_assigned_sized.dequeue();
        copy_constructed_sized.dequeue();
        sized.dequeue();
    }
    while(sized.size() != 0);
}

TEST_F(QUEUE, test_move) {

    queue<int> sized(3);
    sized.enqueue(1);
    sized.enqueue(2);

    queue<int> move_assigned_sized = std::move(sized);
    EXPECT_EQ(sized.size(), 0);

    sized.enqueue(1);
    sized.enqueue(2);
    queue<int> move_constructed_sized(std::move(sized));
    EXPECT_EQ(sized.size(), 0);

    sized.enqueue(1);
    sized.enqueue(2);

    do 
    {
        EXPECT_EQ(sized.peek(), move_assigned_sized.peek());
        EXPECT_EQ(sized.peek(), move_constructed_sized.peek());
        move_assigned_sized.dequeue();
        move_constructed_sized.dequeue();
        sized.dequeue();
    }
    while(sized.size() != 0);
}