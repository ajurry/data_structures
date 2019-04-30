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

    public:
    int max_size = 10;
    int total_size = 15;
    int test_numbers[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    std::string test_strings[15] = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
};

TEST_F(HASH_TABLE, test_creation) {

//    std::unique_ptr<hash_table<custom_hash_container>> test_chaining(
//        new hash_chaining<custom_hash_container>);

    std::unique_ptr<hash_table<custom_hash_container>> test_open(
        new hash_open<custom_hash_container>);
}

TEST_F(HASH_TABLE, test_insertion_and_searching_not_exceeding) {

    std::unique_ptr<hash_table<int>> test_open_int(new hash_open<int>);
    EXPECT_EQ(*test_open_int->insert(test_numbers[0]), test_numbers[0]);
    EXPECT_EQ(*test_open_int->insert(test_numbers[1]), test_numbers[1]);
    EXPECT_EQ(*test_open_int->insert(test_numbers[11]), test_numbers[11]);

    std::unique_ptr<hash_table<custom_hash_container>> test_open_custom(
        new hash_open<custom_hash_container>);

    custom_hash_container first_container{"test_data_one", test_strings[3], test_numbers[7]};
    custom_hash_container second_container{"test_data_two", test_strings[1], test_numbers[1]};
    custom_hash_container third_container{"test_data_three", test_strings[1], test_numbers[1]};

    EXPECT_EQ(test_open_custom->insert(first_container)->stored_data, first_container.stored_data);

    custom_hash_container* inserted_data = test_open_custom->insert(second_container);
    EXPECT_EQ(inserted_data->stored_data, second_container.stored_data);

    test_open_custom->insert(third_container);
    EXPECT_EQ(inserted_data->stored_data, third_container.stored_data);

    EXPECT_EQ(*test_open_int->search(hash_function<int>{}(test_numbers[0])), test_numbers[0]);
    EXPECT_EQ(*test_open_int->search(hash_function<int>{}(test_numbers[1])), test_numbers[1]);
    EXPECT_EQ(*test_open_int->search(hash_function<int>{}(test_numbers[11])), test_numbers[11]);

    EXPECT_EQ(test_open_custom->search(hash_function<custom_hash_container>{}(first_container))->stored_data
                , first_container.stored_data);

    EXPECT_EQ(test_open_custom->search(hash_function<custom_hash_container>{}(third_container))->stored_data
                , third_container.stored_data);

    EXPECT_EQ(test_open_custom->search(hash_function<custom_key>{}(third_container.key))->stored_data
                , third_container.stored_data);

    EXPECT_EQ(test_open_custom->search(hash_function<custom_key>{}(second_container.key))->stored_data
                , third_container.stored_data);
}

TEST_F(HASH_TABLE, test_insertion_and_searching_exceeding) {

    std::unique_ptr<hash_table<int>> test_open_int(new hash_open<int>(3));
    EXPECT_EQ(*test_open_int->insert(test_numbers[0]), test_numbers[0]);
    EXPECT_EQ(*test_open_int->insert(test_numbers[1]), test_numbers[1]);
    EXPECT_EQ(*test_open_int->insert(test_numbers[2]), test_numbers[2]);
    EXPECT_EQ(*test_open_int->insert(test_numbers[3]), test_numbers[3]);

    EXPECT_EQ(*test_open_int->search(hash_function<int>{}(test_numbers[0])), test_numbers[0]);
    EXPECT_EQ(*test_open_int->search(hash_function<int>{}(test_numbers[1])), test_numbers[1]);
    EXPECT_EQ(*test_open_int->search(hash_function<int>{}(test_numbers[2])), test_numbers[2]);
    EXPECT_EQ(*test_open_int->search(hash_function<int>{}(test_numbers[3])), test_numbers[3]);
}

TEST_F(HASH_TABLE, test_removing) {

    std::unique_ptr<hash_table<int>> test_open_int(new hash_open<int>);

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(*test_open_int->insert(test_numbers[i]), test_numbers[i]);
    }

    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(*test_open_int->search(hash_function<int>{}(test_numbers[i])), test_numbers[i]);
        EXPECT_EQ(test_open_int->remove(test_numbers[i]), true);
        EXPECT_EQ(test_open_int->search(hash_function<int>{}(test_numbers[i])), nullptr);
    }
}