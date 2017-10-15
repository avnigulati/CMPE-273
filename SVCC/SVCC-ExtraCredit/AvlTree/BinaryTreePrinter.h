/**
 * Printer for a binary tree of up to height 5.
 */

#ifndef BINARY_TREE_PRINTER_H
#define BINARY_TREE_PRINTER_H

#include <iostream>
#include <iomanip>
#include <string>
#include "BinaryNode.h"
#include "BinarySearchTree.h"

class BinaryTreePrinter
{
public:
    static const int MAX_HEIGHT = 5;  // cannot print trees > MAX_HEIGHT

private:
    static const int MAX_LEVELS = MAX_HEIGHT + 1;
    static const int POWERS_OF_2[];

public:
    BinaryTreePrinter(BinarySearchTree& tree);
    virtual ~BinaryTreePrinter();

    void print();

private:
    BinarySearchTree& tree;  // the tree to print

    void printData(int level, int offset,
                   BinaryNode *levelNodes[]);
    void printOutgoingPointers(int level, int offset,
                               BinaryNode *levelNodes[]);
    void printConnectingDashes(int level, int offset,
                               BinaryNode *levelNodes[]);
    void printIncomingPointers(int level, int offset,
                               BinaryNode *levelNodes[]);
    void nextLevel(int level, BinaryNode *levelNodes[]);
    void printSpaces(int count);
    void printDashes(int count);
};

#endif // BINARY_TREE_PRINTER_H
