cmake_minimum_required(VERSION 3.7)
project(Assignment13)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    #    main.cpp
        AvlTree.cpp
        AvlTree.h
        BinaryNode.cpp
        BinaryNode.h
        BinarySearchTree.cpp
        BinarySearchTree.h
        BinaryTreePrinter.cpp
        BinaryTreePrinter.h
        BSTApp.cpp
        BinaryTreeChecker.cpp
        BinaryTreeChecker.h)
add_executable(Assignment13 ${SOURCE_FILES})