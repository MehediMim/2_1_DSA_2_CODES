#include <bits/stdc++.h>
using namespace std;
#include "color.hpp"
struct node
{
    int key;
    string value;
    node *left;
    node *right;
    node *parent;
    char color;

    node(int key, string value)
    {
        this->key = key;
        this->value = value;
        left = NULL;
        right = NULL;
        parent = NULL;
        color = 'R';
    }
    node()
    {
        left = NULL;
        right = NULL;
        parent = NULL;
        color = 'R';
    }
    void moveDown(node *nParent)
    {
        if (parent != NULL)
        {
            if (this == parent->left)
            {
                parent->left = nParent;
            }
            else
            {
                parent->right = nParent;
            }
        }
        nParent->parent = parent;
        parent = nParent;
    }
};

class RedBlackTree
{
private:
    node *root;
    bool LL, RR, LR, RL;
    int size;

public:
    node *insertutil(node *root, int key, string value);
    void insert(int key, string value);
    node *erase(int key);
    void eraseutil(node *v);
    node *find(int key);
    node *leftRotate(node *node);
    node *rightRotate(node *node);
    node *uFinder(node *v);
    node *successor(node *v);
    node *siblingFinder(node *v);
    void DoubleBlackFix(node *v);
    void iterate_helper(node *root)
    {
        if (root == NULL)
            return;

        iterate_helper(root->left);
        if (root->color == 'R')
        {
            cout << dye::red_on_black(root->key);
            cout << " => ";
            cout << dye::red_on_black(root->value) << " " << endl;
        }
        else
        {
            cout << root->key << " => " << root->value << " " << endl;
        }
        iterate_helper(root->right);
    }

    void iterate()
    {
        iterate_helper(this->root);
    }

    int size_tree()
    {
        return this->size;
    }

    bool isempty()
    {
        return this->size == 0;
    }
    void clearHelper(node *current)
    {
        if (current == nullptr)
            return;

        clearHelper(current->left);
        clearHelper(current->right);

        delete current;
    }

    bool clear()
    {
        if (this->root == nullptr && size == 0)
            return false;
        else
        {
            clearHelper(this->root);
            this->root = nullptr;
            size = 0;
            return true;
        }
    }

    RedBlackTree()
    {
        this->root = NULL;
        this->LL = false;
        this->RR = false;
        this->LR = false;
        this->RL = false;
        size = 0;
    }
    ~RedBlackTree()
    {
        // clear();
    }

    void print_helper(node *root)
    {
        if (root == NULL)
        {
            return;
        }
        if (root->color == 'R')
        {
            cout << dye::red_on_black(root->key);
            cout << dye::red_on_black("_");
            cout << dye::red_on_black(root->value);
        }
        else
            cout << root->key << "_" << root->value;

        if (root->left != NULL || root->right != NULL)
        {
            cout << "(";
            print_helper(root->left);
            cout << ",";
            print_helper(root->right);
            cout << ")";
        }
    }
    void print()
    {
        print_helper(this->root);
        cout << endl;
    }

    void left_Rotate(node *x)
    {

        node *nParent = x->right;

        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        x->right = nParent->left;

        if (nParent->left != NULL)
            nParent->left->parent = x;

        nParent->left = x;
    }

    void right_Rotate(node *x)
    {

        node *nParent = x->left;

        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        x->left = nParent->right;

        if (nParent->right != NULL)
            nParent->right->parent = x;

        nParent->right = x;
    }
};

node *RedBlackTree::leftRotate(node *n)
{
    node *x = n->right;
    node *y = x->left;
    n->right = y;
    x->left = n;
    n->parent = x;
    if (y != nullptr)
        y->parent = n;
    return x;
}

node *RedBlackTree::rightRotate(node *n)
{
    node *x = n->left;
    node *y = x->right;
    n->left = y;
    x->right = n;
    n->parent = x;
    if (y != nullptr)
        y->parent = n;
    return x;
}

void RedBlackTree::insert(int key, string value)
{
    if (root == nullptr)
    {
        root = new node(key, value);
        root->color = 'B';
        size++;
    }
    else
        root = insertutil(root, key, value);
    if (root->parent)
    {
        root->parent = NULL;
    }
}

node *RedBlackTree::insertutil(node *root, int key, string value)
{
    bool RRConflict = false;

    if (root == nullptr)
    {
        size++;
        return new node(key, value);
    }

    if (root->key == key)
    {
        root->value = value;
        return root;
    }
    else if (key < root->key)
    {
        root->left = insertutil(root->left, key, value);
        root->left->parent = root;

        if (root->color == 'R' && root->left->color == 'R')
            RRConflict = true;
    }
    else if (key > root->key)
    {
        root->right = insertutil(root->right, key, value);
        root->right->parent = root;

        if (root->color == 'R' && root->right->color == 'R')
            RRConflict = true;
    }

    if (RR)
    {
        root = leftRotate(root);
        root->color = 'B';
        root->left->color = 'R';
        RR = false;
    }
    else if (LL)
    {
        root = rightRotate(root);
        root->color = 'B';
        root->right->color = 'R';
        LL = false;
    }
    if (RL)
    {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
        root->color = 'B';
        root->left->color = 'R';
        RL = false;
    }
    if (LR)
    {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
        root->color = 'B';
        root->right->color = 'R';
        LR = false;
    }
    if (RRConflict)
    {
        if (root->parent->right == root)
        {
            if (root->parent->left && root->parent->left->color == 'R')
            {
                root->color = 'B';
                root->parent->left->color = 'B';
                if (root->parent != this->root)
                    root->parent->color = 'R';
            }
            else
            {
                if (root->right && root->right->color == 'R')
                {
                    RR = true;
                }
                else if (root->left && root->left->color == 'R')
                {
                    RL = true;
                }
            }
        }
        else if (root->parent->left == root)
        {
            if (root->parent->right && root->parent->right->color == 'R')
            {
                root->color = 'B';
                root->parent->right->color = 'B';
                if (root->parent != this->root)
                    root->parent->color = 'R';
            }
            else
            {
                if (root->right && root->right->color == 'R')
                {
                    LR = true;
                }
                else if (root->left && root->left->color == 'R')
                {
                    LL = true;
                }
            }
        }
        RRConflict = false;
    }
    return root;
}

node *RedBlackTree::find(int key)
{
    node *temp = this->root;
    while (temp != nullptr)
    {
        if (key == temp->key)
        {
            return temp;
        }
        else if (key < temp->key)
        {
            temp = temp->left;
        }
        else if (key > temp->key)
        {
            temp = temp->right;
        }
    }
    return NULL;
}

node *RedBlackTree::erase(int key)
{
    node *temp = find(key);
    if (temp == nullptr)
    {
        return NULL;
    }
    eraseutil(temp);
    this->size--;
    return this->root;
}

node *RedBlackTree::successor(node *v)
{
    node *x = v->right;
    while (x != nullptr && x->left != nullptr)

    {
        x = x->left;
    }
    return x;
}

node *RedBlackTree::uFinder(node *x)
{

    if (x->left != NULL and x->right != NULL)
        return successor(x->right);

    if (x->left == NULL and x->right == NULL)
        return NULL;

    if (x->left != NULL)
        return x->left;
    else
        return x->right;
}

node *RedBlackTree::siblingFinder(node *v)
{
    if (v->parent == NULL)
        return NULL;
    if (v->parent->left == v)
        return v->parent->right;

    return v->parent->left;
}

void RedBlackTree::DoubleBlackFix(node *doubleBlackNode)
{
    if (doubleBlackNode == this->root)
    {
        return;
    }

    node *sibling = siblingFinder(doubleBlackNode);
    node *parent = doubleBlackNode->parent;

    if (sibling == nullptr)
    {
        DoubleBlackFix(parent);
    }
    else
    {
        if (sibling->color == 'R')
        {
            parent->color = 'R';
            sibling->color = 'B';

            if (sibling == sibling->parent->left)
            {
                // left_Rotate(parent);
                right_Rotate(parent);
            }
            else
            {
                // right_Rotate(parent);
                left_Rotate(parent);
            }

            if (parent->parent != nullptr)
            {
                if (parent->parent->left == parent)
                {
                    parent->parent->left = parent;
                }
                else
                {
                    parent->parent->right = parent;
                }
            }
            else
            {
                this->root = parent;
            }
            DoubleBlackFix(doubleBlackNode);
        }
        else
        {
            if (sibling->left != nullptr && sibling->left->color == 'R')
            {
                if (sibling->parent->left == sibling)
                {
                    sibling->left->color = sibling->color;
                    sibling->color = parent->color;
                    parent->color = 'B';
                    // left_Rotate(parent);
                    right_Rotate(parent);
                }
                else
                {
                    sibling->left->color = parent->color;
                    parent->color = 'B';
                    right_Rotate(sibling);
                    left_Rotate(parent);
                }
            }
            else if (sibling->right != nullptr && sibling->right->color == 'R')
            {
                if (sibling == sibling->parent->left)
                {
                    sibling->right->color = parent->color;
                    parent->color = 'B';
                    left_Rotate(sibling);
                    right_Rotate(parent);
                }
                else
                {
                    sibling->right->color = parent->color;
                    sibling->color = parent->color;
                    parent->color = 'B';
                    // right_Rotate(parent);
                    left_Rotate(parent);
                }
            }
            else
            {
                sibling->color = 'R';
                if (parent->color == 'B')
                {
                    DoubleBlackFix(parent);
                }
                else
                {
                    parent->color = 'B';
                }
            }
        }
    }
}

void RedBlackTree::eraseutil(node *v)
{

    node *u = NULL;

    if (v->left != NULL and v->right != NULL)
    {
        u = successor(v);
    }

    else if (v->left == NULL and v->right == NULL)
    {
        u = NULL;
    }

    else
    {
        if (v->left != NULL)
        {
            u = v->left;
        }
        else
        {
            u = v->right;
        }
    }

    bool bothBlack = ((u == nullptr or u->color == 'B') and (v->color == 'B'));
    node *parent = v->parent;
    node *sibling = siblingFinder(v);

    if (u == nullptr)
    {
        if (v == this->root)
        {
            this->root = NULL;
        }
        else
        {
            if (bothBlack)
            {
                DoubleBlackFix(v);
            }
            else if (sibling != NULL)
            {
                sibling->color = 'R';
            }
        }
        if (v->parent->left == v)
        {
            v->parent->left = NULL;
        }
        else
        {
            v->parent->right = NULL;
        }
        // delete v;
        return;
    }
    if (v->left == NULL or v->right == NULL)
    {

        if (v == this->root)
        {
            v->key = u->key;
            v->value = u->value;
            v->left = v->right = NULL;

            delete u;
        }
        else
        {
            if (v->parent->left == v)
            {
                v->parent->left = u;
            }
            else
            {
                v->parent->right = u;
            }
            delete v;
            u->parent = parent;

            if (bothBlack)
            {
                DoubleBlackFix(u);
            }
            else
            {
                u->color = 'B';
            }
        }
        return;
    }

    if (v->left != NULL and v->right != NULL)
    {
        swap(u->key, v->key);
        swap(u->value, v->value);
        eraseutil(u);
    }
}
