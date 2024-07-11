template <typename T>
RBTree<T>::RBTree() : nil(new Node(T(), nullptr, nullptr, nullptr, ColorType::BLACK))
{
    root = nil;
}

template <typename T>
RBTree<T>::RBTree(const std::initializer_list<T>& list) : nil(new Node(T(), nullptr, nullptr, nullptr, ColorType::BLACK))
{
    root = nil;
    for (const auto& elem : list)
    {
        insert(elem);
    }
}

template <typename T>
RBTree<T>::~RBTree()
{
    delete nil;
    clear();
}

template <typename T>
void RBTree<T>::clear()
{
    clearRec(root);
}

template <typename T>
void RBTree<T>::clearRec(Node* node)
{
    if (node != nil)
    {
        clearRec(node->left);
        clearRec(node->right);

        delete node;
    }
}

template <typename T>
RBTree<T>::Node::Node(const T& val, Node* parent, Node* left, Node* right, ColorType color) : 
                        val(val), parent(parent), left(left), right(right), color(color) {}

template <typename T>
void RBTree<T>::leftRotate(Node* x)
{
    Node* y = x->right;
    x->right = y->left;
    
    if (y->left != nil)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nil)
    {
        root = y;
    }

    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }

    else
    {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

template <typename T>
void RBTree<T>::rightRotate(Node* x)
{
    Node* y = x->left;
    x->left = y->right;

    if (x->left != nil)
    {
        x->left->parent = x;
    }

    y->parent = x->parent;

    if (y->parent == nil)
    {
        root = y;
    }

    else if (x->parent->left == x)
    {
        x->parent->left = y;
    }

    else
    {
        x->parent->right = y;
    }

    y->right = x;
    x->parent = y;
}

template <typename T>
void RBTree<T>::insert(const T& val)
{
    Node* new_node = new Node(val, nil, nil, nil, ColorType::RED);
    Node* prev = nil;
    Node* node = root;
    while (node != nil)
    {
        prev = node;
        if (node->val > val)
        {
            node = node->left;
        }

        else if (node->val < val)
        {
            node = node->right;
        }

        else
        {
            return;
        }
    }

    if (prev == nil)
    {
        root = new_node;
    }

    else if (prev->val > val)
    {
        prev->left = new_node;
    }

    else
    {
        prev->right = new_node;
    }

    new_node->parent = prev;
    insertFixUp(new_node);
}

template <typename T>
void RBTree<T>::insertFixUp(Node* node)
{
    while (node->parent->color == ColorType::RED)
    {
        if (node->parent == node->parent->parent->left)
        {
            Node* y = node->parent->parent->right;
            if (y->color == ColorType::RED)
            {
                node->parent->color = ColorType::BLACK;
                y->parent->color = ColorType::RED;
                y->color = ColorType::BLACK;
                node = node->parent->parent;
            }

            else
            {
                if (node == node->parent->right)
                {
                    leftRotate(node->parent);
                }

                node->parent->color = ColorType::BLACK;
                node->parent->parent->color = ColorType::RED;

                rightRotate(node->parent->parent);
            }
        }

        else
        {
            Node* y = node->parent->parent->left;
            if (y->color == ColorType::RED)
            {
                node->parent->color = ColorType::BLACK;
                y->parent->color = ColorType::RED;
                y->color = ColorType::BLACK;
                node = node->parent->parent;
            }

            else
            {
                if (node == node->parent->left)
                {
                    rightRotate(node->parent);
                }

                node->parent->color = ColorType::BLACK;
                node->parent->parent->color = ColorType::RED;

                leftRotate(node->parent->parent);
            }
        }
    }

    root->color = ColorType::BLACK;
}

template <typename T>
void RBTree<T>::transplant(Node* u, Node* v)
{
    if (u->parent == nil)
    {
        root = v;
    }

    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }

    v->parent = u->parent;
}

template <typename T>
void RBTree<T>::delete(const T& val)
{
    Node* z = root;

    while (z != nil && z->val != val)
    {
        if (z->val > val)
        {
            z = z->left;
        }

        else
        {
            z = z->right;
        }
    }

    if (z != nil)
    {
        Node* y = z;
        ColorType y_org_color = y->color;
        Node* x = nil;

        if (z->left == nil)
        {
            x = z->right;
            transplant(z, z->right);
        }

        else if (z->right == nil)
        {
            x = z->left;
            transplant(z, z->left);
        }

        else
        {
            y = getMin(z->right);
            y_org_color = y->color;
            x = y->right;
        
            if (y->parent == z)
            {
                x->parent = z;
            }

            else
            {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
    
            if (y_org_color == ColorType::BlACK)
            {
                deleteFixUp(x);
            }
        }
    }
}

template <typename T>
void RBTree<T>::printTree() const // printing tree (levelOrder + endl + nullptr nodes)
{
	int count = 0; // current count of nodes
	int n = 1; // level nodes count
	bool check = false; // check for not nullptr nodes
	std::queue<Node*> roots; // same mean as in level order
	if (root != nil) // if tree isn't empty, push m_root to roots and initialize count
	{
        std::cout << ":";
		roots.push(root);
		count = 1;
	}

	while (count) // cycle while there are valid nodes
	{
		Node* root = roots.front(); // root to roots first value
		if (root != nil) // if root is valid
		{
			check |= (root->left != nil || root->right != nil); // for finding valid node
			roots.push(root->left); // pushing the nodes
			roots.push(root->right);

            if (root->color == ColorType::BLACK)
            {
                std::cout << "B|";
            }

            else
            {
                std::cout << "R|";
            }

			std::cout << root->val << ':'; // printing nodes value
		}

		else // printing ' '
		{
			roots.push(nil); // for printing tree in appropriate way
			roots.push(nil);
			std::cout << " :";
		}

		--count; // decrease the count of nodes
		if (!count) // if count = 0, check if there are any valid nodes that wasn't printed
		{
			if (!check) // if there aren't break from cycle
			{
				break;
			}
				
			check = false; // refresh check value

			std::cout << std::endl << ':'; // for output clearity
				
			count = 2 * n; // nodes count in current level
			n *= 2; // for next count initialization
		}

		roots.pop(); // removing root from roots
	}

    std::cout << std::endl; // for output clearity
}