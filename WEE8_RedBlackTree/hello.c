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
            cout << "=> ";
            cout << dye::red_on_black(root->value) << " " << endl;
            ;
        }
        else
        {
            cout << root->key << "=> " << root->value << " " << endl;
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
        // new parent will be node's right child
        node *nParent = x->right;

        // update root if current node is root
        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        // connect x with new parent's left element
        x->right = nParent->left;
        // connect new parent's left element with node
        // if it is not null
        if (nParent->left != NULL)
            nParent->left->parent = x;

        // connect new parent with x
        nParent->left = x;
    }

    void right_Rotate(node *x)
    {
        // new parent will be node's left child
        node *nParent = x->left;

        // update root if current node is root
        if (x == root)
            root = nParent;

        x->moveDown(nParent);

        // connect x with new parent's right element
        x->left = nParent->right;
        // connect new parent's right element with node
        // if it is not null
        if (nParent->right != NULL)
            nParent->right->parent = x;

        // connect new parent with x
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
        if (root->color == 'R' and root->left->color == 'R')
            RRConflict = true;
    }
    else if (key > root->key)
    {
        root->right = insertutil(root->right, key, value);
        root->right->parent = root;
        if (root->color == 'R' and root->right->color == 'R')
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
        // root->right->parent = root;
        root = leftRotate(root);
        root->color = 'B';
        root->left->color = 'R';
        RL = false;
    }
    if (LR)
    {
        root->left = leftRotate(root->left);
        // root->left->parent = root;
        root = rightRotate(root);
        root->color = 'B';
        root->right->color = 'R';
        LR = false;
    }
    if (RRConflict)
    {
        if (root->parent->right == root)
        { // SO THEIR WILL BE A L ROTAION FOR SURE
            if (root->parent->left and root->parent->left->color == 'R')
            { // UNCLE PARENT RED COLOR , SO RECOLOR
                root->color = 'B';
                root->parent->left->color = 'B'; ////
                if (root->parent != this->root)
                    root->parent->color = 'R';
            }
            else
            { // UNCLE PARENT NOT RED , SO ROTATE
                if (root->right and root->right->color == 'R')
                { // ROOT'S RIGHT CHILD IS RED
                    RR = true;
                }
                else if (root->left and root->left->color == 'R')
                { // ROOT'S LEFT CHILD IS RED
                    RL = true;
                }
            }
        }
        else if (root->parent->left == root)
        { // SO THEIR WILL BE A R ROTAION FOR SURE
            if (root->parent->right and root->parent->right->color == 'R')
            { // UNCLE PARENT RED COLOR , SO RECOLOR
                root->color = 'B';
                root->parent->right->color = 'B'; ////
                if (root->parent != this->root)
                    root->parent->color = 'R';
            }
            else
            { // UNCLE PARENT NOT RED , SO ROTATE
                if (root->right and root->right->color == 'R')
                { // ROOT'S RIGHT CHILD IS RED
                    LR = true;
                }
                else if (root->left and root->left->color == 'R')
                { // ROOT'S LEFT CHILD IS RED
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
    // when node have 2 children
    if (x->left != NULL and x->right != NULL)
        return successor(x->right);

    // when leaf
    if (x->left == NULL and x->right == NULL)
        return NULL;

    // when single child
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
        // Case 1: The double black node is root, simply make it black and return.
        // doubleBlackNode->color = 'B';
        return;
    }

    node *sibling = siblingFinder(doubleBlackNode);
    node *parent = doubleBlackNode->parent;

    if (sibling == nullptr)
    {
        // Case 2: No sibling, double black pushed up
        DoubleBlackFix(parent);
    }
    else
    {
        if (sibling->color == 'R')
        {
            // Case 3: Sibling is red
            parent->color = 'R';
            sibling->color = 'B';
            if (sibling == sibling->parent->left)
            {
                // left case
                left_Rotate(parent); ////
                // parent = leftRotate(parent);
            }
            else
            {
                // right case
                right_Rotate(parent); ///
                // parent = rightRotate(parent);
            }
            if (parent->parent != nullptr)
            {
                if (parent->parent->left == doubleBlackNode->parent)
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
            DoubleBlackFix(doubleBlackNode); // Continue fixing since structure changed
        }
        else
        {
            // if (sibling->left->color == 'R' or sibling->right->color == 'R')
            {
                if (sibling->left != nullptr && sibling->left->color == 'R')
                {
                    // Case 4: At least 1 red child of sibling
                    if (sibling->parent->left == sibling)
                    {
                        sibling->left->color = sibling->color;
                        sibling->color = parent->color;
                        parent->color = 'B';
                        left_Rotate(parent);
                    }
                    else
                    {
                        sibling->left->color = parent->color;
                        parent->color = 'B';
                        right_Rotate(sibling);
                        left_Rotate(parent);
                    }
                    // parent->color = 'B';
                }
                else if (sibling->right != NULL and sibling->right->color == 'R')
                {
                    if (sibling == sibling->parent->left)
                    {
                        // Case 4.3: Left Right
                        sibling->right->color = parent->color;
                        parent->color = 'B';
                        left_Rotate(sibling);
                        right_Rotate(parent);
                    }

                    else
                    {
                        // Case 4.4: Right Right
                        sibling->right->color = parent->color;
                        sibling->color = parent->color;
                        parent->color = 'B';
                        right_Rotate(parent);
                    }
                }

                else
                {
                    // Case 5: Sibling black and both children of sibling are black.
                    sibling->color = 'R';
                    if (parent->color == 'B')
                    {
                        DoubleBlackFix(parent); // Recurse up the tree
                    }
                    else
                    {
                        parent->color = 'B';
                    }
                }
            }
        }
    }
}

// if (doubleBlackNode == root)
// {
//     doubleBlackNode->color = 'B';
// }
// return;

void RedBlackTree::eraseutil(node *v)
{
    // node *u = uFinder(v);
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
        // node *child = (v->left != nullptr) ? v->left : v->right;

        if (v == this->root)
        {
            // v->key = (child != nullptr) ? child->key : -1;     // Set to -1 or some sentinel value if child is also nullptr
            // v->value = (child != nullptr) ? child->value : ""; // Set to "" or some sentinel value if child is also nullptr
            // v->left = v->right = nullptr;
            // if (child != nullptr)
            // {
            //     delete child;
            // }
            v->key = u->key;
            v->value = u->value;
            v->left = v->right = NULL;
            // cout<<"root"<<endl;
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
            // if (child != nullptr)
            // {
            //     child->parent = parent;
            // }
            // delete v;

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

