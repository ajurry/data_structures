#include "gtest/gtest.h"
#include "heap.hpp"
#include <string>
#include <vector>

using namespace libcontainers;

class HEAP : public::testing::Test {
    
    protected:
    void SetUp() override {
        for (size_t i = 0; i < total_data_points; ++i) 
        {
            data_points.push_back(heap_data_point<std::string>{
                    data_point_string + std::to_string(i),
                    i
                });
        }
    }

    void TearDown() override {}

    std::vector<heap_data_point<std::string>> data_points;
    size_t total_data_points = 100;
    std::string data_point_string = "TEST_";
};

TEST_F(HEAP, test_creation) {

    binary_max_heap<std::string> max_heap;
    
    EXPECT_EQ(max_heap.size(), 0);
    EXPECT_EQ(max_heap.is_empty(), true);
}

TEST_F (HEAP, test_size_and_empty) {

    binary_max_heap<std::string> max_heap;
    EXPECT_EQ(max_heap.is_empty(), true);
    EXPECT_EQ(max_heap.size(), 0);

    for (size_t index = 0; index < data_points.size(); ++index) {
        max_heap.insert(data_points[index]);
        EXPECT_EQ(max_heap.size(), index + 1);
    }

    EXPECT_EQ(max_heap.is_empty(), false);
}

TEST_F (HEAP, test_insert_and_extract) {
        
    binary_max_heap<std::string> max_heap;
    std::random_shuffle(data_points.begin(), data_points.end());

    for (const auto& data_point : data_points) {
        max_heap.insert(data_point);
    }

    EXPECT_EQ(max_heap.size(), data_points.size());
    std::sort(data_points.rbegin(), data_points.rend());

    for (const auto& data_point : data_points) {
        std::string max = max_heap.extract_max();
        EXPECT_EQ(max, data_point.data);
    }

    EXPECT_EQ(max_heap.size(), 0);
    EXPECT_EQ(max_heap.is_empty(), true);
}

TEST_F(HEAP, test_replace) {

    binary_max_heap<std::string> max_heap;
    std::random_shuffle(data_points.begin(), data_points.end());

    for (const auto& data_point : data_points) {
        max_heap.insert(data_point);
    }

    EXPECT_EQ(max_heap.size(), data_points.size());
    std::sort(data_points.rbegin(), data_points.rend());

    data_points[0] = heap_data_point<std::string>{"TEST_" + std::to_string(10), 10};
    max_heap.replace(data_points[0]);

    data_points[1] = heap_data_point<std::string>{"TEST_" + std::to_string(total_data_points*2),
                                                    total_data_points*2};
    max_heap.replace(data_points[1]);

    std::sort(data_points.rbegin(), data_points.rend());

    for (const auto& data_point : data_points) {
        std::string max = max_heap.extract_max();
        EXPECT_EQ(max, data_point.data);
    }

    EXPECT_EQ(max_heap.size(), 0);
    EXPECT_EQ(max_heap.is_empty(), true);
}

TEST_F(HEAP, test_delete_max) {

    binary_max_heap<std::string> max_heap;
    std::random_shuffle(data_points.begin(), data_points.end());

    for (const auto& data_point : data_points) {
        max_heap.insert(data_point);
    }

    EXPECT_EQ(max_heap.size(), data_points.size());
    std::sort(data_points.rbegin(), data_points.rend());

    for (const auto& data_point : data_points) {
        max_heap.delete_max();
    }

    EXPECT_EQ(max_heap.size(), 0);
    EXPECT_EQ(max_heap.is_empty(), true);
}