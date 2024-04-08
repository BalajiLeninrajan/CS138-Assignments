#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "HashTable.h"
#include "a6p1.h"
#include "a6p2.h"
#include "a6p3.h"

using namespace std;

// Ancillary function for powerset.  It adds a character onto the beginning
// of each string in a vector.
vector<string> addChar(const vector<string> &v, char c)
{
    vector<string> ans;
    for (int i = 0; i < (int)v.size(); i++)
    {
        ans.push_back(c + v.at(i));
    }
    return ans;
}

// This takes a string and returns the power(multi)set of its characters
// as a vector.  For example, powerset of "aab" would be the vector with
// elements (in no particular order): "aab" "ab" "aa" "a" "ab" "a" "b".
// Assume we don't care about eliminating duplicates for now.
vector<string> powerset(string s)
{
    vector<string> ans;
    if (s.size() == 0)
    {
        ans.push_back("");
    }
    else
    {
        char c = s.at(0);
        string rest = s.substr(1);
        vector<string> psetRest = powerset(rest);
        ans = addChar(psetRest, c);
        ans.insert(ans.end(), psetRest.begin(), psetRest.end());
    }
    return ans;
}

int scrabbleValue(char c)
{
    switch (tolower(c))
    {
    case 'a':
    case 'e':
    case 'i':
    case 'l':
    case 'n':
    case 'o':
    case 'r':
    case 's':
    case 't':
    case 'u':
        return 1;
    case 'd':
    case 'g':
        return 2;
    case 'b':
    case 'c':
    case 'm':
    case 'p':
        return 3;
    case 'f':
    case 'h':
    case 'v':
    case 'w':
    case 'y':
        return 4;
    case 'k':
        return 5;
    case 'j':
    case 'x':
        return 8;
    case 'q':
    case 'z':
        return 10;
    default:
        cerr << (string) "Error: Received non-alphabetical character '" + c + "'" << endl;
        exit(1);
    }
}

int scrabbleValue(string s)
{
    int res = 0;
    for (char c : s)
    {
        res += scrabbleValue(c);
    }
    return res;
}

string bestScrabbleWord(string letters)
{
    static SmartHashTable dictionary;
    static bool is_loaded = false;
    if (!is_loaded)
    {
        ifstream file{"twl-words.txt"};
        dictionary.insert(file);
    }
    pair<string, int> score = {"", 0};

    for (string s : powerset(letters))
    {
        sort(s.begin(), s.end());
        do
        {
            string s_lower = "";
            for (char c : s)
            {
                s_lower += tolower(c);
            }

            if (scrabbleValue(s) > score.second && dictionary.lookup(s_lower))
            {
                score = {s, scrabbleValue(s)};
            }
        } while (next_permutation(s.begin(), s.end()));
    }
    return score.first;
}
