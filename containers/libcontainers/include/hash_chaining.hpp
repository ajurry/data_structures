#pragma once
#include "hash_table.hpp"
#include "hash_function.hpp"
#include <list>

namespace libcontainers {
    template <typename T> class hash_chaining : public hash_table<T>
    {
        public:
        hash_chaining(size_t number_of_buckets = default_hash_table_size)
            : hash_array(new std::list<hash_node<T>>[number_of_buckets])
            , number_of_buckets(number_of_buckets)
        {
        }

        ~hash_chaining() override 
        {
            delete[] hash_array;
        }

        T* search(const size_t key) override {return nullptr;}
        T* insert(const T& data) override {return nullptr;}
        bool remove(const T& data) override {return false;}

        private:
        std::list<hash_node<T>>* hash_array;
        size_t number_of_buckets;
    };
};