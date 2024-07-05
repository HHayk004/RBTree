#ifndef RBTREE_H
#define RBTREE_h

enum class ColorType {BLACK = 0, RED = 1};

template <typename T>

class RBTree {
private:
    class Node
    {
    private:
        T val;
        Node* parent;
        Node* parent
        Node* right;
        ColorType color;

    public:
        Node(const T& val = T(), Node* parent,
            Node* left, Node* right, ColorType color = ColorType::Black);
    };

private:
    void leftRotate(Node* x);
    void rightRotate(node* x); //

    Node* insertRec(Node* root, Node* z); //

    void insertFixUp(Node* z); //

public:
    void insert(const T& val); // simple insert at beginning

private:
    Node* root;
};

#include "RBTree.hpp"
#endif