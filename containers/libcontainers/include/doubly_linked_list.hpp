#pragma once
#include <string>
#include <iostream>
#include "doubly_linked_list_iterator.hpp"

namespace libcontainers {

    template<typename T>
    class doubly_linked_list {
    public:
        // Construct null
        explicit doubly_linked_list();

        // Construct with point
        explicit doubly_linked_list(const T& data);

        // Prevent copying for the time being
        doubly_linked_list(const doubly_linked_list<T>&) = delete;
        doubly_linked_list<T>& operator=(const doubly_linked_list<T>&) = delete;

        // Bidirectional forward iterators
        typedef doubly_linked_list_iterator<T> iterator;
        typedef doubly_linked_list_iterator<const T> const_iterator;

        // Get begin iterator
        iterator begin() {return iterator(head_node);}

        // Get end iterator
        iterator end() {return iterator(tail_node);}

        // Enable moving
        doubly_linked_list(doubly_linked_list<T>&&) = default;
        doubly_linked_list<T>& operator=(doubly_linked_list<T>&&) = default;

        // Delete all entries in list
        ~doubly_linked_list();

        // Size queries
        bool empty();
        size_t size();
        
        // Clearing queries
        void clear();

        // Insertion queries
        void insert(const T& data);
        void push_back(const T& data);
        void push_front(const T& data);

        // Removal queries
        void remove(const T& data);

        // Searching queries
        void find(const T& data);

    private:
        // Start node
        node<T>* head_node;
        // End node
        node<T>* tail_node;
    };

    template<typename T> doubly_linked_list<T>::doubly_linked_list()
        : head_node(nullptr)
    {
        tail_node = new node<T>{head_node, nullptr};
    }

    template<typename T> doubly_linked_list<T>::doubly_linked_list(const T& data)
    {
        head_node = new node<T>{nullptr, tail_node, data};
        tail_node = new node<T>{head_node, nullptr};
        head_node->next = tail_node;
    }

    template<typename T> doubly_linked_list<T>::~doubly_linked_list()
    {
        clear();
    }

    template<typename T> void doubly_linked_list<T>::clear() {
        iterator iter = begin();
        while(iter.getConstPtr()->next != nullptr) {
            std::cout << *iter << std::endl;
            // delete ((iter++).getPtr());
            ++iter;
            std::cout << *iter << std::endl;
            std::cout << "ATTEMPTING TO DELETE" << std::endl;
        }
    }

    template<typename T> bool doubly_linked_list<T>::empty() {
        return head_node == nullptr;
    }

};