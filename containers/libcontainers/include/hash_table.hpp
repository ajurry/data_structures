#pragma once

namespace libcontainers {

    static const size_t default_hash_table_size = 10;

    template<typename T> class hash_table {
        public:

        hash_table();
        virtual ~hash_table();

        virtual T* search(const size_t key) = 0;
        virtual T* insert(const T& data) = 0;
        virtual bool remove(const T& data) = 0;
    };

};