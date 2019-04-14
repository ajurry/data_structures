#include "gtest/gtest.h"
#include "../libcontainers/include/doubly_linked_list.hpp"

#include <string>

using namespace libcontainers;

namespace {
    class TEST_DOUBLY_LINKED_LIST : public::testing::Test {

        protected:
        void SetUp() override {
        }

        void TearDown() override {
        }

        int test_vals[3] = {5,10,20};
    };

    TEST_F(TEST_DOUBLY_LINKED_LIST, test_creation) {

        doubly_linked_list<int> test_list;
        EXPECT_EQ(test_list.empty(), true);
    }

    TEST_F(TEST_DOUBLY_LINKED_LIST, test_push_back) {

        doubly_linked_list<int> test_list;
        doubly_linked_list<int>::iterator iter;

        test_list.push_back(test_vals[0]);
        iter = test_list.begin();
        EXPECT_EQ(test_list.size(), 1);
        EXPECT_EQ(*iter, test_vals[0]);

        test_list.push_back(test_vals[1]);
        iter = test_list.begin();
        EXPECT_EQ(test_list.size(), 2);
        EXPECT_EQ(*(++iter), test_vals[1]);

        test_list.push_back(test_vals[2]);
        iter = test_list.begin();
        EXPECT_EQ(test_list.size(), 3);
        EXPECT_NE(*(++iter), test_vals[2]);
    }

    TEST_F(TEST_DOUBLY_LINKED_LIST, test_iteration_after_push_back) {

        doubly_linked_list<int> test_list;
        test_list.push_back(test_vals[0]);
        test_list.push_back(test_vals[1]);
        test_list.push_back(test_vals[2]);

        int count = 0;
        auto iter = test_list.begin();
        while (iter != test_list.end())
        {
            EXPECT_EQ(*(iter++), test_vals[count]);
            ++count;
        }

        EXPECT_EQ(iter, test_list.end());
        EXPECT_EQ(count, test_list.size());
    }

    TEST_F(TEST_DOUBLY_LINKED_LIST, test_push_front) {

        doubly_linked_list<int> test_list;
        doubly_linked_list<int>::iterator iter;

        test_list.push_front(test_vals[0]);
        iter = test_list.begin();
        EXPECT_EQ(test_list.size(), 1);
        EXPECT_EQ(*iter, test_vals[0]);

        test_list.push_front(test_vals[1]);
        iter = test_list.begin();
        EXPECT_EQ(test_list.size(), 2);
        EXPECT_EQ(*iter, test_vals[1]);

        test_list.push_front(test_vals[2]);
        iter = test_list.begin();
        EXPECT_EQ(test_list.size(), 3);
        EXPECT_EQ(*iter, test_vals[2]);
    }

    TEST_F(TEST_DOUBLY_LINKED_LIST, test_iteration_after_push_front) {

        doubly_linked_list<int> test_list;
        test_list.push_front(test_vals[0]);
        test_list.push_front(test_vals[1]);
        test_list.push_front(test_vals[2]);

        int count = 3;
        auto iter = test_list.begin();
        while (iter != test_list.end())
        {
            --count;
            EXPECT_EQ(*(iter++), test_vals[count]);
        }

        EXPECT_EQ(iter, test_list.end());
        EXPECT_EQ(count, 0);
    }

    TEST_F(TEST_DOUBLY_LINKED_LIST, test_iteration_mixed) {
        
        doubly_linked_list<int> test_list;
        int expected_order[5] = {test_vals[2],test_vals[1],test_vals[0],test_vals[0],test_vals[2]};

        test_list.push_front(test_vals[0]);
        test_list.push_front(test_vals[1]);
        test_list.push_back(test_vals[0]);
        test_list.push_front(test_vals[2]);
        test_list.push_back(test_vals[2]);

        int count = 0;
        auto iter = test_list.begin();
        while (iter != test_list.end())
        {
            EXPECT_EQ(*(iter++), expected_order[count]);
            ++count;
        }

        EXPECT_EQ(iter, test_list.end());
        EXPECT_EQ(count, 5);
    }

    TEST_F(TEST_DOUBLY_LINKED_LIST, test_pop_back) {
        
        doubly_linked_list<int> test_list;

        test_list.push_back(test_vals[0]);
        test_list.push_back(test_vals[1]);

        EXPECT_EQ(test_list.size(), 2);
        EXPECT_EQ(*(++test_list.begin()), test_vals[1]);

        test_list.pop_back();
        EXPECT_EQ(test_list.size(), 1);
        EXPECT_EQ(*(test_list.begin()), test_vals[0]);
    }

    TEST_F(TEST_DOUBLY_LINKED_LIST, test_pop_front) {
        
        doubly_linked_list<int> test_list;

        test_list.push_front(test_vals[0]);
        test_list.push_front(test_vals[1]);

        EXPECT_EQ(test_list.size(), 2);
        EXPECT_EQ(*(++test_list.begin()), test_vals[0]);

        test_list.pop_front();
        EXPECT_EQ(test_list.size(), 1);
        EXPECT_EQ(*(test_list.begin()), test_vals[0]);
    }

    TEST_F(TEST_DOUBLY_LINKED_LIST, test_insert) {
        doubly_linked_list<int> test_list;

        test_list.insert(test_list.begin(), test_vals[0]);
        EXPECT_EQ(*test_list.begin(), test_vals[0]);
        EXPECT_EQ(test_list.size(), 1);

        test_list.pop_back();
        test_list.insert(test_list.end(), test_vals[0]);
        EXPECT_EQ(*test_list.begin(), test_vals[0]);
        EXPECT_EQ(test_list.size(), 1);

        test_list.insert(test_list.end(), test_vals[2]);
        EXPECT_EQ(*(--test_list.end()), test_vals[2]);
        EXPECT_EQ(test_list.size(), 2);

        doubly_linked_list<int>::iterator iter = test_list.insert(--test_list.end(), test_vals[1]);
        EXPECT_EQ(*iter, test_vals[1]);
        EXPECT_EQ(test_list.size(), 3);

        int count = 0;
        iter = test_list.begin();
        while (iter != test_list.end())
        {
            EXPECT_EQ(*(iter++), test_vals[count]);
            ++count;
        }

        EXPECT_EQ(iter, test_list.end());
        EXPECT_EQ(count, test_list.size());
    }

    TEST_F(TEST_DOUBLY_LINKED_LIST, test_erase) {

        doubly_linked_list<int> test_list;
        doubly_linked_list<int>::iterator iter = test_list.begin();

        test_list.erase(iter);
        EXPECT_EQ(test_list.size(), 0);

        test_list.push_back(test_vals[0]);
        EXPECT_EQ(test_list.size(), 1);
        test_list.erase(test_list.begin());
        EXPECT_EQ(test_list.size(), 0);

        test_list.push_back(test_vals[0]);
        EXPECT_EQ(test_list.size(), 1);
        test_list.erase(test_list.end());
        EXPECT_EQ(test_list.size(), 0);

        test_list.push_back(test_vals[0]);
        test_list.push_back(test_vals[1]);
        test_list.push_back(test_vals[1]);
        test_list.push_back(test_vals[2]);
        EXPECT_EQ(test_list.size(), 4);
        test_list.erase(++test_list.begin());
        EXPECT_EQ(test_list.size(), 3);

        int count = 0;
        iter = test_list.begin();
        while (iter != test_list.end())
        {
            EXPECT_EQ(*(iter++), test_vals[count]);
            ++count;
        }

        EXPECT_EQ(iter, test_list.end());
        EXPECT_EQ(count, test_list.size());
        
    }
};