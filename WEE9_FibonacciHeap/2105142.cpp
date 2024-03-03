#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace chrono;
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

public:
    vector<node *> valueWithPointer;
    int totalnodes;
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
    void increase_key(int value, int new_key);
    void traverseTree(node *start, vector<node *> &result);
    void cut(node *n, node *p);
    void rootprint()
    {
        vector<node *> v = getList();
        // for(auto a:v){
        //     cout<<a->key<<" "<<" "<<a->left->key<<" "<<a->right->key<<endl;
        // }
    }
    void cascadingCut(node *p);
    void deleteNode(int value);
    node *find_max();
    void printHelper();
    static FibonacciHeap make_heap()
    {
        return FibonacciHeap();
    }

    bool is_empty()
    {
        return totalnodes == 0;
    }
};
node *FibonacciHeap::find_max()
{
    return maxnode;
}
void FibonacciHeap::deleteNode(int value)
{
    node *toDelete = valueWithPointer[value];
    if (toDelete != nullptr)
        // cout << "__deleting " << toDelete->key << " " << toDelete->value << endl;
        if (toDelete != nullptr)
        {
            // cout<<"___1_____"<<maxnode->key<<endl;
            increase_key(value, INT_MAX); // Assuming increase_key takes a node pointer and a new key
            // cout<<"___2_____"<<maxnode->key<<endl;

            // print();
            extract_max(); // This will extract and remove the node with INT_MAX key
            // print();
            // cout<<"___3_____"<<maxnode->key<<endl;
        }
}
void FibonacciHeap::cut(node *n, node *p)
{
    if (n->right == n)
    {
        p->child = nullptr;
    }
    else
    {
        n->left->right = n->right;
        n->right->left = n->left;
        if (p->child == n)
        {
            p->child = n->right;
        }
    }
    p->degree--;

    n->left = maxnode;
    n->right = maxnode->right;
    maxnode->right->left = n;
    maxnode->right = n;
    n->parent = nullptr;
    n->mark = false;

    if (n->key > maxnode->key)
    {
        maxnode = n;
    }
}
void FibonacciHeap::cascadingCut(node *p)
{
    node *pp = p->parent;
    if (pp != nullptr)
    {
        if (p->mark)
        {
            cut(p, pp);
            cascadingCut(pp);
        }
        else
        {
            p->mark = true;
        }
    }
}
void FibonacciHeap::traverseTree(node *start, vector<node *> &result)
{
    if (start == nullptr)
    {
        return;
    }

    node *current = start;
    do
    {
        result.push_back(current);
        if (current->child != nullptr)
        {
            traverseTree(current->child, result);
        }
        current = current->right;
    } while (current != start);
}
vector<node *> FibonacciHeap::getAllNode()
{
    vector<node *> allNodes;
    if (root == nullptr)
    {
        return allNodes;
    }
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
        v.push_back(temp);
        temp = temp->right;
        // cout << "______" << temp->value << " " << temproot->value << endl;
        while (temp != temproot and temp != nullptr)
        {
            // cout << "He he he__________";
            // cout<<temp->key<<" "<<temproot->key<<endl;
            v.push_back(temp);
            temp = temp->right;
            // cout << temp->value << " " << temproot->value << endl;;
        }
    }
    return v;
}
void FibonacciHeap::link(node *y, node *x)
{
    // cout<<"link called for y x "<<y->key<<" "<<x->key<<endl;
    y->left->right = y->right;
    y->right->left = y->left;
    y->parent = x;
    if (x->child != nullptr)
    {
        // cout<<"72 called for "<<"y "<<y->key<<" x "<<x->key<<endl;
        y->right = x->child;
        y->left = x->child->left;
        x->child->left->right = y;
        x->child->left = y;
        // cout<<"87 called for "<<"y "<<y->key<<" y left "<<y->left->key<<" y right "<<y->left->key<<endl;
        // cout<<"___"<<y->child->key<<" "<<y->child->left->key<<endl;
    }
    else
    {
        // cout<<"79 called for "<<"y "<<y->key<<" x "<<x->key<<endl;
        x->child = y;
        y->right = y;
        y->left = y;
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
    valueWithPointer[value] = x;
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
        this->valueWithPointer = std::move(H2.valueWithPointer);
        return *this;
    }

    node *thisRight = this->root->right;
    this->root->right = H2.root;
    H2.root->left->right = thisRight;
    thisRight->left = H2.root->left;
    H2.root->left = this->root;

    if (H2.maxnode->key > this->maxnode->key)
    {
        this->maxnode = H2.maxnode;
    }

    this->totalnodes += H2.totalnodes;
    vector<node *> H2nodes = H2.getAllNode();
    for (auto n : H2nodes)
    {
        if (this->valueWithPointer.size() <= n->value)
        {
            this->valueWithPointer.resize(n->value + 1, nullptr);
        }
        this->valueWithPointer[n->value] = n;
    }
    return *this;
}
node *FibonacciHeap::extract_max()
{
    if (totalnodes == 1)
    {
        node *temp = root;
        root = nullptr;
        maxnode = nullptr;
        totalnodes = 0;
        return temp;
    }
    // cout << "now will Extract " << maxnode->key << endl;
    node *max = maxnode;

    if (max != nullptr)
    {
        if (max->child != nullptr)
        {
            node *currentChild = max->child;
            do
            {
                currentChild->parent = nullptr;
                currentChild = currentChild->right;
            } while (currentChild != max->child);
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
                // cout << "__________called______________" << endl;
                maxLeft->right = max->child;
                max->child->left = maxLeft;
                childLeft->right = maxRight;
                maxRight->left = childLeft;
                root = max->right;
                // cout << "print called in 175" << endl;
                // cout << "Before Consolidate..........2" <<" root "<<root->key<<" max "<<max->key<< endl;
                // print();
                // cout << "perfect in 177" << endl;
            }
        }
        // i think here is a error
        else
        {
            max->right->left = max->left;
            max->left->right = max->right;
            root = maxnode->right;
            // cout << "print called in 183" << endl;
            // cout << "Before Consolidate..........3" << endl;
            // print();
            // cout << "perfect in 185" << endl;
        }
        if (max == max->right)
        {
            root = maxnode->child; //////////////////////////
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
            // rootprint();
            // cout<<"Consolidate calling 2 "<<root->key<<endl;
            consolidate();
        }
        totalnodes--;
    }
    // cout << "result:" << max->key << endl;
    // valueWithPointer[max->value] = nullptr;
    return max;
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
        int parentKey = (n->parent == nullptr) ? -1 : n->parent->key;
        int leftKey = (n->left == nullptr) ? -1 : n->left->key;
        int rightKey = (n->right == nullptr) ? -1 : n->right->key;

        cout << string(level * 2, ' ') << "(" << n->key << ", " << n->value << "_ parent: " << parentKey
             << ", left: " << leftKey << ", right: " << rightKey << ")" << endl;

        if (n->child != nullptr)
        {
            printNode(n->child, level + 1);
        }

        n = n->right;
    } while (n != start);
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
void printtree(node *nodes, int depth = 0)
{
    cout << setw(depth);
    cout << "(" << nodes->key << "," << nodes->value << ")";
    if (nodes->child != NULL)
    {
        cout << "->";
        auto temp = nodes->child;
        bool comma = false;
        do
        {
            if (comma)
            {
                cout << ",";
            }
            cout << "(" << temp->key << "," << temp->value << ")";
            comma = true;
            temp = temp->right;
        } while (temp != nodes->child);

        cout << endl;
        cout << endl;
        temp = nodes->child;
        do
        {
            if (temp->child != NULL)
                printtree(temp, 9);

            temp = temp->right;
        } while (temp != nodes->child);
    }
}
void FibonacciHeap::printHelper()
{
    if (root == NULL)
    {
        cout << "Empty" << endl;
        return;
    }
    int tree_count = 0;
    node *temp = root;
    do
    {
        cout << "Tree " << tree_count << ": ";
        printtree(temp);
        tree_count++;
        temp = temp->right;
        cout << endl;
    } while (temp != root);
    cout << endl;
    cout << "Max Node: " << maxnode->key << " " << maxnode->value << endl;
    cout << "Size: " << totalnodes << endl;
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
void FibonacciHeap::increase_key(int value, int new_key)
{
    node *nodeToIncrease = valueWithPointer[value];
    ///////////////////////////////////Have to implement what if less
    if (new_key < nodeToIncrease->key)
        return;
    nodeToIncrease->key = new_key;
    // cout<<nodeToIncrease->key;
    node *parent = nodeToIncrease->parent;
    if (parent != nullptr and parent->key < new_key)
    {
        cut(nodeToIncrease, parent);
        cascadingCut(parent);
    }
    if (maxnode->key < new_key)
    {
        maxnode = nodeToIncrease;
    }
}

class PriorityQueue
{
private:
public:
    PriorityQueue() = default;
    static FibonacciHeap make_heap()
    {
        return FibonacciHeap::make_heap();
    }

    bool is_empty(FibonacciHeap &heap)
    {
        return heap.is_empty();
    }

    void insert(FibonacciHeap &H, int key, int value)
    {
        H.insert(key, value);
    }
    FibonacciHeap meld(FibonacciHeap &H1, FibonacciHeap &H2)
    {
        return H1.meld(H2);
    }
    // void print(FibonacciHeap &H)
    // {
    //     H.print();
    // }
    void print(FibonacciHeap &heap)
    {
        heap.printHelper();
    }
    node *extract_max(FibonacciHeap &H)
    {

        H.extract_max();
    }
    void increase_key(FibonacciHeap &H, int value, int new_key)
    {
        H.increase_key(value, new_key);
    }
    void deleteNode(FibonacciHeap &H, int value)
    {
        H.deleteNode(value);
    }
    node *find_max(FibonacciHeap &H)
    {
        return H.find_max();
    }

    void test()
    {
        bool passed = true;

        // Insert and find_max
        FibonacciHeap heap1 = make_heap();
        insert(heap1, 10, 100);
        insert(heap1, 20, 200);
        insert(heap1, 30, 300);
        node *maxNode1 = find_max(heap1);
        if (maxNode1->key != 30 or maxNode1->value != 300)
        {
            cout << "Test 1 (Insert and find_max) failed" << endl;
            passed = false;
        }

        // Extract max
        node *extractedNode = extract_max(heap1);
        if (extractedNode->key != 30 or extractedNode->value != 300)
        {
            cout << "Test 2 (Extract max) failed" << endl;
            passed = false;
        }

        // Increase key
        insert(heap1, 40, 400);
        increase_key(heap1, 400, 50);
        node *newMaxNode = find_max(heap1);
        if (newMaxNode->key != 50 or newMaxNode->value != 400)
        {
            cout << "Test 3 (Increase key) failed" << endl;
            passed = false;
        }

        // Delete node
        insert(heap1, 15, 150);
        deleteNode(heap1, 400);
        if (find_max(heap1)->key != 20 or find_max(heap1)->value != 200)
        {
            cout << "Test 4 (Delete node) failed" << endl;
            passed = false;
        }

        //  Meld two heaps
        FibonacciHeap heap2 = make_heap();
        insert(heap2, 30, 300);
        FibonacciHeap meldedHeap = meld(heap1, heap2);
        node *maxNodeMelded = find_max(meldedHeap);
        if (maxNodeMelded->key != 30 or maxNodeMelded->value != 300)
        {
            cout << "Test 5 (Meld heaps) failed" << endl;
            passed = false;
        }

        // Extract until empty

        while (!is_empty(meldedHeap))
        {
            extract_max(meldedHeap);
        }

        if (!is_empty(meldedHeap))
        {
            cout << "Test 6 (Extract until empty) failed" << endl;
            passed = false;
        }

        // Insert after extract_max
        insert(meldedHeap, 25, 250);
        if (find_max(meldedHeap)->key != 25 or find_max(meldedHeap)->value != 250)
        {
            cout << "Test 7 (Insert after extract_max) failed" << endl;
            passed = false;
        }

        // Increase key above current max
        insert(meldedHeap, 10, 100);
        increase_key(meldedHeap, 100, 30);
        if (find_max(meldedHeap)->key != 30 or find_max(meldedHeap)->value != 100)
        {
            cout << "Test 8 (Increase key above current max) failed" << endl;
            passed = false;
        }

        deleteNode(heap1, 500); 

        if (find_max(heap1)->key != 30 || find_max(heap1)->value != 300)
        {
            cout << "Test 9 (Delete non-existent node) failed" << endl;
            passed = false;
        }


        //  Meld two empty heaps
        FibonacciHeap emptyHeap1 = make_heap();
        FibonacciHeap emptyHeap2 = make_heap();
        FibonacciHeap emptyMeldedHeap = meld(emptyHeap1, emptyHeap2);
        if (!is_empty(emptyMeldedHeap))
        {
            cout << "Test 11 (Meld two empty heaps) failed" << endl;
            passed = false;
        }



   

        if (passed)
        {
            cout << "All tests passed!" << endl;
        }
        else
        {
            cout << "Some tests did not pass!" << endl;
        }
    }
};

int main()
{

    PriorityQueue pq;

    FibonacciHeap H1 = pq.make_heap();
    FibonacciHeap H2 = pq.make_heap();
    FibonacciHeap H3 = pq.make_heap();
    // pq.test();
    pq.insert(H1,5,5);
    pq.insert(H1,6,6);
    pq.insert(H1,7,7);
    pq.insert(H1,8,8);
    pq.insert(H1,9,9);
    pq.insert(H1,10,10);
    pq.insert(H1,11,11);
    pq.insert(H1,12,12);
    pq.insert(H1,13,13);
    pq.print(H1);
    pq.extract_max(H1);
    // pq.increase_key(H1,7,70);
    // pq.increase_key(H1,6,60);
    pq.print(H1);
    pq.extract_max(H1);
    pq.extract_max(H1);
    pq.extract_max(H1);

    pq.print(H1);
    // cout << pq.is_empty(H1) << endl;
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
    // // // pq.print(H2);
    // H3 = pq.meld(H1, H2);

    // cout << H1.totalnodes << endl;
    // node *temp = pq.find_max(H3);
    // cout << temp->key << endl;
    // pq.extract_max(H3);
    // pq.insert(H3, 1000, 34);
    // pq.increase_key(H3, 34, 200);
    // pq.deleteNode(H3, 10);
    // pq.print(H3);
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
    // int n = 5, m = 10;
    // for (int i = 1; i <= m; i++)
    // {
    //     pq.insert(H1, i, i * 10);
    // }
    // pq.print(H1);
    // for (int i = 0; i < n; i++)
    // {
    //     // cout << "Extracting.........." << endl;
    //     pq.extract_max(H1);
    //     // cout << "Result.........." << endl;
    //     // pq.print(H1);
    // }
    // pq.print(H1);

    // node* p=pq.find_max(H1);
    // cout<<p->key;
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

// int main() {
//     PriorityQueue pq;

//     // Create an instance of FibonacciHeap
//     FibonacciHeap H1;

//     // Record start time
//     auto start_time = high_resolution_clock::now();

//     // Insert 100,000 nodes into the Fibonacci Heap
//     for (int i = 1; i <= 100000; ++i) {
//         pq.insert(H1, i, i);  // Assuming value = key for simplicity
//     }

//     // Record end time after inserts
//     auto end_inserts_time = high_resolution_clock::now();
//     // cout << "Inserts done" << endl;

//     // Extract nodes
//     for (int i = 1; i <= 100000; ++i) {
//         delete pq.extract_max(H1);
//     }

//     // Record end time after extractions
//     auto end_extractions_time = high_resolution_clock::now();

//     // Calculate and print execution times
//     auto inserts_duration = duration_cast<milliseconds>(end_inserts_time - start_time);
//     auto extractions_duration = duration_cast<milliseconds>(end_extractions_time - end_inserts_time);

//     cout << "Time taken for 100,000 inserts: " << inserts_duration.count() << " milliseconds" << endl;
//     cout << "Time taken for 100,000 extractions: " << extractions_duration.count() << " milliseconds" << endl;

//     return 0;
// }
