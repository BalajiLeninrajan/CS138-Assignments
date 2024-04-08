#include "a3p2.h"

#include <string>
#include <cassert>

using namespace std;


// provided for you
NodeChunk* createNewNodeChunk(const int chunkSize) {
    // preconditions
    assert(chunkSize > 0);
    // implementation
    NodeChunk* newNodeChunk = new NodeChunk;
    newNodeChunk->next = nullptr;
    newNodeChunk->val = new string[chunkSize];
    // C++ will initialize this array with empty strings
    // we will switch to our special value for unused stack slots
    for (int i=0; i < chunkSize; i++) {
        newNodeChunk->val[i] = UNUSED_SLOT;
    }
    // postconditions
    return newNodeChunk;
}

// provided for you
void initStack(const int chunkSize, Stack& s){
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
bool isEmpty(const Stack& s) {
    // do not call isValidStack() from here
    // because isEmpty() is part of isValidStack()
    return nullptr == s.firstChunk;
}

// @TODO: define what a wellformed chunkystack looks like
bool isValidStack(const Stack& s) {
    assert(s.chunkSize > 0);
    assert(s.topElt < s.chunkSize); // top element in bounds
    assert((s.topElt == -1 && s.firstChunk == nullptr) || (s.topElt != -1 && s.firstChunk != nullptr));
    assert(s.topElt == -1 || s.firstChunk->val[s.topElt] != UNUSED_SLOT); // only check the current value for illegal, we want to keep it O(1)
    assert(s.topElt == s.chunkSize - 1 || s.firstChunk == nullptr || s.firstChunk->val[s.topElt + 1] == UNUSED_SLOT); // check the next value is the unused if there is a next in this array
    // check that if there is a next array that it's first value is not unused
    assert(s.firstChunk == nullptr || s.firstChunk->next == nullptr || s.firstChunk->next->val[0] != UNUSED_SLOT);
    return true;
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void push(const string v, Stack& s) {
    // preconditions
    assert(isValidStack(s));
    assert(v != UNUSED_SLOT);
    // implementation
    // check if the current chunk is full, and if so add a new element
    if (s.topElt == s.chunkSize - 1 || s.topElt == -1) {
        NodeChunk* newChunk = createNewNodeChunk(s.chunkSize);
        newChunk->val[0] = v;
        newChunk->next = s.firstChunk;
        s.firstChunk = newChunk;
        s.topElt = 0;
    } else {
        s.topElt += 1;
        s.firstChunk->val[s.topElt] = v;
    }
    // postconditions
    assert(isValidStack(s));
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void pop(Stack& s) {
    // preconditions
    assert(isValidStack(s));
    assert(size(s) > 0);
    // implementation
    s.firstChunk->val[s.topElt] = UNUSED_SLOT;
    if (s.topElt == 0) {
        NodeChunk* nodeToKill = s.firstChunk;
        s.firstChunk = s.firstChunk->next;
        delete [] nodeToKill->val;
        delete nodeToKill;
        if (s.firstChunk != nullptr){
            s.topElt = s.chunkSize - 1;
        } else {
            s.topElt = -1;
        }
    } else {
        s.topElt -= 1;
    }
    // postconditions
    assert(isValidStack(s));
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
int size(const Stack& s) {
    // preconditions
    assert(isValidStack(s));
    // implementation
    if (isEmpty(s)) {
        return 0;
    }
    int size = s.topElt + 1;
    NodeChunk* curr = s.firstChunk->next;
    while (curr != nullptr){
        size += s.chunkSize;
        curr = curr->next;
    }
    // postconditions
    // return result
    return size;
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void swap(Stack& s) {
    // preconditions
    assert(isValidStack(s));
    assert(size(s) >= 2);
    // implementation
    string temp = s.firstChunk->val[s.topElt];
    if (s.topElt > 0) { // both values are in the same array
        s.firstChunk->val[s.topElt] = s.firstChunk->val[s.topElt - 1];
        s.firstChunk->val[s.topElt - 1] = temp;
    } else { // check the next array
        s.firstChunk->val[s.topElt] = s.firstChunk->next->val[s.chunkSize - 1];
        s.firstChunk->next->val[s.chunkSize - 1] = temp;
    }
    // postconditions
    assert(isValidStack(s));
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
string toString(const Stack& s) {
    // preconditions
    assert(isValidStack(s));
    // implementation
    string outString = "[";
    int leftThisStack = s.topElt + 1;
    NodeChunk* curr = s.firstChunk;
    while (curr != nullptr) {
        while (leftThisStack > 0) {
            outString += curr->val[leftThisStack-1];
            leftThisStack -= 1;
            if (!(leftThisStack == 0 && curr->next == nullptr)) { // not the last element
                outString += ", ";
            }
        }
        leftThisStack = s.chunkSize;
        curr = curr->next;
        // outString += "|";
    }

    outString += "]";
    // postconditions
    // return result
    return outString;
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
string top(const Stack& s) {
    // preconditions
    assert(isValidStack(s));
    assert(size(s) > 0);
    // implementation
    return s.firstChunk->val[s.topElt]; 
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void nuke(Stack& s) {
    // preconditions
    assert(isValidStack(s));
    // implementation
    NodeChunk* curr = s.firstChunk;
    while (curr != nullptr) {
        NodeChunk* nextNode = curr->next;
        delete [] curr->val;
        delete curr;
        curr = nextNode;
    }

    s.firstChunk = nullptr;
    s.topElt = -1;
    // postconditions
    assert(isValidStack(s));
    assert(isEmpty(s));
}
