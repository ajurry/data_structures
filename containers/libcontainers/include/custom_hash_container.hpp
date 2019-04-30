#pragma once
#include "hash_function.hpp"
#include <string>

struct custom_key {
    std::string string_key;
    int numeric_key;

    bool operator==(custom_key comparison)
    {
        return (string_key == comparison.string_key && numeric_key == comparison.numeric_key);
    }
};

struct custom_hash_container {
    std::string stored_data;
    custom_key key;

    bool operator==(custom_hash_container comparison)
    {
        return (key == comparison.key);
    }
};

// Custom container hash function
template<> struct libcontainers::hash_function<custom_key>
{
    size_t operator()(const custom_key& data)
    {
        size_t ret = 0;

        ret = hash_function<std::string>{}(data.string_key);
        ret ^= hash_function<int>{}(data.numeric_key);

        return ret;
    }
};

// Custom container hash function
template<> struct libcontainers::hash_function<custom_hash_container>
{
    size_t operator()(const custom_hash_container& data)
    {
        size_t ret = 0;
        ret = hash_function<custom_key>{}(data.key);
        return ret;
    }
};