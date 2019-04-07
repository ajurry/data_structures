#include "gtest/gtest.h"
#include "../libcontainers/include/doubly_linked_list.hpp"

#include <string>

namespace {
    class TEST_DOUBLY_LINKED_LIST : public::testing::Test {

        protected:
        void SetUp() override {
        }

        //libcontainers::doubly_linked_list<int> test_list_int;
        //libcontainers::doubly_linked_list<std::string> test_list_string;
    };

    TEST_F(TEST_DOUBLY_LINKED_LIST, TEST) {

    }
};