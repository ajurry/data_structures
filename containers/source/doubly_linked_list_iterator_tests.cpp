#include "gtest/gtest.h"
#include "../libcontainers/include/doubly_linked_list_iterator.hpp"

using namespace libcontainers;

namespace {
    class TEST_DOUBLY_LINKED_LIST_ITERATOR : public::testing::Test {

        protected:
        void SetUp() override {
            // Create some nodes
            node_a = new node<int>{nullptr, nullptr, 1};
            node_b = new node<int>{nullptr, nullptr, 2};
            node_c = new node<int>{nullptr, nullptr, 3};

            // Links nodes together
            node_a->next = node_b;
            node_b->prev = node_a;
            node_b->next = node_c;
            node_c->prev = node_b;
        }

        void TearDown() override {
            // Delete nodes
            delete node_a;
            delete node_b;
            delete node_c;
        }

        node<int>* node_a;
        node<int>* node_b;
        node<int>* node_c;
    };

    TEST_F(TEST_DOUBLY_LINKED_LIST_ITERATOR, test_creation) {
        doubly_linked_list_iterator<int> iter(node_a);
        EXPECT_EQ(*iter, node_a->data);
    }

    TEST_F(TEST_DOUBLY_LINKED_LIST_ITERATOR, test_pre_increment) {
        doubly_linked_list_iterator<int> iter(node_a);
        EXPECT_EQ(*(++iter), node_b->data);
    }

    TEST_F(TEST_DOUBLY_LINKED_LIST_ITERATOR, test_post_increment){
        doubly_linked_list_iterator<int> iter(node_a);
        EXPECT_EQ(*(iter++), node_a->data);
        EXPECT_EQ(*iter, node_b->data);
    }

    TEST_F(TEST_DOUBLY_LINKED_LIST_ITERATOR, test_pre_decrement){
        doubly_linked_list_iterator<int> iter(node_c);
        EXPECT_EQ(*(--iter), node_b->data);
    }

    TEST_F(TEST_DOUBLY_LINKED_LIST_ITERATOR, test_post_decrement){
        doubly_linked_list_iterator<int> iter(node_c);
        EXPECT_EQ(*(iter--), node_c->data);
        EXPECT_EQ(*iter, node_b->data);
    }

    TEST_F(TEST_DOUBLY_LINKED_LIST_ITERATOR, test_copy){
        doubly_linked_list_iterator<int> iter_1(node_b);
        doubly_linked_list_iterator<int> iter_2 = iter_1;
        EXPECT_EQ(iter_1, iter_2);
        EXPECT_EQ(*iter_1, node_b->data);
        EXPECT_EQ(*iter_2, node_b->data);
    }
};