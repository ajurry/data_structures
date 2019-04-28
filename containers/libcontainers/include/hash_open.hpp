#pragma once
#include "hash.hpp"
#include "hash_function.hpp"

namespace libcontainers {
    template <typename T> class hash_open : public hash_table<T>
    {
        public:
        hash_open(size_t number_of_buckets = default_hash_table_size)
            : hash_array(new T[number_of_buckets])
            , number_of_buckets(number_of_buckets)
        {
        }

        ~hash_open() override 
        {
            delete[] hash_array;
        }

        T* search(const size_t key) override {return nullptr;}
        T* insert(const T& data) override {return nullptr;}
        bool remove(const T& data) override {return false;}

        private:
        T* hash_array;
        size_t number_of_buckets;
    };
};