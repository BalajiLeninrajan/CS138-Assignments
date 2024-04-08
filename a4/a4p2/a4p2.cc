#include <iostream>
#include <string>
#include <cassert>
#include "a4p2.h"

using namespace std;

// Provided implementations for BST routines

void BST_init(BST &root)
{
    root = nullptr;
}

bool BST_isEmpty(const BST &root)
{
    return nullptr == root;
}

bool BST_has(const BST &root, std::string key)
{
    if (nullptr == root)
    {
        return false;
    }
    else if (root->key == key)
    {
        return true;
    }
    else if (root->key > key)
    {
        return BST_has(root->left, key);
    }
    else
    {
        return BST_has(root->right, key);
    }
}

void BST_insert(BST &root, std::string key)
{
    if (nullptr == root)
    {
        root = new BST_Node;
        root->key = key;
        root->left = nullptr;
        root->right = nullptr;
    }
    else if (key < root->key)
    {
        BST_insert(root->left, key);
    }
    else
    {
        BST_insert(root->right, key);
    }
}

// Implement the following two routines.
void BST_remove(BST &root, std::string key)
{
    if (!BST_has(root, key))
    {
        cerr << "Error, couldn't find \"" << key << "\" in the BST\n";
        exit(1);
    }

    if (root->key > key)
    {
        BST_remove(root->left, key);
        return;
    }
    else if (root->key < key)
    {
        BST_remove(root->right, key);
        return;
    }

    if (root->left == nullptr)
    {
        BST tmp = root;
        root = root->right;
        delete tmp;
    }
    else if (root->right == nullptr)
    {
        BST tmp = root;
        root = root->left;
        delete tmp;
    }
    else
    {
        BST mx = root->left;
        if (BST_isEmpty(mx->right))
        {
            root->key = mx->key;
            root->left = mx->left;
            delete mx;
            return;
        }

        while (!BST_isEmpty(mx->right->right))
        {
            mx = mx->right;
        }
        BST tmp = mx->right;
        root->key = tmp->key;
        mx->right = tmp->left;
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
