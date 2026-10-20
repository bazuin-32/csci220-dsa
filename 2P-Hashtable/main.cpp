/*
 * main.cpp
 *
 * Includes the main() function for the hashtable project.
 *
 * This code is included in the default build target.  It
 * produces the program run-main.
*/

#include <iostream>
#include <string>

#include "hashtable.h"

using namespace std;

int main() {
    cout << "If you are seeing this, you have successfully run main!" << endl;

    // The code below illustrates how to create your hashtable for string or integer
    // objects, and lets you see the different hash values produced by C++ std::hash.
    std::hash<std::string> strHash;
    std::hash<int> intHash;
    std::hash<double> doubleHash;

    cout << strHash("Hello World") << endl;
    cout << intHash(220) << endl;
    cout << doubleHash(3.1415926535) << endl;

    // Here is how to create a hashtable
    hashtable<std::string> ht;
    ht.insert("Goodbye");
    hashtable<int> it;
    it.insert(220);
}

