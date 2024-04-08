#include <string>
#include <vector>
#include <cassert>

#include "a2p2.h"

using namespace std;

Node *makeList(const std::vector<std::string> v)
{
    if (v.size() == 0)
    {
        return nullptr;
    }

    Node *head = new Node{};
    head->next = nullptr;
    head->val = v.at(0);
    Node *cur = head;

    for (int i = 1; i < v.size(); i++, cur = cur->next)
    {
        Node *newNode = new Node{};
        newNode->next = nullptr;
        newNode->val = v.at(i);
        cur->next = newNode;
    }

    return head;
}

std::string list2string(const Node *first)
{
    if (!first)
    {
        return "";
    }

    string res;
    for (res = ""; first; first = first->next)
    {
        res += " " + first->val;
    }
    res.erase(0, 1);
    return res;
}

std::string pair2sortedString(const Node *p1, const Node *p2)
{
    assert(p1 && p2);
    return p1->val < p2->val ? p1->val + " " + p2->val : p2->val + " " + p1->val;
}

Node *sortPair(Node *p1, Node *p2)
{
    assert(p1 && p2);
    if (p1->val < p2->val)
    {
        p2->next = nullptr;
        p1->next = p2;
        return p1;
    }
    else
    {
        p1->next = nullptr;
        p2->next = p1;
        return p2;
    }
}

Node *makeSortedPairList(const std::string s1, const std::string s2)
{
    Node *n1 = new Node{s1, nullptr};
    Node *n2 = new Node{s2, nullptr};
    if (s1 < s2)
    {
        n1->next = n2;
        return n1;
    }
    else
    {
        n2->next = n1;
        return n2;
    }
}

Node *append(Node *p1, Node *p2)
{
    if (!p1)
    {
        return p2;
    }

    Node *cur;

    for (cur = p1; cur->next; cur = cur->next)
    {
    }

    cur->next = p2;

    return p1;
}
