/**
 * An implementation of the AVL tree and its operations.
 * Derived from the binary search tree.
 */

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "BinarySearchTree.h"

class AvlTree : public BinarySearchTree
{
public:
    AvlTree();
    virtual ~AvlTree();

protected:
    virtual int height(const BinaryNode *ptr) const;
    virtual void insert(const int data, BinaryNode* &ptr);
    virtual void remove(const int data, BinaryNode* &ptr);

private:
    BinaryNode *balance(BinaryNode* &ptr);
    BinaryNode *singleRightRotation(BinaryNode *k2);
    BinaryNode *doubleLeftRightRotation(BinaryNode *k3);
    BinaryNode *doubleRightLeftRotation(BinaryNode *k1);
    BinaryNode *singleLeftRotation(BinaryNode *k1);
    int checkBalance(BinaryNode *ptr);
};

#endif // AVL_TREE_H
