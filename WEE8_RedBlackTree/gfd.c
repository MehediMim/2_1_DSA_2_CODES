#include <bits/stdc++.h>
using namespace std;

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

     void moveDown(node *nParent) {
    if (parent != NULL) {
      if (this==parent->left) {
        parent->left = nParent;
      } else {
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

     void left_Rotate(node *x) {
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

   void right_Rotate(node *x) {
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


    void print()
    {
        print_helper(this->root);
        cout << endl;
    }
};

node *RedBlackTree::leftRotate(node *n)
{
    node *x = n->right;
    node *y = x->left;
    x->left = n;
    n->right = y;
    n->parent = x;
    if (y != nullptr)
        y->parent = n;
    return x;
}

node *RedBlackTree::rightRotate(node *n)
{
    node *x = n->left;
    node *y = x->right;
    x->right = n;
    n->left = y;
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
        root = rightRotate(root);
        root->color = 'B';
        root->right->color = 'R';
        RR = false;
    }
    else if (LL)
    {
        root = leftRotate(root);
        root->color = 'B';
        root->left->color = 'R';
        LL = false;
    }
    if (RL)
    {
        root->right = rightRotate(root->right);
        root->right->parent = root;
        root = leftRotate(root);
        root->color = 'B';
        root->left->color = 'R';
        RL = false;
    }
    if (LR)
    {
        root->left = leftRotate(root->left);
        root->left->parent = root;
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
                    LL = true;
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
                    RR = true;
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
    return temp;
}

node *RedBlackTree::successor(node *v)
{
    node *x = v->right;
    while (x != nullptr)
    {
        x = x->left;
    }
    return x;
}

node *RedBlackTree::uFinder(node *v)
{
    if (v->right == NULL and v->left == NULL)
    { // LEAF
        return NULL;
    }
    else if (v->right == NULL)
    { // Left Child
        return v->left;
    }
    else if (v->left == NULL)
    { // Right Child
        return v->right;
    }
    else
        return successor(v);
}

node *RedBlackTree::siblingFinder(node *v)
{
    if (v->parent == NULL)
        return NULL;
    if (v->parent->left == v)
        return v->parent->right;

    return v->parent->left;
}

void RedBlackTree::DoubleBlackFix(node *doubleBlackNode) {
    if (doubleBlackNode == root) {
        // Case 1: The double black node is root. No further action is necessary.
        return;
    }

    node *sibling = siblingFinder(doubleBlackNode);
    node *parent = doubleBlackNode->parent;

    if (!sibling) {
        // Case 2: No sibling, double black is pushed up the tree.
        DoubleBlackFix(parent);
    } else {
        if (sibling->color == 'R') {
            // Case 3: Sibling is red.
            parent->color = 'R';
            sibling->color = 'B';
            if (sibling == parent->left) {
                // Left case
                rightRotate(parent);
            } else {
                // Right case
                leftRotate(parent);
            }
            DoubleBlackFix(doubleBlackNode); // Continue fixing since structure changed.
        } else {
            // Sibling is black.
            if ((sibling->left && sibling->left->color == 'R') ||
                (sibling->right && sibling->right->color == 'R')) {
                // Case 4: Sibling has at least one red child.
                if (sibling->left && sibling->left->color == 'R') {
                    if (sibling == parent->left) {
                        // Case 4.1: Left Left
                        sibling->left->color = sibling->color;
                        sibling->color = parent->color;
                        rightRotate(parent);
                    } else {
                        // Case 4.2: Right Left
                        sibling->left->color = parent->color;
                        rightRotate(sibling);
                        leftRotate(parent);
                    }
                } else {
                    if (sibling == parent->left) {
                        // Case 4.3: Left Right
                        sibling->right->color = parent->color;
                        leftRotate(sibling);
                        rightRotate(parent);
                    } else {
                        // Case 4.4: Right Right
                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        leftRotate(parent);
                    }
                }
                parent->color = 'B';
            } else {
                // Case 5: Sibling is black and both children of the sibling are black.
                sibling->color = 'R';
                if (parent->color == 'B') {
                    DoubleBlackFix(parent); // Recurse up the tree.
                } else {
                    parent->color = 'B';
                }
            }
        }
    }
    // Ensure the root is black.
    root->color = 'B';
}


void RedBlackTree::eraseutil(node *v) {
    node *u = uFinder(v);  // node to replace 'v'
    bool uvBlack = ((u == nullptr || u->color == 'B') && (v->color == 'B'));
    node *parent = v->parent;

    if (u == nullptr) {
        // 'v' is a leaf
        if (v == root) {
            root = nullptr;
        } else {
            if (uvBlack) {
                // 'v' is black, u is nullptr (also considered black)
                // v is a leaf, fix double black at v
                DoubleBlackFix(v);
            } else {
                // 'v' is red or u is red (u can't be red as u is nullptr)
                if (siblingFinder(v) != nullptr) {
                    siblingFinder(v)->color = 'R';
                }
            }
            // Delete 'v' from the tree
            if (v == parent->left) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        }
        delete v;
        return;
    }

    if (v->left == nullptr || v->right == nullptr) {
        // 'v' has one child
        if (v == root) {
            // 'v' is root, assign the value of u to v, and delete u
            v->key = u->key;
            v->value = u->value;
            v->left = v->right = nullptr;
            delete u;
        } else {
            // Detach 'v' from tree and move 'u' up
            if (v == parent->left) {
                parent->left = u;
            } else {
                parent->right = u;
            }
            delete v;
            u->parent = parent;
            if (uvBlack) {
                // 'u' and 'v' both black, fix double black at 'u'
                DoubleBlackFix(u);
            } else {
                // 'u' or 'v' is red, color 'u' black
                u->color = 'B';
            }
        }
        return;
    }

    // 'v' has two children, swap values with successor and recurse
    swap(u->key, v->key);
    swap(u->value, v->value);
    eraseutil(u);
}
