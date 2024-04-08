#include <string>
#include <fstream>
#include "HashTable.h"
#include "a6p1.h"

using namespace std;

void HashTable::remove(string word)
{
    const int slot = hash(word);
    Node *cur = table[slot];
    if (!cur)
    {
        return;
    }

    if (cur->word == word)
    {
        table[slot] = cur->next;
        delete cur;
        return;
    }

    while (cur->next)
    {
        if (cur->next->word == word)
        {
            Node *tmp = cur->next;
            cur->next = cur->next->next;
            delete tmp;
            return;
        }
        cur = cur->next;
    }
}

void HashTable::insert(ifstream &file)
{
    string word;
    while (file >> word)
    {
        insert(word);
    }
}

SimpleHashTable::SimpleHashTable() : HashTable() {}

SimpleHashTable::SimpleHashTable(int k) : HashTable(k) {}

SimpleHashTable::~SimpleHashTable() {}

int SimpleHashTable::hash(string key) const
{
    int res = 0;
    for (char c : key)
    {
        res += (int)c;
    }
    return res % getTableSize();
}
