#include "gtest/gtest.h"
#include "hash_function.hpp"
#include "hash_table.hpp"
#include "hash_chaining.hpp"
#include "hash_open.hpp"
#include "custom_hash_container.hpp"

#include <iostream>
#include <memory>

using namespace libcontainers;

template<typename T>
class HASH_TABLE : public::testing::Test {
    public:
    int test_numbers[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    std::string test_strings[15] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "k", "l", "m", "n", "o", "p"};
};

typedef testing::Types<hash_open<custom_hash_container>, hash_chaining<custom_hash_container>> hash_container_type;

TYPED_TEST_CASE(HASH_TABLE, hash_container_type);

TYPED_TEST(HASH_TABLE, test_creation) {

    std::unique_ptr<hash_table<custom_hash_container>> test_hash_table(
        new TypeParam);
}

TYPED_TEST(HASH_TABLE, test_insertion_and_searching_not_exceeding) {
    std::unique_ptr<hash_table<custom_hash_container>> test_open_custom(
        new TypeParam);

    custom_hash_container first_container{"test_data_one", TestFixture::test_strings[3], TestFixture::test_numbers[7]};
    custom_hash_container second_container{"test_data_two", TestFixture::test_strings[1], TestFixture::test_numbers[1]};
    custom_hash_container third_container{"test_data_three", TestFixture::test_strings[1], TestFixture::test_numbers[1]};
    custom_hash_container absent_container{"test_data_absent", TestFixture::test_strings[5], TestFixture::test_numbers[2]};

    EXPECT_EQ(test_open_custom->insert(first_container)->stored_data, first_container.stored_data);

    custom_hash_container* inserted_data = test_open_custom->insert(second_container);
    EXPECT_EQ(inserted_data->stored_data, second_container.stored_data);

    test_open_custom->insert(third_container);
    EXPECT_EQ(inserted_data->stored_data, third_container.stored_data);

    EXPECT_EQ(test_open_custom->search(hash_function<custom_hash_container>{}(first_container))->stored_data
                , first_container.stored_data);

    EXPECT_EQ(test_open_custom->search(hash_function<custom_hash_container>{}(third_container))->stored_data
                , third_container.stored_data);

    EXPECT_EQ(test_open_custom->search(hash_function<custom_key>{}(third_container.key))->stored_data
                , third_container.stored_data);

    EXPECT_EQ(test_open_custom->search(hash_function<custom_key>{}(second_container.key))->stored_data
                , third_container.stored_data);

    EXPECT_EQ(test_open_custom->search(hash_function<custom_hash_container>{}(absent_container))
                , nullptr);
}

TYPED_TEST(HASH_TABLE, test_insertion_and_searching_exceeding) {

    std::unique_ptr<hash_table<custom_hash_container>> test_open_custom(new TypeParam);

    custom_hash_container first_container{"test_data_one", TestFixture::test_strings[3], TestFixture::test_numbers[1]};
    custom_hash_container second_container{"test_data_two", TestFixture::test_strings[2], TestFixture::test_numbers[2]};
    custom_hash_container third_container{"test_data_three", TestFixture::test_strings[5], TestFixture::test_numbers[3]};
    custom_hash_container fourth_container{"test_data_fourth", TestFixture::test_strings[5], TestFixture::test_numbers[7]};

    EXPECT_EQ(test_open_custom->insert(first_container)->stored_data, first_container.stored_data);
    EXPECT_EQ(test_open_custom->insert(second_container)->stored_data, second_container.stored_data);
    EXPECT_EQ(test_open_custom->insert(third_container)->stored_data, third_container.stored_data);
    EXPECT_EQ(test_open_custom->insert(fourth_container)->stored_data, fourth_container.stored_data);

    EXPECT_EQ(test_open_custom->search(hash_function<custom_hash_container>{}(first_container))->stored_data
                , first_container.stored_data);

    EXPECT_EQ(test_open_custom->search(hash_function<custom_hash_container>{}(second_container))->stored_data
                , second_container.stored_data);

    EXPECT_EQ(test_open_custom->search(hash_function<custom_hash_container>{}(third_container))->stored_data
                , third_container.stored_data);

    EXPECT_EQ(test_open_custom->search(hash_function<custom_hash_container>{}(fourth_container))->stored_data
                , fourth_container.stored_data);
    
}

TYPED_TEST(HASH_TABLE, test_removing) {

    std::unique_ptr<hash_table<custom_hash_container>> test_open_custom(new TypeParam);
    custom_hash_container first_container{"test_data_one", TestFixture::test_strings[3], TestFixture::test_numbers[1]};
    custom_hash_container second_container{"test_data_two", TestFixture::test_strings[2], TestFixture::test_numbers[2]};
    custom_hash_container third_container{"test_data_three", TestFixture::test_strings[5], TestFixture::test_numbers[3]};
    custom_hash_container fourth_container{"test_data_fourth", TestFixture::test_strings[5], TestFixture::test_numbers[7]};

    EXPECT_EQ(test_open_custom->insert(first_container)->stored_data, first_container.stored_data);
    EXPECT_EQ(test_open_custom->insert(second_container)->stored_data, second_container.stored_data);
    EXPECT_EQ(test_open_custom->insert(third_container)->stored_data, third_container.stored_data);
    EXPECT_EQ(test_open_custom->insert(fourth_container)->stored_data, fourth_container.stored_data);

    EXPECT_EQ(test_open_custom->search(hash_function<custom_hash_container>{}(first_container))->stored_data
        , first_container.stored_data);
    EXPECT_EQ(test_open_custom->remove(first_container), true);
    EXPECT_EQ(test_open_custom->search(hash_function<custom_hash_container>{}(first_container))
        , nullptr);

    EXPECT_EQ(test_open_custom->search(hash_function<custom_hash_container>{}(second_container))->stored_data
        , second_container.stored_data);
    EXPECT_EQ(test_open_custom->remove(second_container), true);
    EXPECT_EQ(test_open_custom->search(hash_function<custom_hash_container>{}(second_container))
        , nullptr);

    EXPECT_EQ(test_open_custom->search(hash_function<custom_hash_container>{}(third_container))->stored_data
        , third_container.stored_data);
    EXPECT_EQ(test_open_custom->remove(third_container), true);
    EXPECT_EQ(test_open_custom->search(hash_function<custom_hash_container>{}(third_container))
        , nullptr);

    EXPECT_EQ(test_open_custom->search(hash_function<custom_hash_container>{}(fourth_container))->stored_data
        , fourth_container.stored_data);
    EXPECT_EQ(test_open_custom->remove(fourth_container), true);
    EXPECT_EQ(test_open_custom->search(hash_function<custom_hash_container>{}(fourth_container))
        , nullptr);
}