#pragma once
#include <string>

namespace libcontainers {

    const int alphabet_length = 26;
    const int starting_offset = 'a';

    struct trie_node {

        trie_node* children[alphabet_length];

        ~trie_node() {
            int i = 0;

            while (i < alphabet_length) {

                trie_node* node = children[i];
                if (node != nullptr) {
                    delete(node);
                    children[i] = nullptr;
                }

                ++i;
            }
        }
    };

    // Dedicated trie class to strings ... char only
    class trie {
    public:
        trie();

        // Disable copy mechanics
        trie(const trie&) = delete;
        trie& operator=(const trie&) = delete;

        // Disable move mechanics
        trie(trie&&) = delete;
        trie& operator = (trie&&) = delete;

        void insert_string(const std::string& str);
        bool search_for_string(const std::string& str);

        ~trie();

    private:
        trie_node* root;
    };
};