#include <string>
#include "BinarySearchTree.h"

using namespace std;

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() : root(nullptr)
{
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree()
{
    clear();
}

/**
 * @return pointer to the root of the tree.
 */
BinaryNode *BinarySearchTree::getRoot() const
{
    return root;
}

/**
 * Public method to return the height of a subtree.
 * @return the height.
 */
int BinarySearchTree::height() const
{
    return height(root);
}

/**
 * Protected method to compute the height of a subtree.
 * @param ptr pointer to the root node of the subtree.
 * @return the height.
 */
int BinarySearchTree::height(const BinaryNode *ptr) const
{
    return ptr == nullptr ? -1
                          : 1 + max(height(ptr->left),
                                    height(ptr->right));
}

/**
 * Public method to find the minimum data item in a subtree.
 * @return the minimum data item in the tree
 *         or nullptr if the tree is empty.
 */
int BinarySearchTree::findMin() const throw(string)
{
    if (isEmpty()) throw(string("Empty tree"));
    return findMin(root)->data;
}

/**
 * Private method to find the minimum data item in a subtree.
 * @param ptr pointer to the root node of the subtree.
 * @return pointer to the node containing the smallest data item
 *         or nullptr if the subtree is empty.
 */
BinaryNode *BinarySearchTree::findMin(BinaryNode *ptr) const
{
    if (ptr != nullptr)
    {
        while(ptr->left != nullptr) ptr = ptr->left;
    }

    return ptr;
}

/**
 * Public method to find the maximum data item in a subtree.
 * @return pointer to the maximum data item in the tree
 *         or nullptr if the tree is empty.
 */
int BinarySearchTree::findMax() const throw(string)
{
    if (isEmpty()) throw(string("Empty tree"));
    return findMax(root)->data;
}

/**
 * Private method to find the maximum data item in a subtree.
 * @param ptr pointer to the root node of the subtree.
 * @return pointer to the node containing the largest data item
 *         or nullptr if the subtree is empty.
 */
BinaryNode *BinarySearchTree::findMax(BinaryNode *ptr) const
{
    if (ptr != nullptr)
    {
        while(ptr->right != nullptr) ptr = ptr->right;
    }

    return ptr;
}

/**
 * Public method to empty a subtree.
 */
void BinarySearchTree::clear()
{
    clear(root);
}

/**
 * Private method to empty a subtree.
 * @param ptr pointer to the root node of the subtree.
 */
void BinarySearchTree::clear(BinaryNode* &ptr)
{
    if (ptr != nullptr)
    {
        clear(ptr->left);
        clear(ptr->right);
        delete ptr;
        ptr = nullptr;
    }
}

/**
 * @return true if and only if the tree is empty.
 */
bool BinarySearchTree::isEmpty() const
{
    return root == nullptr;
}

/**
 * Public method to search for a data item in the tree.
 * @param data the data to search for.
 * @return true if and only if data is in the tree.
 */
bool BinarySearchTree::contains(const int data) const
{
    return contains(data, root);
}

/**
 * Private method to search for a data item in a subtree.
 * @param data the data to search for.
 * @param ptr pointer to the root node of the subtree.
 * @return true if and only if data is in the tree.
 */
bool BinarySearchTree::contains(const int data, BinaryNode *ptr) const
{
    while (ptr != nullptr)
    {
        if (data < ptr->data)
        {
            ptr = ptr->left;
        }
        else if (data > ptr->data)
        {
            ptr = ptr->right;
        }
        else
        {
            return true;  // found
        }
    }

    return false;         // not found
}

/**
 * Public method to insert a data item into a subtree
 * and set the new root of the subtree.
 * @param data the data to insert into the tree.
 */
void BinarySearchTree::insert(const int data)
{
    insert(data, root);
}

/**
 * Protected method to insert a data item into a subtree
 * and set the new root of the subtree.
 * @param data the data to insert.
 * @param ptr pointer to the root node of the subtree.
 */
void BinarySearchTree::insert(const int data, BinaryNode* &ptr)
{
    if (ptr == nullptr)
    {
        ptr = new BinaryNode(data);
    }
    else if (data < ptr->data)
    {
        insert(data, ptr->left);
    }
    else if (data > ptr->data)
    {
        insert(data, ptr->right);
    }
}

/**
 * Public method to remove a data item from a subtree
 * and set the new root of the subtree.
 * Do nothing if the data item is not found.
 * @param data the data to remove.
 */
void BinarySearchTree::remove(const int data)
{
    remove(data, root);
}

/**
 * Protected method to remove a data item from a subtree
 * and set the new root of the subtree.
 * Do nothing if the data item is not found.
 * @param data the data to remove.
 * @param ptr pointer to the root node of the subtree.
 */
void BinarySearchTree::remove(const int data, BinaryNode* &ptr)
{
    if (ptr == nullptr) return;   // not found, so do nothing

    // First search for the target node to remove.
    if (data < ptr->data)
    {
        remove(data, ptr->left);
    }
    else if (data > ptr->data)
    {
        remove(data, ptr->right);
    }

        // Remove a target node with two children.
    else if (   (ptr->left  != nullptr)
                && (ptr->right != nullptr))
    {
        // Replace the target node's data with the successor node's data.
        ptr->data = findMin(ptr->right)->data;

        // Search for and remove the successor node.
        remove(ptr->data, ptr->right);
    }

        // Remove a target node with one or no children.
    else
    {
        BinaryNode *oldNode = ptr;
        ptr = (ptr->left != nullptr) ? ptr->left
                                     : ptr->right;
        delete oldNode;
    }
}