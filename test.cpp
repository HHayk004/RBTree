#include "RBTree.h"

int main()
{
    RBTree<int> tree{8, 7, 6, 5, 4, 3, 2, 1, 0};

    tree.printTree();
    std::cout << std::endl;

    tree.deleteNode(7);

    tree.printTree();
    std::cout << std::endl;

    return 0;
}