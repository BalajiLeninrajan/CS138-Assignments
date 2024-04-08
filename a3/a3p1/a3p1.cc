#include "a3p1.h"

#include <string>
#include <cassert>

using namespace std;

// provided for you
void initStew(Stew &q)
{
    // no preconditions
    // implementation
    q.first = nullptr;
    q.last = nullptr;
    // postconditions
    assert(isEmpty(q));
    assert(isValidStew(q));
}

// provided for you
bool isEmpty(const Stew &q)
{
    // no preconditions
    // note: if we called isValidStew(q) here we would likely get
    // stuck in an infinite loop, because isValidStew(q) might
    // call isEmpty(q)
    return (q.first == nullptr) && (q.last == nullptr);
}

// @TODO: define what a wellformed node looks like
// Note that simply returning true will pass some tests.
// Similarly, simply triggering an assertion will pass some tests.
// That is inherent in any procedure that returns bool.
// The challenge is to pass all the tests.
bool isValidNode(const Node &n)
{
    // either trip an assertion or return true
    // never return false
    assert(n.next != &n && n.prev != &n); // Checks if n points to itself
    if (n.next)
    {
        assert(n.next->prev == &n); // Checks if next points back to n
    }
    if (n.prev)
    {
        assert(n.prev->next == &n); // Checks if prev points back to n
    }
    // no assertions tripped, so return true
    return true;
}

// @TODO: define what a wellformed stew looks like
// Note that simply returning true will pass some tests.
// Similarly, simply triggering an assertion will pass some tests.
// That is inherent in any procedure that returns bool.
// The challenge is to pass all the tests.
bool isValidStew(const Stew &s)
{
    // either trip an assertion or return true
    // never return false
    if (isEmpty(s))
    {
        return true;
    }
    assert(s.first && s.last);               // Check if first and last exist
    assert(!s.first->prev && !s.last->next); // Check if ends are actually ends
    Node *cur;
    for (cur = s.first; cur->next; cur = cur->next)
    {
        isValidNode(*cur); // check if every node is valid
    }
    assert(cur == s.last); // Check if list fully connected
    isValidNode(*cur);

    // no assertions tripped, so return true
    return true;
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void addFront(Stew &q, string val)
{
    // preconditions
    assert(isValidStew(q));
    // implementation
    Node *new_node = new Node{val, q.first, nullptr};
    if (isEmpty(q))
    {
        q.last = new_node;
    }
    else
    {
        q.first->prev = new_node;
    }
    q.first = new_node;
    // postconditions
    assert(isValidStew(q));
    assert(q.first->val == val);
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void addBack(Stew &q, string val)
{
    // preconditions
    assert(isValidStew(q));
    // implementation
    Node *new_node = new Node{val, nullptr, q.last};
    if (isEmpty(q))
    {
        q.first = new_node;
    }
    else
    {
        q.last->next = new_node;
    }
    q.last = new_node;
    // postconditions
    assert(isValidStew(q));
    assert(q.last->val == val);
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void leaveFront(Stew &q)
{
    // preconditions
    assert(isValidStew(q));
    assert(!isEmpty(q));
    // implementation
    Node *tmp = q.first;
    q.first = q.first->next;
    if (!q.first)
    {
        q.last = nullptr;
        assert(isEmpty(q));
    }
    else
    {
        q.first->prev = nullptr;
    }
    delete tmp;
    // postconditions
    assert(isValidStew(q));
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void leaveBack(Stew &q)
{
    // preconditions
    assert(isValidStew(q));
    assert(!isEmpty(q));
    // implementation
    Node *tmp = q.last;
    q.last = q.last->prev;
    if (!q.last)
    {
        q.first = nullptr;
        assert(isEmpty(q));
    }
    else
    {
        q.last->next = nullptr;
    }
    delete tmp;
    // postconditions
    assert(isValidStew(q));
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
string peekBack(const Stew &q)
{
    // preconditions
    assert(isValidStew(q));
    assert(!isEmpty(q));
    // implementation
    // return result
    return q.last->val; // so this stub compiles and runs
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
string peekFront(const Stew &q)
{
    // preconditions
    assert(isValidStew(q));
    assert(!isEmpty(q));
    // implementation
    // return result
    return q.first->val; // so this stub compiles and runs
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
string toString(const Stew &q, char direction)
{
    // preconditions
    assert(isValidStew(q));
    if (direction != 'f' && direction != 'r')
    {
        return "Error, illegal direction: (" + string(1, direction) + ")";
    }
    // implementation
    string result = "[";
    Node *cur;
    if (direction == 'f')
    {
        for (cur = q.first; cur; cur = cur->next)
        {
            result += cur->val;
            if (cur->next)
            {
                result += ", ";
            }
        }
    }
    else
    {
        for (cur = q.last; cur; cur = cur->prev)
        {
            result += cur->val;
            if (cur->prev)
            {
                result += ", ";
            }
        }
    }
    result += "]";
    // return result
    return result; // so this stub compiles and runs
}

// @TODO: Preconditions, Postconditions, Tests, Implementation (in that order)
void nuke(Stew &q)
{
    // preconditions
    assert(isValidStew(q));
    // implementation
    while (!isEmpty(q))
    {
        leaveFront(q);
    }
    // postconditions
    assert(isEmpty(q));
}
