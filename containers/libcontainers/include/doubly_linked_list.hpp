#pragma once
#include <string>
#include <iostream>
#include "doubly_linked_list_iterator.hpp"

namespace libcontainers {

/*     template<typename T>
    class doubly_linked_list {
    public:
        // Construct null
        explicit doubly_linked_list();

        // Construct with point
        explicit doubly_linked_list(const T& data);

        // Prevent copying for the time being
        doubly_linked_list(const doubly_linked_list&) = delete;
        doubly_linked_list operator=(const doubly_linked_list&) = delete;

        // Bidirectional forward iterators
        typedef doubly_linked_list_iterator<T> iterator;
        typedef doubly_linked_list_iterator<const T> const_iterator;

        // Enable moving
        doubly_linked_list(doubly_linked_list&&) = default;
        doubly_linked_list operator=(doubly_linked_list&&) = default;

        // Delete all entries in list
        explicit ~doubly_linked_list();

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
        void rfind(const T& data);
    private:
        // Start node
        node* head_node;
        // End node
        node* tail_node;
    };

    template<typename T> doubly_linked_list<T>::doubly_linked_list()
    : head_node(nullptr)
    , tail_node(nullptr)
    {
    }

    template<typename T> doubly_linked_list<T>::doubly_linked_list(const T& data)
    : tail_node(nullptr)
    {
        head_node = new node<T>(nullptr, tail_node, data);
    }

    template<typename T> doubly_linked_list<T>::~doubly_linked_list()
    {
        // WOULD USE AN ITERATOR
    } */

};