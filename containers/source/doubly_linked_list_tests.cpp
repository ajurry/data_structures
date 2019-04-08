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

        doubly_linked_list<int> test_list_int_with_entry = doubly_linked_list<int>(5);
    };

    TEST_F(TEST_DOUBLY_LINKED_LIST, test_creation) {

        EXPECT_EQ(test_list_int_with_entry.empty(), false);

        test_list_int_with_entry.clear();
        EXPECT_EQ(test_list_int_with_entry.empty(), true);
    }
};