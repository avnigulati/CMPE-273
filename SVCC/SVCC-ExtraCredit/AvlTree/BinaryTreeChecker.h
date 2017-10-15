/**
 * A binary tree checker for those of us who are paranoid
 * about getting binary trees correct. It maintains a running
 * copy of a tree's node data in set elements. A tree node
 * deletion has a corresponding set element deletion. The tree
 * node data is compared to the set elements. Both the tree node
 * data and the set elements can be printed to verify they match.
 */

#ifndef BINARY_TREE_CHECKER_H
#define BINARY_TREE_CHECKER_H

#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
#include "BinaryNode.h"
#include "BinarySearchTree.h"

class BinaryTreeChecker
{
public:
    static const int NO_ERROR          =  0;
    static const int DATA_MISMATCH     = -1;
    static const int INSUFFICIENT_DATA = -2;
    static const int REMAINING_DATA    = -3;

    BinaryTreeChecker(BinarySearchTree& tree);
    virtual ~BinaryTreeChecker();

    void clear();
    void add(const int data);
    void remove(const int data);
    int check(bool dump);

private:
    BinarySearchTree& tree;  // the tree to check
    set<int> cache;          // the cache of data items
    set<int> data;           // the tree's data items

    void walk(BinaryNode *node);
    int compare(bool dump);
};

#endif // BINARY_TREE_CHECKER_H
