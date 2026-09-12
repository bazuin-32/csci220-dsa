/*
 * stack-stage3.h
 *
 * Implements a simple stack class using dynamic arrays.
 * This may be implemented in 3 stages:
 *   Stage 1: non-template stack class storing strings,
 *            unsafe copies/assignments
 *   Stage 2: template stack class, unsafe copies/assignments
 *   Stage 3: template stack class, safe copies/assignments
 *
 * Note: no underflow detection is performed.  Performing pop() or top()
 * on an empty stack results in undefined behavior (possibly crashing your
 * program)!
 *
 * Author: Your Name
 */

#ifndef _STACK_H
#define _STACK_H

#include <cstddef> // for size_t

template<typename T>
class stack {
  public:
    T top(); // non-inline, implemented in stack-stage1.cpp

    void push(const T &);
    void pop();
    size_t size();
    bool is_empty();

    stack();
    stack(const stack<T>& other); // copy constructor
    ~stack();
    
    stack<T>& operator=(const stack<T>& other); // assignment operator

  private:
    T* _data;
    std::size_t _size = 0; // number of elements currently in the stack
    std::size_t _capacity = 1; // maximum number of elements the stack can hold
};

/***
 * DO NOT put unscoped 'using namespace std;' in header files!
 * Instead use the std:: prefix where required in class definitions, as
 * demonstrated in the stack starter code for stage1.
 */

 
template<typename T>
inline stack<T>::stack() {
    _data = new T[_capacity];
}

template<typename T>
inline stack<T>::stack(const stack<T>& other) {
    // copy size and capacity
    _size = other._size;
    _capacity = other._capacity;
    
    // allocate new array for the copied data
    _data = new T[_capacity];
    
    // copy the elements from the other stack
    for (std::size_t i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
}

template<typename T>
inline stack<T>::~stack() {
    delete[] _data;
}

template<typename T>
inline stack<T>& stack<T>::operator=(const stack<T>& other) {
    // check for self-assignment
    if (this == &other) {
        return *this;
    }

    // deallocate current array
    delete[] _data;

    // copy size, capacity, and allocate new array
    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];

    // copy the elements from the other stack
    for (std::size_t i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
    
    return *this;
}

template<typename T>
inline T stack<T>::top() {
    if (_size == 0) {
        return T(); // return default-constructed T if stack is empty
    }

    return _data[_size - 1];
}

template<typename T>
inline void stack<T>::push(const T& s) {
    // check if we need to resize the array
    if (_size == _capacity) {
        // double the capacity
        _capacity *= 2;
        T* new_data = new T[_capacity];

        // copy old data to new array
        for (std::size_t i = 0; i < _size; i++) {
            new_data[i] = _data[i];
        }

        // delete old array and update pointer
        delete[] _data;
        _data = new_data;
    }

    _data[_size] = s;
    _size++;
}

template<typename T>
inline void stack<T>::pop() {
    _size--;
}

template<typename T>
inline std::size_t stack<T>::size() {
    return _size;
}

template<typename T>
inline bool stack<T>::is_empty() {
    return _size == 0;
}


#endif
