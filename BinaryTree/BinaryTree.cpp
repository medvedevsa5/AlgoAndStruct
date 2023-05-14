#include <iostream>
#include "BinarySearchTree.h"

template <typename T>
bool isBalancedRecurrent(BinarySearchTree<T>& tree);
template <typename T>
bool isBalancedIterative(BinarySearchTree<T>& tree);

int main()
{
    auto tree = new BinarySearchTree<int>();

    tree->insert(5);
    tree->insert(3);
    tree->insert(7);

    //tree->insert(10);
    //tree->insert(15); // раскомментируйте, чтобы сделать несбалансированным
    //tree->insert(20);

    tree->print(std::cout);

    std::cout << '\n' << std::boolalpha
        << isBalancedIterative(*tree) << '\n'
        << isBalancedRecurrent(*tree) << std::endl;

    delete tree;
}

template <typename T>
bool isBalancedRecurrent(BinarySearchTree<T>& tree)
{
    return tree.isBalancedRecurrent();
}

template <typename T>
bool isBalancedIterative(BinarySearchTree<T>& tree)
{
    return tree.isBalancedIterative();
}