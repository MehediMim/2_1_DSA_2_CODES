#include <bits/stdc++.h>
using namespace std;
#define llint long long int

bool isPrime(llint n)
{
    if (n <= 1)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    for (int i = 3; i <= sqrt(n); i += 2)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}
llint findNextPrime(int n)
{
    while (!isPrime(n))
        n++;
    return n;
}
llint findPreviousPrime(int n)
{
    while (!isPrime(n))
        n--;
    if (n < 2)
        return 2;
    return n;
}

class node
{
public:
    string key;
    string name;
    string phonenumber;
    
    int value;

    node(string key, string name,string phonenumber)
    {
        this->key = key;
        this->name=name;
        this->phonenumber=phonenumber;
    }
};

class hashTable
{
private:
    vector<list<node *>> table;
    vector<bool> trace;
    llint table_size;
    llint collision;
    llint probe;
    llint _N;
    llint insertions;
    llint deletions;
    llint C;
    llint initialSize;
    llint totalNode;

public:
    hashTable()
    {
        this->_N = 0;
        this->C = 0;
        this->table_size = findNextPrime(_N);
        table.resize(this->table_size);
        trace.resize(this->table_size, false);
        collision = 0;
        probe = 0;
        insertions = 0;
        deletions = 0;
        totalNode = 0;
    }
    hashTable(llint _N, llint C)
    {
        this->_N = _N;
        this->C = C;
        this->table_size = findNextPrime(_N);
        table.resize(this->table_size);
        trace.resize(this->table_size, false);
        collision = 0;
        probe = 0;
        insertions = 0;
        deletions = 0;
        totalNode = 0;
    }
    void printTable()
    {
        for (llint i = 0; i < table_size; ++i)
        {
            cout << "Slot " << i << ": ";
            if (table[i].empty())
            {
                cout << "Empty" << endl;
            }
            else
            {
                for (auto nodePtr : table[i])
                {
                    cout << "{" << nodePtr->key << ", " << nodePtr->value << "} ";
                }
                cout << endl;
            }
        }
    }

    llint hash1(string s)
    {
        llint hash = 0;
        for (size_t i = 0; i < s.size(); i++)
        {
            hash += s[i];
            hash += (hash << 10);
            hash ^= (hash >> 6);
        }
        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);
        return abs(hash);
    }
    llint hash2(string s)
    {
        unsigned long hash = 0;
        for (unsigned char c : s)
        {
            hash = c + (hash << 6) + (hash << 16) - hash;
        }
        return abs(hash);
    }
    llint hash3(string s)
    {
        {
            unsigned long long hash = 14695981039346656037ULL;
            for (unsigned char c : s)
            {
                hash ^= c;
                hash *= 1099511628211ULL;
            }
            return abs(hash);
        }
    }

    llint auxHash(string s)
    {
        llint index = 0;
        llint r = findPreviousPrime(table_size);
        for (int i = 0; i < s.size(); i++)
            index += (int)s[i];
        return index;
    }
    llint doubleHash(int hashDetector, string key, int i)
    {
        llint temp = (hashDetector == 1 ? hash1(key) : hash2(key)) % table_size;
        llint hash_value = 0;
        hash_value = (temp + i * auxHash(key)) % table_size;
        return labs(hash_value);
    }
    llint customProbing(int hashDetector, string key, int i)
    {
        llint temp = (hashDetector == 1 ? hash1(key) : hash2(key)) % table_size;
        llint hash_value = 0;
        int C1 = 107, C2 = 1007;
        hash_value = (temp + C1 * i * auxHash(key) + C2 * i * i) % table_size;
        return labs(hash_value);
    }
    void resetProb()
    {
        probe = 0;
    }
    llint getCollitionCounter()
    {
        return collision;
    }
    llint getProbeCounter()
    {
        return probe;
    }
    llint getMaxChainLength()
    {
        llint maxChainLength = 0;
        for (auto &chain : table)
        {
            if (chain.size() > maxChainLength)
            {
                maxChainLength = chain.size();
            }
        }
        return maxChainLength;
    }
    /////////////////////////CHAIN HASH/////////////////////////////////////////////////////////////////
    void rehash_chain(int hashDetector, bool increase)
    {
        llint old_size = this->table_size;
        llint newSize = increase ? findNextPrime(table_size * 2) : findNextPrime(table_size / 2);
        if (newSize < initialSize)
        { // Do not resize below initial size
            newSize = initialSize;
        }
        collision = 0;
        probe = 0;
        insertions = 0;
        deletions = 0;
        _N = newSize;
        table_size = newSize;

        vector<list<node *>> old_table(this->table_size);
        vector<bool> old_trace(this->table_size, false);
        old_table = this->table;
        old_trace = this->trace;
        this->table.resize(this->table_size);
        this->trace.resize(this->table_size, false);

        for (llint i = 0; i < old_size; i++)
        {
            for (auto a : old_table[i])
            {
                llint index = (hashDetector == 1 ? hash1(a->key) : hash2(a->key)) % table_size;
                this->table[index].push_back(a);
                this->trace[index] = true;
            }
        }
    }
    node *search_chain(int hashDetector, string key)
    {
        llint index = (hashDetector == 1 ? hash1(key) : hash2(key)) % table_size;
        for (auto v : table[index])
        {
            probe++;
            if (v->key == key)
            {
                return v;
            }
        }
        return nullptr;
    }
    void insert_chain(int hashDetector, string key, string NID,string phonenumber)
    {
        llint index = (hashDetector == 1 ? hash1(key) : hash2(key)) % table_size;
        if (table[index].size() > 0)
            collision++;
        table[index].push_back(new node(key, NID,phonenumber));
        insertions++;
        if (insertions % 100 == 0)
        {
            if (getMaxChainLength() > C)
            {
                rehash_chain(hashDetector, true);
            }
        }
    }
    void delete_chain(int hashDetector, string key)
    {
        if (deletions % 100 == 0)
        {
            if (getMaxChainLength() < 0.8 * C)
            {
                rehash_chain(hashDetector, false);
            }
        }
        if (search_chain(hashDetector, key) != nullptr)
        {
            llint index = (hashDetector == 1 ? hash1(key) : hash2(key)) % table_size;
            for (auto it = table[index].begin(); it != table[index].end();)
            {
                if ((*it)->key == key)
                {
                    // delete *it;
                    it = table[index].erase(it);
                    deletions++;
                    return;
                }
                it++;
            }
        }
        // NULL
    }
    //////////////////////////CUSTOM PROBING///////////////////////////////////////////////////////////////
    // node *search_custom(int hashDetector, string key)
    // {
    //     int i = 0;
    //     llint index = (hashDetector == 1 ? hash1(key) : hash2(key)) % table_size;
    //     // llint index = customProbing(hashDetector, key, i);
    //     // probe++;
    //     // cout<<index<<endl;
    //     if (table[index].empty() and trace[index] == false)
    //     {
    //         return nullptr;
    //     }
    //     else if (table[index].front()->key == key)
    //     {
    //         return table[index].front();
    //     }
    //     else
    //     {
    //         probe++;
    //         while (1)
    //         {
    //             index = customProbing(hashDetector, key, i);
    //             if (table[index].empty() and trace[index] == false)
    //             {
    //                 return nullptr;
    //             }
    //             else if (table[index].front()->key == key)
    //             {
    //                 return table[index].front();
    //             }
    //             else
    //             {
    //                 i++;
    //                 probe++;
    //             }
    //         }
    //     }
    // }

    // void insert_custom(int hashDetector, string key, int value)
    // {
    //     if (totalNode * 2 >= _N)
    //     {
    //         // cout<<"Returning "<<value<<" "<<totalNode<<" inserted "<<_N<<endl;;
    //         return;
    //     }
    //     int i = 0;
    //     llint index = (hashDetector == 1 ? hash1(key) : hash2(key)) % table_size;
    //     if (table[index].empty())
    //     {
    //         table[index].push_back(new node(key, value));
    //         trace[index] = true;
    //         totalNode++;
    //         return;
    //     }
    //     else
    //     {
    //         collision++;
    //         while (1)
    //         {
    //             index = customProbing(hashDetector, key, i);
    //             if (!table[index].empty())
    //             {
    //                 // collision++;
    //                 i++;
    //             }
    //             else
    //             {
    //                 table[index].push_back(new node(key, value));
    //                 trace[index] = true;
    //                 totalNode++;
    //                 return;
    //             }
    //         }
    //     }
    // }
    // void delete_custom(int hashDetector, string key)
    // {
    //     int i = 0;
    //     llint index = (hashDetector == 1 ? hash1(key) : hash2(key)) % table_size;
    //     if (table[index].empty() and trace[index] == false)
    //         return;
    //     else if (table[index].front()->key == key)
    //     {
    //         // delete table[index].front();         //Potential
    //         table[index].clear();
    //         return;
    //     }
    //     else
    //     {
    //         while (1)
    //         {
    //             index = customProbing(hashDetector, key, i);
    //             if (table[index].empty() and trace[index] == false)
    //             {
    //                 return;
    //             }
    //             else if (table[index].front()->key == key)
    //             {
    //                 // delete table[index].front();
    //                 table[index].clear();
    //                 return;
    //             }
    //             else
    //             {
    //                 i++;
    //             }
    //         }
    //     }
    // }
    // //////////////////////////DOUBLE HASHING///////////////////////////////////////////////////////////////
    // node *search_double(int hashDetector, string key)
    // {
    //     int i = 0;
    //     llint index = (hashDetector == 1 ? hash1(key) : hash2(key)) % table_size;
    //     if (table[index].empty() and trace[index] == false)
    //     {
    //         return nullptr;
    //     }
    //     else if (table[index].front()->key == key)
    //     {
    //         return table[index].front();
    //     }
    //     else
    //     {
    //         probe++;
    //         while (1)
    //         {
    //             index = doubleHash(hashDetector, key, i);
    //             if (table[index].empty() and trace[index] == false)
    //             {
    //                 return nullptr;
    //             }
    //             else if (table[index].front()->key == key)
    //             {
    //                 return table[index].front();
    //             }
    //             else
    //             {
    //                 i++;
    //                 probe++;
    //             }
    //         }
    //     }
    // }

    // void insert_double(int hashDetector, string key, int value)
    // {
    //     // cout<<"inserted "<<totalNode<<endl;
    //     if (totalNode * 2 >= _N)
    //         return;
    //     int i = 0;
    //     llint index = (hashDetector == 1 ? hash1(key) : hash2(key)) % table_size;
    //     if (table[index].empty())
    //     {
    //         table[index].push_back(new node(key, value));
    //         trace[index] = true;
    //         // cout<<".."<<endl;
    //         totalNode++;
    //         return;
    //     }
    //     else
    //     {
    //         collision++;
    //         while (1)
    //         {
    //             index = doubleHash(hashDetector, key, i);
    //             if (!table[index].empty())
    //             {
    //                 // collision++;
    //                 // return;
    //                 i++;
    //             }
    //             else
    //             {
    //                 table[index].push_back(new node(key, value));
    //                 trace[index] = true;
    //                 totalNode++;
    //                 return;
    //             }
    //             // i++;
    //         }
    //     }
    // }
    // void delete_double(int hashDetector, string key)
    // {
    //     int i = 0;
    //     llint index = (hashDetector == 1 ? hash1(key) : hash2(key)) % table_size;
    //     if (table[index].empty() and trace[index] == false)
    //         return;
    //     else if (table[index].front()->key == key)
    //     {
    //         // delete table[index].front();
    //         table[index].clear();
    //         return;
    //     }
    //     else
    //     {
    //         while (1)
    //         {
    //             index = doubleHash(hashDetector, key, i);
    //             if (table[index].empty() and trace[index] == false)
    //             {
    //                 return;
    //             }
    //             else if (table[index].front()->key == key)
    //             {
    //                 // delete table[index].front();
    //                 table[index].clear();
    //                 return;
    //             }
    //             else
    //             {
    //                 i++;
    //             }
    //         }
    //     }
    // }
};


