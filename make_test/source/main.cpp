#include <string>
#include <vector>
#include <algorithm>
#include "../include/test.hpp"
#include "gtest/gtest.h"

namespace {
    class TEST_TESTING : public::testing::Test {

        protected:
        void SetUp() override {
        }

        test_output_class test_class;
    };

    TEST_F(TEST_TESTING, combine_strings) {
        EXPECT_EQ(test_class.concatenate_strings(
            std::string("one"), std::string("two")), std::string("onetwo")
        );
    }

    TEST_F(TEST_TESTING, combine_strings_first_empty) {
        EXPECT_EQ(test_class.concatenate_strings(
            std::string(""), std::string("two")), std::string("two")
        );
    }

    TEST_F(TEST_TESTING, combine_strings_second_empty) {
        EXPECT_EQ(test_class.concatenate_strings(
            std::string("one"), std::string("")), std::string("one")
        );
    }
};

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}