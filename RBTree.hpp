template <typename T>
void RBTree<T>::leftRotate(Node* x)
{
    Node* y = x->right;
    x->right = y->left;
    
    if (y->left != nil) // esim es nili momenty
    {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nil)
    {
        root = y;
    }

    else if (x == x->left->parent)
    {
        x->parent->left = y;
    }

    y->left = x;
    x->parent = y;
}