#include <iostream>
#include "BinaryTreeChecker.h"

using namespace std;

/**
 * Default constructor.
 */
BinaryTreeChecker::BinaryTreeChecker(BinarySearchTree& tree)
        : tree(tree)
{
    cache.clear();
}

/**
 * Destructor.
 */
BinaryTreeChecker::~BinaryTreeChecker()
{
}

/**
 * Clear the cache.
 */
void BinaryTreeChecker::clear()
{
    cache.clear();
}

/**
 * Add a tree node's data item to the cache.
 * @param data the data item to add.
 */
void BinaryTreeChecker::add(const int data)
{
    cache.insert(data);
}

/**
 * Remove a data item from the cache.
 * @param data the data item to remove.
 */
void BinaryTreeChecker::remove(const int data)
{
    cache.erase(data);
}

/**
 * Check the tree's current data items against the cache.
 * @param dump true to dump the data items in the tree and in the cache.
 * @return a status code.
 */
int BinaryTreeChecker::check(bool dump)
{
    data.clear();
    walk(tree.getRoot());

    return compare(dump);
}

/**
 * Do an inorder walk of the tree to collect its data items.
 * @param node the root node of the subtree to walk (initially the tree root).
 */
void BinaryTreeChecker::walk(BinaryNode *node)
{
    if (node == nullptr) return;

    walk(node->left);
    data.insert(node->data);
    walk(node->right);
}

/**
 * Compare the tree's data items against the data items in the cache.
 * @return a status code.
 */
int BinaryTreeChecker::compare(bool dump)
{
    typename set<int>::iterator itCache;
    typename set<int>::iterator itData;

    itCache = cache.begin();
    itData  = data.begin();

    if (dump) cout << endl;

    while (itCache != cache.end())
    {
        if (itData == data.end()) return INSUFFICIENT_DATA;
        if (dump) cout << *itData << ":" << *itCache << " ";
        if (*itCache != *itData) return DATA_MISMATCH;

        itCache++;
        itData++;
    }

    if (dump) cout << endl;
    if (itData != data.end()) return REMAINING_DATA;

    return NO_ERROR;
}