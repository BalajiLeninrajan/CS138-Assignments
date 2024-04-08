#include <string>
#include <cassert>

struct Node
{
    std::string val;
    Node *next;
    Node *prev;
};

struct Stew
{
    Node *first;
    Node *last;
};

bool isValidNode(const Node &n);
bool isValidStew(const Stew &s);
