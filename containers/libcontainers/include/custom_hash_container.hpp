#pragma once
#include "hash_function.hpp"
#include <string>

struct custom_hash_container {
    std::string string_info;
    int numeric_info;
};

// Custom container hash function
template<> struct libcontainers::hash_function<custom_hash_container>
{
    size_t operator()(const custom_hash_container& data)
    {
        size_t ret = 0;

        ret = hash_function<std::string>{}(data.string_info);
        ret ^= hash_function<int>{}(data.numeric_info);

        return ret;
    }
};