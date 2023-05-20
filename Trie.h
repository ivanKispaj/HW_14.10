//
// Trie.h
// 2023-05-18
// Ivan Konishchev
//

#pragma once
#include <string>
const int ALPHABET_SIZE = 26;

// Структура узела дерева
struct Trie
{
    /// @brief Init
    Trie();

    /// @brief Deinit
    ~Trie();

    /// @brief Inserts the key into the tree if it is not there,
    /// otherwise, if the key is a prefix of the tree node
    /// marks the end of the word as a cast one
    /// @param string word
    void insert(const std::string &);

    bool search(Trie *, const std::string &);

    Trie *remove(Trie *, std::string &, int depth = 0);

    /// @brief Returns a string with all minimum unique prefixes
    /// @return Returns a string with all minimum unique prefixes
    std::string getMinPrefixes();

    /// @brief
    /// @param
    /// @param prefix initial prefix string
    /// @param ret a string that will contain words separated by a space
    void getAllWordsByPrefix(Trie *, const std::string &prefix, std::string &ret);

    /// @brief generates a dictionary from which the search will be conducted
    void generateDictionary();

    // children array
    Trie *children[ALPHABET_SIZE];

private:
    bool isEmpty(Trie *);

    /// @brief Create new node
    /// @return new node with empty children
    Trie *getNewNode();

    void getAllWordFromNodePosition(Trie *node, char buf[], int ind, std::string &res);
    void getAllMinPrefixes(Trie *, char[], int, std::string &);

    // isEndOfWord - true, если ключ является концом слова
    bool isEndOfWord{false};
    int freq = 1;
};
