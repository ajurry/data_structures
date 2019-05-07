#pragma once
#include "hash_function.hpp"

namespace libcontainers {

    static const size_t default_hash_table_size = 10;

    template<typename T> struct hash_node {
        size_t key;
        T data;
    };

    template<typename T> class hash_table {
        public:

        hash_table() = default;
        virtual ~hash_table() = default;

        virtual T* search(const size_t key) = 0;
        virtual T* insert(const T& data) = 0;
        virtual bool remove(const T& data) = 0;

        protected:
        size_t create_hash_value(const T& data)
        {
            size_t hash_value = libcontainers::hash_function<T>{}(data);
            return hash_value;
        }
    };

};