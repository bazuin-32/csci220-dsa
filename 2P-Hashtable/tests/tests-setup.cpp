/*
 * Authors: Joey Lovato & C. Painter Wakefield
 *
 * Tests for the hashtable assignment
 * 
 * Last modified: 10/17/2022
 */

#include "tests-setup.h"
#include <unordered_set>

#define MAX_WORD_SIZE 10
#define NUMBER_OF_WORDS 200000

// helper function to produce random word of a given length
std::string random_word(int len) {
	std::string random;
    for(int i = 0; i < len; i++) {
        random += 'a' + (rand() % 26);
    }
    return random;
}

// fixture to set up unique random word vector for use in large testswords.size()
std::vector<std::string> HashtableTest::words = std::vector<std::string>();

void HashtableTest::SetUpTestSuite() {
	srand(1234);
	std::unordered_set<std::string> word_set;
	while(word_set.size() < NUMBER_OF_WORDS) {
		word_set.insert(random_word((rand() % MAX_WORD_SIZE) + 1));
	}
	for(const std::string &s: word_set) {
		words.push_back(s);
	}
}

void HashtableTest::TearDownTestSuite() {
	words.clear();
}


