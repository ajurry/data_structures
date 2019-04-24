#include "gtest/gtest.h"
#include "trie.hpp"

#include <string>

using namespace libcontainers;

class TRIE : public::testing::Test {

    protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    trie people;
    std::vector<std::string> names_in_trie = {"planck" , "lorrentz"
                                        , "lagrange" , "newton"
                                        , "tesla", "maxwell"
                                        , "feynman", "dirac"
                                        , "einstein", "higgs"
                                        };

    std::vector<std::string> names_not_in_trie = {"hawking" , "bohr"
                                        , "galilei" , "heisenberg"
                                        ,  "sagan"
                                        };
};


    TEST_F(TRIE, test_insertion) {

        for (auto& name : names_in_trie) {
            people.insert_string(name);
            EXPECT_EQ(people.search_for_string(name), true);
        }

        for (auto& name : names_not_in_trie) {
            EXPECT_NE(people.search_for_string(name), true);
        }
    }