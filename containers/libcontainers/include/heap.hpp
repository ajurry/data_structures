#pragma once

namespace libcontainers {

    size_t default_heap_size = 15;

    template<typename T> struct heap_data_point {
        T data;
        size_t priority = 0;

        bool operator<=(const heap_data_point& comparison){
            return this->priority <= comparison.priority;
        }

        bool operator<(const heap_data_point& comparison){
            return this->priority < comparison.priority;
        }

        bool operator>=(const heap_data_point& comparison){
            return this->priority >= comparison.priority;
        }

        bool operator>(const heap_data_point& comparison){
            return this->priority > comparison.priority;
        }
    };

    template<typename T> class binary_max_heap {
        public:
        binary_max_heap();
        ~binary_max_heap();

        void insert(const heap_data_point<T>& entry);
        void replace(const heap_data_point<T>& entry);
        void delete_max();
        T extract_max();

        size_t size();
        bool is_empty();

        private:
        void sift_up(const size_t current_position);
        void sift_down(const size_t current_position);
        void remove_max();
        size_t get_parent_position(const size_t current_position);
        size_t get_left_child(const size_t parent_position);
        size_t get_right_child(const size_t parent_position);
        void swap(const size_t first_position, const size_t second_position);
        void resize();

        heap_data_point<T>* heap_array;
        size_t heap_array_size;
        size_t current_size;
    };

    template<typename T>
    binary_max_heap<T>::binary_max_heap()
        : heap_array(new heap_data_point<T>[default_heap_size])
        , heap_array_size(default_heap_size)
        , current_size(0)
    {
        for (size_t index = 0; index < default_heap_size; ++index) {
            heap_array[index] = heap_data_point<T>();
        }
    }

    template<typename T>
    binary_max_heap<T>::~binary_max_heap()
    {
        delete[] heap_array;
        heap_array = nullptr;
    }

    template<typename T>
    void binary_max_heap<T>::insert(const heap_data_point<T>& entry)
    {
        if (current_size == heap_array_size) {
            resize();
        }

        heap_array[current_size] = entry;
        sift_up(current_size);
        ++current_size;
    }

    template<typename T>
    void binary_max_heap<T>::replace(const heap_data_point<T>& entry)
    {
        heap_array[0] = entry;
        sift_down(0);
    }

    template<typename T>
    void binary_max_heap<T>::delete_max()
    {
        if (current_size == 0) {
            return;
        }
        remove_max();
    }

    template<typename T>
    T binary_max_heap<T>::extract_max()
    {
        if (current_size == 0) {
            return NULL;
        }

        T max = heap_array[0].data;
        remove_max();
        return max;
    }

    template<typename T>
    void binary_max_heap<T>::remove_max()
    {
        heap_array[0] = heap_array[current_size - 1];
        heap_array[current_size - 1] = heap_data_point<T>();
        sift_down(0);
        --current_size;
    }

    template<typename T>
    size_t binary_max_heap<T>::size()
    {
        return current_size;
    }

    template<typename T>
    bool binary_max_heap<T>::is_empty()
    {
        return current_size == 0;
    }

    template<typename T>
    void binary_max_heap<T>::sift_up(const size_t current_position)
    {
        size_t parent_position = get_parent_position(current_position);
        if (heap_array[current_position] > heap_array[parent_position]) {
            swap(parent_position, current_position);
            sift_up(parent_position);
        }
    }

    template<typename T>
    void binary_max_heap<T>::sift_down(const size_t current_position)
    {
        size_t left_position = get_left_child(current_position);
        size_t right_position = get_right_child(current_position);

        if (left_position >= heap_array_size) {
            return;
        }

        bool left_bigger = heap_array[left_position] > heap_array[current_position];
        bool right_bigger = heap_array[right_position] > heap_array[current_position];

        if (left_bigger && right_bigger) {
            left_bigger = heap_array[left_position] > heap_array[right_position];

        }

        if (left_bigger) {
            swap(current_position, left_position);
            sift_down(left_position);
        }
        else if (right_bigger) {
            swap(current_position, right_position);
            sift_down(right_position);
        }
    }

    template<typename T>
    size_t binary_max_heap<T>::get_parent_position(const size_t current_position)
    {
        size_t parent_position = 0;

        if (current_position != 0) {
            size_t distance_to_parent = (current_position / 2) + 1;
            parent_position = current_position - distance_to_parent;
        }

        return parent_position;
    }

    template<typename T>
    size_t binary_max_heap<T>::get_left_child(const size_t parent_position)
    {
        return (2 * parent_position) + 1;
    }

    template<typename T>
    size_t binary_max_heap<T>::get_right_child(const size_t parent_position)
    {
        return (2 * parent_position) + 2;
    }

    template<typename T>
    void binary_max_heap<T>::swap(const size_t first_position, const size_t second_position)
    {
        heap_data_point<T> temp = heap_array[first_position];
        heap_array[first_position] = heap_array[second_position];
        heap_array[second_position] = temp;
    }

    template<typename T>
    void binary_max_heap<T>::resize()
    {
        size_t new_heap_array_size = heap_array_size * 2;
        heap_data_point<T>* new_heap_array = new heap_data_point<T>[new_heap_array_size];

        for (size_t i = 0; i < heap_array_size; ++i) {
            new_heap_array[i] = heap_array[i];
        }

        for (size_t i = heap_array_size; i < new_heap_array_size; ++i) {
            new_heap_array[i] = heap_data_point<T>();
        }

        delete[] heap_array;
        
        heap_array_size = new_heap_array_size;
        heap_array = new_heap_array;
    }
};