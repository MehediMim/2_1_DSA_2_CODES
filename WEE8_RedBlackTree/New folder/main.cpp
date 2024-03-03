#include <iostream>
#include "color.hpp"
#include "map.cpp"

using namespace std;

int main()
{
    RedBlackTree tree;
    freopen("input.txt", "r", stdin);
    // freopen("output.txt","w",stdout);

    string c;
    while (cin >> c && !cin.eof())
    {
        cout<<"___"<<c;
        if (c == "I")
        {
            int key;
            string value;
            cin >> key >> value;
            cout<<"__"<<key<<endl;
            tree.insert(key, value);
            tree.print();
        }
        else if (c == "F")
        {
            int key;
            cin >> key;
            node* node = tree.find(key);
            cout<<"__"<<key<<endl;
            if (node != nullptr)
            {
                cout << key << " "<< "found" << endl;
            }
            else
            {
                cout << key << " " << "Not found" << endl;
            }
        }
        else if (c == "E")
        {
            int key;
            cin >> key;
            auto temp = tree.erase(key);
            cout<<"__"<<key<<endl;
            if (temp == NULL)
            {
                cout << key << " " << "Not found" << endl;
            }
            else
            {
                tree.print();
            }
        }
        // else if (c == "S")
        // {
        //     cout << tree.size_tree() << endl;
        // }
        // else if (c == "Itr")
        // {
        //     tree.iterate();
        // }
        // else if (c == "Clr")
        // {
        //     bool clr = tree.clear();
        //     if (clr)
        //     {
        //         cout << dye::green_on_black("Successful") << endl;
        //     }
        //     else
        //     {
        //         cout << dye::red_on_black("Unsuccessful") << endl;
        //     }
        // }
        // else if (c == "Em")
        // {
        //     bool em = tree.isempty();
        //     if (em)
        //     {
        //         cout << "Yes" << endl;
        //     }
        //     else
        //     {
        //         cout << "No" << endl;
        //     }
        // }
        // else
        // {
        //     cout << dye::red_on_black("Invalid Input") << endl;
        // }
    }

    return 0;
}
