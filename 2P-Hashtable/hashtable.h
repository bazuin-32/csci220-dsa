/*
 * hashtable.h
 *
 * A basic hashtable implementation, using chaining.
 * 
 * Author: Ameen Johnson
 */

#ifndef _HASHTABLE_PROJECT_H
#define _HASHTABLE_PROJECT_H

#include <cstddef>      // for size_t
#include <functional>   // for std::hash
#include <list>         // for std::list
#include <vector>       // for std::vector

/***
 * DO NOT put unscoped 'using namespace std;' in header files!
 * Instead put them at the beginning of class or function definitions
 * (as demonstrated below).
 */

template <class T, class H = std::hash<T>>
class hashtable {
public:
    // constructor
    hashtable();

    // basic hashset operations
    void insert(const T& key);
    void remove(const T& key);
    bool contains(const T& key);
    size_t size();

    // diagnostic functions
    double load_factor();

    // convenience method, invokes the "hash" template parameter
    // function object to get a hash code
    static size_t hash(const T &key) {
        H h;
        return h(key);
    }

private:
    using chain_t = std::list<T>; // type of a single chain
    static constexpr double MAX_LOAD_FACTOR = 0.75; // maximum load factor before resizing
    
    std::size_t _size = 0; // number of elements in the hashtable
    double _load_factor = 0.0;
    std::vector<chain_t> _table;

    void expand_table(); // doubles table size and rehashes all elements
};

template<class T, class H>
hashtable<T, H>::hashtable() : _table(4) { // initial table size of 4
    //
}

template<class T, class H>
void hashtable<T, H>::insert(const T &key) {
    // check if adding the key would exceed max load factor
    if (static_cast<double>(_size + 1) / _table.size() > MAX_LOAD_FACTOR) {
        expand_table();
    }
    
    // find the index for the key
    std::size_t index = hash(key) % _table.size();

    // check if the key already exists in the chain
    for (const auto& item : _table[index]) {
        if (item == key) {
            return; // key already exists, do not insert
        }
    }

    // insert the key into the chain
    _table[index].push_back(key);
    _size++;
    
    // update the load factor
    _load_factor = static_cast<double>(_size) / _table.size();
}

template<class T, class H>
void hashtable<T, H>::remove(const T &key) {
    // find the index for the key
    std::size_t index = hash(key) % _table.size();

    // find the key in the chain and remove it
    chain_t& chain = _table[index];
    for (auto it = chain.begin(); it != chain.end(); ++it) {
        if (*it == key) {
            // remove from chain
            chain.erase(it);
            _size--;

            // update the load factor
            _load_factor = static_cast<double>(_size) / _table.size();
            return;
        }
    }
}

template<class T, class H>
bool hashtable<T, H>::contains(const T &key) {
    // find the index for the key
    std::size_t index = hash(key) % _table.size();

    // check if the key exists in the chain
    for (const T& item : _table[index]) {
        if (item == key) {
            return true;
        }
    }

    return false;
}

template<class T, class H>
size_t hashtable<T, H>::size() {
    return _size;
}

template<class T, class H>
double hashtable<T, H>::load_factor() {
    return _load_factor;
}

template<class T, class H>
void hashtable<T, H>::expand_table() {
    // create a new table with double the size
    std::vector<chain_t> new_table(_table.size() * 2);
    
    // rehash all elements from the old table into the new table
    for (const chain_t& chain : _table) {
        for (const T& key : chain) {
            std::size_t index = hash(key) % new_table.size();
            new_table[index].push_back(key);
        }
    }
    
    // replace the old table with the new table
    _table = std::move(new_table);

    // update the load factor
    _load_factor = static_cast<double>(_size) / _table.size();
}

#endif
