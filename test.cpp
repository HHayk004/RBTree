#include "RBTree.h"

int main() //{1, 5, 2, 6, 7, 3, 4, 0}
{
    RBTree<int> tree{8, 7, 6, 5, 4, 3, 2, 1, 0};

    tree.printTree();

    return 0;
}