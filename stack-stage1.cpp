/*
 * stack-stage1.cpp
 *
 * Method definitions for the stack implementation (stage 1).
 *
 * Author: Ameen Johnson
 */

#include "stack-stage1.h"

stack::stack() {
    _data = new std::string[_capacity];
}

std::string stack::top() {
    if (_size == 0) {
        return "";
    }

    return _data[_size - 1];
}

void stack::push(const std::string& s) {
    // check if we need to resize the array
    if (_size == _capacity) {
        // double the capacity
        _capacity *= 2;
        std::string* new_data = new std::string[_capacity];

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

void stack::pop() {
    _size--;
}

std::size_t stack::size() {
    return _size;
}

bool stack::is_empty() {
    return _size == 0;
}
