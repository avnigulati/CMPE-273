/**
 * An implementation of the binary search tree and its operations.
 */

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <string>
#include "BinaryNode.h"

using namespace std;

class BinarySearchTree
{
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& rhs);
    virtual ~BinarySearchTree();

    BinaryNode *getRoot() const;
    int height() const;
    int findMin() const throw(string);
    int findMax() const throw(string);

    void clear();
    bool isEmpty() const;
    bool contains(const int data) const;
    void insert(const int data);
    void remove(const int data);

protected:
    virtual int height(const BinaryNode *ptr) const;
    virtual void insert(const int data, BinaryNode* &ptr);
    virtual void remove(const int data, BinaryNode* &ptr);

private:
    BinaryNode *root;

    BinaryNode *findMin(BinaryNode *ptr) const;
    BinaryNode *findMax(BinaryNode *ptr) const;
    void clear(BinaryNode* &ptr);
    bool contains(const int data, BinaryNode *ptr) const;
};


#endif // BINARY_TREE_CHECKER_H
