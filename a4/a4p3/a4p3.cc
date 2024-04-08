#include <iostream>
#include <string>
#include <cassert>
#include "a4p3.h"
using namespace std;

/* ************************************************************** */
// Queue Functions
// -----------------------------------------------------------------

void Q_init(Queue &q)
{
    q.first = nullptr;
    q.last = nullptr;
}

bool Q_isEmpty(const Queue &q)
{
    return nullptr == q.first;
}

void Q_enter(Queue &q, Qnode *p)
{
    if (Q_isEmpty(q))
    {
        q.first = p;
    }
    else
    {
        q.last->next = p;
    }
    q.last = p;
}

string Q_first(const Queue &q)
{
    return q.first->name;
}

void Q_leave(Queue &q)
{
    q.first = q.first->next;
    if (nullptr == q.first)
    {
        q.last = nullptr;
    }
}

/* ************************************************************** */
// BST Functions
// -----------------------------------------------------------------
void BST_init(BST &root)
{
    root = nullptr;
}

bool BST_isEmpty(const BST &root)
{
    return nullptr == root;
}

bool BST_has(const BST &root, std::string name)
{
    if (nullptr == root)
    {
        return false;
    }
    else if (root->name == name)
    {
        return true;
    }
    else if (root->name > name)
    {
        return BST_has(root->left, name);
    }
    else
    {
        return BST_has(root->right, name);
    }
}

void BST_insert(BST &root, BST_Node *node)
{
    if (nullptr == root)
    {
        root = node;
    }
    else if (node->name < root->name)
    {
        BST_insert(root->left, node);
    }
    else
    {
        BST_insert(root->right, node);
    }
}

void BST_remove(BST &root, std::string name)
{
    if (root->name > name)
    {
        BST_remove(root->left, name);
        return;
    }
    else if (root->name < name)
    {
        BST_remove(root->right, name);
        return;
    }

    BST tmp = root;
    if (root->left == nullptr)
    {
        root = root->right;
        delete tmp;
    }
    else if (root->right == nullptr)
    {
        root = root->left;
        delete tmp;
    }
    else
    {
        BST mx = root->left;
        if (BST_isEmpty(mx->right))
        {
            mx->right = root->right;
            root = mx;
            delete tmp;
            return;
        }

        while (!BST_isEmpty(mx->right->right))
        {
            mx = mx->right;
        }
        BST new_root = mx->right;
        mx->right = new_root->left;
        new_root->left = root->left;
        new_root->right = root->right;
        root = new_root;
        delete tmp;
    }
}

void BST_nuke(BST &root)
{
    if (BST_isEmpty(root))
    {
        return;
    }
    BST_nuke(root->left);
    BST_nuke(root->right);
    delete root;
}

string BST_to_string(const BST &root)
{
    if (BST_isEmpty(root))
    {
        return "";
    }
    return BST_to_string(root->left) + root->name + ", " + BST_to_string(root->right);
}

/* ************************************************************** */
// SBL Functions
// -----------------------------------------------------------------

// Implement the following SBL functions.
void SBL_init(SBL &sbl)
{
    Queue q;
    Q_init(q);
    sbl.q = q;

    BST root;
    BST_init(root);
    sbl.root = root;

    sbl.numElts = 0;
}

int SBL_size(const SBL &sbl)
{
    return sbl.numElts;
}

void SBL_arrive(SBL &sbl, std::string name)
{
    SBLnode *newNode = new SBLnode{name, nullptr, nullptr};
    Q_enter(sbl.q, newNode);
    BST_insert(sbl.root, newNode);
    sbl.numElts++;
}

void SBL_leave(SBL &sbl)
{
    if (SBL_size(sbl) == 0)
    {
        cerr << "Error, SBL is empty." << endl;
        exit(1);
    }
    string key = Q_first(sbl.q);
    Q_leave(sbl.q);
    BST_remove(sbl.root, key);
    sbl.numElts--;
}

std::string SBL_first(const SBL &sbl)
{
    if (SBL_size(sbl) == 0)
    {
        cerr << "Error, SBL is empty." << endl;
        exit(1);
    }
    return Q_first(sbl.q);
}

bool SBL_has(const SBL &sbl, std::string name)
{
    return BST_has(sbl.root, name);
}

std::string SBL_toArrivalOrderString(const SBL &sbl)
{
    if (SBL_size(sbl) == 0)
    {
        return "[]";
    }

    string res = "[" + sbl.q.first->name;
    for (SBLnode *curr = sbl.q.first->next; curr; curr = curr->next)
    {
        res += ", " + curr->name;
    }
    return res + "]";
}

std::string SBL_toLexicographicalOrderString(const SBL &sbl)
{
    if (SBL_size(sbl) == 0)
    {
        return "[]";
    }
    string res = "[" + BST_to_string(sbl.root);
    res.replace(res.end() - 2, res.end(), "]");
    return res;
}

void SBL_nuke(SBL &sbl)
{
    BST_nuke(sbl.root);
    BST_init(sbl.root);
    Q_init(sbl.q);
}