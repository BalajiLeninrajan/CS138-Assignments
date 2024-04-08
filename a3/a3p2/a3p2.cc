#include "a3p2.h"

#include <string>
#include <cassert>

using namespace std;

// provided for you
NodeChunk *createNewNodeChunk(const int chunkSize)
{
    // preconditions
    assert(chunkSize > 0);
    // implementation
    NodeChunk *newNodeChunk = new NodeChunk;
    newNodeChunk->next = nullptr;
    newNodeChunk->val = new string[chunkSize];
    // C++ will initialize this array with empty strings
    // we will switch to our special value for unused stack slots
    for (int i = 0; i < chunkSize; i++)
    {
        newNodeChunk->val[i] = UNUSED_SLOT;
    }
    // postconditions
    return newNodeChunk;
}

// provided for you
void initStack(const int chunkSize, Stack &s)
{
    // preconditions
    assert(chunkSize > 0);
    // implementation
    s.chunkSize = chunkSize;
    s.firstChunk = nullptr;
    s.topElt = -1;
    // postconditions
    assert(isEmpty(s));
    assert(isValidStack(s));
}

// provided for you
bool isEmpty(const Stack &s)
{
    // do not call isValidStack() from here
    // because isEmpty() is part of isValidStack()
    return nullptr == s.firstChunk;
}

// @TODO: define what a wellformed chunkystack looks like
// Note that simply returning true will pass some tests.
// Similarly, simply triggering an assertion will pass some tests.
// That is inherent in any procedure that returns bool.
// The challenge is to pass all the tests.
bool isValidStack(const Stack &s)
{
    // either trip an assertion or return true
    assert(s.chunkSize > 0);
    assert(s.topElt < s.chunkSize);
    if (isEmpty(s))
    {
        assert(s.topElt == -1);
        return true;
    }
    assert(s.firstChunk->val[s.topElt] != UNUSED_SLOT);
    for (int i = s.topElt + 1; i < s.chunkSize; i++)
    {
        assert(s.firstChunk->val[i] == UNUSED_SLOT);
    }
    for (NodeChunk *cur = s.firstChunk->next; cur; cur = cur->next)
    {
        for (int i = 0; i < s.chunkSize; i++)
        {
            assert(cur->val[i] != UNUSED_SLOT);
        }
    }

    // no assertions tripped, so return true
    return true;
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void push(const string v, Stack &s)
{
    // preconditions
    assert(isValidStack(s));
    // implementation
    if (isEmpty(s) || s.topElt == s.chunkSize - 1)
    {
        NodeChunk *new_chunk = createNewNodeChunk(s.chunkSize);
        new_chunk->next = s.firstChunk;
        s.firstChunk = new_chunk;
        s.topElt = -1;
    }
    s.topElt++;
    s.firstChunk->val[s.topElt] = v;
    // postconditions
    assert(isValidStack(s));
    assert(s.firstChunk->val[s.topElt] == v);
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void pop(Stack &s)
{
    // preconditions
    assert(isValidStack(s));
    assert(!isEmpty(s));
    // implementation
    s.firstChunk->val[s.topElt] = UNUSED_SLOT;
    s.topElt--;
    if (s.topElt < 0)
    {
        delete[] s.firstChunk->val;
        NodeChunk *tmp = s.firstChunk;
        s.firstChunk = s.firstChunk->next;
        delete tmp;
        if (!isEmpty(s))
        {
            s.topElt = s.chunkSize - 1;
        }
    }
    // postconditions
    assert(isValidStack(s));
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
int size(const Stack &s)
{
    // preconditions
    assert(isValidStack(s));
    // implementation
    if (isEmpty(s))
    {
        return 0;
    }
    int count = s.topElt + 1;
    for (NodeChunk *cur = s.firstChunk->next; cur; cur = cur->next)
    {
        count += s.chunkSize;
    }
    // return result
    return count; // something so this stub compiles
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void swap(Stack &s)
{
    // preconditions
    assert(isValidStack(s));
    assert(size(s) >= 2);
    // implementation
    string first = top(s);
    pop(s);
    string second = top(s);
    pop(s);
    push(first, s);
    push(second, s);
    // postconditions
    assert(isValidStack(s));
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
string toString(const Stack &s)
{
    // preconditions
    assert(isValidStack(s));
    // implementation
    if (isEmpty(s))
    {
        return "[]";
    }
    string result = "[";
    for (int i = s.topElt; i >= 0; i--)
    {
        result += s.firstChunk->val[i] + ", ";
    }
    for (NodeChunk *cur = s.firstChunk->next; cur; cur = cur->next)
    {
        for (int i = s.chunkSize - 1; i >= 0; i--)
        {
            result += cur->val[i] + ", ";
        }
    }
    result.replace(result.end() - 2, result.end(), "]");

    // postconditions
    // return result
    return result; // something so this stub compiles
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
string top(const Stack &s)
{
    // preconditions
    assert(isValidStack(s));
    assert(!isEmpty(s));
    // implementation
    // return result
    return s.firstChunk->val[s.topElt];
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void nuke(Stack &s)
{
    // preconditions
    assert(isValidStack(s));
    // implementation
    while (!isEmpty(s))
    {
        pop(s);
    }
    // postconditions
    assert(isValidStack(s));
    assert(isEmpty(s));
}
