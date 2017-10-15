#include <iostream>
#include "BinaryTreePrinter.h"

using namespace std;

const int BinaryTreePrinter::POWERS_OF_2[] = {1, 2, 4, 8, 16, 32, 64, 128};

/**
 * Constructor.
 * @param tree the tree to print.
 */
BinaryTreePrinter::BinaryTreePrinter(BinarySearchTree& tree)
        : tree(tree)
{
}

/**
 * Destructor.
 */
BinaryTreePrinter::~BinaryTreePrinter()
{
}

/**
 * Print the tree using a level-order traversal.
 */
void BinaryTreePrinter::print()
{
    // Queue of nodes at this level.
    BinaryNode *thisLevelNodes[32];

    int height = tree.height();
    int offset = POWERS_OF_2[(height+1)]-1;

    thisLevelNodes[0] = tree.getRoot();

    // Loop to print each level of nodes.
    for (int level = 0; level <= height; level++)
    {
        if (level > MAX_LEVELS)
        {
            cout << "*** Too many levels to print. ***\n";
            break;
        }

        // Print node data.
        printData(level, offset, thisLevelNodes);

        if (level != height)
        {
            // Print outgoing pointers /\ from each parent node->
            printOutgoingPointers(level, offset, thisLevelNodes);

            offset = POWERS_OF_2[height - level] - 1;

            // Print connecting dashes ----
            if (level < height-1)
            {
                printConnectingDashes(level, offset, thisLevelNodes);
            }

            // Print incoming pointers / and \ to each child node->
            printIncomingPointers(level, offset, thisLevelNodes);

            // Prepare the next level of nodes.
            nextLevel(level, thisLevelNodes);
        }
    }
}

/**
 * Print node data.
 * @param level the current level
 * @param offset the current offset
 * @param levelNodes the current level of nodes
 */
void BinaryTreePrinter::printData(int level, int offset,
                                  BinaryNode *levelNodes[])
{
    printSpaces(offset);

    int k = POWERS_OF_2[level];
    for (int i = 0; i < k; i++)
    {
        BinaryNode *ptr = levelNodes[i];

        if (ptr != nullptr)
        {
            cout << setw(3) << ptr->data << " ";
        }
        else
        {
            cout << "    ";
        }

        // Space over to the next node in this level.
        if (i < k-1) printSpaces(2*offset - 2);
    }

    cout << endl;
}

/**
 * Print outgoing pointers /\ from each non-null parent node->
 * @param level the current level
 * @param offset the current offset
 * @param levelNodes the current level of nodes
 */
void BinaryTreePrinter::printOutgoingPointers(int level, int offset,
                                              BinaryNode *levelNodes[])
{
    printSpaces(offset);

    int k = POWERS_OF_2[level];
    for (int i = 0; i < k; i++)
    {
        BinaryNode *ptr = levelNodes[i];

        // Has left child: print / forward slash
        if ((ptr != nullptr) && (ptr->left != nullptr))
        {
            cout << " /";
        }

            // No left child: print space
        else
        {
            cout << "  ";
        }

        // Has right child: print \ backward slash
        if ((ptr != nullptr) && (ptr->right != nullptr))
        {
            cout << "\\ ";
        }

            // No right child: print space
        else
        {
            cout << "  ";
        }

        // Space over to the next node in this level.
        if (i < k-1) printSpaces(2*offset-2);
    }

    cout << endl;
}

/**
 * Print the connecting dashes between
 * an outgoing pointer and an incoming pointer.
 * @param level the current level
 * @param offset the current offset
 * @param levelNodes the current level of nodes
 */
void BinaryTreePrinter::printConnectingDashes(int level, int offset,
                                              BinaryNode *levelNodes[])
{
    if (offset > 1) printSpaces(offset);

    int k = POWERS_OF_2[level];
    for (int i = 0; i < k; i++)
    {
        BinaryNode *ptr = levelNodes[i];

        // Has left child: print dashes
        if ((ptr != nullptr) && (ptr->left != nullptr))
        {
            printSpaces(3);
            printDashes(offset-1);
        }

            // No left child: print spaces
        else
        {
            printSpaces(offset+2);
        }

        // Has right child: print dashes
        if ((ptr != nullptr) && (ptr->right != nullptr))
        {
            printSpaces(2);
            printDashes(offset-1);
        }

            // No right child: print spaces
        else
        {
            printSpaces(offset+1);
        }

        // Space over to the next node in this level.
        if (i < k-1) printSpaces(2*offset+1);
    }

    cout << endl;
}

/**
 * Print incoming pointers / or \ to each non-null child node->
 * @param level the current level
 * @param offset the current offset
 * @param levelNodes the current level of nodes
 */
void BinaryTreePrinter::printIncomingPointers(int level, int offset,
                                              BinaryNode *levelNodes[])
{
    printSpaces(offset);

    int k = POWERS_OF_2[level];
    for (int i = 0; i < k; i++)
    {
        BinaryNode *ptr = levelNodes[i];

        // Left child: print /
        if ((ptr != nullptr) && (ptr->left != nullptr))
        {
            cout <<"  /";
        }

            // No left child: print spaces
        else
        {
            printSpaces(3);
        }

        // Right child: print \ backward slash
        if ((ptr != nullptr) && (ptr->right != nullptr))
        {
            printSpaces(2*offset);
            cout << "\\";
        }

            // No right child: print spaces
        else
        {
            printSpaces(2*offset+1);
        }

        // Space over to the next node in this level.
        if (i < k-1) printSpaces(2*offset);
    }

    cout << endl;
}

/**
 * Prepare the next level of nodes.
 * @param level the current level
 * @param levelNodes the current level of nodes
 * @return the next level of nodes.
 */
void BinaryTreePrinter::nextLevel(int level, BinaryNode *levelNodes[])
{
    int size = POWERS_OF_2[level+1];
    BinaryNode *nextLevel[size];

    for (int i = 0; i < POWERS_OF_2[level]; i++)
    {
        BinaryNode *ptr = levelNodes[i];

        // Queue the left child nodes of each non-null parent node->
        nextLevel[2*i] = (ptr != nullptr) && (ptr->left != nullptr)
                         ? ptr->left : nullptr;

        // Queue the right child nodes of each non-null parent node->
        nextLevel[2*i+1] = (ptr != nullptr) && (ptr->right != nullptr)
                           ? ptr->right : nullptr;
    }

    for (int i = 0; i < size; i++) levelNodes[i] = nextLevel[i];
}

/**
 * Print spaces.
 * @param count the number of spaces.
 */
void BinaryTreePrinter::printSpaces(int count)
{
    for (int i = 0; i < count; i++) cout << " ";
}

/**
 * Print dashes.
 * @param count the number of dashes.
 */
void BinaryTreePrinter::printDashes(int count) {
    for (int i = 0; i < count; i++) cout << "-";
}
