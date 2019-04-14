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

        // Prevent copying for the time being
        doubly_linked_list(const doubly_linked_list<T>&) = delete;
        doubly_linked_list<T>& operator=(const doubly_linked_list<T>&) = delete;

        // Bidirectional forward iterators
        typedef doubly_linked_list_iterator<T> iterator;
        typedef doubly_linked_list_iterator<const T> const_iterator;

        // Get begin iterator
        iterator begin() {return iterator(head_node);}

        // Get end iterator
        iterator end() {if (entries != 0){ return iterator(sentinal_node);} else {return iterator(tail_node);}}

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
        iterator insert(const iterator& insert_position, const T& data);
        void push_back(const T& data);
        void push_front(const T& data);

        // Removal queries
        void erase(const iterator& erase_position);
        void pop_back();
        void pop_front();

        // Searching queries
        void find(const T& data);

    private:
        // Initial node insertion
        void intial_insertion(node<T>* new_node);

    private:
        // Start node
        node<T>* head_node;
        // End node
        node<T>* tail_node;
        // Sentinal node
        node<T>* sentinal_node;
        // Size count
        size_t entries;
    };

    template<typename T> 
    doubly_linked_list<T>::doubly_linked_list()
        : head_node(nullptr)
        , entries(0)
    {
        head_node = tail_node = nullptr;
        // Using this to implement std::begin and std::end
        sentinal_node = new node<T> {head_node, tail_node};
    }

    template<typename T> 
    doubly_linked_list<T>::~doubly_linked_list()
    {
         clear();
         delete(sentinal_node);
    }

    template<typename T> 
    void doubly_linked_list<T>::clear() {
        iterator iter = begin();
        while(iter != end()) {
            iterator temp = iter++;
            delete ((temp).getPtr());
        }

        entries = 0;
    }

    template<typename T> 
    bool doubly_linked_list<T>::empty() {
        return entries == 0;
    }

    template<typename T> 
    size_t doubly_linked_list<T>::size() {
        return entries;
    }

    template<typename T> 
    void doubly_linked_list<T>::intial_insertion(node<T>* new_node) {
            new_node->next = sentinal_node;
            new_node->prev = sentinal_node;
            head_node = tail_node = new_node;
            sentinal_node->next = head_node;
            sentinal_node->prev = tail_node;
    }

    template<typename T>
    void doubly_linked_list<T>::push_back(const T& data) {
        node<T>* new_node = new node<T>{nullptr, nullptr, data};

        if (head_node == nullptr) {
            intial_insertion(new_node);
        }
        else {
            new_node->next = sentinal_node;
            new_node->prev = tail_node;

            tail_node->next = new_node;
            tail_node = new_node;

            sentinal_node->prev = tail_node;
        }

        ++entries;
    }

    template<typename T>
    void doubly_linked_list<T>::push_front(const T& data) {
        node<T>* new_node = new node<T>{nullptr, nullptr, data};

        if (head_node == nullptr) {
            intial_insertion(new_node);
        }
        else {
            new_node->prev = sentinal_node;
            new_node->next = head_node;

            head_node->prev = new_node;
            head_node = new_node;

            sentinal_node->next = head_node;
        }

        ++entries;
    }

    template<typename T>
    void doubly_linked_list<T>::pop_back() {

        if (tail_node == head_node) {
            delete(tail_node);
            tail_node = head_node = nullptr;
        }
        else {
            node<T>* temporary_node = tail_node->prev;
            temporary_node->next = sentinal_node;
            delete(tail_node);

            temporary_node->next = sentinal_node;
            tail_node = temporary_node;
        }

        --entries;
    }

    template<typename T>
    void doubly_linked_list<T>::pop_front() {

        if (tail_node == head_node) {
            delete(head_node);
            tail_node = head_node = nullptr;
        }
        else {
            node<T>* temporary_node = head_node->next;
            temporary_node->prev = sentinal_node;
            delete(head_node);

            temporary_node->prev = sentinal_node;
            head_node = temporary_node;
        }

        --entries;
    }

    template<typename T> typename
    doubly_linked_list<T>::iterator doubly_linked_list<T>::insert(
        const iterator& insert_position, const T& data
        )
    {
        iterator ret;

        if (head_node == nullptr) {
            node<T>* new_node = new node<T>{nullptr, nullptr, data};
            intial_insertion(new_node);
            ret = begin();
            ++entries;
        }
        else if (insert_position == begin()) {
            push_front(data);
            ret = begin();
        }
        else if (insert_position == end()){
            push_back(data);
            ret = --end();
        }
        else {
            node<T>* new_node = new node<T>{nullptr, nullptr, data};
            node<T>* current_node = insert_position.getPtr();
            node<T>* node_before_current = current_node->prev;

            node_before_current->next = new_node;
            new_node->prev = node_before_current;

            current_node->prev = new_node;
            new_node->next = current_node;

            ret = iterator(new_node);
            ++entries;
        }

        return ret;
    }

    template<typename T>
    void doubly_linked_list<T>::erase(const iterator& erase_position)
    {
        if (erase_position == nullptr) {
            return;
        }
        else if (erase_position == begin()) {
            pop_front();
        }
        else if (erase_position == end()) {
            pop_back();
        }
        else {
            node<T>* current_node = erase_position.getPtr();
            node<T>* node_before_current = current_node->prev;
            node<T>* node_after_current = current_node->next;

            delete(current_node);
            node_before_current->next = node_after_current;
            node_after_current->prev = node_before_current;

            --entries;
        }
    }
};