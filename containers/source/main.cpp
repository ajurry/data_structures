#include <string>
#include <vector>
#include <algorithm>
#include "../libcontainers/include/doubly_linked_list.hpp"
#include "gtest/gtest.h"


namespace {
    class TEST_TESTING : public::testing::Test {

        protected:
        void SetUp() override {
        }
    };

    TEST_F(TEST_TESTING, combine_strings) {
        EXPECT_EQ(concatenate_strings(
            std::string("one"), std::string("two")), std::string("onetwo")
        );
    }

    TEST_F(TEST_TESTING, combine_strings_first_empty) {
        EXPECT_EQ(concatenate_strings(
            std::string(""), std::string("two")), std::string("two")
        );
    }

    TEST_F(TEST_TESTING, combine_strings_second_empty) {
        EXPECT_EQ(concatenate_strings(
            std::string("one"), std::string("")), std::string("one")
        );
    }
};

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}