#include <bits/stdc++.h>
using namespace std;




class node
{
public:
    int key;
    int value;
    int degree;
    node *parent;
    node *child;
    node *left;
    node *right;
    bool mark;
    node() : degree(0), parent(nullptr), child(nullptr), left(this), right(this), mark(false) {}
    node(int key, int value) : key(key), value(value), degree(0), parent(nullptr), child(nullptr), left(this), right(this), mark(false) {}
};

class FibonacciHeap
{
private:
    node *maxnode;
    node *root;
    int totalnodes;
    vector<node *> valueWithPointer;

public:
    FibonacciHeap() : maxnode(nullptr), root(nullptr), totalnodes(0), valueWithPointer(100000, nullptr)
    {
    }
    void insert(int key, int value);
    FibonacciHeap meld(FibonacciHeap H2);
    void print();
    node *extract_max();
    void consolidate();
    void link(node *y, node *x);
    vector<node *> getList();
    vector<node *> getAllNode();
    void increase_key(int value,int new_key);
    void traverseTree(node *start, vector<node *> &result);
    void cut(node* n, node* p);
    node* find_max();
    void rootprint()
    {
        vector<node *> v = getList();
        // for(auto a:v){
        //     cout<<a->key<<" "<<" "<<a->left->key<<" "<<a->right->key<<endl;
        // }
    }  
    void cascadingCut(node* p);
    void deleteNode(int  value);
};

node* FibonacciHeap::find_max(){
    // return  
}
void FibonacciHeap::deleteNode(int value){
    node* toDelete = valueWithPointer[value];
    if (toDelete != nullptr) {
        // cout<<"___1_____"<<maxnode->key<<endl;
        increase_key(value, INT_MAX); // Assuming increase_key takes a node pointer and a new key
        // cout<<"___2_____"<<maxnode->key<<endl;

        // print(); 
        extract_max(); // This will extract and remove the node with INT_MAX key
        // print();
        // cout<<"___3_____"<<maxnode->key<<endl;
    }
}

void FibonacciHeap::cut(node* n, node* p){
    if(n->right==n){
        p->child=nullptr;
    }
    else{
        n->left->right=n->right;
        n->right->left=n->left;
        if(p->child==n){
            p->child=n->right;
        }
    }
    p->degree--;

    n->left=maxnode;
    n->right=maxnode->right;
    maxnode->right->left=n;
    maxnode->right=n;
    n->parent=nullptr;
    n->mark=false;

    if(n->key>maxnode->key){
        maxnode=n;
    }
}
void FibonacciHeap::cascadingCut(node* p)
{
    node *pp=p->parent;
    if(pp!=nullptr){
        if(p->mark){
            cut(p,pp);
            cascadingCut(pp);
        }
        else {
            p->mark=true;
        }
    }
}
void FibonacciHeap::traverseTree(node *start, vector<node *> &result) {
    if (start == nullptr) {
        return;
    }

    node *current = start;
    do {
        result.push_back(current);
        // If this node has children, traverse the subtree
        if (current->child != nullptr) {
            traverseTree(current->child, result);
        }
        // Move to the next node in the list
        current = current->right;
    } while (current != start); // Ensure we don't loop infinitely
}
vector<node *> FibonacciHeap::getAllNode() {
    vector<node *> allNodes;
    if (root == nullptr) {
        return allNodes; // Return an empty vector if the heap is empty
    }

    // Start with the root list
    traverseTree(root, allNodes);
    return allNodes;
}
vector<node *> FibonacciHeap::getList()
    {
        vector<node *> v;
        if (root != nullptr)
        {
            node *temp = root;
            node *temproot = temp;
            // Add the first node to the vector
            v.push_back(temp);

            // Move to the next node in the root list
            temp = temp->right;

            // Traverse the rest of the nodes until the circle is complete
            while (temp != temproot and temp != nullptr)
            {
                // cout<<temp->key<<" "<<temproot->key<<endl;
                v.push_back(temp);
                temp = temp->right;
            }
        }
        return v;
    }
void FibonacciHeap::link(node *y, node *x)
    {
        // cout<<"link called for y x "<<y->key<<" "<<x->key<<endl;
        // Remove y from its current position
        y->left->right = y->right;
        y->right->left = y->left;

        // Make y a child of x
        y->parent = x;
        if (x->child != nullptr)
        {
            // x already has children, insert y into the child list of x
            // cout<<"72 called for "<<"y "<<y->key<<" x "<<x->key<<endl;
            y->right = x->child;
            y->left = x->child->left;
            x->child->left->right = y; // Make sure the left sibling of x->child points to y
            x->child->left = y;        // Now, x->child's left should point to y
            // cout<<"87 called for "<<"y "<<y->key<<" y left "<<y->left->key<<" y right "<<y->left->key<<endl;
            // cout<<"___"<<y->child->key<<" "<<y->child->left->key<<endl;
        }
        else
        {
            // cout<<"79 called for "<<"y "<<y->key<<" x "<<x->key<<endl;
            // x has no children, y becomes the only child of x
            x->child = y;
            y->right = y; // y's right points to itself, forming a circular list
            y->left = y;  // y's left points to itself, forming a circular list
            // cout<<"84 called for "<<"y "<<y->key<<" y left "<<y->left->key<<" y right "<<y->left->key<<endl;
        }
        // cout<<"89 called for "<<"y "<<y->key<<" y left "<<y->left->key<<" y right "<<y->left->key<<endl;
        // print();

        x->degree++;
        y->mark = false;
    }
void FibonacciHeap::insert(int key, int value)
{
    node *x = new node(key, value);
    if (maxnode == nullptr)
    {
        root = x;
        maxnode = x;

    }
    else
    {
        root->left->right = x;
        x->left = root->left;
        x->right = root;
        root->left = x;
        if (x->key > maxnode->key)
        {
            maxnode = x;
        }
    }
    valueWithPointer[value]=x;
    totalnodes++;
}
FibonacciHeap FibonacciHeap::meld(FibonacciHeap H2)
{
    if (!H2.root)
        return *this;
    if (!this->root)
    {
        this->root = H2.root;
        this->maxnode = H2.maxnode;
        this->totalnodes = H2.totalnodes;
        return *this;
    }
    node *temp = new node();

    temp = this->root;
    temp->left->right = H2.root;
    temp->left = H2.root->left;
    H2.root->left = temp->left;
    H2.root->left->right = temp;

    if (H2.maxnode->key < this->maxnode->key)
    {
        this->maxnode = H2.maxnode;
    }

    this->totalnodes += H2.totalnodes;
    vector<node*>H2nodes=H2.getAllNode();
    for(auto n:H2nodes){
        this->valueWithPointer[n->value]=n;
    }
    return *this;
}
node *FibonacciHeap::extract_max()
{
    if(totalnodes==1){
        // node *temp=root;
        // temp
        // root=nullptr;
        // return temp;
        // Have To Work
    }
    // cout << "now will Extract " << maxnode->key << endl;
    node *max = maxnode; // Save the pointer to the max node

    if (max != nullptr)
    {
        // If max node has children, add them to the root list
        if (max->child != nullptr)
        {
            node *currentChild = max->child;
            do
            {
                currentChild->parent = nullptr; // Set parent to nullptr as it's going to be added to root list
                currentChild = currentChild->right;
            } while (currentChild != max->child);

            // Add children to the root list
            node *maxLeft = max->left;
            node *maxRight = max->right;
            node *childLeft = max->child->left;
            if (maxnode == maxLeft)
            {
                root = maxnode->child;
                // cout << "Before Consolidate..........1" <<" max "<<maxnode->key<< endl;
                // print();
            }
            else
            {
                maxLeft->right = max->child;
                max->child->left = maxLeft;
                childLeft->right = maxRight;
                maxRight->left = childLeft;
                root=max->right;
                // cout << "print called in 175" << endl;
                // cout << "Before Consolidate..........2" <<" root "<<root->key<<" max "<<max->key<< endl;
                // print();
                // cout << "perfect in 177" << endl;
            }
        }
        // Remove max from the root list
        // i think here is a error
        else 
        {
            max->left->right = max->right;
            max->right->left = max->left;
            root = maxnode->right;
            // cout << "print called in 183" << endl;
            // cout << "Before Consolidate..........3" << endl;
            // print();
            // cout << "perfect in 185" << endl;
        }
        if (max == max->right)
        { // max was the only node in the root list
            maxnode = nullptr;
            // cout<<"Consolidate calling 1"<<endl;
            consolidate();
        }
        else
        {
            //  
            // cout << "___" << endl;
            // cout << "Root " << root->key << " " << endl;
            maxnode = max->right;
            rootprint();
            // cout<<"Consolidate calling 2 "<<root->key<<endl;
            consolidate();
        }
        totalnodes--;
    }
    // cout << "result:" << max->key << endl;
    return max; // Return the removed max node
}
void printNode(node *start, int level = 0)
{
    if (start == nullptr)
    {
        return;
    }

    node *n = start;
    do
    {
        // cout<<n->key<<" "<<n->left->key<<" "<<n->right->key<<endl;
        // Get the parent key, left key, and right key, handling nullptrs appropriately
        int parentKey = (n->parent == nullptr) ? -1 : n->parent->key;
        int leftKey = (n->left == nullptr) ? -1 : n->left->key;    // -1 if it's a self loop or nullptr
        int rightKey = (n->right == nullptr) ? -1 : n->right->key; // -1 if it's a self loop or nullptr

        // Print the current node with its parent, left, and right keys
        cout << string(level * 2, ' ') << "(" << n->key << ", "<<n->value<<"_ parent: " << parentKey
             << ", left: " << leftKey << ", right: " << rightKey << ")" << endl;

        // If this node has children, recursively print them
        if (n->child != nullptr)
        {
            printNode(n->child, level + 1);
        }

        // Move to the next node in the circular list
        n = n->right;
    } while (n != start); // Ensure that the entire circular list is traversed
}
void FibonacciHeap::print()
{
    // cout << "Fibonacci Heap: Root:" << root->key << endl;
    if (root != nullptr)
    {
        printNode(root);
    }
    cout << endl;
}
void FibonacciHeap::consolidate()
{
    // cout << "called for root " << root->key << endl;
    int max_rank = (int)log2(this->totalnodes) + 1;
    vector<node *> A(max_rank, nullptr);
    vector<node *> rootList = getList();
    // cout << "called" << endl;
    for (auto r : rootList)
    {
        node *x = r;
        int d = x->degree;
        while (A[d] != nullptr)
        {
            node *y = A[d];
            if (x->key < y->key)
            {
                swap(x, y);
            }
            link(y, x);
            A[d] = nullptr;
            d++;
        }
        A[d] = x;
    }
    maxnode = nullptr;
    root = nullptr;
    for (int i = 0; i < max_rank; i++)
    {
        if (A[i] != nullptr)
        {
            if (root == nullptr)
            {
                root = A[i];
                root->left = root;
                root->right = root;
            }
            else
            {
                // Add the current tree to the root list
                root->left->right = A[i];
                A[i]->left = root->left;
                A[i]->right = root;
                root->left = A[i];
            }
            if (maxnode == nullptr || A[i]->key > maxnode->key)
            {
                maxnode = A[i];
            }
        }
    }
}
void FibonacciHeap::increase_key(int value,int new_key)
{
    node *nodeToIncrease=valueWithPointer[value];  // Now Increase It
    ///////////////////////////////////Have to implement what if less
    nodeToIncrease->key=new_key;
    // cout<<nodeToIncrease->key;
    node *parent=nodeToIncrease->parent;
    if(parent!=nullptr and parent->key<new_key){
        cut(nodeToIncrease,parent);
        cascadingCut(parent);
    }
    if(maxnode->key<new_key){
        maxnode=nodeToIncrease;
    }
}
class PriorityQueue
{
private:
public:
    PriorityQueue() = default;

    void insert(FibonacciHeap &H, int key, int value)
    {
        H.insert(key, value);
    }
    FibonacciHeap meld(FibonacciHeap &H1, FibonacciHeap &H2)
    {
        return H1.meld(H2);
    }
    void print(FibonacciHeap &H)
    {
        H.print();
    }
    node *extract_max(FibonacciHeap &H)
    {

        H.extract_max();
    }
    void increase_key(FibonacciHeap  &H ,int value,int new_key){
        H.increase_key(value,new_key);
    }
    void deleteNoad(FibonacciHeap &H ,int value){
        H.deleteNode(value);
    }
};

int main()
{

    FibonacciHeap H1;
    FibonacciHeap H2;
    PriorityQueue pq;
    
    // pq.insert(H1, 1, 2);
    // pq.insert(H1, 3, 4);
    // pq.insert(H1, 5, 6);
    // pq.insert(H2, 7, 8);
    // pq.insert(H2, 9, 10);
    // pq.insert(H1, 11, 12);
    // pq.insert(H2, 13, 14);
    // pq.insert(H1, 15, 16);
    // pq.insert(H2, 17, 18);
    // pq.insert(H1, 19, 20);
    // pq.print(H1);
    // pq.print(H2);
    // // pq.print(H2);
    // pq.meld(H1, H2);
    // pq.print(H1);
    // pq.increase_key(H1,10,89);
    // pq.print(H1);
    // pq.print(H1);
    // H1.getList();
    // H1.consolidate();
    // pq.extract_max(H1);
    // cout << "res____________" << endl;
    // pq.print(H1);
    // pq.extract_max(H1);
    // cout << "res____________" << endl;
    // pq.print(H1);
    // pq.extract_max(H1);
    // cout << "res____________" << endl;
    // pq.print(H1);

    // vector<node*>v=H1.getAllNode();
    // for(auto a:v){
    //     cout<<a->value<<" "<<a->key<<endl;
    // }
    // pq.print(H1);
    int n = 6 , m = 10;
    for (int i = 1; i <= m; i++)
    {
        pq.insert(H1, i, i*10);
    }
    pq.print(H1);
    for (int i = 0; i < n; i++)
    {
        // cout << "Extracting.........." << endl;
        pq.extract_max(H1);
        // cout << "Result.........." << endl;
        // pq.print(H1);
    }
    pq.print(H1);


    // pq.increase_key(H1,40,9);
    // pq.print(H1);
    // pq.extract_max(H1);
    // pq.deleteNoad(H1,80);
    // pq.print(H1);
    // pq.deleteNoad(H1,60);
    // pq.print(H1);
    // pq.insert(H1,10,0);
    // pq.insert(H1,20,0);
    // pq.insert(H1,30,0);
    // pq.print(H1);
    // cout << "Extracting.........." << endl;
    //     pq.extract_max(H1);
    //     cout << "Result.........." << endl;
    //     pq.print(H1);
    return 0;
}
