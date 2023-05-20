//
// main.cpp
// 2023-05-18
// Ivan Konishchev
//

#include <iostream>
#include "Trie.h"

int main(int argc, const char *argv[])
{

    Trie *dictionary = new Trie;
    dictionary->generateDictionary();
    std::string prefix;
    std::cout << "Введите префикс: ";
    std::getline(std::cin, prefix);
    std::string res;
    dictionary->getAllWordsByPrefix(dictionary, prefix, res);
    std::cout << "Варианты слов по префиксу: " << res << "\n";
    delete dictionary;
    return 0;
}