#include <string>
#include "a6p2.h"

using namespace std;

SmartHashTable::SmartHashTable() : HashTable() {}

SmartHashTable::SmartHashTable(int k) : HashTable(k) {}

SmartHashTable::~SmartHashTable() {}

// djb2
int SmartHashTable::hash(string key) const
{
    unsigned long res = 5381;
    for (char c : key)
    {
        res = (res << 5) + res + (int)c;
    }
    return res % getTableSize();
}
