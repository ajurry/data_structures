#pragma once

namespace libcontainers {

    static const size_t default_stack_size = 10;

    template <typename T> class stack  {

        public:
            explicit stack()
            : storage_array(new T[default_stack_size])
            , current_size(0)
            , max_size(default_stack_size)
            {}

            explicit stack(size_t starting_size)
            : storage_array(new T[starting_size])
            , current_size(0)
            , max_size(starting_size)
            {}

            ~stack()
            {
                delete[] storage_array;
                storage_array = nullptr;
            }

            stack<T>(const stack<T>& copy)
            {
                current_size = copy.current_size;
                max_size = copy.max_size;

                storage_array = new T[max_size];

                for (size_t i = 0; i < max_size; ++i) {
                    storage_array[i] = copy.storage_array[i];
                }
            }

            stack<T>& operator=(const stack<T>& copy)
            {
                current_size = copy.current_size;
                max_size = copy.max_size;

                storage_array = new T[max_size];

                for (size_t i = 0; i < max_size; ++i) {
                    storage_array[i] = copy.storage_array[i];
                }

                return *this;
            }

            stack<T>(stack<T>&& moved)
            {
                current_size = moved.current_size;
                max_size = moved.max_size;
                storage_array = moved.storage_array;
                moved.reset();
            }

            stack<T>& operator=(stack<T>&& moved)
            {
                current_size = moved.current_size;
                max_size = moved.max_size;
                storage_array = moved.storage_array;
                moved.reset();

                return *this;
            }

            T peek()
            {
                T ret;

                if (current_size != 0) {
                    ret = storage_array[current_size - 1];
                }

                return ret;
            }

            T pop()
            {
                T ret;

                if (current_size != 0) {
                    ret = storage_array[current_size - 1];
                    storage_array[current_size - 1] = 0;
                }

                --current_size;
                return ret;
            }

            void push(const T& data)
            {
                if (current_size == max_size) {
                    expand_storage_array();
                }

                storage_array[current_size] = data;
                ++current_size;
            }

            size_t size(){return current_size;};
            size_t array_size(){return max_size;};

        private:
            void reset()
            {
                storage_array = nullptr;
                current_size = 0;
                max_size = 0;
            }

            void expand_storage_array()
            {
                T* new_storage_array = new T[max_size * 2];
                for (int i = 0; i < max_size; ++i) {
                    new_storage_array[i] = storage_array[i];
                }
                delete[] storage_array;
                storage_array = new_storage_array;
                max_size *= 2;
            }

            T* storage_array;
            size_t current_size;
            size_t max_size;
    };

};