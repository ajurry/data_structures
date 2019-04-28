#include "gtest/gtest.h"
#include "hash_function.hpp"
#include "custom_hash_container.hpp"
#include <iostream>

using namespace libcontainers;

class HASH_FUNCTION : public::testing::Test {
};

TEST_F(HASH_FUNCTION, test_int) {

    int int_to_hash = 100;
    EXPECT_EQ(int_to_hash, hash_function<int>{}(int_to_hash));

    int_to_hash = -100;
    size_t hashed_int = -100;
    EXPECT_EQ(hashed_int, hash_function<int>{}(int_to_hash));
}

TEST_F(HASH_FUNCTION, test_string) {
    
    std::string string_to_hash = "abcdefg";
    size_t hashed_string = 700;
    EXPECT_EQ(hashed_string, hash_function<std::string>{}(string_to_hash));

    hashed_string = 1015;
    string_to_hash = "abcdefghijk";
    EXPECT_EQ(hashed_string, hash_function<std::string>{}(string_to_hash));

    string_to_hash = "abcdefghij";
    EXPECT_EQ(hashed_string, hash_function<std::string>{}(string_to_hash));
}

TEST_F(HASH_FUNCTION, test_custom_data_structure) {

    custom_hash_container custom_to_hash{"abcdefg", 100};
    EXPECT_EQ(728, hash_function<custom_hash_container>{}(custom_to_hash));

    custom_to_hash = {"abcdefghijk", 100};
    EXPECT_EQ(915, hash_function<custom_hash_container>{}(custom_to_hash));
}