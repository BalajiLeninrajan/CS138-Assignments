#include <iostream>
#include <string>
#include <cctype> // for tolower()
#include <map>
#include <cassert>
#include "a5p2.h"

using namespace std;

LexTree::LexTree() : isWord(false) {}

LexTree::~LexTree()
{
    for (pair<char, LexTree *> child : children)
    {
        delete child.second;
    }
}

bool LexTree::isValid() const
{
    for (pair<char, LexTree *> child : children)
    {
        if (child.first != tolower(child.first))
        {
            exit(1);
        }

        if (child.second->children.empty() && !child.second->isWord)
        {
            exit(1);
        }

        child.second->isValid();
    }

    return true;
}

void LexTree::addWord(const string &s)
{
    assert(isValid()); // precondition

    if (s == "")
    {
        isWord = true;
        return;
    }

    char c = tolower(s[0]);
    if (children.find(c) == children.end())
    {
        children[c] = new LexTree{};
    }

    children[c]->addWord(s.substr(1));

    assert(isValid()); // postcondition
}

bool LexTree::hasWord(const string &s) const
{
    assert(isValid()); // precondition

    if (s == "")
    {
        return isWord;
    }

    char c = tolower(s[0]);
    if (children.find(c) == children.end())
    {
        return false;
    }

    return children.at(c)->hasWord(s.substr(1));
}

string LexTree::toString_helper(string current_word) const
{
    string res = isWord ? "\n" : "";

    for (pair<char, LexTree *> child : children)
    {
        if (isWord || children.find(child.first) != children.begin())
        {
            res += current_word;
        }
        res += child.first + child.second->toString_helper(current_word + child.first);
    }
    return res;
}

string LexTree::toString() const
{
    assert(isValid()); // precondition
    return toString_helper("");
}
