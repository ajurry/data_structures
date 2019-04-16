#include "trie.hpp"
#include <string>

using namespace libcontainers;

trie::trie()
{
    root = new trie_node;
}

trie::~trie()
{
    int i = 0;
    while (i < alphabet_length) {

        trie_node* node = root->children[i];
        if (node != nullptr) {
            delete(node);
            root->children[i] = nullptr;
        }

        ++i;
    }

    delete(root);
}

void trie::insert_string(const std::string& str)
{
    trie_node* current_node = root;

    for (auto& token : str) {

        trie_node* new_node = current_node->children[(int)token - starting_offset];

        if (new_node == nullptr) {
            new_node = new trie_node;
            current_node->children[(int)token - starting_offset] = new_node;
        }

        current_node = new_node;
    }
}

bool trie::search_for_string(const std::string& str)
{
    bool ret = true;
    trie_node* current_node = root;
    
    for (auto& token : str) {

        trie_node* new_node = current_node->children[(int)token - starting_offset];
        if (new_node == nullptr) {
            ret = false;
            break;
        }

        current_node = new_node;
    }

    return ret;
}
