#pragma once
#include "hash_table.hpp"
#include "hash_function.hpp"

namespace libcontainers {
    template <typename T> class hash_open : public hash_table<T>
    {
        public:
        hash_open(size_t number_of_buckets = default_hash_table_size)
            : hash_array(new hash_node<T>*[number_of_buckets])
            , number_of_buckets(number_of_buckets)
        {
            null_hash_array();
        }

        ~hash_open() override 
        {
            delete_current_hash_array();
        }

        T* search(const size_t key) override 
        {
            T* ret = nullptr;

            size_t normalised_hash_value = normalise_hash_value(key);
            size_t original_normalised_hash_value = normalised_hash_value;

            do 
            {
                if (normalised_hash_value == number_of_buckets) {
                    normalised_hash_value = 0;
                }

                if (hash_array[normalised_hash_value] != nullptr) {
                    if (hash_array[normalised_hash_value]->key == key) {
                        ret = &hash_array[normalised_hash_value]->data;
                        break;
                    }
                }

                ++normalised_hash_value;
            }
            while (normalised_hash_value != original_normalised_hash_value);

            return ret;
        }

        T* insert(const T& data) override 
        {
            T* ret = nullptr;
            
            size_t hash_value = create_hash_value(data);
            size_t normalised_hash_value = normalise_hash_value(hash_value);
            size_t original_normalised_hash_value = normalised_hash_value;
            ret = attempt_to_insert(data, normalised_hash_value);

            while(ret == nullptr) {

                ++normalised_hash_value;

                if (normalised_hash_value == original_normalised_hash_value) {
                    resize_and_reallocate();
                    hash_value = create_hash_value(data);
                    normalised_hash_value = normalise_hash_value(hash_value);
                    original_normalised_hash_value = normalised_hash_value;
                }

                if (normalised_hash_value == number_of_buckets) {
                    normalised_hash_value = 0;
                }

                ret = attempt_to_insert(data, normalised_hash_value);
            }

            return ret;    
        }

        bool remove(const T& data) override 
        {
            bool ret = false;

            hash_node<T>* data_point = nullptr;
            size_t hash_value = hash_function<T>{}(data);
            size_t normalised_hash_value = normalise_hash_value(hash_value);
            size_t original_normalised_hash_value = normalised_hash_value;
            
            do 
            {
                if (normalised_hash_value == number_of_buckets) {
                    normalised_hash_value = 0;
                }

                if (hash_array[normalised_hash_value] != nullptr) {
                    if (hash_array[normalised_hash_value]->key == hash_value) {
                        data_point = hash_array[normalised_hash_value];
                        break;
                    }
                }

                ++normalised_hash_value;
            }
            while (normalised_hash_value != original_normalised_hash_value);

            if (data_point != nullptr) {
                delete hash_array[normalised_hash_value];
                hash_array[normalised_hash_value] = nullptr;
                ret = true;
            }

            return ret;
        }
        
        private:
        void null_hash_array()
        {
            for (auto index = 0; index < number_of_buckets; ++index) 
            {
                hash_array[index] = nullptr;
            }
        }

        void delete_current_hash_array()
        {
            delete_hash_array(hash_array, number_of_buckets);
        }

        void delete_hash_array(hash_node<T>** hash_array, size_t number_of_buckets)
        {
            for (auto index = 0; index < number_of_buckets; ++index) 
            {
                if (hash_array[index] != nullptr) {
                    delete hash_array[index];
                    hash_array[index] = nullptr;
                }
            }

            delete[] hash_array;
        }

        void resize_and_reallocate()
        {
            size_t previous_number_of_buckets = number_of_buckets;
            number_of_buckets *= 2;

            hash_node<T>** previous_hash_array = hash_array;
            hash_array = new hash_node<T>*[number_of_buckets];
            null_hash_array();

            for (int i = 0; i < previous_number_of_buckets; ++i) {
                insert(previous_hash_array[i]->data);
            }

            delete_hash_array(previous_hash_array, previous_number_of_buckets);
        }

        T* attempt_to_insert(const T& data, const size_t normalised_hash_value)
        {
            T* ret = nullptr;

            if (hash_array[normalised_hash_value] == nullptr) {
                hash_array[normalised_hash_value] = new hash_node<T>{create_hash_value(data), data};
                ret = &(hash_array[normalised_hash_value]->data);
            }
            else if (create_hash_value(hash_array[normalised_hash_value]->data) == create_hash_value(data)) {
                hash_array[normalised_hash_value]->data = data;
                ret = &(hash_array[normalised_hash_value]->data);
            }

            return ret;
        }

        size_t create_hash_value(const T& data)
        {
            size_t hash_value = libcontainers::hash_function<T>{}(data);
            return hash_value;
        }

        size_t normalise_hash_value(size_t hash_value)
        {
            return (hash_value % number_of_buckets);
        }

        hash_node<T>** hash_array;
        size_t number_of_buckets;
    };
};