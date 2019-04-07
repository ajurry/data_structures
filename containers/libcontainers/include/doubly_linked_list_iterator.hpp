#include <iterator>

namespace libcontainers {

    template<typename T>
    struct node
    {
        node* prev;
        node* next;
        T data;
    };

    template<typename T>
    class doubly_linked_list_iterator 
        : public std::iterator<std::bidirectional_iterator_tag,
                                T,
                                std::ptrdiff_t,
                                T*,
                                T& >
    {
    public:
        // Construction mechanics
        doubly_linked_list_iterator(node<T>* ptr = nullptr) {m_ptr = ptr;}
        ~doubly_linked_list_iterator() = default;

        // Copy mechanics
        doubly_linked_list_iterator(const doubly_linked_list_iterator<T>& iter) = default;
        doubly_linked_list_iterator<T>& operator=(const doubly_linked_list_iterator<T>& iter) = default;

        // Pre operators
        doubly_linked_list_iterator<T> operator++(){m_ptr = m_ptr->next; return (*this);}
        doubly_linked_list_iterator<T> operator--(){m_ptr = m_ptr->prev; return (*this);}

        // Post operators
        doubly_linked_list_iterator<T> operator++(int){auto temp(*this); m_ptr = m_ptr->next; return temp;}
        doubly_linked_list_iterator<T> operator--(int){auto temp(*this); m_ptr = m_ptr->prev; return temp;}

        // Iterator comparisons
        bool operator==(const doubly_linked_list_iterator& iter) const
            {m_ptr == iter.getConstPtr();}

        bool operator!=(const doubly_linked_list_iterator& iter) const
            {return m_ptr != iter.getConstPtr();}

        // Access to underlying data/ptr
        T& operator*(){return m_ptr->data;}
        const T& operator*() const {return m_ptr->data;}
        T* operator->(){return &m_ptr->data;}

        // Access to ptr
        node<T>* getPtr() const {return m_ptr;}
        const  node<T>* getConstPtr() const {return m_ptr;}


    private:
        node<T>*  m_ptr;
    };
};