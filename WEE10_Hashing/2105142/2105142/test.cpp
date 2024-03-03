#include <bits/stdc++.h>
#include "generator.cpp"
#include "OpenAdressingHashTable.cpp"

using namespace std;

class twolayerd : HashTable
{
public:
    vector<OpenAdressingHashTable *> htable;
    vector<bool> wasoccupied;

    twolayerd(int size) : HashTable(size)
    {
        htable.resize(size, nullptr);
        wasoccupied.resize(size, false);
    }

    ll auxHash(string key)
    {
        int hashValue = 0;
        ll R = prime_less_than_size(this->size);

        for (int i = 0; i < key.size(); i++)
        {
            hashValue += (int)key[i];
        }
        hashValue = R - (hashValue % R);

        return (ll)hashValue;
    }

    ll customProbing(int h, string key, int i)
    {
        ll hashValue = 0;
        ll C1 = 5, C2 = 3;
        hashValue = ((h == 1 ? hash1(key) : hash2(key)) + C1 * i * auxHash(key) + C2 * i * i) % size;
        return hashValue;
    }

    void insert(string key1, string key2, int value)
    {
        int index = customProbing(1, key1, 0);

        if (htable[index] == nullptr)
        {
            htable[index] = new OpenAdressingHashTable(this->size, ResulationMethod::CUSTOM_PROBING);
            htable[index]->insert(1, key2, value);
        }

        else
        {
            htable[index]->insert(1, key2, value);
        }
    }

    node *search(string key1, string key2)
    {
        int i = 0;
        ll index = customProbing(1, key1, i);
        cout << "index :" << index << endl;

        if (htable[index] == nullptr)
        {
            return nullptr;
        }

        return htable[index]->find(1, key2);
    }

    OpenAdressingHashTable *search(string key1)
    {
        int i = 0;
        ll index = customProbing(1, key1, i);
        cout << "index :" << index << endl;

        if (htable[index] == nullptr)
        {
            return nullptr;
        }

        return htable[index];
    }

    void print()
    {
        cout << "hello world" << endl;
    }
};

int main()
{

    twolayerd table(100);

    table.insert("bd", "dhaka", 500);
    table.insert("bd", "ctg", 300);
    table.insert("uk", "london", 800);

    auto x = table.search("bd", "ctg");
    if (x == nullptr)
        cout << "empty";
    else
        cout << x->value;

    auto t = table.search("bd");

    for(auto n : t->table){
        if(n!=nullptr)
        {
            cout<<n->key<<" "<<n->value<<endl;
        }
    }
}