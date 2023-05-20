//
// Trie.cpp
// 2023-05-18
// Ivan Konishchev
//

#include "Trie.h"
#include <iostream>

Trie::Trie()
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        children[i] = nullptr;
    }
}

Trie::~Trie()
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (this->children[i])
        {
            delete this->children[i];
        }
    }
}

/// Public Methods

void Trie::insert(const std::string &key)
{
    Trie *node = this;

    for (int i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфите через смещение отнситьельно первой буквы
        int index = key[i] - 'a';

        // если указатель пустрой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
            node->children[index] = getNewNode();
        else
            node->children[index]->freq++;
        node = node->children[index];
    }

    // помечаем последний узлел как лист, т.е. конец слова
    node->isEndOfWord = true;
}

// Возврашает true если ключ есть в дереве, иначе false
bool Trie::search(struct Trie *root, const std::string &key)
{
    struct Trie *node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node != nullptr && node->isEndOfWord);
}

// Рекурсивная функция удаления ключа из дерева
Trie *Trie::remove(Trie *root, std::string &key, int depth)
{
    // Если дерево пустое
    if (!root)
        return nullptr;

    // если дошли до конца ключа
    if (depth == key.size())
    {

        // Этот узел больше не конец слова
        if (root->isEndOfWord)
            root->isEndOfWord = false;

        // Если ключ не евляется префиксом, удаляем его
        if (isEmpty(root))
        {
            delete (root);
            root = nullptr;
        }

        return root;
    }

    // Если не дошли до конца ключа, рекурсивно вызываем для ребенка
    // соответствующего символа
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);

    // Если у корня нет дочернего слова
    // (удален только один его дочерний элемент),
    // и он не заканчивается другим словом.
    if (isEmpty(root) && root->isEndOfWord == false)
    {
        delete (root);
        root = nullptr;
    }

    // возвращаем новый корень
    return root;
}

std::string Trie::getMinPrefixes()
{
    std::string ret;
    char buf[ALPHABET_SIZE];
    getAllMinPrefixes(this, buf, 0, ret);
    return ret;
}

void Trie::getAllWordsByPrefix(Trie *root, const std::string &prefix, std::string &ret)
{
    // Corner case
    if (root == nullptr)
        return;

    char buf[ALPHABET_SIZE];
    int ind = 0;
    Trie *node = root;

    for (int i = 0; i < prefix.size(); i++)
    {
        buf[i] = prefix[ind];

        for (int j = 0; j < ALPHABET_SIZE; j++)
        {
            if (node->children[j] != nullptr && (j + 'a') == prefix[i])
            {

                if (node->children[j]->isEndOfWord)
                {
                    buf[ind + 1] = '\0';
                    ret.append(buf);
                    ret.push_back(' ');
                }
                node = node->children[j];
                break;
            }
        }
        ind++;
    }
    getAllWordFromNodePosition(node, buf, ind, ret);
}

void Trie::generateDictionary()
{
    std::string dictArray[30] = {"hello", "friend", "people", "enter",
                                 "name", "address", "girl", "children",
                                 "age", "old", "young", "you", "he", "she",
                                 "parents", "father", "wife", "sister", "brother",
                                 "uncle", "arm", "bone", "eye", "face", "hair", "hand",
                                 "head", "she", "singl", "sinoptics"};

    for (int i = 0; i < 30; i++)
    {
        this->insert(dictArray[i]);
    }
}

/// Private Methods

// Вохвращает true если root имеет лист, иначе false
bool Trie::isEmpty(Trie *root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

Trie *Trie::getNewNode()
{
    // Выделяем память по новый узел
    Trie *pNode = new Trie;

    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false;

    // инициализируем детей нулевым уазателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}

void Trie::getAllWordFromNodePosition(Trie *node, char buf[], int ind, std::string &res)
{
    // Corner case
    if (node == nullptr)
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {

        if (node->children[i] != nullptr)
        {
            buf[ind] = i + 'a';
            if (node->children[i]->isEndOfWord)
            {
                buf[ind + 1] = '\0';
                res.append(buf);
                res.push_back(' ');
            }

            getAllWordFromNodePosition(node->children[i], buf, ind + 1, res);
        }
    }
}

void Trie::getAllMinPrefixes(Trie *root, char buf[], int ind, std::string &res)
{
    // Corner case
    if (root == nullptr)
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {

        if (root->children[i] != nullptr)
        {
            buf[ind] = i + 'a';
            if (root->children[i]->freq == 1)
            {
                buf[ind + 1] = '\0';
                res.append(buf);
                res.push_back(' ');
                buf[ind] = '\0';
                continue;
            }

            getAllMinPrefixes(root->children[i], buf, ind + 1, res);
        }
    }
}