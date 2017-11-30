//
// Created by oded on 30/11/17.
//

#ifndef DS_WET_2_LINKEDLIST_H
#define DS_WET_2_LINKEDLIST_H

#include "Exceptions.h"

using ListExceptions::ElementNotFound;

template <class T> class List {
public:
    /** List empty constructor  */
    List();

    /** List copy constructor  */
    List(const List<T> &list);

    /** List destructor  */
    ~List();

    /** List assignment operator */
    List<T>& operator=(const List<T>& other);

    /**
     * Insert an element to the end of the generic list.
     *
     * @tparam T : Type of the generic list.
     * @param data : The data of type T we want to insert to the end of the list.
     */
    void insert(const T &data);

    /**
     * Sorts the list using a Compare function object.
     * @tparam T : Type of the generic list.
     * @tparam Compare : Comparison function object type.
     * @param compare : Comparison function object.
     */
    template <class Compare> void sort(const Compare& compare);

    /**
     * Returns the number of elements on the list.
     * @tparam T : Type of the generic list.
     * @return
     *      The number of elements on the list (not including the dummy end
     *      object of course).
     */
    int getSize() const;

    /** Iterator for the list of type T */
    class Iterator {
    public:

        /**
         * Postfix increment iterator operator
         * @tparam T : Type of the generic list.
         * @return
         *       The iterator BEFORE increment.
         */
        Iterator operator++(int);

        /**
         * prefix increment iterator operator
         * @tparam T : Type of the generic list.
         * @return
         *       The iterator AFTER increment.
         */
        Iterator& operator++();

        /**
         * Postfix decrement iterator operator
         * @tparam T : Type of the generic list.
         * @return
         *       The iterator BEFORE decrement.
         */
        Iterator operator--(int);

        /**
         * Postfix decrement iterator operator
         * @tparam T : Type of the generic list.
         * @return
         *       The iterator AFTER decrement.
         */
        Iterator& operator--();

        /**
         * Dereferencing iterator operator
         * @tparam T : Type of the generic list.
         * @return
         *       The data of the node pointed by the iterator.
         */
        T& operator*();

        /**
         * Iterator comparison (Equal) operator
         * @tparam T : Type of the generic list.
         * @param A : First iterator to be compared.
         * @param B : Second iterator to be compared.
         * @return
         *       TRUE - The iterators points to the SAME (same address) node.
         *       values.
         *       FALSE - The iterators DONT to the SAME (same address) node.
         */
        bool operator==(const List<T>::Iterator& iterator) const;

        /**
         * Iterator comparison (Non-Equal) operator
         * @tparam T : Type of the generic list.
         * @param A : First iterator to be compared.
         * @param B : Second iterator to be compared.
         * @return
         *       TRUE - The iterators DONT points to the SAME (same address)
         *       node values.
         *       FALSE - The iterators to the SAME (same address) node.
         */
        bool operator!=(const List<T>::Iterator& iterator) const;

        /**
         * Iterator comparison (Smaller) operator
         * @tparam T : Type of the generic list.
         * @param A : First iterator to be compared.
         * @param B : Second iterator to be compared.
         * @return
         *       TRUE - The iterators DONT points to the SAME (same address)
         *       node values.
         *       FALSE - The iterators to the SAME (same address) node.
         */
        bool operator<(int num) const;

        Iterator& operator=(const List<T>::Iterator& iterator) = default;

    private:
        friend class List;
        typename List<T>::Node *_element;
        const List<T> *_list;
    };

    /**
     * Finds the first element in the list that match to the 'Predicate'
     * function object.
     * @tparam T : Type of the generic list.
     * @tparam Predicate : function object type.
     * @param predicate : the function object we use to match the element on
     * the list.
     * @return
     *      Iterator tht points to the first element that matches to Predicate.
     */
    template <class Predicate>
    List<T>::Iterator find(const Predicate& predicate);

    /**
     * Returns an iterator that points to the head of the list.
     * @tparam T : Type of the generic list.
     * @return
     *      Iterator : An iterator that points to the first Node object on the
     *      list.
     */
    List<T>::Iterator begin() const;

    /**
     * Returns an iterator that points to the end of the list.
     * @tparam T : Type of the generic list.
     * @return
     *      Iterator : An iterator that points to the last Node object on the
     *      list (Not the dummy object).
     */
    List<T>::Iterator end() const;

    /**
     * Insert an element to the list, locating it right before the element
     * pointed by the iterator.
     *
     * @tparam T : Type of the generic list.
     * @param data : The data of type T we want to insert to the end of the
     * list.
     * @param iterator : The iterator that points to the element that will be
     * located right after the insertion.
     * @throw ElementNotFound() in case Iterator belongs to another list.
     */
    void insert(const T &data, List<T>::Iterator iterator);

    /**
     * Removes an element from the list.
     * @tparam T : Type of the generic list.
     * @param iterator : An iterator that points to the element we want to
     * remove.
     */
    void remove(List<T>::Iterator iterator);
private:
    class Node {

        /**
         * Node Object empty constructor.
         * Used to create a dummy object for List<T>.end();
         */
        Node();

        /**
         * Node Object full-data constructor.
         * @tparam T : Type of the generic list.
         * @param data : Data element of type T of the Node.
         * @param next : pointer to the next Node object on the list.
         * @param prev : pointer to the previous Node object on the list.
         */
        Node(const T &data,
             Node* const next = nullptr,
             Node* const prev = nullptr);


        Node(const Node& node) = default;

        /**
         * Node Object destructor.
         * (Not deleting 'prev' in order to not cause conflicts on list
         * destruct.
         * @tparam T : Type of the generic list.
         */
        ~Node();

        /**
         * Detached a Node object from the list (sets prev & next to NULL).
         * Used in order to delete a Node object without harming its siblings.
         * @tparam T : Type of the generic list.
         */
        void isolate();

        T* _data;
        List<T>::Node *_next;
        List<T>::Node *_prev;
        friend class List<T>;
    };

    /**
     * [static] Swaps the location of 2 Node object in the list.
     * @tparam T : Type of the generic list.
     * @param A : First Node element.
     * @param B : Second Node element.
     */
    static void swap(List<T>::Node& A, List<T>::Node& B);

    List<T>::Node *_tail; // Just some random address to represent end.
    List<T>::Node *_head;
};

template <class T>
List<T>::List() : _tail(new Node()) {
    _head = _tail;
}

template <class T>
List<T>::List(const List<T> &list) :  List() {
    List<T>::Iterator it = list.begin();
    while (it != list.end()) {
        (*this).insert(*it);
        it++;
    }
}

template <class T>
List<T>::~List() {
    delete _head;
}

template <class T>
List<T>& List<T>::operator=(const List<T>& other) {
    if (this == &other) return *this;
    List<T> list(other);
    delete _head;
    _tail = list._tail;
    _head = list._head;
    list._head = nullptr;
    list._tail = nullptr;
    return *this;
}

template <class T>
void List<T>::insert(const T &data) {
    List<T>::insert(data, this->end());
}

template <class T>
void List<T>::insert(const T &data,List<T>::Iterator iterator) {
    if (iterator._list != this) throw ElementNotFound();
    Node *new_node = new Node(data, iterator._element,
                              iterator._element->_prev);
    Node *tmp = iterator._element->_prev;
    iterator._element->_prev = new_node;
    if (!tmp) {
        _head = new_node;
    } else {
        tmp->_next = new_node;
    }
}

template <class T>
void List<T>::remove(List<T>::Iterator iterator) {

    if ((iterator._list != this) || (iterator == (*this).end())) {
        throw ElementNotFound();
    }
    if (iterator._element == _tail) return;
    if (iterator._element->_prev) {
        iterator._element->_prev->_next = iterator._element->_next;
        iterator._element->_next->_prev = iterator._element->_prev;
    } else {
        _head = iterator._element->_next;
        iterator._element->_next->_prev = nullptr;
    }

    iterator._element->isolate();
    delete iterator._element;
}

template <class T>
int List<T>::getSize() const {
    List<T>::Iterator iterator = begin();
    int counter = 0;
    while (iterator != this->end()) {
        counter++;
        iterator++;
    }
    return counter;
}

template <class T>
typename List<T>::Iterator List<T>::end() const {
    List<T>::Iterator iterator;
    iterator._element = _tail;
    iterator._list = this;
    return iterator;
}

template <class T>
typename List<T>::Iterator List<T>::begin() const {
    List<T>::Iterator iterator;
    iterator._element = _head;
    iterator._list = this;
    return iterator;
}

/**
 * List comparison (Equal) operator
 * @tparam T : Type of the generic list.
 * @param A : First list to be compared.
 * @param B : Second list to be compared.
 * @return
 *       TRUE : The lists contains the same numbers of elements with the same
 *       values.
 *       FALSE : The lists DONT contains the same numbers of elements with the
 *       same values.
 */
template <class T>
bool operator==(const List<T> &A, const List<T> &B) {
    if (A.getSize() != B.getSize()) return false;

    typename List<T>::Iterator itA = A.begin();
    typename List<T>::Iterator itB = B.begin();
    while ( itA != A.end()) {
        if (*itA != *itB) return false;
        itA++;
        itB++;
    }
    return true;
}

/**
 * List comparison (Non-Equal) operator
 * @tparam T : Type of the generic list.
 * @param A : First list to be compared.
 * @param B : Second list to be compared.
 * @return
 *       TRUE - The lists DONT contains the same numbers of elements with
 *       the same values.
 *       FALSE - The lists contains the same numbers of elements with the
 *       same values.
 */
template <class T>
bool operator!=(const List<T> A, const List<T> B) {
    return !(A == B);
}



template <class T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    List<T>::Iterator it(*this); // Saves the position before the increment.
    if (_element->_next)  _element = _element->_next;
    return it;
}

template <class T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    (*this)++;
    return *this;
}

template <class T>
typename List<T>::Iterator List<T>::Iterator::operator--(int) {
    List<T>::Iterator it(*this);  // Saves the position before the decrement.
    if (_element->_prev) _element = _element->_prev;
    return it;
}

template <class T>
typename List<T>::Iterator& List<T>::Iterator::operator--() {
    (*this)--;
    return *this;
}

template <class T>
T& List<T>::Iterator::operator*() {
    if (_element == _list->_tail) {
        throw ElementNotFound();
    }
    return *(_element->_data);
}

template <class T>
bool List<T>::Iterator::operator==(const List<T>::Iterator& iterator) const {
    return (_element == iterator._element) && (_list == iterator._list);
}

template <class T>
bool List<T>::Iterator::operator!=(const List<T>::Iterator& iterator) const {
    return !(*this == iterator);
}

template <class T>
bool List<T>::Iterator::operator<(int num) const {
    return (_element < num);
}

template <class T>
List<T>::Node::Node() : _data(new T()), _next(), _prev() {}

template <class T>
List<T>::Node::Node(const T &data,Node* const next,Node* const prev) :
        _data(new T(data)), _next(next), _prev(prev) {}

template <class T>
List<T>::Node::~Node() {
    delete _next;
    delete _data;
}

template <class T>
void List<T>::Node::isolate() {
    _next = nullptr;
    _prev = nullptr;
}

template <class T>
void List<T>::swap(List<T>::Node& A, List<T>::Node& B) {
    Node tmp(A);
    A._data = B._data;
    B._data = tmp._data;
    tmp._data = nullptr;
    tmp.isolate();
}

template <class T>
template <class Compare>
void List<T>::sort(const Compare& compare) {
    List<T>::Iterator it;

    bool swapped;
    do {
        it = this->begin();
        swapped = false;
        while(it._element != _tail && it._element->_next != _tail) {
            if (compare(*(it._element->_next->_data), *(it._element->_data))) {
                swap(*it._element, *it._element->_next);
                swapped = true;
            }
            it++;
        }
    } while (swapped);
}

template <class T>
template <class Predicate>
typename List<T>::Iterator List<T>::find(const Predicate& predicate) {
    List<T>::Iterator it = (*this).begin();
    while (it != (*this).end()) {
        if (predicate(*it)) break;
        it++;
    }
    return it;
}

#endif //DS_WET_2_LINKEDLIST_H
