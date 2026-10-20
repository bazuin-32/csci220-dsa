/*
 * Authors: Joey Lovato & C. Painter Wakefield
 *
 * Tests for the hashtable assignment
 * 
 * Last modified: 10/17/2022
 */

#include <vector>

#include "gtest/gtest.h"
#include "tests-setup.h"

#include "hashtable.h"

#include "header-sans-using-namespace.h"
#include "sneaky-project-requirements.h"     // look for project-requirement circumvention
											 
// a bad hash function class to test collisions
class bad_hash : std::hash<std::string> {
public:
    size_t operator()(const std::string&) { return 29; }
};

TEST_F(HashtableTest, Empty) {
    hashtable<std::string> h;
    ASSERT_FALSE(h.contains("apple"));
    ASSERT_EQ(h.size(), 0);
}

TEST_F(HashtableTest, StringInsertRemoveOnce) {
    hashtable<std::string> h;
    h.insert("apple");
    ASSERT_TRUE(h.contains("apple"));
    ASSERT_EQ(h.size(), 1);
    h.remove("apple");
    ASSERT_FALSE(h.contains("apple"));
    ASSERT_EQ(h.size(), 0);
}

TEST_F(HashtableTest, IntInsertRemoveOnce) {
    hashtable<int> h;
    h.insert(17);
    ASSERT_TRUE(h.contains(17));
    ASSERT_EQ(h.size(), 1);
    h.remove(17);
    ASSERT_FALSE(h.contains(17));
    ASSERT_EQ(h.size(), 0);
}

TEST_F(HashtableTest, InsertTwiceRemoveOnce) {
    hashtable<std::string> h;
    h.insert("apple");
    h.insert("apple");
    ASSERT_TRUE(h.contains("apple"));
    ASSERT_EQ(h.size(), 1);
    h.remove("apple");
    ASSERT_FALSE(h.contains("apple"));
    ASSERT_EQ(h.size(), 0);
}

TEST_F(HashtableTest, InsertOnceRemoveTwice) {
    hashtable<std::string> h;
    h.insert("apple");
    ASSERT_TRUE(h.contains("apple"));
    ASSERT_EQ(h.size(), 1);
    h.remove("apple");
    h.remove("apple");
    ASSERT_FALSE(h.contains("apple"));
    ASSERT_EQ(h.size(), 0);
}

TEST_F(HashtableTest, InsertRemoveMany) {
    hashtable<std::string> h;
    for (size_t i = 0; i < 1000; i++) {
        h.insert(words[i]);
    }

    for (size_t i = 0; i < 1000; i++) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 1000; i += 2) {
        h.remove(words[i]);
    }

    for (size_t i = 0; i < 1000; i += 2) {
        ASSERT_FALSE(h.contains(words[i]));
    }

    for (size_t i = 1; i < 1000; i += 2) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 1000; i += 2) {
        h.insert(words[i]);
    }

    for (size_t i = 0; i < 1000; i++) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 1; i < 1000; i += 2) {
        h.remove(words[i]);
    }

    for (size_t i = 1; i < 1000; i += 2) {
        ASSERT_FALSE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 1000; i += 2) {
        ASSERT_TRUE(h.contains(words[i]));
    }
}

TEST_F(HashtableTest, CollisionTest) {
    hashtable<std::string, bad_hash> h;
    for (size_t i = 0; i < 100; i++) {
        h.insert(words[i]);
    }

    for (size_t i = 0; i < 100; i++) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 100; i += 2) {
        h.remove(words[i]);
    }

    for (size_t i = 0; i < 100; i += 2) {
        ASSERT_FALSE(h.contains(words[i]));
    }

    for (size_t i = 1; i < 100; i += 2) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 100; i += 2) {
        h.insert(words[i]);
    }

    for (size_t i = 0; i < 100; i++) {
        ASSERT_TRUE(h.contains(words[i]));
    }

    for (size_t i = 1; i < 100; i += 2) {
        h.remove(words[i]);
    }

    for (size_t i = 1; i < 100; i += 2) {
        ASSERT_FALSE(h.contains(words[i]));
    }

    for (size_t i = 0; i < 100; i += 2) {
        ASSERT_TRUE(h.contains(words[i]));
    }
}

TEST_F(HashtableTest, LoadFactorTest) {
    hashtable<std::string> h;

    // insert some to get the load factor up
    for (size_t i = 0; i < 100; i++) {
        h.insert(words[i]);
        ASSERT_LT(h.load_factor(), 0.76);
    }

    for (size_t i = 0; i < 1000; i++) {
        h.insert(words[i]);
        ASSERT_LT(h.load_factor(), 0.76);   // shouldn't be too full
        ASSERT_GT(h.load_factor(), 0.3);    // shouldn't be too empty, either
    }
}

TEST_F(HashtableTest, LargeTest) {
    hashtable<std::string> h;
    for (std::string &s: words) {
        h.insert(s);
    }
    ASSERT_EQ(h.size(), words.size());

    for (std::string &s: words) {
        ASSERT_TRUE(h.contains(s));
    }

    for (std::string &s: words) {
        h.remove(s);
    }
    ASSERT_EQ(h.size(), 0);

    for (std::string &s: words) {
        ASSERT_FALSE(h.contains(s));
    }
}
