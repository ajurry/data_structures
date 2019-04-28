#pragma once
#include <string>
#include <exception>

namespace libcontainers {

    template<typename T> struct hash_function
    {
        size_t operator()(const T& data)
        {
            throw std::runtime_error("Please implement a valid hash function");
        }
    };

    // Basic int hash function
    template<> struct hash_function<int>
    {        
        size_t operator()(int data)
        {
            return data;
        }
    };

    // Basic string hash function
    template<> struct hash_function<std::string>
    {
        size_t operator()(const std::string& data)
        {
            size_t ret = 0;

            int limit;
            data.size() < 10 ? limit = data.size() : limit = 10;
            for (auto i = 0; i < limit; ++i) {
                ret += int(data[i]);
            }

            return ret;
        }
    };

};