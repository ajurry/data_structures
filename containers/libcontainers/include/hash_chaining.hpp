#pragma once
#include "hash_table.hpp"
#include <forward_list>

namespace libcontainers {
    template <typename T> class hash_chaining : public hash_table<T>
    {
        public:
        hash_chaining(size_t number_of_buckets = default_hash_table_size)
            : hash_array(new std::forward_list<hash_node<T>*>[number_of_buckets])
            , number_of_buckets(number_of_buckets)
        {
        }

        ~hash_chaining() override 
        {
            for (auto index = 0; index < number_of_buckets; ++index) {

                if (!hash_array[index].empty()) {
                    for (auto& node : hash_array[index]) {
                        delete node;
                        node = nullptr;
                    }
                }
            }

            delete[] hash_array;
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

                if (!hash_array[normalised_hash_value].empty()) {
                    for (hash_node<T>* node_iter : hash_array[normalised_hash_value]) {
                        if (node_iter->key == key) {
                            ret = &node_iter->data;
                            break;
                        }
                    }

                    if (ret != nullptr) {
                        break;
                    }
                }

                if (normalised_hash_value == original_normalised_hash_value) {
                    break;
                }
                else {
                    ++normalised_hash_value;
                }
            }
            while (normalised_hash_value != original_normalised_hash_value);

            return ret;
        }

        T* insert(const T& data) override 
        {
            T* ret = nullptr;

            size_t hash_value = this->create_hash_value(data);
            size_t normalised_hash_value = normalise_hash_value(hash_value);

            hash_node<T>* node;
            if (!hash_array[normalised_hash_value].empty()) {

                bool found = false;
                for (hash_node<T>* node_iter : hash_array[normalised_hash_value]) {
                    if (node_iter->key == hash_value) {
                        node = node_iter;
                        found = true;
                    }
                }

                if (!found) {
                    node = new hash_node<T>{hash_value, data};
                    hash_array[normalised_hash_value].push_front(node);
                }
                else {
                    node->data = data;
                }
            }
            else {
                node = new hash_node<T>{hash_value, data};
                hash_array[normalised_hash_value].push_front(node);
            }

            ret = &node->data;

            return ret;
        }

        bool remove(const T& data) override 
        {
            bool ret = false;

            size_t hash_value = hash_function<T>{}(data);
            size_t normalised_hash_value = normalise_hash_value(hash_value);
            size_t original_normalised_hash_value = normalised_hash_value;

            do
            {
                if (!hash_array[normalised_hash_value].empty()) {
                    for (auto iter = hash_array[normalised_hash_value].begin();
                            iter != hash_array[normalised_hash_value].end();
                            ++iter)
                    {
                        if ((*iter)->key == hash_value) {
                            hash_array[normalised_hash_value].remove_if (
                                [&] (hash_node<T>* node) {
                                    return node->key == hash_value;
                                }
                            );
                            delete *iter;
                            ret = true;
                            break;
                        }
                    }

                    if (ret == true) {
                        break;
                    }
                }

                if (normalised_hash_value == original_normalised_hash_value) {
                    break;
                }
                else {
                    ++normalised_hash_value;
                }
            } 
            while (normalised_hash_value != original_normalised_hash_value);

            return ret;      
        }

        private:

        size_t normalise_hash_value(size_t hash_value)
        {
            return (hash_value % number_of_buckets);
        }

        std::forward_list<hash_node<T>*>* hash_array;
        size_t number_of_buckets;
    };
};