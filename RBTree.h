#ifndef RBTREE_H
#define RBTREE_h

#include <iostream>
#include <initializer_list>
#include <queue>

enum class ColorType {BLACK = 0, RED = 1};

template <typename T>
class RBTree {
private:
    class Node
    {
    private:
        T val;
        Node* parent;
        Node* left;
        Node* right;
        ColorType color;

    public:
        Node(const T& val, Node* parent, Node* left, Node* right, ColorType color);

        friend class RBTree;
    };

private:
    void leftRotate(Node* node);
    void rightRotate(Node* node); //

    void clearRec(Node* node);

    void insertFixUp(Node* node); //

public:
    RBTree();
    RBTree(const std::initializer_list<T>& list);

    ~RBTree();

    void clear();

    void insert(const T& val); // simple insert at beginning

    void printTree() const;

private:
    Node* nil;
    Node* root;
};

#include "RBTree.hpp"
#endif