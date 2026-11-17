/*
 * trie.cpp
 *
 * Method definitions for the trie class.
 *
 * Author: Ameen Johnson
 */

#include "trie.h"

void trie::insert(const std::string& s) {
    // iterate through each character of the string while traversing the trie
    node* current = &root;
    for (char c : s) {
        // get the index in the `children` array
        int index = c - 'a';
        
        // if the child does not exist, create it
        if (! current->children[index]) {
            current->children[index] = new node();
        }
        
        // advance to the child node
        current = current->children[index];
    }
    
    // we have reached the end of the string, so mark this node as terminal
    current->is_terminal = true;
}

bool trie::contains(const std::string& s) {
    // iterate through each character of the string while traversing the trie
    node* current = &root;
    for (char c : s) {
        // get the index in the `children` array
        int index = c - 'a';

        // if the child does not exist, the string is not in the trie
        if (! current->children[index]) {
            return false;
        }
        
        // advance to the child node
        current = current->children[index];
    }

    // we have reached the end of the string
    // if this node is terminal, the string is in the trie
    return current->is_terminal;
}

bool trie::is_prefix(const std::string& s) {
    // iterate through each character of the string while traversing the trie
    node* current = &root;
    for (char c : s) {
        // get the index in the `children` array
        int index = c - 'a';

        // if the child does not exist, the string is not in the trie
        if (! current->children[index]) {
            return false;
        }
        
        // advance to the child node
        current = current->children[index];
    }

    // we have reached the end of the string
    // since we only care about the string being a prefix, we return true regardless of whether the node is terminal
    return true;
}

void trie::extend(const std::string& prefix, std::vector<std::string>& result) {
    // find the node at the end of the prefix
    node* current = &root;
    for (char c : prefix) {
        // get the index in the `children` array
        int index = c - 'a';

        // if the child does not exist, the prefix is not in the trie
        if (! current->children[index]) {
            return;
        }

        // advance to the child node
        current = current->children[index];
    }

    // now we have the node that is the root of all words that start with the prefix
    // recursively get all words under that subtree
    std::vector<std::string> words = _get_words(current, prefix);

    // add the words to the result vector
    result.insert(result.end(), words.begin(), words.end());
}

std::vector<std::string> trie::_get_words(node* root, const std::string& current) {
    std::vector<std::string> words;
    
    // if the current node is terminal, add it to the list of words
    if (root->is_terminal) {
        words.push_back(current);
    }

    // perform a pre-order traversal of the trie
    for (int i = 0; i < 26; i++) {
        if (! root->children[i]) {
            // this child does not exist, so we skip it
            continue;
        }

        // get the character corresponding to this child
        char c = 'a' + i;

        // recursively get the words from this child
        std::vector<std::string> child_words = _get_words(root->children[i], current + c);
        
        // add the words from this child to the list of words
        words.insert(words.end(), child_words.begin(), child_words.end());
    }

    return words;
}