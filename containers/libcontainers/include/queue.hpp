#pragma once

namespace libcontainers {

    static const size_t default_queue_size = 10;

    template<typename T> class queue {
        public:

        explicit queue() 
        : storage_array(new T[default_queue_size])
        , start_position(0)
        , end_position(0)
        , current_size(0)
        , max_size(default_queue_size)
        {}

        explicit queue(size_t starting_size)
        : storage_array(new T[starting_size])
        , start_position(0)
        , end_position(0)
        , current_size(0)
        , max_size(starting_size)
        {}

        ~queue()
        {
            delete[] storage_array;
        }

        queue<T>(const queue<T>& copy)
        {
            start_position = copy.start_position;
            end_position = copy.end_position;
            max_size = copy.max_size;
            current_size = copy.current_size;
            storage_array = new T[copy.max_size];

            for (size_t i = 0; i < copy.max_size; ++i) {
                storage_array[i] = copy.storage_array[i];
            }
        }

        queue<T>& operator=(const queue<T>& copy)
        {
            start_position = copy.start_position;
            end_position = copy.end_position;
            max_size = copy.max_size;
            current_size = copy.current_size;
            storage_array = new T[copy.max_size];

            for (size_t i = 0; i < copy.max_size; ++i) {
                storage_array[i] = copy.storage_array[i];
            }

            return *this;
        }

        queue<T>(queue<T>&& moved)
        {
            start_position = moved.start_position;
            end_position = moved.end_position;
            max_size = moved.max_size;
            current_size = moved.current_size;
            storage_array = moved.storage_array;

            moved.reset();
        }
        
        queue<T>& operator=(queue<T>&& moved)
        {
            start_position = moved.start_position;
            end_position = moved.end_position;
            max_size = moved.max_size;
            current_size = moved.current_size;
            storage_array = moved.storage_array;
            moved.reset();

            return *this;
        }

        void enqueue(const T& data) {

            if (current_size == max_size) {
                T* new_storage_array = new T[max_size * 2];

                for (size_t i = start_position; i < max_size; ++i) {
                    int test_val = storage_array[i];
                    new_storage_array[i - start_position] = storage_array[i];
                }

                if (end_position != max_size) {
                    for (size_t i = 0; i <= end_position; ++i) {
                        int test_val = storage_array[i];
                        new_storage_array[i + end_position - 1] = storage_array[i];
                    }
                }

                start_position = 0;
                end_position = current_size;
                max_size *= 2;

                delete[] storage_array;
                storage_array = new_storage_array;
            }
            else if (end_position == max_size) {
                end_position = 0;
            }

            storage_array[end_position] = data;
            ++end_position;
            ++current_size;
        }

        T dequeue() {
            T ret;

            if (current_size != 0) {
    
                if (start_position == max_size) {
                    start_position = 0;
                }

                ret = storage_array[start_position];
                storage_array[start_position] = 0;
                ++start_position;
                --current_size;
            }

            return ret;
        };

        T peek() {
            T ret;

            if (current_size != 0) {
                ret = storage_array[start_position];
            }

            return ret;
        };

        size_t size() {return current_size;}
        size_t array_size() {return max_size;}

        private:
        void reset() {
            storage_array = new T[default_queue_size];
            max_size = default_queue_size;
            start_position = 0;
            end_position = 0;
            current_size = 0;
        }


        T* storage_array;

        size_t start_position;
        size_t end_position;
        size_t current_size;
        size_t max_size;
    };

};