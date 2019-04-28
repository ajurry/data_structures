#include "gtest/gtest.h"
#include "hash_function.hpp"
#include "hash_table.hpp"
#include "hash_chaining.hpp"
#include "hash_open.hpp"
#include "custom_hash_container.hpp"

#include <iostream>
#include <memory>

using namespace libcontainers;

class HASH_TABLE : public::testing::Test {
};

TEST_F(HASH_TABLE, test_int) {

    std::unique_ptr<hash_table<custom_hash_container>> test_chaining(
        new hash_chaining<custom_hash_container>);

    std::unique_ptr<hash_table<custom_hash_container>> test_open(
        new hash_open<custom_hash_container>);
}